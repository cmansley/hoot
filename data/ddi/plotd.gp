reset
#set logscale x
set title 'D-Double Integrator'
set xlabel 'Number of Action Dimensions'
set ylabel 'Total Reward'

set output './plot/ddid.eps'

load "../style.gp"

set xrange [0.75:4.25]
set xtics (1,2,3,4)
set term post eps
set size 0.6,0.6

set key left bottom

plot      'ddi_D_lqr.txt' using 7:4 with lines ls 31 title 'LQR','ddi_D_lqr.txt' using 7:4:3:5 with yerrorbars ls 34 title '',\
     'ddi_D_hoot.txt' using 7:4 with lines  ls 21 title 'HOOT','ddi_D_hoot.txt' using 7:4:3:5 with yerrorbars ls 24 title '',\
     'ddi_D_uct_5A.txt' using 7:4 with lines ls 11 title 'UCT 5','ddi_D_uct_5A.txt' using 7:4:3:5 with yerrorbars ls 14 title '',\
     'ddi_D_uct_10A.txt' using 7:4 with lines ls 12 title 'UCT 10','ddi_D_uct_10A.txt' using 7:4:3:5 with yerrorbars ls 14 title '',\
     'ddi_D_uct_20A.txt' using 7:4 with lines ls 13 title 'UCT 20','ddi_D_uct_20A.txt' using 7:4:3:5 with yerrorbars ls 14 title ''

