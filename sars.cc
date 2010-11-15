/*
 * Code by Chris Mansley
 */
#include "sars.hh"

/*!
 * Output operator for the SARS class
 */
std::ostream& operator<<(std::ostream &out, const SARS &sars)
{
  /* Print state */
  for(State::const_iterator it = sars.s.begin(); it != sars.s.end(); ++it) {
    out << *it << ",";
  }

  /* Print action */
  for(Action::const_iterator it = sars.a.begin(); it != sars.a.end(); ++it) {
    out << *it << ",";
  }

  /* Print reward */
  out << sars.reward << ",";
  
  /* Print next state */
  for(State::const_iterator it = sars.s_prime.begin(); it != sars.s_prime.end(); ++it) {
    out << *it << ",";
  }

  /* Print out terminal */
  out << sars.terminal;

  return out;
}
