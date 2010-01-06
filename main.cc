#include <iostream>
#include "ccl.hh"
#include "ip.hh"
#include "ss.hh"
#include "uct.hh"
#include "lander.hh"

using namespace std;

int main()
{

  /* Create domain */
  //CCL *domain = new CCL(0.9);
  IP *domain = new IP(0.9);
  //Lander *domain = new Lander(0.9);

  /* Create and initialize planner */
  UCT planner(domain, 0.1);
  //SS planner(domain, 0.1, 1, 5);
  //Corput planner(domain, 0.1);

  planner.initialize();

  /* Initialize state/action variables */
  State s = domain->getInitialState();
  Action a(1);
  SARS *sars = NULL;

  for(int queries = 128; queries < 4097; queries*=2) {

    /* Initialize stats */
    int steps = 0;
    int count = 0;
    double epReward = 0.0;

    /* Set maximum queries planner is allowed */
    planner.setMaxQueries(queries);

    // Perform a couple of episodes
    while(count < 10) {

      /* Plan and execute in world */
      a = planner.plan(s);
      delete sars;
      sars = domain->step(s, a);
      
      steps += 1;
      epReward += sars->reward;
      if(steps > 1000 || sars->terminal) {
	// report 
	cout << queries << " " << count << " " << epReward/steps << " " << domain->getNumSamples()/steps << " " << epReward << endl;
	
	domain->resetSamples();
	
	// reset
	epReward = 0.0;
	steps = 0;
	s = domain->getInitialState();
	count += 1;
      } else {
	s = sars->s_prime;
      }
    } // end while


  } // end for 

  return 0;
}
