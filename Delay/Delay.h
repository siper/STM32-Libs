#include <stm32f10x.h>
#define	F_APB1	24000000

void Delay_ms(unsigned int delay);
void Delay_us(unsigned int delay);

//Не забыть включить TIM7 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
