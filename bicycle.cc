/* Implementation dependencies */
#include <iostream>
#include <algorithm>
#include <cmath>

#include "bicycle.hh"

const double Bicycle::dt = 0.01; // 50 ms update

const double Bicycle::v=(10.0/3.6);  /* 10 km/h in m/s */
const double Bicycle::g=9.82;
const double Bicycle::dCM=0.3;
const double Bicycle::c=0.66;
const double Bicycle::h=0.94;
const double Bicycle::Mc=15.0;
const double Bicycle::Md=1.7;
const double Bicycle::Mp=60.0;
const double Bicycle::M=(Mc + Mp);
const double Bicycle::R=0.34;          /* tyre radius */
const double Bicycle::sigma_dot=(((double) v) /R);
const double Bicycle::I_bike=((13.0/3)*Mc*h*h + Mp*(h+dCM)*(h+dCM));
const double Bicycle::I_dc=(Md*R*R);
const double Bicycle::I_dv=((3.0/2)*Md*R*R);
const double Bicycle::I_dl=((1.0/2)*Md*R*R); 
const double Bicycle::l=1.11;     /* distance between the point where the front and back tyre touch the ground */
const double Bicycle::mypi = acos(-1);
const double Bicycle::x_goal=1000.0;
const double Bicycle::y_goal=0.0;
const double Bicycle::radius_goal=10.0;

/*!
 *
 */
Bicycle::Bicycle(double gamma) : stateDimension(5), actionDimension(2)
{
  /* Initialize our initial state */
  initialState.resize(stateDimension);
  std::fill(maxStateRange.begin(), maxStateRange.end(), 0.0);

  /* Create max and min state range */
  maxStateRange.resize(stateDimension);
  minStateRange.resize(stateDimension);

  maxStateRange[0] = mypi;
  maxStateRange[1] = 5.0;
  maxStateRange[2] = mypi/15;
  maxStateRange[3] = 1.0;
  maxStateRange[4] = 5.0;
  
  minStateRange[0] = -mypi;
  minStateRange[1] = -5.0;
  minStateRange[2] = -mypi/15;
  minStateRange[3] = -1.0;
  minStateRange[4] = -5.0;
  
  /* Create max and min action range */
  maxActionRange.resize(actionDimension);
  minActionRange.resize(actionDimension);

  std::fill(maxActionRange.begin(), maxActionRange.end(), 2.0);
  std::fill(minActionRange.begin(), minActionRange.end(), -2.0);

  /* Initialize gamma */
  this->gamma = gamma;
}

/*!
 *
 */
SARS *Bicycle::step(State s, Action a)
{
  SARS *sars = new SARS(stateDimension, actionDimension);

  sars->s = s;
  sars->a = a;

  
  double endsim;
  double max_noise = noise;
  dynamics(sars->s_prime, &sars->reward, &endsim, sars->s, sars->a, 2, &max_noise);

  /* 
   * Record the terminal status
   */
  if (endsim > 0.0)
    sars->terminal = true;
  else
    sars->terminal = false;

  /* 
   * Rescale reward the reward function to zero to one. This allows us
   * to standardize our algorithms to match most theoretical work
   */
  //sars->reward = 0; /* Normalize me */

  return sars;
}

/*!
 *
 */
void Bicycle::dynamics(State &nextstate, double *reward, double *endsim, State &istate,  Action &action, int to_do, double *maxnoise)
{
  double omega, omega_dot, omega_d_dot,
    theta, theta_dot, theta_d_dot;
  double T, d;
  double rCM, rf, rb;
  double phi;
  double noise;

  theta = istate[0];
  theta_dot = istate[1];
  omega = istate[2];
  omega_dot = istate[3];
  omega_d_dot = istate[4];
  
  T = action[0];
  d = action[1];

  /*
  // Noise in steering
  //    noise = ( (double) (random() % ((long) pow(2,30)) ) ) / pow(2,30); 
  //    T = T + 1.0 * (noise * 2 - 1);

  // Noise in displacement
  */
  noise = ( (double) (random() % ((long) pow(2,30)) ) ) / pow(2,30); 
  noise = noise*2 - 1;
  d = d + *maxnoise * noise; /* Max noise is 2 cm */


  if (theta == 0) {
    rCM = rf = rb = 9999999; /* just a large number */
  } else {
    rCM = sqrt(pow(l-c,2) + l*l/(pow(tan(theta),2)));
    rf = l / fabs(sin(theta));
    rb = l / fabs(tan(theta));
  } /* rCM, rf and rb are always positiv */
  
  /* Main physics eq. in the bicycle model coming here: */
  phi = omega + atan(d/h);
  omega_d_dot = ( h*M*g*sin(phi) 
                  - cos(phi)*(I_dc*sigma_dot*theta_dot 
		              + sign(theta)*v*v*(Md*R*(1.0/rf + 1.0/rb) 
						 +  M*h/rCM) )
		  ) / I_bike;
  theta_d_dot =  (T - I_dv*omega_dot*sigma_dot) /  I_dl;
  
  /*--- Eulers method ---*/
  omega_dot += omega_d_dot * dt;
  omega     += omega_dot   * dt;
  theta_dot += theta_d_dot * dt;
  theta     += theta_dot   * dt;
  
  if (fabs(theta) > 1.3963) { /* handlebars cannot turn more than 
				 80 degrees */
    theta = sign(theta) * 1.3963;
  }
    
  nextstate[0] = theta; 
  nextstate[1] = theta_dot;
  nextstate[2] = omega;
  nextstate[3] = omega_dot;
  nextstate[4] = omega_d_dot;

  /*-- Calculation of the reward  signal --*/

  //*reward = sqr(old_omega*15/mypi) - sqr(omega*15/mypi);
  // /*
  //  *reward = (fabs(old_omega) - fabs(omega))*15/mypi;
  //  *reward = ((old_omega)*(old_omega) - (omega * omega))*15/mypi;
  //  *reward = exp(-fabs(old_omega*15/mypi)) - exp(-fabs(omega*15/mypi));
  //  */

  if (fabs(omega) > (mypi/15)) { /* the bike has fallen over */
    *endsim =  1.0;
    *reward = 0.0;
    /* a good place to print some info to a file or the screen */  
  } else {
    *endsim = 0.0;
    /*
    // 0.0008 turns away from goal
    // 0.008 crashes
    // 0.08 worked well before
    // 0.01 with discount 0.81 works
    */

    //*reward += (lastdtg - dtg) * 0.01;
    *reward = 1.0;
    /*
    //    *reward += (sign(lastdtg-dtg)*sqr(lastdtg - dtg)) * 0.35;
    */
  }

  return;
  
}

/*!
 *
 */
double Bicycle::sign(double x)
{
  if (x==0.0)
    return 0.0;
  else if (x>0.0)
    return +1.0;
  else 
    return -1.0;
}

