#include <iostream>
#include <gflags/gflags.h>

#include "ccl.hh"
#include "ip.hh"
#include "di.hh"
#include "ddi.hh"

#include "ss.hh"
#include "uct.hh"
#include "lander.hh"
#include "hoot.hh"
#include "lqr.hh"

#include "chopper.hh"

using namespace std;

DEFINE_int32(minquery, 128 , "Minimum number of queries for planning algorithm");
DEFINE_int32(maxquery, 4096 , "Maximum number of queries for planning algorithm");
DEFINE_int32(minaction, 5, "Minimum number of action discretization");
DEFINE_int32(maxaction, 50, "Maximum number of action discretization");
DEFINE_string(planner, "hoot","Planner to run in a domain");
DEFINE_string(domain, "ip", "Current domain to run experiments in"); 
DEFINE_bool(debug, false, "Turn on debugging, which prints state-action");

int main(int argc, char* argv[])
{
  /* Init Gflags */
  google::ParseCommandLineFlags(&argc, &argv, true);

  /* Create domain */
  Domain *domain;
  if(FLAGS_domain.find("ip") != string::npos) {
      domain = new IP(0.9);
  } else if(FLAGS_domain.find("ddi") != string::npos) {
      domain = new DDI(0.9);
  }

  /* Number of actions */
  for(int i=FLAGS_minaction; i<=FLAGS_maxaction; i+=10) { 

    /* Create mapper from domain to planner*/
    Chopper *chopper = new Chopper(domain, 20, i);

    /* Create and initialize planner */
    Planner *planner;
    if(FLAGS_planner.find("hoot") != string::npos) {
      planner = new HOOT(domain, chopper, 0.1);
    } else if(FLAGS_planner.find("uct") != string::npos) {
      planner = new UCT(domain, chopper, 0.1);
    } else if(FLAGS_planner.find("ss") != string::npos) {
      planner = new SS(domain, chopper, 0.1);
    }

    /* Initialize planner */
    planner->initialize();

    /* Initialize state/action variables */
    State s = domain->getInitialState();
    Action a;
    SARS *sars = NULL;

    /* Main experiment loop */
    for(int queries = FLAGS_minquery; queries <= FLAGS_maxquery; queries*=2) {

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

	/* Debugging */
	if(FLAGS_debug) {
	  cout << sars->s[0] << " " << sars->s[1] << " " << a[0] << endl;
	}
      
	/* Update stats */
	steps += 1;
	epReturn += sars->reward;

	/* Check for end conditions */
	if(steps > 200 || sars->terminal) {
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
      cout << queries << " " << i << " " << mean - bound << " " << mean << " " << mean + bound  << endl;

    } // end for 

    delete planner;
    delete chopper;

  }

  return 0;
}
