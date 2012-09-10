#include"std.h"

/********************************************************/
/*                      ��������
/********************************************************/
void Pwm_Port_Init(void);
void Timer1_Init(void);
void Set_M_Pwm(int matchbyte);
void Pwm_Init_Devices(void);

void Pwm_Port_Init(void)
{
  DDRB|=BIT(1);//ͨ��1���
}
// TIMER1 initialize - prescale:1
// WGM: 14) PWM fast, TOP=ICRn
// desired value: 15KHz
// actual value: 15.010KHz (0.1%)
void Timer1_Init(void)
{
 CLI();
 TCCR1B = 0x00; //stop
 TCNT1H = 0xFB; //setup
 TCNT1L = 0x35; //������ʼֵ����Ҫ�������ڸտ�ʼ��ʱ��
 OCR1AH = 0x00;
 OCR1AL = 0x00;
 ICR1H  = 0x04;//1227
 ICR1L  = 0xCB;
 TCCR1A = 0x82;
 TCCR1B = 0x19; //start Timer
 SEI();
}
void Set_M_Pwm(int matchbyte)
{
 OCR1A = matchbyte;
}
void Pwm_Init_Devices(void)
{
 Pwm_Port_Init();
 Timer1_Init();
}
