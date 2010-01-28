reset
set logscale x
set title 'N-Double Integrator - 1D'
set xlabel 'Samples per Planning Step (logscale)'
set ylabel 'Total Reward'

set style line 11 lt 1 lc rgb "red" lw 1
set style line 12 lt 2 lc rgb "red" lw 1
set style line 13 lt 4 lc rgb "red" lw 1
set style line 14 lt 1 lc rgb "blue" lw 1
set style line 15 lt 2 lc rgb "blue" lw 1
set style line 16 lt 4 lc rgb "blue" lw 1

set term post eps
set output 'ddi_1D.eps'

set key right bottom

plot 'ddi_1D_uct_20A.txt' using 1:4 with lines ls 11 title 'UCT 20A','ddi_1D_uct_20A.txt' using 1:4:3:5 with yerrorbars ls 2 title '', \
     'ddi_1D_uct_5A.txt' using 1:4 with lines ls 12 title 'UCT 5A','ddi_1D_uct_5A.txt' using 1:4:3:5 with yerrorbars ls 2 title '', \
     'ddi_1D_hoot.txt' using 1:4 with lines ls 14 title 'HOOT','ddi_1D_hoot.txt' using 1:4:3:5 with yerrorbars ls 2 title ''