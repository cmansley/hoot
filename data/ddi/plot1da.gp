reset
#set logscale x
set title 'N-Double Integrator - 1D'
set xlabel 'Number of Discrete Actions'
set ylabel 'Total Reward'

set output './plot/ddi1da.eps'

load "../style.gp"

set xrange [0:50]
set term post eps

set key right bottom

plot 'ddi_1D_hoot_A.txt' using 2:4 with lines ls 21 title 'HOOT','ddi_1D_hoot_A.txt' using 2:4:3:5 with yerrorbars ls 24 title '',\
     'ddi_1D_whoot_A.txt' using 2:4 with lines ls 31 title 'WHOOT','ddi_1D_whoot_A.txt' using 2:4:3:5 with yerrorbars ls 34 title '',\
     'ddi_1D_uct_A.txt' using 2:4 with lines ls 11 title 'UCT','ddi_1D_uct_A.txt' using 2:4:3:5 with yerrorbars ls 14 title '',\
     'ddi_1D_ss_A.txt' using 2:4 with lines ls 41 title 'SS','ddi_1D_ss_A.txt' using 2:4:3:5 with yerrorbars ls 44 title ''
