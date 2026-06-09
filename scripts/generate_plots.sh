#!/usr/bin/env bash
set -euo pipefail

CSV="results/results.csv"

if [ ! -f "$CSV" ]; then
    echo "Error: no se encontro $CSV. Corre primero: make run"
    exit 1
fi

echo "Generando archivos .dat..."

LC_ALL=C awk -F, 'NR>1 && $2=="random" && $1=="quick" && $6==1 {sum[$3]+=$5; c[$3]++} END{for(n in sum) print n, sum[n]/c[n]}' "$CSV" | sort -n > results/avg_quick_random.dat

LC_ALL=C awk -F, 'NR>1 && $2=="random" && $1=="merge" && $6==1 {sum[$3]+=$5; c[$3]++} END{for(n in sum) print n, sum[n]/c[n]}' "$CSV" | sort -n > results/avg_merge_random.dat

LC_ALL=C awk -F, 'function log2(x){return log(x)/log(2)} NR>1 && $2=="random" && $1=="quick" && $6==1 {sum[$3]+=$5; c[$3]++} END{for(n in sum) print n, (sum[n]/c[n])/(n*log2(n))}' "$CSV" | sort -n > results/norm_quick_random.dat

LC_ALL=C awk -F, 'function log2(x){return log(x)/log(2)} NR>1 && $2=="random" && $1=="merge" && $6==1 {sum[$3]+=$5; c[$3]++} END{for(n in sum) print n, (sum[n]/c[n])/(n*log2(n))}' "$CSV" | sort -n > results/norm_merge_random.dat

LC_ALL=C awk -F, 'NR>1 && $2=="random" && $6==1 {sum[$1","$3]+=$5; c[$1","$3]++} END{for(k in c){split(k,a,","); avg[a[1]","a[2]]=sum[k]/c[k]} for(k in avg){split(k,a,","); if(a[1]=="merge"){n=a[2]; q=avg["quick,"n]; if(q>0) print n, avg[k]/q}}}' "$CSV" | sort -n > results/ratio_random.dat

echo "Generando graficas..."
gnuplot scripts/plot2.gp

echo "Listo. Graficas en results/"
xdg-open results/time_random.png
xdg-open results/normalized_random.png
xdg-open results/ratio_random.png
