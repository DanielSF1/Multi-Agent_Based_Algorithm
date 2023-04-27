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
#datos=load('Resultados_bur_3');
#datos=load('Resultados_chr18b_3');
datos=load('Resultados_chr20a_3');
#datos=load('Resultados_chr20b_3');
#datos=load('Resultados_esc32a_3');
#datos=load('Resultados_esc32e_3');
#datos=load('Resultados_had20_3');
#datos=load('Resultados_rou20_3');
#datos=load('Resultados_scr_20_3');
#datos=load('Resultados_tai20b_3');

d2=sortrows(datos,1);
d3=d2(:,2);
d4=reshape(d3,ejecuciones,2000);

subplot(2,1,1);
#boxplot(d4);
plot(mean(d4));
hold on;
plot(median(d4));
subplot(2,1,2);
boxplot(d4(:,2000));
