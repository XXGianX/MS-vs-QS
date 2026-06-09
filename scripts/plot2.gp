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
