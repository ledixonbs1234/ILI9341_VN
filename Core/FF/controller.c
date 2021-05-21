#include "controller.h"
#include "stm32f1xx_hal.h"

int encoderVal = 0;
int oldEncoderVal = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);
  switch (GPIO_Pin)
  {
  case GPIO_PIN_0:
  case GPIO_PIN_1:
      readEncoderISR();

      break;
  
  default:
      break;
  }
}


void readEncoderISR(){
  static uint8_t lastPos = 0x00;
  
  uint8_t aNow = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0);
  uint8_t bNow = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);
  
  uint8_t posNow = aNow <<1 | bNow;
    if((lastPos == 0b01) && (posNow == 0b11))
        encoderVal++;
    else if((lastPos == 0b11) && (posNow == 0b10))
        encoderVal++;
    else if((lastPos == 0b10) && (posNow == 0b00))
        encoderVal++;
    else if((lastPos == 0b00) && (posNow == 0b01))
        encoderVal++;
    else if((lastPos == 0b00) && (posNow == 0b10))
        encoderVal--;
    else if((lastPos == 0b10) && (posNow == 0b11))
        encoderVal--;
    else if((lastPos == 0b11) && (posNow == 0b01))
        encoderVal--;
    else if((lastPos == 0b01) && (posNow == 0b00))
        encoderVal--;
    lastPos = posNow;
  if(encoderVal != oldEncoderVal){
    oldEncoderVal = encoderVal;
    // uprintNumber(encoderVal);
  }
}


