#!/usr/bin/env bash
set -euo pipefail

mkdir -p results
out="results/results.csv"
echo "algorithm,inputType,n,seed,timeSeconds,sorted" > "$out"

sizes=(1000 2000 5000 10000 20000 50000 100000)
inputTypes=(random sorted reversed repeated)
seeds=(101 102 103 104 105)

for inputType in "${inputTypes[@]}"; do
  for n in "${sizes[@]}"; do
    for seed in "${seeds[@]}"; do
      ./experiment quick "$inputType" "$n" "$seed" >> "$out" || true
      ./experiment merge "$inputType" "$n" "$seed" >> "$out"
    done
  done
done

echo "Resultados guardados en $out"
