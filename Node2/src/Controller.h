#define PID_P 1
#define PID_I 1
#define PID_D 1

#include <stdio.h>

void CONTROLLER_Init();
//short int CONTORLLER_calculateError(short int  measured_value);
//short int CONTROLLER_calculateOutput(short int error);
void CONTROLLER_setControlTerms(float p, float i, float d);
void CONTROLLER_setReference(short int in);
void CONTROLLER_updateController();
//ISR(TIMER3_OVF_vect);

int getTerm(int n);
