reset
set logscale x
set title 'Bicycle - 0.02cm'
set xlabel 'Samples per Planning Step (logscale)'
set ylabel 'Total Reward'

set output './plot/bicycle0.02.eps'

load "../style.gp"

set term post eps

set key right bottom

plot 'bicycle_uct_5A_0.02.txt' using 1:4 with lines ls 11 title 'UCT 5A','bicycle_uct_5A_0.02.txt' using 1:4:3:5 with yerrorbars ls 14 title '', \
     'bicycle_uct_10A_0.02.txt' using 1:4 with lines ls 12 title 'UCT 10A','bicycle_uct_10A_0.02.txt' using 1:4:3:5 with yerrorbars ls 14 title '', \
     'bicycle_uct_20A_0.02.txt' using 1:4 with lines ls 13 title 'UCT 20A','bicycle_uct_20A_0.02.txt' using 1:4:3:5 with yerrorbars ls 14 title '', \
     'bicycle_hoot_0.02.txt' using 1:4 with lines ls 21 title 'HOOT','bicycle_hoot_0.02.txt' using 1:4:3:5 with yerrorbars ls 24 title ''
