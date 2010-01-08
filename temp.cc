#include <iostream>
#include <algorithm>
#include <vector>
#include "gaussian.hh"
#include "hoo.hh"

using namespace std;


int main()
{

  Gaussian *domain = new Gaussian();
  HOO *hoo = new HOO(domain);
  
  State s = domain->getInitialState();
  Action a;
  SARS *sars = NULL;

  double epReward = 0.0;
  double regret[2048];
  std::fill(regret, regret+2048, 0.0);

  for(int laps=0; laps<50; laps++) {
    hoo->clear();
    for(int i=0; i<2048; i++) {
      /* Plan and execute in world */
      a = hoo->queryAction();
      delete sars;
      sars = domain->step(s, a);
      epReward += sars->reward;
      
      hoo->insertAction(a, sars->reward);
      /*
      for(unsigned int j=0; j<a.size(); j++) {
	cout << a[j] << " ";
      }
      
      cout << sars->reward << " " << epReward << " " << (1 - sars->reward) << endl;
      */
      regret[i] += (1-sars->reward);
    }
  }

  for(int i=0; i<2048; i++) {
    cout<< regret[i]/2048 << endl;
  }
  
  return 0;
}
