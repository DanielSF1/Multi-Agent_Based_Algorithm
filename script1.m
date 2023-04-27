close all;
clear all;
#clc;
#graphics_toolkit ("gnuplot");
graphics_toolkit ("qt");

#ejecuciones=20;
#datos=load('resultados_chr18b_2');
#ejecuciones=20;
#datos=load('resultados_chr20a_2');
#ejecuciones=20;
#datos=load('resultados_chr20b_2');
#ejecuciones=20;
#datos=load('resultados_esc32a_2');
#ejecuciones=20;
#datos=load('resultados_had20_2');
#ejecuciones=25;
#datos=load('resultados_Rou20_2');
#ejecuciones=20;
#datos=load('resultados_tai20b_2');

ejecuciones=20;
datos1=load('Resultados_bur_3');
datos2=load('Resultados_chr18b_3');
datos3=load('Resultados_chr20a_3');
datos4=load('Resultados_chr20b_3');
datos5=load('Resultados_els19_3');
datos6=load('Resultados_esc32a_3');
datos7=load('Resultados_esc32e_3');
datos8=load('Resultados_had20_3');
datos9=load('Resultados_nug20_3');
datos10=load('Resultados_rou20_3');
datos11=load('Resultados_scr_20_3');
datos12=load('Resultados_tai20b_3');

#d2=sortrows(datos8,1);
#d3=d2(:,2);
#d4=reshape(d3,ejecuciones,2000);

#subplot(2,1,1);
#plot(mean(d4));
#hold on;
#plot(median(d4));
#plot(min(d4));
#subplot(2,1,2);
#boxplot(d4(:,2000));

subplot(4,3,1);
boxplot((reshape(sortrows(datos1,1)(:,2),ejecuciones,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("bur26a")
subplot(4,3,2);
boxplot((reshape(sortrows(datos2,1)(:,2),ejecuciones,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("chr18b")
subplot(4,3,3);
boxplot((reshape(sortrows(datos3,1)(:,2),ejecuciones,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("chr20a")
subplot(4,3,4);
boxplot((reshape(sortrows(datos4,1)(:,2),ejecuciones,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("chr20b")
subplot(4,3,5);
boxplot((reshape(sortrows(datos5,1)(:,2),ejecuciones,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("els19")
subplot(4,3,6);
boxplot((reshape(sortrows(datos6,1)(:,2),ejecuciones,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("esc32a")
subplot(4,3,7);
boxplot((reshape(sortrows(datos7,1)(:,2),ejecuciones,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("esc32e")
subplot(4,3,8);
boxplot((reshape(sortrows(datos8,1)(:,2),ejecuciones,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("had20")
subplot(4,3,9);
boxplot((reshape(sortrows(datos9,1)(:,2),ejecuciones,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("nug20")
subplot(4,3,10);
boxplot((reshape(sortrows(datos10,1)(:,2),ejecuciones,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("rou20")
subplot(4,3,11);
boxplot((reshape(sortrows(datos11,1)(:,2),ejecuciones,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("scr20")
subplot(4,3,12);
boxplot((reshape(sortrows(datos12,1)(:,2),ejecuciones,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("tai20b")


##subplot(4,3,1);
##plot(mean(reshape(sortrows(datos1,1)(:,2),ejecuciones,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("bur26a")
##
##subplot(4,3,2);
##plot(mean(reshape(sortrows(datos2,1)(:,2),ejecuciones,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("chr18b")
##
##subplot(4,3,3);
##plot(mean(reshape(sortrows(datos3,1)(:,2),ejecuciones,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("chr20a")
##
##subplot(4,3,4);
##plot(mean(reshape(sortrows(datos4,1)(:,2),ejecuciones,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("chr20b")
##
##subplot(4,3,5);
##plot(mean(reshape(sortrows(datos5,1)(:,2),ejecuciones,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("els19")
##
##subplot(4,3,6);
##plot(mean(reshape(sortrows(datos6,1)(:,2),ejecuciones,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("esc32a")
##
##subplot(4,3,7);
##plot(mean(reshape(sortrows(datos7,1)(:,2),ejecuciones,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("esc32e")
##
##subplot(4,3,8);
##plot(mean(reshape(sortrows(datos8,1)(:,2),ejecuciones,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("had20")
##
##subplot(4,3,9);
##plot(mean(reshape(sortrows(datos9,1)(:,2),ejecuciones,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("nug20")
##
##subplot(4,3,10);
##plot(mean(reshape(sortrows(datos10,1)(:,2),ejecuciones,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("rou20")
##
##subplot(4,3,11);
##plot(mean(reshape(sortrows(datos11,1)(:,2),ejecuciones,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("scr20")
##
##subplot(4,3,12);
##plot(mean(reshape(sortrows(datos12,1)(:,2),ejecuciones,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("tai20b")
