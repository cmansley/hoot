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

  Domain *domain = new DDI(0.9);
  Chopper *chopper = new Chopper(domain, 20, 5);

  Action c;
  int b;

  for(int i = 0; i<25; i++) {

    c = chopper->continuousAction(i);
    b = chopper->discretizeAction(c);

    std::cout << i << "\t->\t" << c[0] << " " << c[1] << "\t->\t" << b  << std::endl;
  }

  

  return 0;
}
