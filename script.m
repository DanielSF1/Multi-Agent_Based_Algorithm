close all;
clear all;
#clc;
#graphics_toolkit ("gnuplot");
graphics_toolkit ("qt");

#executions=20;
#data=load('results_chr18b_2');
#data=load('results_chr20a_2');
#data=load('results_chr20b_2');
#data=load('results_esc32a_2');
#data=load('results_had20_2');
#data=load('results_Rou20_2');
#data=load('results_tai20b_2');

executions=20;
#data=load('Results_bur_3');
#data=load('Results_chr18b_3');
data=load('Results_chr20a_3');
#data=load('Results_chr20b_3');
#data=load('Results_esc32a_3');
#data=load('Results_esc32e_3');
#data=load('Results_had20_3');
#data=load('Results_rou20_3');
#data=load('Results_scr_20_3');
#data=load('Results_tai20b_3');

d2=sortrows(data,1);
d3=d2(:,2);
d4=reshape(d3,executions,2000);

subplot(2,1,1);
#boxplot(d4);
plot(mean(d4));
hold on;
plot(median(d4));
subplot(2,1,2);
boxplot(d4(:,2000));
