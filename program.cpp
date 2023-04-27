/*
Se implementa el razonamiento bayesiano adicionando la técnica de "resetting" aleatorio para algunos agentes...
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string.h>
#include <string>

struct Individuo{
    int id;//identificador del individuo...
    std::vector<int> solucion;//vector solucion...
    std::vector< std::vector<double> > certeza;//vector de probabilidades de certeza de cada posicion de la solucion...
    double fitness1;//calidad real de la solucion...
    double fitness2;//creencia de la calidad de la solucion...
    int tipo;//tipo de individuo (0. individuo realista -> fitness1=fitness2,
    //1. individuo creyente -> fitness1!=fitness2)
    //accion: 0. mantener solucion, 1. cambiar solucion de forma aleatoria,
    //2. generar solución de los vecinos, 3. copiar solucion de un vecino
    //(el que tiene más influencia)
    std::vector<double> accion;//vector de probabilidades de cada accion
};

struct Poblacion{
    std::vector<Individuo> poblacion;
    double p;//porcentaje de individuos creyentes...
};

std::vector< std::vector<double> > a;
std::vector< std::vector<double> > b;
int tAccion0=0,tAccion1=0,tAccion2=0,tAccion3=0,tAccion4=0,tAccion5=0;
std::vector<int> solucion_reset;

double fitness(std::vector<int> p){
    double sum1=0,sum2=0;
    for(int i=0;i<a.size();i++){
	sum2=0;
	for(int j=0;j<a.size();j++){
	    sum2+=a[i][j]*b[p[i]][p[j]];
	}
	sum1+=sum2;
    }
//    printf("suma:%d\n",sum1);
    return sum1;
}

Individuo InicializaIndividuo(int id, int instancias, int n_Acciones){
    Individuo ind;
    int val, sval, indice1, indice2;
    std::vector<double> vect;

    //crea vector ordenado de indices...
    ind.id=id;
    for(int i=0;i<instancias;i++){
	ind.solucion.push_back(i);
	//Inicializa vector de certezas de forma aleatoria
	//vect.push_back(((rand()%100)+1)/100.0);
	//Incializa vector de certezas de forma uniforme
	vect.clear();
	for(int j=0;j<instancias;j++){
	    vect.push_back(1.0/instancias);
	}
	ind.certeza.push_back(vect);
    }
    //combina los indices de forma aleatoria...
    for(int i=0;i<4;i++){
	indice1=rand()%ind.solucion.size();
	indice2=rand()%ind.solucion.size();
	val=ind.solucion[indice1];
	ind.solucion[indice1]=ind.solucion[indice2];
	ind.solucion[indice2]=val;
    }

    //inicializa el vector de probabilidad de las acciones...
    sval=0;
    val=1.0;//Probabilidad uniforme...
    for(int i=0;i<n_Acciones;i++){
//	val=rand()%100;
	ind.accion.push_back(val);
	sval+=val;
    }
/*
  //Normalizacion...
    for(int i=0;i<ind.accion.size();i++){
	ind.accion[i]=(double)ind.accion[i]/sval;
    }
*/
    //inicializa las variables complementarias...
    ind.tipo=0;
    ind.fitness1=fitness(ind.solucion);
    ind.fitness2=-1;
    return ind;
}

std::vector<Individuo> GeneraPoblacion(int nIndividuos, double p, int instancias, std::vector< std::vector<double> > red){
    std::vector<Individuo> poblacion;
    int indice, numero, n_Acciones;
    //Inicializa los individuos de la poblacion...
    for(int i=0;i<nIndividuos;i++){
	n_Acciones=1;
	for(int j=0;j<red.size();j++){
	    if(red[i][j]>0)
		n_Acciones=2;
	}
	poblacion.push_back(InicializaIndividuo(i,instancias,n_Acciones));
    }
    //Configurar el porcentaje de creyentes...
    numero=0;
    while(numero<poblacion.size()*p){
	indice=rand()%poblacion.size();
	if(poblacion[indice].tipo==0){
	    poblacion[indice].tipo=1;
	    numero++;
	}
    }
    return poblacion;
}

std::vector< std::vector<double> > InicializaRed(int numeroIndividuos){
    std::vector< std::vector<double> > red;
    std::vector<double> fila;
    red.clear();
    for(int i=0;i<numeroIndividuos;i++){
	fila.clear();
	for(int j=0;j<numeroIndividuos;j++){
	    fila.push_back(0);
	}
	red.push_back(fila);
    }
    return red;
}

int gradoNodo(std::vector< std::vector<double> > red, int id){
    int grado=0;
    int nIndividuos=red.size();
    for(int i=0;i<nIndividuos;i++){
	if(red[i][id]!=0){
	    grado++;
	}
    }
    return grado;
}

//Genera red Free Scale (Barabasi-Albert)
std::vector< std::vector<double> > GeneraFSRed(std::vector< std::vector<double> > red){
    int nIndividuos=red.size();
    //Inicializa los tres primeros nodos...
    int nd;
    for(int i=0;i<3;i++){
	nd=rand()%3;
	while(nd==i) nd=rand()%3;
	red[nd][i]=((rand()%100)+1)/100.0;
    }
    int suma=0;
    double p_i;
    for(int n=3;n<nIndividuos;n++){
	nd=rand()%n;
	while(nd==n) nd=rand()%n;
	red[nd][n]=((rand()%100)+1)/100.0;//el nuevo nodo entra atrayendo un enlace...
	suma=0;
	for(int j=0;j<nIndividuos;j++){
	    suma+=gradoNodo(red,j);
	}
	for(int i=0;i<nIndividuos;i++){
	    if(n!=i){
		p_i=(double)gradoNodo(red,i)/suma;
		double prob=(rand()%100)/100.0;
//		printf("%f %f %d %d\n",prob,p_i,n,i);
		if(prob<p_i){
		    red[n][i]=((rand()%100)+1)/100.0;
		}
	    }
	}
    }
    return red;
}

void ImprimeRed(std::vector< std::vector<double> > red){
    
    int cont_entra=0;
    int cont_sale=0;
    int nIndividuos=red.size();
    
    for(int i=0;i<nIndividuos;i++){	
	cont_entra=0;
	cont_sale=0;
	for(int j=0;j<nIndividuos;j++){
	    //printf("%f ",red[i][j]);
	    if(red[j][i]!=0)
		cont_entra++;
	    if(red[i][j]!=0)
		cont_sale++;
	}
	//printf("\n");
	printf("%d %d %d\n",i,cont_entra,cont_sale);
    }
}

int esta(int elemento, std::vector<int> velem){
    int vesta=0, i=0;
    while(vesta==0 && i<velem.size()){
	if(velem[i]==elemento){
	    vesta=1;
	}
	i++;
    }
    return vesta;
}

std::vector<int> completa(std::vector<int> velem){
    int elemento=0;
    for(int i=0;i<velem.size();i++){
	if(velem[i]==-1){
	    elemento=0;
	    while(esta(elemento,velem))
		elemento=rand()%velem.size();
	    velem[i]=elemento;
	}
    }
    return velem;
}

/*
std::vector<int> invertir(std::vector<int> lvec, int numero){
    int indice1=0,indice2=0,val=0;
    for(int j=0;j<numero;j++){
	indice1=j;
	indice2=lvec.size()-j-1;
	val=lvec[indice1];
	lvec[indice1]=lvec[indice2];
	lvec[indice2]=val;
    }
    return lvec;
}
*/

std::vector<int> combina(std::vector<int> lvec, int numero){
    int indice1=0,indice2=0,val=0;
    for(int j=0;j<numero;j++){
	indice1=rand()%lvec.size();
	indice2=rand()%lvec.size();
	val=lvec[indice1];
	lvec[indice1]=lvec[indice2];
	lvec[indice2]=val;
    }
    return lvec;
}

std::vector<int> vecinos(std::vector<int> lvec, std::vector<Individuo> poblacion, std::vector< std::vector<double> > red, int i){
    for(int j=2;j<lvec.size();j++){
	lvec[j]=-1;
    }
    int j=2;
    for(int z=0;z<red.size();z++){
	if(red[i][z]!=0 && j<lvec.size() && !esta(poblacion[z].solucion[j],lvec)){
	    lvec[j]=poblacion[z].solucion[j];
//	    z--;
	    j++;
	}
    }
    lvec=completa(lvec);
    return lvec;
}

std::vector<int> vecinos2(std::vector<int> lvec, std::vector<Individuo> poblacion, std::vector< std::vector<double> > red, int i, int numero){

    int cambio=0;
    int imayor=0;
    std::vector<double> contador;
    for(int z=0;z<lvec.size();z++){
      contador.push_back(1);
    }

    for(int nc=0;nc<numero;nc++){
	int j=rand()%lvec.size();

	//Contar el numero de repeticiones de cada indice en los vecinos
	double total1=lvec.size();
	for(int z=0;z<red.size();z++){
	    if(red[i][z]!=0 && poblacion[i].fitness1>=poblacion[z].fitness1){
		//Si hay algun individuo con mejor fitness, entonces los valores de probabilidad de certeza cambian
//	    if(red[i][z]!=0){
		contador[poblacion[z].solucion[j]]+=1.0;
		//		total1+=0.5;
		total1+=1.0;
		cambio=1;
	    }
	}
	
	//Normaliza los valores contador... p(E|H_i)
	for(int z=0;z<contador.size();z++){
	    contador[z]/=total1;
	}
	
	//Cambia los valores de certezas en la posicion j de la solucion
	//p(H_i) es la probabilidad a priori (certeza)
	double total2=0;
	for(int z=0;z<poblacion[i].certeza[j].size();z++){
	    poblacion[i].certeza[j][z]*=contador[z];//p(E|H_i)*p(H_i)
	    total2+=poblacion[i].certeza[j][z];
	}
	    
//	printf("************\n");
	//Calcula la probabilidad a posteriori p(H_i|E)
	//Probabilidad de que un numero H este en la posicion i dada la solución óptima E
	//Normaliza los valores de certeza...
	for(int z=0;z<poblacion[i].certeza[j].size();z++){
	    poblacion[i].certeza[j][z]/=total2;//(p(E|H_i)*p(H_i))/p(E)
//	    printf("%d %f ",j,poblacion[i].certeza[j][z]);
	}
//	printf("************\n");
	
	/**/
	int tipo=rand()%2;
	if(tipo==0){
	    //Actualiza el valor de la posición según los valores calculados de certeza (Selección aleatoria)
	    double indice=(rand()%100)/100.0;
	    double suma=poblacion[i].certeza[j][0];
	    for(int z=1;z<poblacion[i].certeza[j].size();z++){
		suma+=poblacion[i].certeza[j][z];
		if(suma<indice){
		    imayor=z+1;
		}
	    }
	}
	else if(tipo==1){
	    /**/
	    /**/
	    //Actualiza el valor de la posición según los valores calculados de certeza (Selección del mayor)
	    double mayor=poblacion[i].certeza[j][0];
	    for(int z=1;z<lvec.size();z++){
		if(mayor<poblacion[i].certeza[j][z]){
		    mayor=poblacion[i].certeza[j][z];
		    imayor=z;
		}
	    }
	}
	/**/
	//No se ha encontrado un individuo con mejor fitness
	if(cambio!=0){
	    std::vector<int> lvec2;	    
	    for(int z=0;z<lvec.size();z++){
		lvec2.push_back(lvec[z]);
	    }
	    for(int z=0;z<lvec2.size();z++){
		if(lvec2[z]==imayor){
		    lvec2[z]=lvec2[j];
		    lvec2[j]=imayor;
		}
	    }
	    //Se realiza un cambio aleatorio en la solución solamente si el resultado da un mejor fitness
	    if(fitness(lvec2)<poblacion[i].fitness1){
		for(int z=0;z<lvec2.size();z++){
		    lvec[z]=lvec2[z];
		}
	    }
	}
	else{
	    for(int z=0;z<lvec.size();z++){
		if(lvec[z]==imayor){
		    lvec[z]=lvec[j];
		    lvec[j]=imayor;
		}
	    }
	}

	/*
	int numero=contador[0];
	int indice=0;
	for(int z=1;z<contador.size();z++){
	    if(numero<contador[z]){
		numero=contador[z];
		indice=z;
	    }
	}

	for(int z=0;z<lvec.size();z++){
	    if(lvec[z]==contador[indice]){
		lvec[z]=lvec[j];
		lvec[j]=contador[indice];
	    }
	}
	*/
    }
    
    lvec=completa(lvec);

    return lvec;
}

std::vector<int> copia_reset(std::vector<int> lvec, std::vector<int> solucion_reset){

    for(int j=0;j<solucion_reset.size();j++){
	lvec[j]=solucion_reset[j];
    }
    return lvec;
}

std::vector<int> reset(std::vector<int> lvec, std::vector<Individuo> poblacion, int indice_reset){

    if(rand()%100<60){
	if(lvec.size()==0){
	    for(int j=0;j<poblacion[indice_reset].solucion.size();j++){
		lvec.push_back(poblacion[indice_reset].solucion[j]);
	    }
	}
	else{
	    for(int j=0;j<poblacion[indice_reset].solucion.size();j++){
		lvec[j]=poblacion[indice_reset].solucion[j];
	    }
	}
    }
    else{
	lvec.clear();
	int tmp=0, indice1=0, indice2=0;
	for(int j=0;j<poblacion[indice_reset].solucion.size();j++){
	    lvec.push_back(j);
	}
	for(int j=0;j<20;j++){
	    indice1=rand()%lvec.size();
	    indice2=rand()%lvec.size();
	    tmp=lvec[indice1];
	    lvec[indice1]=lvec[indice2];
	    lvec[indice2]=tmp;
	}
	
    }
    
    return lvec;
}

std::vector<int> copia(std::vector<int> lvec, std::vector<Individuo> poblacion, std::vector< std::vector<double> > red, int i, int tipo){
    double mejor;
    int j,imejor;
    //Copia la solución del vecino que tiene mayor influencia
    if(tipo==0){
	mejor=red[i][0];
	imejor=0;
	for(j=1;j<red.size();j++){
	    if(mejor<red[i][j]){
		mejor=red[i][j];
		imejor=j;
	    }
	}
	for(j=0;j<poblacion[i].solucion.size();j++){
	    lvec[j]=poblacion[imejor].solucion[j];
	}
    }

    //Copia la solución del vecino que tiene el mejor fitness
    else if(tipo==1){
	imejor=-1;

	for(j=0;j<red.size();j++){
	    if(red[i][j]>0){
		if(imejor==-1)
		    imejor=0;
		else
		    if(poblacion[imejor].fitness1>poblacion[j].fitness1){
			imejor=j;
		    }
	    }
	}

	if(imejor>=0){
	    for(j=0;j<poblacion[i].solucion.size();j++){
		lvec[j]=poblacion[imejor].solucion[j];
	    }
	}
    }
    return lvec;
}

std::vector<Individuo> iteracion(std::vector<Individuo> poblacion, std::vector< std::vector<double> > red){

    std::vector<Individuo> lpob;
    int j,indice1,indice2,val,imejor,tipo3,iAccion;
    double mejor,nAccion,sAccion,vfitness;

    //copia poblacion a una estructura local...
    lpob.clear();
    for(int i=0;i<poblacion.size();i++){
	lpob.push_back(poblacion[i]);
	lpob[i].solucion.clear();
	for(int j=0;j<poblacion[i].solucion.size();j++){
	    lpob[i].solucion.push_back(poblacion[i].solucion[j]);
	}
    }

    for(int i=0;i<poblacion.size();i++){
	iAccion=0;
	sAccion=0;
	//Cada individuo tiene una probabilidad específica de ejecutar cada una de las acciones predefinidas
	nAccion=(rand()%100)/100.0;
	double tvalor=0;
	for(int j=0;j<poblacion[i].accion.size();j++){
	    tvalor+=poblacion[i].accion[j];
	}
	for(int j=0;j<poblacion[i].accion.size();j++){
	    sAccion+=poblacion[i].accion[j]/tvalor;
	    if(sAccion<nAccion){
		iAccion=j+1;
	    }
	}

	if(rand()%100<5){//Ejecuta la accion de 'resetting'
	    if(solucion_reset.size()==0 || rand()%100<20){//Cambia la solucion de 'reset'
		solucion_reset=reset(solucion_reset,poblacion,rand()%poblacion.size());
	    }
	    lpob[i].solucion=copia_reset(lpob[i].solucion,solucion_reset);
	}
	
	else if(rand()%100<3){//10 //Replica la solución de un vecino...
	    //printf("***********************************2\n");
	    lpob[i].solucion=copia(lpob[i].solucion,poblacion,red,i,rand()%2);
	}
	
	else if(iAccion==0){//cambiar solucion de forma aleatoria (Exploración local)...
	    //combina los indices de forma aleatoria...
	    //lpob[i].solucion=combina(lpob[i].solucion,(rand()%10)+1);
	    lpob[i].solucion=combina(lpob[i].solucion,(rand()%3)+1);
	    tAccion0++;
	}

	else if(iAccion==1){//algoritmo de razonamiento bayesiano...
	    //lpob[i].solucion=vecinos2(lpob[i].solucion,poblacion,red,i,(rand()%10)+1);
//	    if(rand()%100<5){
//		lpob[i].solucion=copia(lpob[i].solucion,poblacion,red,i,rand()%2);
//	    }
	    lpob[i].solucion=vecinos2(lpob[i].solucion,poblacion,red,i,(rand()%2)+1);
	    tAccion1++;
	}
	
	//Actualiza el vector se probabilidades para la elección de las acciones...
	double f0=lpob[i].fitness1;
	lpob[i].fitness1=fitness(lpob[i].solucion);
	if(f0>lpob[i].fitness1){
	    poblacion[i].accion[iAccion]+=0.3;
	}
	else{
	    if(poblacion[i].accion[iAccion]>0.1)
		poblacion[i].accion[iAccion]-=0.1;
	}
    }

    //Verifica que el vector solución esté bien construido...
    for(int i=0;i<poblacion.size();i++){
	if(lpob[i].fitness1<poblacion[i].fitness1){
	    for(int z=0;z<poblacion[i].solucion.size();z++){
		poblacion[i].solucion[z]=lpob[i].solucion[z];
	    }
	    poblacion[i].fitness1=lpob[i].fitness1;
	    if(lpob[i].fitness1!=fitness(lpob[i].solucion)){
		printf("Error 2 %d %f %f\n",i,poblacion[i].fitness1,fitness(poblacion[i].solucion));
		exit(0);
	    }
	    if(poblacion[i].fitness1!=fitness(poblacion[i].solucion)){
		printf("Error 1 %f %f\n",poblacion[i].fitness1,fitness(poblacion[i].solucion));
		exit(0);
	    }
	}
    }

    return poblacion;
}

void cargaArchivo(std::string archivo){

    int nmat=0, linea=0;
    char buf[1024];
    const char *p;
    double val=0.0;
    std::vector<std::string> cads;
    std::vector<double> fila;
    std::vector< std::vector<double> > matriz1;
    std::vector< std::vector<double> > matriz2;
    FILE *fp=fopen(archivo.c_str(),"r");
    a.clear();
    b.clear();

    if(fp!=NULL){
	while(fgets(buf,sizeof(buf),fp)!=NULL){
	    cads.clear();
	    fila.clear();
	    for(p=strtok(buf," "); p; p=strtok(NULL," ")){
		cads.push_back(p);
	    }
	    if(cads[0]=="\n"){
		nmat++;
	    }
	    if(linea>0 && cads.size()>1 && cads[0]!="%" && cads[0][0]!='%'){
		for(int i=0;i<cads.size();i++){
		    val=atof(cads[i].c_str());
		    fila.push_back(val);
		}
		if(nmat==1)
//		    matriz1.push_back(fila);
		    a.push_back(fila);
		else
//		    matriz2.push_back(fila);
		    b.push_back(fila);
		fila.clear();
	    }
	    linea++;
	}
//	a=matriz1;
//	b=matriz2;
	fclose(fp);
    }
}

int main(int argc, char **argv){

    std::vector< std::vector<double> > red;
    Poblacion P;
    int numeroIndividuos=200;
    int iteraciones=2000;//20 instancias
    double mejor=0;
    int imejor;

    if(argc<2){
	printf("Error, se debe pasar como parámetro el nombre del archivo de datos...\n");
	exit(0);
    }
    
    cargaArchivo(argv[1]);
    int instancias=a.size();
    
    srand(time(NULL));

    //Crea red...
    red=InicializaRed(numeroIndividuos);
    red=GeneraFSRed(red);
    //ImprimeRed(red);

    //Crea poblacion...
    P.p=0.0;//Todos los individuos son no creyentes...
    P.poblacion=GeneraPoblacion(numeroIndividuos,P.p,instancias,red);

//Inicia iteraciones...
    for(int i=0;i<iteraciones;i++){
	/**/
	mejor=P.poblacion[0].fitness1;
	imejor=0;
	for(int j=1;j<P.poblacion.size();j++){
	    if(mejor>P.poblacion[j].fitness1){
		mejor=P.poblacion[j].fitness1;
		imejor=j;
	    }
	}

	//Cantidad
	int cantidad=0;
	for(int j=0;j<P.poblacion.size();j++){
	    if((int)P.poblacion[j].fitness1==(int)mejor)
		cantidad++;
	}
	
	/*Imprime*/
	//printf("%d %f %d %d(",i,mejor,imejor,cantidad);
	printf("%d %f %d %d ",i,mejor,imejor,cantidad);
	for(int j=0;j<P.poblacion[imejor].solucion.size();j++){
	    printf("%d ",P.poblacion[imejor].solucion[j]);
	}
	printf("\n");
	//printf(")\n");
	/**/

	/**/
//	for(int i=0;i<numeroIndividuos;i++){
//	    printf("%f ",P.poblacion[i].fitness1);
//	}
	P.poblacion=iteracion(P.poblacion,red);
/**/
//	printf("\n");
/**/  
    }

    mejor=P.poblacion[0].fitness1;
    imejor=0;
    for(int j=1;j<P.poblacion.size();j++){
	if(mejor>P.poblacion[j].fitness1){
	    mejor=P.poblacion[j].fitness1;
	    imejor=j;
	}
    }
    //    printf("%f\n",mejor);
    //    printf("%d %d %d %d %d\n",tAccion0,tAccion1,tAccion2,tAccion3,tAccion4);
    
    return 0;
}
