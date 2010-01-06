reset
set logscale x
set title 'Inverted Pendulum'
set xlabel '# samples allowed (logscale)'
set ylabel 'average reward'

set style line 11 lt 1 lc rgb "red" lw 1
set style line 12 lt 2 lc rgb "red" lw 1
set style line 13 lt 4 lc rgb "red" lw 1
set style line 14 lt 1 lc rgb "blue" lw 1
set style line 15 lt 2 lc rgb "blue" lw 1
set style line 16 lt 4 lc rgb "blue" lw 1

set term post eps
set output 'ip.eps'

set key right bottom

plot 'ip_20A_30NBounds.out' using 1:3 with lines ls 14 title 'UCT 20A 30N','ip_20A_30NBounds.out' using 1:3:2:4 with yerrorbars ls 2 title '', \
     'ip_10A_30NBounds.out' using 1:3 with lines ls 15 title 'UCT 10A 30N','ip_10A_30NBounds.out' using 1:3:2:4 with yerrorbars ls 2 title '',\
     'ip_5A_30NBounds.out' using 1:3 with lines ls 16 title 'UCT 5A 30N','ip_5A_30NBounds.out' using 1:3:2:4 with yerrorbars ls 2 title ''


#'ipSR_30N_20A_ARBounds.out' using 1:3 with lines ls 11 title 'UCT 20A 30N','ipSR_30N_20A_ARBounds.out' using 1:3:2:4 with yerrorbars ls 2 title '', \
     #'ipSR_30N_10A_ARBounds.out' using 1:3 with lines ls 12 title 'UCT 10A 30N','ipSR_30N_10A_ARBounds.out' using 1:3:2:4 with yerrorbars ls 2 title '', \
     #'ipSR_30N_5A_ARBounds.out' using 1:3 with lines ls 13 title 'UCT 5A 30N','ipSR_30N_5A_ARBounds.out' using 1:3:2:4 with yerrorbars ls 2 title '', \