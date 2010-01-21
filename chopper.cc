/* Implementation dependencies */
#include "chopper.hh"

/*
 *
 */
Chopper::Chopper(Domain *d) : domain(d)
{
  /* Store ranges locally */
  maxStateRange = domain->getMaximumStateRange();
  minStateRange = domain->getMinimumStateRange();
  maxActionRange = domain->getMaximumActionRange();
  minActionRange = domain->getMinimumActionRange();

  zero.resize(domain->getActionDimension());
  one.resize(domain->getActionDimension());
  std::fill(zero.begin(), zero.end(), 0.0);  
  std::fill(one.begin(), one.end(), 1.0);  
}

/*
 *
 */
std::vector<int> Chopper::discretizeState(State s)
{
  std::vector<int> ds;
 
  int temp;
  for(unsigned int i=0; i<s.size(); i++) {
    temp = (int) floor(stateGrid / (maxStateRange[i] - minStateRange[i]) * (s[i] - minStateRange[i]));
    ds.push_back(temp);
  }

  return ds;
}

/*
 *
 */
int Chopper::discretizeAction(Action a)
{ 
  int id = 0;
  int temp;
  for(unsigned int i=0; i<a.size(); i++) {
    id *= actionGrid;

    temp = (int) floor(actionGrid / (maxActionRange[i] - minActionRange[i]) * (a[i] - minActionRange[i]));
    /* Handle upper end */
    if(temp == actionGrid) {
      temp = temp - 1;
    }

    id += temp;
    
  }

  return temp;
}

/*
 *
 */
Action Chopper::scaledownAction(Action a)
{
  Action out;
  
  double temp;
  for(unsigned int i=0; i<a.size(); i++) {
    temp = ((1.0 - 0.0) / (maxActionRange[i] - minActionRange[i])) * (a[i] - minActionRange[i]);
    out.push_back(temp);
  }

  return out;
}

/*
 *
 */
Action Chopper::scaleupAction(Action a)
{
  Action out;
  
  double temp;
  for(unsigned int i=0; i<a.size(); i++) {
    temp = ((maxActionRange[i] - minActionRange[i]) / (1.0 - 0.0)) * a[i] + minActionRange[i];
    out.push_back(temp);
  }

  return out;
}



/*
 *
 */
Action Chopper::continuousAction(int a)
{
  Action action;

  /* Convert to tuple of continuous numbers */
  int temp;
  double u;
  unsigned int i = 0;
  for(i = 0; i < maxActionRange.size()-1; i++) {
    temp = a % actionGrid;
    u = (maxActionRange[i] - minActionRange[i]) * a / (actionGrid - 1) + minActionRange[i];
    action.push_back(u);
    a = (a - temp) / actionGrid;
  }

  u = (maxActionRange[i] - minActionRange[i]) * a / (actionGrid - 1) + minActionRange[i];
  action.push_back(u);
  
  return action;
}

