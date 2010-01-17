#include <iostream>
#include "ccl.hh"
#include "ip.hh"
#include "ss.hh"
#include "uct.hh"
#include "lander.hh"
#include "hoot.hh"

using namespace std;

int main()
{
  /* Create domain */
  //CCL *domain = new CCL(0.9);
  Domain *domain = new IP(0.9);
  //Lander *domain = new Lander(0.9);

  /* Create and initialize planner */
  Planner *planner = new HOOT(domain, 0.1);
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
  for(int queries = 128; queries < 4097; queries*=2) {

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
    cout << queries << " " << mean - bound << " " << mean << " " << mean + bound  << endl;

  } // end for 

  return 0;
}
