reset
#set logscale x
set title 'N-Double Integrator'
set xlabel 'Number of Action Dimensions'
set ylabel 'Total Reward'

set output './plot/ddid.eps'

load "../style.gp"

set xrange [0.75:3.25]
set xtics (1,2,3)
set term post eps

#set key right bottom

plot 'ddi_D_hoot.txt' using 7:4 with lines ls 21 title 'HOOT','ddi_D_hoot.txt' using 7:4:3:5 with yerrorbars ls 24 title '',\
     'ddi_D_uct_5A.txt' using 7:4 with lines ls 11 title 'UCT 5A','ddi_D_uct_5A.txt' using 7:4:3:5 with yerrorbars ls 14 title '',\
     'ddi_D_uct_10A.txt' using 7:4 with lines ls 12 title 'UCT 10A','ddi_D_uct_10A.txt' using 7:4:3:5 with yerrorbars ls 14 title '',\
     'ddi_D_uct_20A.txt' using 7:4 with lines ls 13 title 'UCT 20A','ddi_D_uct_20A.txt' using 7:4:3:5 with yerrorbars ls 14 title ''
