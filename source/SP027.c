
/***********************************************************
*   ������˵����SP027 ����Һ��ģ�������⺯��               *
*     			VSS     CLK      DI    VDD                 *
*              ��Դ��  ʱ���ź�  ����  ��Դ��              *
*  ע��: Ӧ��д��һ�����ݺ���ĩβ����һ��ʱ��������(Paulse)*
***********************************************************/
/********************
* ͷ �� �� �� �� �� *
********************/
# include "std.h"

//�˿��Զ�������
/***********************************************/
#define   SP027_PORT  	PORTC  		//SP027��  ��
#define   CLK         	PC5   		//SP027ʱ����
#define   DI          	PC4			//SP027������
/***********************************************/
/**********************************************
*  SP027��ʾģ��                              *
*  �ӿڶ��壺                                 *
*                VSS     CLK      DI    VDD   *
*              ��Դ��  ʱ���ź�  ����  ��Դ�� *
***********************************************/
#define   CLK0        SP027_PORT&=(~(1<<CLK)) 
#define   CLK1        SP027_PORT|=((1<<CLK))
#define   DI0         SP027_PORT&=(~(1<<DI)) 
#define   DI1         SP027_PORT|=((1<<DI))
#define   Wrt1         CLK0;CLK1;DI1;DI0;              //д����"1"
#define   Wrt0         CLK0;CLK1;DI0;DI1;              //д����"0" 
#define   Paulse       CLK0;CLK1;                      //һ��������
#define   GO           0x01
#define   Ready        0x02

/********************
*   �� �� �� �� ��  *
********************/
void Display_Onechar(unsigned char Data);

/********************
*   ģ�麯��������  *
********************/
void CLS(void);
void DisplayINTNum_SP027(long Number);
void DisplayFloatNum_SP027(float Num);

/********************
*   ģ�����������  *
********************/
const unsigned char DisplayCode[] = {0x09,0xcf,0x91,0x85,0x47,0x25,0x21,0x8f,0x01,0x05,       // signed   char
                         0x03,0x61,0x39,0xc1,0x31,0x33,0x29,0x43,0x7b,0xc9,
						 0x79,0xe1,0x13,0xf3,0x49,0xf7,0xfd,0xff}; 
						 /*{0~F,G,H,I,J,L,O,P,r,U,_,-}*/ 
						 			 
/***********************************************************
*   �������ܣ���������                                     *
***********************************************************/
void CLS(void)
{
   unsigned char k = 0; 
   for(k=0;k<41;k++)
   {
      Wrt0;
   }	   
}                       
/***********************************************************
*   �������ܣ�ʮ����������ʾ����                           *
*   ��    �룺Ҫ��ʾ����(long)                             *
***********************************************************/
void DisplayINTNum_SP027(long Number)
{	
	unsigned char lcv_Counter = 0;
    unsigned char cNonce_BIT_Number = 0;
	unsigned char tmpNumber[5] = {0};
	unsigned char isNegative = FALSE;
	if(Number<0)
	{
		isNegative = TRUE;
	}
	Number =fabs(Number);//ȡ����ֵ
	CLS();	//����
	
	do
	{   
		if(lcv_Counter+isNegative>=5)
		{
			tmpNumber[0] &=~BIT(0);	//�����
			break;
		}
		tmpNumber[lcv_Counter] = DisplayCode[Number%10];   //���㵱ǰλ�ϵ�����Number%10
		Number=Number/10;    //����ȵ�ǰλ����λ�ϵ�����
		lcv_Counter ++;
	}while(Number);
	if(isNegative)
	{
		tmpNumber[lcv_Counter]=0xF7;	//����
		lcv_Counter++;
	}
	while(lcv_Counter--)
	{
		Display_Onechar(tmpNumber[lcv_Counter]);	//��ʾ
	}
    Paulse;   
}   
/***********************************************************
*   �������ܣ�Float������ʾ����                            *
*   ��    �룺Ҫ��ʾ����(float)                            *
***********************************************************/
void DisplayFloatNum_SP027(float Num)
{
    unsigned char lcv_Counter = 0;
    unsigned char cNonce_BIT_Number = 0;
	unsigned char tmpNumber[5] = {0};
    unsigned long Number = 0;
	unsigned char isNegative = FALSE;
	
	if(Num<0)
	{
		isNegative = TRUE;         //# define TRUE    (!0x00)
	}
	Number =fabs((long)(Num*100));
	CLS();	//����
	
	do
	{   
		if(lcv_Counter+isNegative>=5)
		{
			tmpNumber[0] &=~BIT(0);	//�����
			break;
		}
		tmpNumber[lcv_Counter] = DisplayCode[Number%10];   //���㵱ǰλ�ϵ�����Number%10
		Number=Number/10;    //����ȵ�ǰλ����λ�ϵ�����
		lcv_Counter ++;
	}while(Number||(lcv_Counter<=2));
	tmpNumber[2] &=~BIT(0);	//С����
	if(isNegative)
	{
		tmpNumber[lcv_Counter]=0xF7;	//����
		lcv_Counter++;
	}
	while(lcv_Counter--)
	{
		Display_Onechar(tmpNumber[lcv_Counter]);	//��ʾ
	}
    Paulse;
}    

/***********************************************************
*   �������ܣ�д��������                                   *
*   ��    �룺Ҫ��ʾ����(UINT8)                            *
*   ��    ����    ��                                       *
* -------------------------------------------------------- *
*  [ʹ��˵��]                                              *
***********************************************************/
void Display_Onechar(unsigned char Data)
{
   unsigned char CharLength = 0;
   unsigned char NumTemp = 0;
   
   for (CharLength=0;CharLength<8;CharLength++)
   {
	  NumTemp = (( Data >>(7-CharLength))&0x01);
	  if (NumTemp == 0)
	  {
		Wrt1;
	  }
	  else
	  {
	    Wrt0;
	  }	  
   }         
}
/*********************
 ʮ��������ʾ������������
**********************/
void Display_Onecha(unsigned char Data)
{
   unsigned char CharLength = 0;
   unsigned char NumTemp = 0;
   
   for (CharLength=0;CharLength<8;CharLength++)
   {
	  NumTemp = ((DisplayCode[ Data ]>>(7-CharLength))&0x01);
	  if (NumTemp == 0)
	  {
		Wrt1;
	  }
	  else
	  {
	    Wrt0;
	  }	  
   }         
}
/************************
   ʮ��������ʾ����
***********************/

void HEXDispNum(int Num)
{
   static char i = 0;
   static char TempData[]={0,0,0,0,0};
   
   TempData[4]= Num&0x000f;
   TempData[3]= (Num&0x00f0)>>4;
   TempData[2]= (Num&0x0f00)>>8;
   TempData[1]= (Num&0xf000)>>12;
   for (i=0;i<5;i++)
   {   
      Display_Onecha(TempData[i]);
   }	  
   Paulse;
} 
