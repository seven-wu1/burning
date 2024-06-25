#ifndef __BASE_H
#define __BASE_H


#include "main.h"
#include "calibration.h"
extern uint8_t   Help_Flag;
extern uint8_t   Busy_Flag;
void USART_protocol_parsing(void);
void LED_Yellow(void);
void LED_GREEN(void);
void LED_RED(void);
void LED_DISPALY(void);
void SET_VAL(void);
void reset(void);

#endif


