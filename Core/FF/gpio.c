#include "gpio.h"
#include "stm32f1xx_hal.h"

void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_AFIO_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);

	/*Configure GPIO pins : PC13 PC14 PC15 */
	GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : PA6 */
	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PB0 PB1 PB2 PB3
                           PB4 PB5 PB6 PB7
                           PB9 */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin : PA15 */
	GPIO_InitStruct.Pin = GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//Thiết lập kích hoạt interrupt tại xung lên và xung xuống
	SET_BIT(EXTI->RTSR, 0x0003);
	SET_BIT(EXTI->FTSR, 0x00FB);

	//Thiết lập clock cho xung interrupts
	//Setup EXTI0,EXTI1,EXTI3,EXTI4,EXTI5_9 to map to GPIOB
	SET_BIT(AFIO->EXTICR[0], 0x1011);
	SET_BIT(AFIO->EXTICR[1], 0x1111);

	//Cho phep ngat
	//Enable EXTI interrupts
	SET_BIT(EXTI->IMR, 0x0FB);

	//thiet dat yeu tien cho ngat
	//Set Encoder Priorities
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0x08, 0);
	HAL_NVIC_SetPriority(EXTI1_IRQn, 0x08, 0);
	HAL_NVIC_SetPriority(EXTI3_IRQn, 0x08, 0);
	HAL_NVIC_SetPriority(EXTI4_IRQn, 0x08, 0);
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0x08, 0);
	//Set Trigger Priorities
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0x06, 0);
	HAL_NVIC_SetPriority(ADC1_2_IRQn, 0x06, 0);
	//Set Timer Priority
	HAL_NVIC_SetPriority(TIM2_IRQn, 0x0A, 0);
	//Enable NVIC Interrupts
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	HAL_NVIC_EnableIRQ(ADC1_2_IRQn);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}
