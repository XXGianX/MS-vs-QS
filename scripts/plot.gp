# Generar archivos .dat desde el CSV
system("awk -F, 'NR>1 && $2==\"random\" && $1==\"quick\" && $6==1 {sum[$3]+=$5; c[$3]++} END{for(n in sum) print n, sum[n]/c[n]}' results/results.csv | sort -n > results/avg_quick_random.dat")
system("awk -F, 'NR>1 && $2==\"random\" && $1==\"merge\" && $6==1 {sum[$3]+=$5; c[$3]++} END{for(n in sum) print n, sum[n]/c[n]}' results/results.csv | sort -n > results/avg_merge_random.dat")
system("awk -F, 'function log2(x){return log(x)/log(2)} NR>1 && $2==\"random\" && $1==\"quick\" && $6==1 {sum[$3]+=$5; c[$3]++} END{for(n in sum) print n, (sum[n]/c[n])/(n*log2(n))}' results/results.csv | sort -n > results/norm_quick_random.dat")
system("awk -F, 'function log2(x){return log(x)/log(2)} NR>1 && $2==\"random\" && $1==\"merge\" && $6==1 {sum[$3]+=$5; c[$3]++} END{for(n in sum) print n, (sum[n]/c[n])/(n*log2(n))}' results/results.csv | sort -n > results/norm_merge_random.dat")
system("awk -F, 'NR>1 && $2==\"random\" && $6==1 {sum[$1\",\"$3]+=$5; c[$1\",\"$3]++} END{for(k in c){split(k,a,\",\"); avg[a[1]\",\"a[2]]=sum[k]/c[k]} for(k in avg){split(k,a,\",\"); if(a[1]==\"merge\"){n=a[2]; q=avg[\"quick,\"n]; if(q>0) print n, avg[k]/q}}}' results/results.csv | sort -n > results/ratio_random.dat")

set datafile separator " "
set terminal pngcairo size 1000,700
set key outside
set xlabel "n"
set grid

set ylabel "Tiempo promedio (s)"
set output "results/time_random.png"
plot "results/avg_quick_random.dat" using 1:2 with linespoints title "quicksort", \
     "results/avg_merge_random.dat" using 1:2 with linespoints title "merge sort"

set ylabel "Tiempo / (n log2 n)"
set output "results/normalized_random.png"
plot "results/norm_quick_random.dat" using 1:2 with linespoints title "quicksort", \
     "results/norm_merge_random.dat" using 1:2 with linespoints title "merge sort"

set ylabel "R(n) = T_merge / T_quick"
set output "results/ratio_random.png"
set yrange [0:2]
plot "results/ratio_random.dat" using 1:2 with linespoints title "R(n)", \
     1 dashtype 2 lc rgb "red" title "R=1 (empate)"
