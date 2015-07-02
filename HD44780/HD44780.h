#include <stm32f10x.h>

#define lcdPort GPIOC
#define RS GPIO_Pin_0
#define E  GPIO_Pin_1
#define D4 GPIO_Pin_2
#define D5 GPIO_Pin_3
#define D6 GPIO_Pin_4
#define D7 GPIO_Pin_5

void lcdPortInit();
void lcdInit();
void lcdCursorOff();
void lcdCursorOnBlinkOn();
void lcdCursorOnBlinkOff();
void lcdSendCommand(char code);
void lcdWriteText(char *text);
void lcdCls();
void lcdGoToXY(char x, char y);
void lcdWriteInt(int num);
void lcdWriteFloat(float num, int param);
