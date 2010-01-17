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
void HOOT::reset()
{
  /* Clear all HOOs before clearing pointers */
  for(boost::unordered_map<std::vector<int>, HOO*>::const_iterator it = HOOS.begin(); it != HOOS.end(); ++it) {
    it->second->clear();
  }

  HOOS.clear();
}

/*
 *
 */
void HOOT::updateValue(int depth, SARS *sars, double qvalue)
{
  /* Create vector of ints for state, action and depth */
  std::vector<int> sd = domain->discretizeState(sars->s);
  sd.push_back(depth);

  /* Insert value into HOO tree */
  HOOS[sd]->insertAction(sars->a, qvalue);
}

/*
 *
 */
Action HOOT::selectAction(State s, int depth, bool greedy)
{
  /* Create vector of ints for state, action and depth */
  std::vector<int> sd = domain->discretizeState(s);
  sd.push_back(depth);

  /* Pick action using HOO */
  Action a;
  if(HOOS.find(sd) != HOOS.end()) {
    a = HOOS[sd]->queryAction();
  } else {
    HOOS[sd] = new HOO(domain);
    a = HOOS[sd]->queryAction();
  }

  return a;
}

