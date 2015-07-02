#include "HD44780.h"
#include <Delay.h>

//������� ������������� �������
void lcdInit()
{
	lcdPortInit();
	Delay_ms(40);
	lcdSendCommand(0x33);
	lcdSendCommand(0x32);
	lcdSendCommand(0x28); //4� ������ ���������, 2 ������
	lcdSendCommand(0x0C); //���������� �������
	lcdSendCommand(0x01); //������� ������
	Delay_ms(2);
}

//������� �������� �������� �� 4� ������� ����������
void lcdSendCommand(char code)
{
	//�������� ������� �������
	GPIO_ResetBits(lcdPort, D4|D5|D6|D7);
	if((code >> 4) & 0x01)
	{
		GPIO_SetBits(lcdPort, D4);
	}
	if((code >> 5) & 0x01)
	{
		GPIO_SetBits(lcdPort, D5);
	}
	if((code >> 6) & 0x01)
	{
		GPIO_SetBits(lcdPort, D6);
	}
	if((code >> 7) & 0x01)
	{
		GPIO_SetBits(lcdPort, D7);
	}
	GPIO_SetBits(lcdPort, E);
	Delay_ms(1);
	GPIO_ResetBits(lcdPort, E);
	Delay_ms(1);
	//�������� ������� �������
	GPIO_ResetBits(lcdPort, D4|D5|D6|D7);
	if((code >> 0) & 0x01)
	{
		GPIO_SetBits(lcdPort, D4);
	}
	if((code >> 1) & 0x01)
	{
		GPIO_SetBits(lcdPort, D5);
	}
	if((code >> 2) & 0x01)
	{
		GPIO_SetBits(lcdPort, D6);
	}
	if((code >> 3) & 0x01)
	{
		GPIO_SetBits(lcdPort, D7);
	}
	GPIO_SetBits(lcdPort, E);
	Delay_ms(1);
	GPIO_ResetBits(lcdPort, E);
	Delay_ms(1);
}

//������� �������� ������ �� �����
void lcdWriteText(char *text)
{
	GPIO_SetBits(lcdPort, RS);
	while(*text)
	{
		lcdSendCommand(*text++);
	}
	GPIO_ResetBits(lcdPort, RS);
}

//������� ������ ������ �����
void lcdWriteInt(int num)
{
	int n = 0, re = 0, i = 0;
	char numbers[] = {'0x30', '0x31', '0x32', '0x33', '0x34', '0x35', '0x36', '0x37', '0x38', '0x39'};
	int ui[9];
	i = num;
	if(num==0)
	{
		GPIO_SetBits(lcdPort, RS);
		lcdSendCommand(numbers[0]);
		GPIO_ResetBits(lcdPort, RS);
		return;
	}
	while(i)
	{
		i/=10;
		n++;
	}
	i = n - 1;
	while(num)
	{
		re = num%10;
		num = num/10;
		ui[i] = re;
		i--;
	}
	i = 0;
	while(n)
	{
		GPIO_SetBits(lcdPort, RS);
		lcdSendCommand(numbers[ui[i]]);
		GPIO_ResetBits(lcdPort, RS);
		n--;
		i++;
	}
}

//������� ������ ����� � ��������� ������, ��� num - �����, ������� ��������� �������, param - ����� ������ ����� �����
void lcdWriteFloat(float num, int param)
{
	int re1 = 0, re2 = 0, g = 0, t = 0.1;
	g = param;
	param = 1;
	while(g)
	{
		param *=10;
		g--;
	}
	if(num==0.0)
	{
		lcdWriteInt(0);
		lcdWriteText(".");
		lcdWriteInt(0);
		return;
	}
	re1 = num;
	re2 = (num*param)-(re1*param);
	g = param;
	lcdWriteInt(re1);
	while(g)
	{
		if((num-re1)<t)
		{
			lcdWriteInt(0);
		}
		g--;
		t *= 0.1;
	}
	lcdWriteInt(re2);
}

//������� ������ ������
void lcdCls()
{
	lcdSendCommand(0x01);
}

//������� ���������� �������
void lcdCursorOff()
{
	lcdSendCommand(0x0C);
}

//������� �������� ������, �� ��������� ������� ��������
void lcdCursorOnBlinkOff()
{
	lcdSendCommand(0x0E);
}

//������� �������� ������ � �������� ������� ��������
void lcdCursorOnBlinkOn()
{
	lcdSendCommand(0x0F);
}

//������� ��������� ������ �� �������� ������ (�) � �� �������� ������ (�)
void lcdGoToXY(char x, char y)
{
  char cmd, addr;
  switch(y)
  {
     case 0: addr = 0x00; break; //��������� ����� 1�� ������
     case 1: addr = 0x40; break; //��������� ����� 2�� ������
     case 2: addr = 0x14; break; //��������� ����� 3�� ������
     case 3: addr = 0x54; break; //��������� ����� 4�� ������
     default: ;
  }
  addr += x;
  cmd = 0x80 | addr;
  lcdSendCommand(cmd);
}

//������� ������������� ������
void lcdPortInit()
{
	if(lcdPort == GPIOA)
	{
		GPIO_InitTypeDef    lcdGPIOInit_InitStruct;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		lcdGPIOInit_InitStruct.GPIO_Pin = (RS | E | D4 | D5 | D6 | D7);
		lcdGPIOInit_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		lcdGPIOInit_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(lcdPort, &lcdGPIOInit_InitStruct);
	}
	if(lcdPort == GPIOB)
	{
		GPIO_InitTypeDef    lcdGPIOInit_InitStruct;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		lcdGPIOInit_InitStruct.GPIO_Pin = (RS | E | D4 | D5 | D6 | D7);
		lcdGPIOInit_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		lcdGPIOInit_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(lcdPort, &lcdGPIOInit_InitStruct);
	}
	if(lcdPort == GPIOC)
	{
		GPIO_InitTypeDef    lcdGPIOInit_InitStruct;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		lcdGPIOInit_InitStruct.GPIO_Pin = (RS | E | D4 | D5 | D6 | D7);
		lcdGPIOInit_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		lcdGPIOInit_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(lcdPort, &lcdGPIOInit_InitStruct);
	}
	if(lcdPort == GPIOD)
	{
		GPIO_InitTypeDef    lcdGPIOInit_InitStruct;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
		lcdGPIOInit_InitStruct.GPIO_Pin = (RS | E | D4 | D5 | D6 | D7);
		lcdGPIOInit_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		lcdGPIOInit_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(lcdPort, &lcdGPIOInit_InitStruct);
	}
	if(lcdPort == GPIOE)
	{
		GPIO_InitTypeDef    lcdGPIOInit_InitStruct;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
		lcdGPIOInit_InitStruct.GPIO_Pin = (RS | E | D4 | D5 | D6 | D7);
		lcdGPIOInit_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		lcdGPIOInit_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(lcdPort, &lcdGPIOInit_InitStruct);
	}
	if(lcdPort == GPIOF)
	{
		GPIO_InitTypeDef    lcdGPIOInit_InitStruct;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
		lcdGPIOInit_InitStruct.GPIO_Pin = (RS | E | D4 | D5 | D6 | D7);
		lcdGPIOInit_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		lcdGPIOInit_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(lcdPort, &lcdGPIOInit_InitStruct);
	}
	if(lcdPort == GPIOG)
	{
		GPIO_InitTypeDef    lcdGPIOInit_InitStruct;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
		lcdGPIOInit_InitStruct.GPIO_Pin = (RS | E | D4 | D5 | D6 | D7);
		lcdGPIOInit_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		lcdGPIOInit_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(lcdPort, &lcdGPIOInit_InitStruct);
	}
}
