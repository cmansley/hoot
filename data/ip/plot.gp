reset
set logscale x
set title 'Inverted Pendulum - 20N'
set xlabel 'Samples per Planning Step (logscale)'
set ylabel 'Total Reward'

set style line 11 lt 1 lc rgb "red" lw 1
set style line 12 lt 2 lc rgb "red" lw 1
set style line 13 lt 4 lc rgb "red" lw 1
set style line 14 lt 1 lc rgb "blue" lw 1
set style line 15 lt 2 lc rgb "blue" lw 1
set style line 16 lt 4 lc rgb "blue" lw 1

set term post eps
set output 'plot/ip_20N.eps'

set key right bottom

plot 'ip_uct_20A_20N.txt' using 1:4 with lines ls 11 title 'UCT 20A','ip_uct_20A_20N.txt' using 1:4:3:5 with yerrorbars ls 2 title '', \
     'ip_hoot_20N.txt' using 1:4 with lines ls 14 title 'HOOT','ip_hoot_20N.txt' using 1:4:3:5 with yerrorbars ls 2 title ''