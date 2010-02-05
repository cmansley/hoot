#include <iostream>
#include <algorithm>
#include <vector>
#include "gaussian.hh"
#include "hoo.hh"
#include "ip.hh"
#include "chopper.hh"
#include "ddi.hh"

using namespace std;


int main()
{

  Gaussian *g = new Gaussian();

  Chopper *c = new Chopper(g,20,20);

  HOO h(g, c);

  State s = g->getInitialState();

  double regret = 0.0;
  double mean = 0.0;

  for(int t=1; t<2; t++) {
    regret = 0.0;
    h.clear();
    for(int i=0; i<5000; i++) {
      
      Action a = h.queryAction(false);
      SARS *sars = g->step(s, a);
      h.insertAction(a, sars->reward);
      
      regret += 1.0 - sars->reward;
      delete sars;
    }
    //std::cout << regret <<std::endl;
    mean = mean + (regret - mean)/t;
  }


  std::cout << mean << std::endl;

  return 0;
}
