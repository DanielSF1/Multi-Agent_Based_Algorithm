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
data1=load('Results_bur_3');
data2=load('Results_chr18b_3');
data3=load('Results_chr20a_3');
data4=load('Results_chr20b_3');
data5=load('Results_els19_3');
data6=load('Results_esc32a_3');
data7=load('Results_esc32e_3');
data8=load('Results_had20_3');
data9=load('Results_nug20_3');
data10=load('Results_rou20_3');
data11=load('Results_scr_20_3');
data12=load('Results_tai20b_3');

#d2=sortrows(data8,1);
#d3=d2(:,2);
#d4=reshape(d3,executions,2000);

#subplot(2,1,1);
#plot(mean(d4));
#hold on;
#plot(median(d4));
#plot(min(d4));
#subplot(2,1,2);
#boxplot(d4(:,2000));

subplot(4,3,1);
boxplot((reshape(sortrows(data1,1)(:,2),executions,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("bur26a")
subplot(4,3,2);
boxplot((reshape(sortrows(data2,1)(:,2),executions,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("chr18b")
subplot(4,3,3);
boxplot((reshape(sortrows(data3,1)(:,2),executions,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("chr20a")
subplot(4,3,4);
boxplot((reshape(sortrows(data4,1)(:,2),executions,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("chr20b")
subplot(4,3,5);
boxplot((reshape(sortrows(data5,1)(:,2),executions,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("els19")
subplot(4,3,6);
boxplot((reshape(sortrows(data6,1)(:,2),executions,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("esc32a")
subplot(4,3,7);
boxplot((reshape(sortrows(data7,1)(:,2),executions,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("esc32e")
subplot(4,3,8);
boxplot((reshape(sortrows(data8,1)(:,2),executions,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("had20")
subplot(4,3,9);
boxplot((reshape(sortrows(data9,1)(:,2),executions,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("nug20")
subplot(4,3,10);
boxplot((reshape(sortrows(data10,1)(:,2),executions,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("rou20")
subplot(4,3,11);
boxplot((reshape(sortrows(data11,1)(:,2),executions,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("scr20")
subplot(4,3,12);
boxplot((reshape(sortrows(data12,1)(:,2),executions,2000)(:,2000)));
axis([0.5 1.5])
xlabel("Last Iteration")
ylabel("Fitness")
title("tai20b")


##subplot(4,3,1);
##plot(mean(reshape(sortrows(data1,1)(:,2),executions,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("bur26a")
##
##subplot(4,3,2);
##plot(mean(reshape(sortrows(data2,1)(:,2),executions,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("chr18b")
##
##subplot(4,3,3);
##plot(mean(reshape(sortrows(data3,1)(:,2),executions,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("chr20a")
##
##subplot(4,3,4);
##plot(mean(reshape(sortrows(data4,1)(:,2),executions,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("chr20b")
##
##subplot(4,3,5);
##plot(mean(reshape(sortrows(data5,1)(:,2),executions,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("els19")
##
##subplot(4,3,6);
##plot(mean(reshape(sortrows(data6,1)(:,2),executions,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("esc32a")
##
##subplot(4,3,7);
##plot(mean(reshape(sortrows(data7,1)(:,2),executions,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("esc32e")
##
##subplot(4,3,8);
##plot(mean(reshape(sortrows(data8,1)(:,2),executions,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("had20")
##
##subplot(4,3,9);
##plot(mean(reshape(sortrows(data9,1)(:,2),executions,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("nug20")
##
##subplot(4,3,10);
##plot(mean(reshape(sortrows(data10,1)(:,2),executions,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("rou20")
##
##subplot(4,3,11);
##plot(mean(reshape(sortrows(data11,1)(:,2),executions,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("scr20")
##
##subplot(4,3,12);
##plot(mean(reshape(sortrows(data12,1)(:,2),executions,2000)),'linewidth',3);
##xlabel("Iterations")
##ylabel("Fitness")
##title("tai20b")
