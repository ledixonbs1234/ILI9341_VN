#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "stm32f1xx_hal.h"

typedef enum
{
    PULSE_NUMBER,
    PULSE_FRE,
    PULSE_PULSE
} Tan_so;

void readEncoderISR();
void thietLapXungRa();
void xuatXung();
void readE(uint16_t GPIO_pin);


#endif