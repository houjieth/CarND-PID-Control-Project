#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Kd, double Ki) {
  this->Kp = Kp;
  this->Kd = Kd;
  this->Ki = Ki;
}

void PID::UpdateError(double cte) {
  d_error = cte - p_error;
  p_error = cte;
  i_error = i_error + cte;
}

double PID::TotalError() {
  return Kp * p_error + Kd * d_error + Ki * i_error;
}

