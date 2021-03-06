reset
set logscale x
set title 'Inverted Pendulum - 10N'
set xlabel 'Samples per Planning Step (logscale)'
set ylabel 'Cummulative Reward'

set style line 11 lt 1 lc rgb "red" lw 1
set style line 12 lt 2 lc rgb "red" lw 1
set style line 13 lt 4 lc rgb "red" lw 1
set style line 14 lt 1 lc rgb "blue" lw 1
set style line 15 lt 2 lc rgb "blue" lw 1
set style line 16 lt 4 lc rgb "blue" lw 1

set term post eps
set output 'ip.eps'

set key right bottom

plot 'ip_uct_20A_10N.out' using 1:3 with lines ls 11 title 'UCT 20A','ip_uct_20A_10N.out' using 1:3:2:4 with yerrorbars ls 2 title '', \
     'ip_uct_5A_10N.out' using 1:3 with lines ls 12 title 'UCT 5A','ip_uct_5A_10N.out' using 1:3:2:4 with yerrorbars ls 2 title '', \
     'ip_hoot_10N.out' using 1:3 with lines ls 14 title 'HOOT','ip_hoot_10N.out' using 1:3:2:4 with yerrorbars ls 2 title ''


#'ipSR_30N_20A_ARBounds.out' using 1:3 with lines ls 11 title 'UCT 20A 30N','ipSR_30N_20A_ARBounds.out' using 1:3:2:4 with yerrorbars ls 2 title '', \
     #'ipSR_30N_10A_ARBounds.out' using 1:3 with lines ls 12 title 'UCT 10A 30N','ipSR_30N_10A_ARBounds.out' using 1:3:2:4 with yerrorbars ls 2 title '', \
     #'ipSR_30N_5A_ARBounds.out' using 1:3 with lines ls 13 title 'UCT 5A 30N','ipSR_30N_5A_ARBounds.out' using 1:3:2:4 with yerrorbars ls 2 title '', \