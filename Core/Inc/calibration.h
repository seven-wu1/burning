#ifndef __CALIBRATION_H
#define __CALIBRATION_H
#include "main.h"

float ADC_GetValue(void);
float GetValue(int N);
float firstOrderFilter(float newValue, float oldValue, float a);
float GetValue2(int N);
#endif



