reset
set logscale x
set title 'Inverted Pendulum - 20N'
set xlabel 'Samples per Planning Step (logscale)'
set ylabel 'Total Reward'

set output './plot/ip20n.eps'

load "../style.gp"

set term post eps

set key right bottom

plot 'ip_uct_5A_20N.txt' using 1:4 with lines ls 11 title 'UCT 5A','ip_uct_5A_20N.txt' using 1:4:3:5 with yerrorbars ls 14 title '', \
     'ip_hoot_20N.txt' using 1:4 with lines ls 21 title 'HOOT','ip_hoot_20N.txt' using 1:4:3:5 with yerrorbars ls 24 title '',\
     'ip_uct_10A_20N.txt' using 1:4 with lines ls 12 title 'UCT 10A','ip_uct_10A_20N.txt' using 1:4:3:5 with yerrorbars ls 14 title '', \
     'ip_uct_20A_20N.txt' using 1:4 with lines ls 13 title 'UCT 20A','ip_uct_20A_20N.txt' using 1:4:3:5 with yerrorbars ls 14 title ''
