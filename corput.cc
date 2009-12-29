/* Implementation dependencies */
#include <iostream>
#include <sstream>
#include <cmath>

#include "corput.hh"

/*!
 *
 */
Corput::Corput(Domain *d, double epsilon) : Planner(d, epsilon)
{
  maxDepth = 100;
}

/*!
 *
 */
Action Corput::plan(State s)
{
  /* Clear data structures */
  Nsad.clear();
  Nsd.clear();
  Q.clear();

  /* Do rollouts */
  int i = 0;
  while(i < 200) {
    search(0, s, false);
    i++;
  }

  return getBestAction(s);
}


double Corput::search(int depth, State s, bool terminal)
{
  double q;
  double gamma = domain->getDiscountFactor();

  /* If a leaf has been reached, return */
  if(terminal) {
    return 0.0;
  }

  /* If the maximum search depth has been reached return */
  if(depth > maxDepth) {
    return 0.0;
  }

  /* Select action */
  Action a = selectAction(s, depth);
  
  /* Simulate next action */
  SARS *sars = NULL;
  sars = domain->simulate(s, a);

  /* Backup rewards */
  q = sars->reward + gamma * search(depth + 1, sars->s_prime, sars->terminal);
  
  /* Update the stored values */
  updateValue(depth, sars, q);

  /* Clean up */
  delete sars;

  return q;
}

void Corput::updateValue(int depth, SARS *sars, double qvalue)
{  
  /* Construct vectors from state, action, depth */
  std::vector<int> sd = discretizeState(sars->s);
  std::vector<int> sad = sd;
  sd.push_back(depth);
  sad.push_back((int) sars->a[0]);
  sad.push_back(depth);

  /* Update counts */
  Nsd[sd] += 1;
  Nsad[sad] += 1;

  /* Compute mean of Q-values and insert into structure as
     necessary (Computation of mean by way of Knuth) */
  int n; double mean; double delta;
  if(Q.find(sad) != Q.end()){
    n = Nsad[sad];
    mean = Q[sad];
    delta = qvalue - mean;
    Q[sad] = mean + delta/n;
  } else {
    Q[sad] = qvalue;
  }

}

/*!
 *
 */
Action Corput::selectAction(State s, int depth)
{
  int k = domain->getNumActions();
  double vmax = 0.0;
  
  std::vector<double> qtemp(k);

  /* Construct vectors from state, action, depth */
  std::vector<int> sd = discretizeState(s);
  std::vector<int> sad = sd;
  sd.push_back(depth);
  sad.push_back(0);
  sad.push_back(depth);

  /* Compute Q-values for all actions */
  std::vector<int> maxActions;
  for(int i = 0; i<k; i++) {
    sad[2] = i;
    if(Q.find(sad) != Q.end()) {
      qtemp[i] = Nsad[sad];
    } else {
      qtemp[i] = vmax;
      maxActions.push_back(i);
    }
  }

  Action act(1);
  if(maxActions.empty()) {
    /* Compute max action */
    std::vector<double>::iterator pos = min_element(qtemp.begin(), qtemp.end());
    int a = pos-qtemp.begin();
    act[0] = a;
  } else {
    random_shuffle(maxActions.begin(), maxActions.end());
    act[0] = maxActions[0];
  }

  return act;
}

/*!
 *
 */
Action Corput::getBestAction(State s) 
{
  int k = domain->getNumActions();
  double vmax = 0.0;
  
  std::vector<double> qtemp(k);

  /* Construct vectors from state, action, depth */
  std::vector<int> sd = discretizeState(s);
  std::vector<int> sad = sd;
  sd.push_back(0);
  sad.push_back(0);
  sad.push_back(0);

  /* Compute Q-values for all actions */
  for(int i = 0; i<k; i++) {
    sad[2] = i;
    if(Q.find(sad) != Q.end()) {
      qtemp[i] = Q[sad];
    } else {
      qtemp[i] = vmax;
    }
  }

  /* Compute max action */
  std::vector<double>::iterator pos = max_element(qtemp.begin(), qtemp.end());
  Action act(1);
  int a = pos-qtemp.begin();
  act[0] = a;

  return act;
}

/*!
 *
 */
std::vector<int> Corput::discretizeState(State s)
{
  int numofgrids = 20;

  std::vector<int> ds;

  std::vector<double>::iterator maxItr = domain->getMaximumRange().begin();
  std::vector<double>::iterator minItr = domain->getMinimumRange().begin();
  std::vector<double>::iterator sItr = s.begin();

  while(sItr != s.end()) {
    ds.push_back( (int) floor( numofgrids/ (*maxItr-*minItr)*(*sItr-*minItr) )); 
    sItr++; minItr++; maxItr++;
  }

  return ds;
}
