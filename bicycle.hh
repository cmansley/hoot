/*
 * Code by Chris Mansley
 */

#ifndef BICYCLE_HH
#define BICYCLE_HH

/* Definition dependencies */

#include "domain.hh"

/*!
 *
 */
class Bicycle: public Domain
{
public:
  /** Constructor */
  Bicycle(double gamma);

  /** Destructor */
  ~Bicycle() { }

  /** Perform an interaction with the environment */
  SARS *step(State s, Action a);

  /** Get starting state from domain */
  State getInitialState( ) { return initialState; }

  /** Get discount factor for domain */
  double getDiscountFactor( ) { return gamma; }

  /** Get maximum range for action features */
  std::vector<double> getMaximumActionRange( ) { return maxActionRange; }

  /** Get minimum range for action features */
  std::vector<double> getMinimumActionRange( ) { return minActionRange; }

  /** Get maximum range for state features */
  std::vector<double> getMaximumStateRange( ) { return maxStateRange; }

  /** Get maximum range for state features */
  std::vector<double> getMinimumStateRange( ) { return minStateRange; }

  /** Get number of state dimensions */
  int getStateDimension( ) { return stateDimension; }

  /** Get number of action dimensions */
  int getActionDimension( ) { return actionDimension; }

  /** Set domain parameters */ /* This is ugly? */
  void setParam(double d, int i) { }

  /** Get maximum reward */
  double getRmax( ) { return rmax; }

  /** Get minimum reward */
  double getRmin( ) { return rmin; }

private:
  /** Store starting state */
  State initialState;

  /** Domain Parameters */
  std::vector<double> maxStateRange;
  std::vector<double> minStateRange;
  std::vector<double> maxActionRange;
  std::vector<double> minActionRange;
  int stateDimension;
  int actionDimension;
  static const double rmin = 0;
  static const double rmax = 1;

  /** Domain Properties */
  double gamma;

  /** Domain Specific */
  static const double dt;
  static const double noise;

  static const double v;
  static const double g;
  static const double dCM;
  static const double c;
  static const double h;
  static const double Mc;
  static const double Md;
  static const double Mp;
  static const double M;
  static const double R;
  static const double sigma_dot;
  static const double I_bike;
  static const double I_dc;
  static const double I_dv;
  static const double I_dl;
  static const double l;
  static const double mypi;
  static const double x_goal;
  static const double y_goal;
  static const double radius_goal;


  /** Domain Helpers */
  double sign(double x);
  double calc_dist_to_goal(double xf, double xb, double yf, double yb);
  double calc_angle_to_goal(double xf, double xb, double yf, double yb);
  double orig_calc_angle_to_goal(double xf, double xb, double yf, double yb);
  void dynamics(State &nextstate, double *reward, double *endsim, State &istate,  Action &action, int to_do, double *maxnoise);
  void getStart(State &nextstate);
  
  inline double sqr(double x) { return x*x; }

};

#endif // DI_HH
