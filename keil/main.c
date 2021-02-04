//��Ƭ���ͺţ�STC15w104
//����Ƶ�ʣ�12MHz
//��������ͺŻ���Ƶ�ʲ�ͬ����stcisp��������Delay40ms����
//����޸��˾���Ƶ�����޸�freq2timer.py��һ�ж���ľ���Ƶ��(��λ��Hz)��ִ�У�Ȼ������ɵ�tone.h�ļ����Ƶ�keil�ļ���
#include <STC89C5xRC.H>
#include "beep.h"
#include "tone.h"

sbit BEEP = P3^5;													//����˿�,��ӦT0CLKO����ֹ�������رպ����ĵ���
sfr WAKE_CLKO = 0x8f;               //wakeup and clock output control register
unsigned int t0tmp;
#define beep(tone) TL0 = tonetofreq[tone];TH0 = tonetofreq[tone] >>8

void Delay40ms(unsigned char tm)		//@12.000MHz STC15w104��STCISP���ɵ�ֻ����ʱ�̶�ʱ�䣬��Ҫ����һ��whileѭ��
{
	++tm;
	while(--tm)
	{
		unsigned char i, j, k;

	i = 2;
	j = 211;
	k = 231;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
	}
}

void play(unsigned char *table)
{
	unsigned int pos = 0;
	while(1)
	{
		BEEP = 0;
		if(table[pos] == 'B')
		{
			TR0 = 1;
			beep(table[pos+1]);
			Delay40ms(table[pos+2]);
			TR0 = 0;
			BEEP = 0;
			BEEP = 0;
			BEEP = 0;
			pos += 3;
			
		}
		else if(table[pos] == 'S')
		{
			TR0 = 0;
			BEEP = 0;
			BEEP = 0;
			BEEP = 0;
			Delay40ms(table[pos+1]);
			pos += 2;
			BEEP = 0;
			BEEP = 0;
			BEEP = 0;
		}
		else if(table[pos] == 'T')
		{
			TR0 = 0;
			BEEP = 0;
			BEEP = 0;
			BEEP = 0;
			return;
		}
		else return;
	}
}

void main()
{
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD = 0;
	TR0 = 0;
  WAKE_CLKO = 0x01;               //enable timer0 clock output
	EA = 1;
	play(beeptable);
	while(1);
}
