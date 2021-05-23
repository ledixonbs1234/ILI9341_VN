#include "controller.h"
#include "stm32f1xx_hal_tim.h"
#include "stdio.h"

int encoderVal = 0;
int oldEncoderVal = 0;
float compare = 999;
extern TIM_HandleTypeDef htim4;



Tan_so tan_so = PULSE_NUMBER;
uint8_t cheDoNumber = 1;
uint16_t setNumber = 39;
uint16_t _setNumberOLD = 0;
uint16_t setTanSo = 0;
uint16_t _setTanSoOLD = 0;
uint8_t setPulse = 50;
uint8_t _setPulseOLD = 0;
uint8_t toggleEncoder = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(GPIO_Pin);
    switch (GPIO_Pin)
    {
    case GPIO_PIN_0:
    case GPIO_PIN_1:
        // readEncoderISR();
        readE(GPIO_Pin);
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
    xuatXung();
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
uint32_t giatri = 0;
float tinhxung = 0;

uint8_t chiaPre = 0;
uint32_t preXung = 72000000;

uint32_t countTest = 0;
uint32_t checkGiatri = 0;
uint32_t cnt;
uint32_t checkPulse;
uint32_t giatri;
uint32_t test1 = 0;
uint32_t test2 = 0;

void kiemtraxung()
{
    //xu ly tin hieu xung ra
    //kiem tra du lieu  co cap nhat khong
    if (setNumber == _setNumberOLD && setTanSo == _setTanSoOLD && _setPulseOLD == setPulse)
    {
        return;
    }
    _setPulseOLD = setPulse;
    _setNumberOLD = setNumber;
    _setTanSoOLD = setTanSo;

    countTest = 0;
    for (uint32_t i = 1; i < 65000; i++)
    {
        chiaPre = preXung % i;
        if (chiaPre == 0)
        {
            if (setTanSo)
            {
                giatri = setNumber * 1000;
            }
            else
            {
                giatri = setNumber * 1;
            }
            checkGiatri = (preXung / i) % giatri;
            if (checkGiatri == 0)
            {
                cnt = ((preXung / i) / giatri);
                if (cnt < 65000)
                {
                    checkPulse = cnt % 100;
                    if (checkPulse == 0)
                    {
                        test1 = i;
                        test2 = cnt;

                        countTest++;
                        break;
                    }
                }
            }
        }
    }
}

void xuatXung()
{
    HAL_Delay(10);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_15);
    __HAL_TIM_SET_PRESCALER(&htim4, test1 -1);
    __HAL_TIM_SET_AUTORELOAD(&htim4, test2 - 1);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, (test2 / 100) * setPulse);
}

uint8_t countRead = 0;
uint8_t oldCountRead = 0;
uint8_t isWaiting = 0;

uint32_t time = 0;
uint32_t currentTime = 0;
uint8_t test = 0;
uint8_t isChanged = 0;
uint16_t lastPin = 0;

void readE(uint16_t GPIO_pin)
{
    currentTime = HAL_GetTick();

    static uint8_t lastPos = 0x00;

    uint8_t aNow = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
    uint8_t bNow = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);

    uint8_t tempNow = aNow << 1 | bNow;
    if (tempNow == 0b10)
    {
        lastPos = tempNow;
    }
    if (tempNow == 0b01)
    {
        lastPos = tempNow;
    }

    if (lastPin == GPIO_pin)
    {

        return;
    }
    lastPin = GPIO_pin;

    if (currentTime - time < 5)
    {
        time = currentTime;
        return;
    }
    time = currentTime;
    if (tempNow == 0b00 && lastPos == 0b10)
    {
        countRead++;
    }

    else if ((lastPos == 0b11) && (tempNow == 0b10))
        countRead++;

    else if (tempNow == 0b11 && lastPos == 0b10)
    {
        countRead++;
    }
    else if ((lastPos == 0b11) && (tempNow == 0b01))
        countRead--;

    else if ((lastPos == 0b00) && (tempNow == 0b01))
        countRead++;
    else if ((lastPos == 0b00) && (tempNow == 0b10))
        countRead--;

    else if (tempNow == 0b00 && lastPos == 0b01)
    {
        countRead--;
    }
    else if (tempNow == 0b11 && lastPos == 0b01)
    {
        countRead--;
    }
    if (countRead != oldCountRead)
    {

        if (countRead - oldCountRead > 0)
            xuLyTinHieu(1);
        else
            xuLyTinHieu(0);
        kiemtraxung();
        //thietLapXungRa();
        oldCountRead = countRead;
        // uprintNumber(encoderVal);
    }

    // if (tempNow == 0b00 && isWaiting && lastPos == 0b01)
    // {
    //     isWaiting = 0;
    //     encoderVal--;
    //     countRead--;
    // }
    // if (tempNow == 0b11 && isWaiting && lastPos == 0b10)
    // {
    //     isWaiting = 0;
    //     encoderVal--;
    //     countRead--;
    // }

    // uint8_t posNow = aNow << 1 | bNow;
    // if(posNow == 0b00 && lastPos == 0b10){
    // encoderVal++;
    // }
}

void readEncoderISR()
{
    static uint8_t lastPos = 0x00;

    uint8_t aNow = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
    uint8_t bNow = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);

    uint8_t posNow = aNow << 1 | bNow;
    if ((lastPos == 0b01) && (posNow == 0b11))
        encoderVal++;
    // else if ((lastPos == 0b11) && (posNow == 0b10))
    // encoderVal++;
    else if ((lastPos == 0b10) && (posNow == 0b00))
        encoderVal++;
    // else if ((lastPos == 0b00) && (posNow == 0b01))
    // encoderVal++;
    // else if ((lastPos == 0b00) && (posNow == 0b10))
    // encoderVal--;
    else if ((lastPos == 0b10) && (posNow == 0b11))
        encoderVal--;
    // else if ((lastPos == 0b11) && (posNow == 0b01))
    // encoderVal--;
    else if ((lastPos == 0b01) && (posNow == 0b00))
        encoderVal--;
    lastPos = posNow;
    if (encoderVal != oldEncoderVal)
    {

        countRead++;
        if (encoderVal - oldEncoderVal > 0)
            xuLyTinHieu(1);
        else
            xuLyTinHieu(0);
        oldEncoderVal = encoderVal;
        thietLapXungRa();
        // uprintNumber(encoderVal);
    }
}
