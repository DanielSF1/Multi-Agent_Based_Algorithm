#!/bin/bash

#rm salida

for i in {1..10}
do
    echo $i
    ./programa chr12a.dat >> salida
done
