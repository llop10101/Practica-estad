#!/bin/bash

for i in 10 100 1000 10000 1000000 1000000000
do
    head -n $i bench.txt >> bench$i.txt
done
