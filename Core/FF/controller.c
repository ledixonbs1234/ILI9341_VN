#include "controller.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"
#include "stdio.h"

int encoderVal = 0;
int oldEncoderVal = 0;
uint32_t compare = 999;
extern TIM_HandleTypeDef htim4;

typedef enum
{
    PULSE_NUMBER,
    PULSE_FRE,
    PULSE_PULSE
} Tan_so;

Tan_so tan_so = PULSE_NUMBER;
uint8_t cheDoNumber = 1;
uint16_t setNumber = 10;
uint16_t setTanSo = 0;
uint8_t setPulse = 50;

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
    case GPIO_PIN_4:
        //Neu phim nay duoc nhan
        if (tan_so == PULSE_NUMBER && cheDoNumber < 3)
        {
            cheDoNumber += 1;
        }
        else
        {
            cheDoNumber = 1;
            tan_so = PULSE_NUMBER;
        }
        break;
    case GPIO_PIN_5:
        tan_so = PULSE_FRE;
        if (setTanSo == 0)
            setTanSo = 1;
        else
            setTanSo = 0;
        break;
    case GPIO_PIN_6:
        //cong tru xung
        tan_so = PULSE_PULSE;

        break;
    case GPIO_PIN_7:
        break;

    default:
        break;
    }
}

void xuLyTinHieu(uint8_t isHigh)
{
    switch (tan_so)
    {
    case PULSE_NUMBER:
        switch (cheDoNumber)
        {
        case 1:
            if (isHigh)
                setNumber++;
            else if (setNumber > 1)
            {
                setNumber--;
            }

            break;
        case 2:
            if (isHigh)
                setNumber += 10;
            else if (setNumber > 11)
                setNumber -= 10;

            break;
        case 3:
            if (isHigh)
                setNumber += 100;
            else if (setNumber > 101)
                setNumber -= 100;
            break;

        default:
            break;
        }

        break;
    case PULSE_FRE:

        break;
    case PULSE_PULSE:
        if (isHigh)
            setPulse++;
        else
            setPulse--;

        break;

    default:
        break;
    }
}

void thietLapXungRa()
{
    compare = encoderVal * 2 - 1;
    __HAL_TIM_SET_AUTORELOAD(&htim4, compare);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, compare / 2 + 1);
}

void readEncoderISR()
{
    static uint8_t lastPos = 0x00;

    uint8_t aNow = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
    uint8_t bNow = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);

    uint8_t posNow = aNow << 1 | bNow;
    if ((lastPos == 0b01) && (posNow == 0b11))
        encoderVal++;
    else if ((lastPos == 0b11) && (posNow == 0b10))
        encoderVal++;
    else if ((lastPos == 0b10) && (posNow == 0b00))
        encoderVal++;
    else if ((lastPos == 0b00) && (posNow == 0b01))
        encoderVal++;
    else if ((lastPos == 0b00) && (posNow == 0b10))
        encoderVal--;
    else if ((lastPos == 0b10) && (posNow == 0b11))
        encoderVal--;
    else if ((lastPos == 0b11) && (posNow == 0b01))
        encoderVal--;
    else if ((lastPos == 0b01) && (posNow == 0b00))
        encoderVal--;
    lastPos = posNow;
    if (encoderVal != oldEncoderVal)
    {
        if (encoderVal - oldEncoderVal > 0)
            xuLyTinHieu(1);
        else
            xuLyTinHieu(0);
        oldEncoderVal = encoderVal;

        thietLapXungRa();
        // uprintNumber(encoderVal);
    }
}
