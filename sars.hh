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
  SARS(int sd, int ad) { s.resize(sd); a.resize(ad); s_prime.resize(sd); }

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
