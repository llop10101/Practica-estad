#!/bin/bash
echo "Generating all the benchs, this will last a bit"
# Definir l'array de valors
sizes=(10 25 50 75 100 250 500 750 1000 2500 5000 7500 10000 25000 50000 75000 100000 250000 500000 750000)

# Generar els altres fitxers de bench
for i in "${sizes[@]}"; do
    head -n "$i" bench.txt > bench"$i".txt
done
