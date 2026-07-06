#!/bin/bash
echo "n,time_sec,gflops" > results.csv
for n in 2000 4000 6000 8000 10000 12000 14000 16000 18000 20000; do
    echo "Running n=$n..."
    ./matmul_bench $n >> results.csv
done
echo "Done. Results in results.csv"
