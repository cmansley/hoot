/*
 * Code by Chris Mansley
 */
#include <iostream>
#include <cmath>

#include "hoot.hh"

/*
 *
 */
HOOT::HOOT(Domain *d, Chopper *c, double epsilon) : MCPlanner(d, c, epsilon)
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

void HOOT::print(State s)
{
  /* Create vector of ints for state, action and depth */
  std::vector<int> sd = chopper->discretizeState(s);
  sd.push_back(0);

  HOOS[sd]->print();
}

/*
 *
 */
void HOOT::updateValue(int depth, SARS *sars, double qvalue)
{
  /* Create vector of ints for state, action and depth */
  std::vector<int> sd = chopper->discretizeState(sars->s);
  sd.push_back(depth);

  /* Scale down into zero-one action space*/
  Action a = chopper->scaledownAction(sars->a);

  /* Insert value into HOO tree */
  HOOS[sd]->insertAction(a, qvalue);
}

/*
 *
 */
Action HOOT::selectAction(State s, int depth, bool greedy)
{
  /* Create vector of ints for state, action and depth */
  std::vector<int> sd = chopper->discretizeState(s);
  sd.push_back(depth);

  /* Pick action using HOO */
  Action a;
  if(HOOS.find(sd) != HOOS.end()) {
    a = HOOS[sd]->queryAction(greedy);
  } else {
    HOOS[sd] = new HOO(domain, chopper);
    a = HOOS[sd]->queryAction(greedy);
  }

  /* Convert back to original action space */
  Action b = chopper->scaleupAction(a);

  return b;
}

