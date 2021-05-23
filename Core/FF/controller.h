#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "stm32f1xx_hal.h"

void readEncoderISR();
void thietLapXungRa();
void xuatXung();
void readE(uint16_t GPIO_pin);


#endif