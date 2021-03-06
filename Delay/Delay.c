#include "Delay.h"

void Delay_ms(unsigned int delay)
{
     TIM7->PSC = F_APB1/1000+1;	//������������� ������������
     TIM7->ARR = delay;	//������������� �������� ������������ �������, � ������ � �������� ��� ������� ������������ ������� ����������
     TIM7->EGR |= TIM_EGR_UG;	//���������� ������� ���������� ��� ������ ������ � �������� PSC � ARR
     TIM7->CR1 |= TIM_CR1_CEN|TIM_CR1_OPM;	//��������� ������ ������� ���� CEN � ������������� ����� ������ ������� ���������� ���� OPM
     while (TIM7->CR1&TIM_CR1_CEN!=0);
}

void Delay_us(unsigned int delay)
{
     TIM7->PSC = F_APB1/1000000+1;	//������������� ������������
     TIM7->ARR = delay;	//������������� �������� ������������ �������, � ������ � �������� ��� ������� ������������ ������� ����������
     TIM7->EGR |= TIM_EGR_UG;	//���������� ������� ���������� ��� ������ ������ � �������� PSC � ARR
     TIM7->CR1 |= TIM_CR1_CEN|TIM_CR1_OPM;	//��������� ������ ������� ���� CEN � ������������� ����� ������ ������� ���������� ���� OPM
     while (TIM7->CR1&TIM_CR1_CEN!=0);
}
