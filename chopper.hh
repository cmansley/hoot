/*
 * Code by Chris Mansley
 */

#ifndef CHOPPER_HH
#define CHOPPER_HH

/* Definition dependencies */
#include <cmath>

#include "state.hh"
#include "action.hh"
#include "domain.hh"

class Chopper
{
public:
  /** Constructor */
  Chopper(Domain *d);
 
  /** Destructor */
  ~Chopper( ) { }

  /** Convert domain continuous to discrete state */
  std::vector<int> discretizeState(State s);

  /** Convert domain continuous to discrete action */
  int discretizeAction(Action a);
  /* This is fundementally different from discretizeState for the
     following reason: most of the time you need to perform the max
     over actions, which is easier if you can just iterate over the
     ints from 0 to maxAction instead of some other scheme */

  /** Convert domain continuous to continuous state */
  State rescaleState(State s);

  /** Convert domain continuous to continuous action */
  Action rescaleAction(Action a);

  /** Concert discrete state back to continuous state */

  /** Convert discrete action to domain continuous action */
  Action continuousAction(int a);

  /** Return number of discrete actions offered by this chopper */
  int getNumDiscreteActions() { return (int)pow(actionGrid, maxActionRange.size()); }

private:
  /** Storage for domain */
  Domain *domain;

  /** State discretization by dimension */
  //std::vector<int> stateGrid;
  static const int stateGrid = 20;
  
  /** Action discretization by dimension */
  //std::vector<int> actionGrid;
  static const int actionGrid = 20;

  /** Local domain storage */
  std::vector<double> maxStateRange; 
  std::vector<double> minStateRange;
  std::vector<double> maxActionRange;
  std::vector<double> minActionRange;

};

#endif // CHOPPER_HH
