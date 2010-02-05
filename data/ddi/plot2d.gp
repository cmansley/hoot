reset
set logscale x
set title 'Double Integrator - 2D'
set xlabel 'Samples per Planning Step (logscale)'
set ylabel 'Total Reward'

set output './plot/ddi2d.eps'

load "../style.gp"

set term post eps

set key right bottom

plot 'ddi_2D_uct_5A.txt' using 1:4 with lines ls 11 title 'UCT 5A','ddi_2D_uct_5A.txt' using 1:4:3:5 with yerrorbars ls 14 title '', \
     'ddi_2D_uct_20A.txt' using 1:4 with lines ls 13 title 'UCT 20A','ddi_2D_uct_20A.txt' using 1:4:3:5 with yerrorbars ls 14 title '', \
     'ddi_2D_hoot.txt' using 1:4 with lines ls 21 title 'HOOT','ddi_2D_hoot.txt' using 1:4:3:5 with yerrorbars ls 24 title ''