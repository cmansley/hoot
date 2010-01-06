/*
 * Code by Chris Mansley
 */
#include <iostream>
#include <cmath>

#include "hoot.hh"

/*
 *
 */
HOOT::HOOT(Domain *d, double epsilon) : MCPlanner(d, epsilon)
{
}

/*
 *
 */
void HOOT::initialize()
{
}

/*
 *
 */
void HOOT::updateValue(int depth, SARS *sars, double qvalue)
{
  /* Create vector of ints for state, action and depth */
  std::vector<int> sd = discretizeState(sars->s);
  sd.push_back(depth);

  /* Repair HOO tree */
  repairTree(HOOS[sd], sars->a, qvalue);
}

/*
 *
 */
Action HOOT::selectAction(State s, int depth, bool greedy)
{
  /* Create vector of ints for state, action and depth */
  std::vector<int> sd = discretizeState(s);
  sd.push_back(depth);

  /* Pick action using HOO */
  Action a;
  if(HOOS.find(sd) != HOOS.end()) {
    a = HOOS[sd]->bestAction();
  } else {
    HOOS[sd] = new HOO();
    a = HOOS[sd]->bestAction();
  }

  return a;
}
