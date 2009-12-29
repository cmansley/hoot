/*
 * Code by Chris Mansley
 */

#ifndef SARS_HH
#define SARS_HH

/* Definition dependencies */
#include <string>

#include "state.hh"
#include "action.hh"

class SARS
{
public:
  /** Constructor */
  SARS() { s.resize(2); a.resize(1); s_prime.resize(2); }

  /** Destructor */
  ~SARS() { };

  /** Current state */
  State s;

  /** Action taken */
  Action a;

  /** Reward signal */
  double reward;

  /** Next state */
  State s_prime;

  /** Is this a terminal state */
  bool terminal;

};

#endif //SARS_HH
