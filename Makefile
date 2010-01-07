CFLAGS=-Wall #-pg
INCLUDES=-I/home/cmansley/boost_1_41_0

plan: main.o ccl.o ss.o ip.o uct.o lander.o hoo.o node.o
	g++ $(CFLAGS) -o plan main.o ccl.o ss.o ip.o uct.o lander.o hoo.o node.o -lgsl -lgslcblas -lm

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

clean:
	rm *~ *.o plan