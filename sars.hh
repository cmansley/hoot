/*
 * Code by Chris Mansley
 */

#ifndef SARS_HH
#define SARS_HH

/* Definition dependencies */
#include <string>
#include <fstream>

#include "state.hh"
#include "action.hh"

class SARS
{
public:
  /** Constructor */
  SARS(int sd, int ad) { s.resize(sd); a.resize(ad); s_prime.resize(sd); reward = 0.0; terminal = false; }

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

  /** Overload output operator */
  friend std::ostream& operator<<(std::ostream &out, const SARS &sars);

  /** Overload input operator */
  friend std::istream& operator>>(std::istream &in, SARS &sars);
};

#endif //SARS_HH
