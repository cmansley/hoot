reset
#set logscale x
set title 'Inverted Pendulum - 20N'
set xlabel 'Number of Discrete Actions'
set ylabel 'Total Reward'

set output './plot/ipa20.eps'

load "../style.gp"

set xrange [0:50]
set term post eps

set key right bottom

plot      'ip_hoot_A_20N.txt' using 2:4 with lines ls 21 title 'HOOT','ip_hoot_A_20N.txt' using 2:4:3:5 with yerrorbars ls 24 title '',\
     'ip_uct_A_20N.txt' using 2:4 with lines ls 11 title 'UCT','ip_uct_A_20N.txt' using 2:4:3:5 with yerrorbars ls 14 title ''
