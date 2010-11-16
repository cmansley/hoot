#include <iostream>
#include <gflags/gflags.h>

#include "ccl.hh"
#include "ip.hh"
#include "di.hh"
#include "ddi.hh"
#include "bicycle.hh"

#include "ss.hh"
#include "uct.hh"
#include "lander.hh"
#include "hoot.hh"
#include "lqr.hh"
#include "sarsa.hh"

#include "chopper.hh"

using namespace std;

DEFINE_int32(minquery, 128 , "Minimum number of queries for planning algorithm");
DEFINE_int32(maxquery, 4096 , "Maximum number of queries for planning algorithm");
DEFINE_int32(minaction, 5, "Minimum number of action discretization");
DEFINE_int32(maxaction, 50, "Maximum number of action discretization");
DEFINE_int32(stepaction, 10, "Step size of action discretization");
DEFINE_string(planner, "hoot","Planner to run in a domain");
DEFINE_string(domain, "ip", "Current domain to run experiments in"); 
DEFINE_bool(debug, false, "Turn on debugging, which prints state-action");
DEFINE_bool(print, false, "Print data structure at initial state");
DEFINE_double(noise, 10.0, "Noise parameter");
DEFINE_int32(dim, 1, "Dimension parameter");
DEFINE_int32(runs, 20, "Number of runs to average over");

int main(int argc, char* argv[])
{
  int iterations;
  
  /* Init Gflags */
  google::ParseCommandLineFlags(&argc, &argv, true);

  /* Create domain */
  Domain *domain;
  if(FLAGS_domain.find("ip") != string::npos) {
      domain = new IP(0.9);
      domain->setParam(FLAGS_noise, 0);
      iterations = 999;  
  } else if(FLAGS_domain.find("ddi") != string::npos) {
      domain = new DDI(0.9);
      domain->setParam(0.0, FLAGS_dim);
      iterations = 200;     
  } else if(FLAGS_domain.find("bicycle") != string::npos) {
      domain = new Bicycle(0.99);
      domain->setParam(FLAGS_noise, 0);
      // iterations = 72000;     
      iterations = 2000;
  }


  /* Number of actions */
  for(int i=FLAGS_minaction; i<=FLAGS_maxaction; i+=FLAGS_stepaction) { 

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
    } else if(FLAGS_planner.find("lqr") != string::npos) {
      planner = new LQR(domain, chopper, 0.1);      
    } else if(FLAGS_planner.find("sarsa") != string::npos) {
      planner = new SARSA(domain, chopper, 0.1);
    }

    /* Initialize planner */
    planner->initialize("log.txt");

    /* Initialize state/action variables */
    State s = domain->getInitialState();
    Action a;
    SARS *sars = NULL;

    /* Dump data structure */
    if(FLAGS_print) {
      planner->setMaxQueries(64000);
      a = planner->plan(s);
      planner->print(s);
    } else {

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
	while(n < FLAGS_runs) {

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
	  if(steps > iterations || sars->terminal) {
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
	cout << queries << " " << i << " " << mean - bound << " " << mean << " " << mean + bound  << " " << FLAGS_noise << " " << FLAGS_dim << endl;

      } // end for 
    }
    
    /* Clean up */
    delete planner;
    delete chopper;

  }

  return 0;
}
