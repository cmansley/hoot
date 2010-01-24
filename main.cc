#include <iostream>
#include "ccl.hh"
#include "ip.hh"
#include "di.hh"

#include "ss.hh"
#include "uct.hh"
#include "lander.hh"
#include "hoot.hh"
#include "lqr.hh"

#include "chopper.hh"

using namespace std;

int main()
{
  /* Create domain */
  //CCL *domain = new CCL(0.9);
  Domain *domain = new IP(0.95);
  //Lander *domain = new Lander(0.9);

  for(int i=5; i<50; i+=10) { 

  /* Create mapper from domain to planner*/
  Chopper *chopper = new Chopper(domain, 20, i);

  /* Create and initialize planner */
  Planner *planner = new HOOT(domain, chopper, 0.1);
  //UCT planner(domain, 0.1);
  //HOOT planner(domain, 0.1);
  //SS planner(domain, 0.1, 1, 5);
  //Corput planner(domain, 0.1);

  /* Initialize planner */
  planner->initialize();

  /* Initialize state/action variables */
  State s = domain->getInitialState();
  Action a;
  SARS *sars = NULL;

  /* Main experiment loop */
  for(int queries = 2048; queries < 2049; queries*=2) {

    /* Initialize stats */
    int steps = 0;
    int n = 0;
    double epReturn = 0.0;

    double delta = 0.0;
    double mean = 0.0;
    double M2 = 0.0;

    /* Set maximum queries planner is allowed */
    planner->setMaxQueries(queries);

    // Perform a couple of episodes
    while(n < 10) {

      /* Plan and execute in world */
      a = planner->plan(s);
      delete sars;
      sars = domain->step(s, a);
      //cout << a[0] <<" " << sars->reward <<endl;
      //cout << sars->s[0] << " " << sars->s[1] << " " << a[0] << endl;
      
      /* Update stats */
      steps += 1;
      epReturn += sars->reward;

      /* Check for end conditions */
      if(steps > 999 || sars->terminal) {
	/* Compute mean and variance */
	n += 1;
        delta = epReturn - mean;
	mean = mean + delta/n;
	M2 = M2 + delta*(epReturn - mean);

	/* Reset stats*/
	epReturn = 0.0;
	steps = 0;
	domain->resetSamples();
	s = domain->getInitialState();

      } else {
	s = sars->s_prime;
      } // end if

    } // end while

    /* Report */
    double stdev = sqrt(M2/n);
    double bound = 1.96 * stdev/sqrt(n);
    //cout << queries << " " << mean - bound << " " << mean << " " << mean + bound  << endl;
    cout << i << " " << mean - bound << " " << mean << " " << mean + bound  << endl;

  } // end for 

  delete planner;
  delete chopper;

  }
  return 0;
}
