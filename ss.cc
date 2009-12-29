/* Implementation dependencies */
#include <iostream>
#include <cmath>

#include "ss.hh"

/*!
 *
 */
SS::SS(Domain *d, double epsilon) : Planner(d, epsilon)
{
  
}

/*!
 *
 */
void SS::setMaxQueries(int queries) 
{ 
  maxQueries = queries; 
  
  int N = queries;
  int A = domain->getNumActions();

  C = 1;
  H = (int) (log(N*A*C-N+1)/log(A*C) - 1);
  
}


/*!
 *
 */
Action SS::plan(State s)
{
  /* Compute Q-values and pick best action */
  std::vector<double> Q = estimateQ(H, s);

  std::vector<double>::iterator pos = max_element(Q.begin(), Q.end());

  /* Get action */
  int a = pos-Q.begin();

  Action act(1);
  act[0] = a;

  return act;
}

/*!
 *
 */
std::vector<double> SS::estimateQ(int h, State s)
{
  std::vector<double> Q(domain->getNumActions());

  /* Initialize Q to zero */
  std::fill(Q.begin(), Q.end(), 0.0);

  /* Termination of recursion */
  if(h == 0) {
    return Q;
  }

  double gamma = domain->getDiscountFactor();

  /* Loop over actions compute Q values */
  SARS *sars = NULL;
  Action a(1);
  double sum, sum_rew;
  for(unsigned int i = 0; i < Q.size(); i++) {

    sum = 0.0;
    sum_rew = 0.0;
    a[0] = i;

    /* Average over C samples*/
    for(int k = 0; k < C; k++) {
      sars = domain->simulate(s, a);
      sum += estimateV(h - 1, sars->s_prime);
      sum_rew += sars->reward;
      delete sars;
    }

    /* Compute estimated Q-value for this action */
    Q[i] = sum_rew / C + gamma * sum / C;
  }

  return Q;
}

/*!
 *
 */
double SS::estimateV(int h, State s)
{
  double min;

  /* Compute Q values and find the max */
  std::vector<double> Q = estimateQ(h, s);
  min = *max_element( Q.begin(), Q.end());

  return min;
}

