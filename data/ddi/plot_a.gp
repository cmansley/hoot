reset
#set logscale x
set title 'N-Double Integrator - 2D'
set xlabel 'Number of Actions'
set ylabel 'Total Reward'

set xrange [0:50]

set style line 11 lt 1 lc rgb "red" lw 1
set style line 12 lt 2 lc rgb "red" lw 1
set style line 13 lt 4 lc rgb "red" lw 1
set style line 14 lt 1 lc rgb "blue" lw 1
set style line 15 lt 2 lc rgb "blue" lw 1
set style line 16 lt 4 lc rgb "blue" lw 1

set term post eps
set output 'plot/ddi_2Da.eps'

set key right bottom

plot 'ddi_2D_hoot_A.txt' using 2:4 with lines ls 11 title 'HOOT','ddi_2D_hoot_A.txt' using 2:4:3:5 with yerrorbars ls 2 title '', \
     'ddi_2D_uct_A.txt' using 2:4 with lines ls 12 title 'UCT','ddi_2D_uct_A.txt' using 2:4:3:5 with yerrorbars ls 2 title ''