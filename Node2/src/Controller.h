#define PID_P 1
#define PID_I 1
#define PID_D 1

#include <stdio.h>

void CONTROLLER_Init();
short int CONTORLLER_calculateError(short int reference_value, short int  measured_value);
short int CONTROLLER_calculateOutput(short int error);
void CONTROLLER_setControlTerms(float p, float i, float d);
int getTerm(int n);
