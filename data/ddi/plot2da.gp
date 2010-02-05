reset
#set logscale x
set title 'N-Double Integrator - 2D'
set xlabel 'Number of Discrete Actions'
set ylabel 'Total Reward'

set output './plot/ddi2da.eps'

load "../style.gp"

set xrange [0:50]
set term post eps

set key right bottom

plot 'ddi_2D_uct_A.txt' using 2:4 with lines ls 11 title 'UCT','ddi_2D_uct_A.txt' using 2:4:3:5 with yerrorbars ls 14 title '',\
     'ddi_2D_hoot_A.txt' using 2:4 with lines ls 21 title 'HOOT','ddi_2D_hoot_A.txt' using 2:4:3:5 with yerrorbars ls 24 title ''