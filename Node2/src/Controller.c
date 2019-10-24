#include "Controller.h"
#include "MotorDriver.h"
float K_i;
float K_p;
float K_d;
float T_PID;
short int error_sum;
short int last_error;

void CONTROLLER_Init() {
  CONTROLLER_setControlTerms(1,1,1);
  T_PID = 1;
  error_sum = 0;
}

short int CONTROLLER_calculateError(uint8_t reference_value, short int  measured_value) {
   return reference_value - measured_value;
 }

void CONTROLLER_setControlTerms(p, i, d) {
  K_p = p;
  K_i = i;
  K_d = d;
}

short int CONTROLLER_calculateOutput(short int error) {
  error_sum += error;
  printf("error sum: %hi\n\r", error_sum);

  float output = (K_p * error) + (T_PID * K_i * error_sum) + ((K_d/T_PID) * (error - last_error));

  last_error = error;
  return output;
}
