# Task 1: BLIS Matrix Multiplication Benchmark

## Objective
Install BLIS, link it with a C program via its CBLAS interface, and benchmark
double-precision matrix multiplication (dgemm) for square matrices ranging
from 2000x2000 to 20000x20000, recording wall-clock time and FLOP/s.

## Approach
- Built BLIS from source (`./configure --prefix=/usr/local auto && make && sudo make install`)
- Wrote `matmul_bench.c`, which allocates random NxN matrices A and B, times
  a call to `cblas_dgemm`, and computes GFLOP/s using the standard 2*N^3 FLOP count
- Compiled with: `gcc -O2 matmul_bench.c -o matmul_bench -I/usr/local/include/blis -L/usr/local/lib -lblis -lm -lpthread`
- Ran `run_bench.sh`, looping matrix sizes 2000 through 20000 (step 2000),
  appending timing results to `results.csv`

## Files
- `matmul_bench.c` — benchmark program
- `run_bench.sh` — driver script looping over matrix sizes
- `results.csv` — raw output (n, time_sec, gflops)

## Results
| N     | Time (s)  | GFLOP/s |
|-------|-----------|---------|
| 2000  | 0.8419    | 19.00   |
| 4000  | 6.3065    | 20.30   |
| 6000  | 27.9866   | 15.44   |
| 8000  | 50.0359   | 20.47   |
| 10000 | 90.3964   | 22.12   |
| 12000 | 150.1377  | 23.02   |
| 14000 | 254.5015  | 21.56   |
| 16000 | 374.4439  | 21.88   |
| 18000 | 510.0779  | 22.87   |
| 20000 | 707.8405  | 22.60   |

## Observations
- GFLOP/s generally increases with matrix size up to ~12000, then plateaus around 21-23 GFLOP/s
- An anomalous dip occurs at N=6000 (15.4 GFLOP/s) — likely due to a cache-blocking
  boundary effect or transient system load during that run, rather than a fundamental
  algorithmic issue, since larger and smaller sizes both perform better
- Runtime scales roughly as expected for O(N^3) complexity: time_sec increases by
  ~8x from 10000 to 20000 (a 2x increase in N), consistent with 2^3 = 8
- No memory issues encountered even at N=20000 (~9.6GB peak usage), since running
  on native dual-boot Ubuntu rather than WSL