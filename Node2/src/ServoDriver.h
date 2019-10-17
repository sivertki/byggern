#ifndef _SERVO_DRIVER
#define _SERVO_DRIVER

void servoInit();
void setDutyCycle(uint8_t controlIn);
uint16_t getScaledSensorValue(uint8_t controlIn); //TODO remove from here

#endif
