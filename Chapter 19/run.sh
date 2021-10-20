#!/bin/bash
if [[ "$1" == "" ]]; then
    echo "Wrong input 1"
    exit 1
fi

if [[ "$2" == "" ]]; then
    echo "Wrong input 2"
    exit 1
fi

rm tabelle.csv
#i += 1 / i += 4
for (( i = 1; i <= $1; i *= 2)) 
do
    ./tlb -n $i -i $2
    wait
done

python3 ./plot.py
