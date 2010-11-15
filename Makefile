CFLAGS=-Wall -g #-pg
INCLUDES=-I/home/cmansley/boost_1_41_0 #-I /koko/rl3/cmansley/boost_1_41_0 -I/koko/rl3/cmansley/local/include
LIBS= #-L/koko/rl3/cmansley/local/lib

plan: main.o ccl.o ss.o ip.o uct.o lander.o hoo.o node.o gaussian.o hoot.o mcplanner.o chopper.o di.o lqr.o ddi.o bicycle.o sars.o sarsa.o
	g++ $(CFLAGS) -o plan main.o ccl.o ss.o ip.o uct.o lander.o hoo.o node.o hoot.o mcplanner.o chopper.o di.o lqr.o ddi.o bicycle.o sars.o sarsa.o  $(LIBS) -lgsl -lgslcblas -lm -lgflags

temp: temp.o gaussian.o hoo.o node.o chopper.o ip.o ddi.o
	g++ $(CFLAGS) -o temp temp.o gaussian.o hoo.o node.o ip.o chopper.o ddi.o -lgsl -lgslcblas -lm

temp.o: temp.cc
	g++ -c $(CFLAGS) temp.cc $(INCLUDES)

main.o: main.cc
	g++ -c $(CFLAGS) main.cc $(INCLUDES)

ccl.o: ccl.cc ccl.hh
	g++ -c $(CFLAGS) ccl.cc $(INCLUDES)

ip.o: ip.cc ip.hh
	g++ -c $(CFLAGS) ip.cc $(INCLUDES)

lander.o: lander.cc lander.hh
	g++ -c $(CFLAGS) lander.cc $(INCLUDES)

ss.o: ss.cc ss.hh
	g++ -c $(CFLAGS) ss.cc $(INCLUDES)

uct.o: uct.cc uct.hh
	g++ -c $(CFLAGS) uct.cc $(INCLUDES)

hoo.o: hoo.cc hoo.hh node.hh
	g++ -c $(CFLAGS) hoo.cc  $(INCLUDES)

node.o: node.cc node.hh
	g++ -c $(CFLAGS) node.cc $(INCLUDES)

gaussian.o: gaussian.cc gaussian.hh
	g++ -c $(CFLAGS) gaussian.cc $(INCLUDES)

hoot.o: hoot.cc hoot.hh
	g++ -c $(CFLAGS) hoot.cc $(INCLUDES)

mcplanner.o: mcplanner.cc mcplanner.hh
	g++ -c $(CFLAGS) mcplanner.cc $(INCLUDES)

chopper.o: chopper.cc chopper.hh
	g++ -c $(CFLAGS) chopper.cc $(INCLUDES)

di.o: di.cc di.hh
	g++ -c $(CFLAGS) di.cc $(INCLUDES)

ddi.o: ddi.cc ddi.hh
	g++ -c $(CFLAGS) ddi.cc $(INCLUDES)

lqr.o: lqr.cc lqr.hh
	g++ -c $(CFLAGS) lqr.cc $(INCLUDES)

bicycle.o: bicycle.cc bicycle.hh
	g++ -c $(CFLAGS) bicycle.cc $(INCLUDES)

sars.o: sars.cc sars.hh
	g++ -c $(CFLAGS) sars.cc $(INCLUDES)

sarsa.o: sarsa.cc sarsa.hh
	g++ -c $(CFLAGS) sarsa.cc $(INCLUDES)

clean:
	rm -f *~ *.o plan temp
