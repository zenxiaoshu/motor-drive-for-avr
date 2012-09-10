#include"std.h"
#include"globle.h"
#include"queue.h"
#include"sp027.h"


/*=========================================================*
*                   �����궨��                            
*=========================================================*/
#define DATA_LENGTH         11

#define SPEED_ONE	  		0x01				 //ͨ�Ų���
#define SPEED_TWO	  		0x02				 //ͨ�Ų���
#define SPEED_THREE	  		0x03				 //ͨ�Ų���

/********************************************************/
/*                      ��������
/********************************************************/

BOOL DecodeMsg( DATABUF* pdataBuf, UINT8 u8DataSize );
BOOL AddDecodeMsg( DATABUF* pdataBuf, BYTE Data );


BOOL AddDecodeMsg( DATABUF* pdataBuf, BYTE Data )
{
 QueueAdd(pdataBuf, Data );
 if(GetSize(pdataBuf) >= DATA_LENGTH)
 {
  DecodeMsg(pdataBuf,DATA_LENGTH);
 }
 return FALSE;
}
BOOL DecodeMsg( DATABUF* pdataBuf, UINT8 u8DataSize )
{

	
	UINT8 i = 0;
    UINT8 lcv_Parity=0;
    UINT8 lcv_Cmd=0;
    UINT8 lcv_DataLength=0;
	BOOL bSuccessed = FALSE;
	BYTE bySpeed[2] = { 0 };

	if (pdataBuf == NULL )
	{
		return FALSE;
	}

	//�жϻ��������ݳ���
	while( pdataBuf->Datasize >= u8DataSize ) 
	{
        //�ж�֡ͷ
		if( QueueGet(pdataBuf,0) != 0xAA )     
		{   
		    //ɾ��1λ
			QueueDel(pdataBuf,1);            
			continue;
		}
		
		//��ȡ���ݳ���
		lcv_DataLength = QueueGet(pdataBuf,1); 
        //�жϻ�ȡ�����ݳ����Ƿ���ڻ����������ݳ���
		if( lcv_DataLength > pdataBuf->Datasize) 
		{   
		    //ɾ��
			QueueDel(pdataBuf,pdataBuf->Datasize);
			return bSuccessed;
		}
		if( lcv_DataLength != u8DataSize)
		{
		   //ɾ��
		   QueueDel(pdataBuf,lcv_DataLength);
		   continue; 
		}
        //�ж�֡β
		if( QueueGet(pdataBuf,lcv_DataLength-1) !=0x55 ) 
		{
			QueueDel(pdataBuf,u8DataSize);
			continue;
		}
		//����У��
		for(i = 1;i < lcv_DataLength - 2; i++)
		{
			lcv_Parity ^= QueueGet(pdataBuf,i);
		}
		//���У��λ
	 	if(lcv_Parity != QueueGet(pdataBuf, lcv_DataLength - 2))
		{
			QueueDel(pdataBuf,u8DataSize);
			continue;
		}
		bSuccessed = TRUE;
		//�������λ
		lcv_Cmd = QueueGet(pdataBuf,2); 
		//�ж�����λ
		switch(lcv_Cmd)
		{
            case SPEED_ONE:
			    bySpeed[0] = QueueGet(pdataBuf,3);
				bySpeed[1] = QueueGet(pdataBuf,4);
				g_speed.A = *( short* )bySpeed;
				
				bySpeed[0] = QueueGet(pdataBuf,5);
				bySpeed[1] = QueueGet(pdataBuf,6);
				g_speed.B = *( short* )bySpeed;
				
				bySpeed[0] = QueueGet(pdataBuf,7);
				bySpeed[1] = QueueGet(pdataBuf,8);
				g_speed.C = *( short* )bySpeed;
		
			break;
			case SPEED_TWO:
				bySpeed[0] = QueueGet(pdataBuf,3);
				bySpeed[1] = QueueGet(pdataBuf,4);
				g_speed.D = *( short* )bySpeed;
				
				bySpeed[0] = QueueGet(pdataBuf,5);
				bySpeed[1] = QueueGet(pdataBuf,6);
				g_speed.E = *( short* )bySpeed;
				
				bySpeed[0] = QueueGet(pdataBuf,7);
				bySpeed[1] = QueueGet(pdataBuf,8);
				g_speed.F = *( short* )bySpeed;
			break;
			/*
			case SPEED_THREE:
			    bySpeed[0] = QueueGet(pdataBuf,3);
				bySpeed[1] = QueueGet(pdataBuf,4);
				g_speed.A = *( short* )bySpeed;
				
				bySpeed[0] = QueueGet(pdataBuf,5);
				bySpeed[1] = QueueGet(pdataBuf,6);
				g_speed.B = *( short* )bySpeed;
				
				bySpeed[0] = QueueGet(pdataBuf,7);
				bySpeed[1] = QueueGet(pdataBuf,8);
				g_speed.C = *( short* )bySpeed;
			break;
			*/
			default :
				break;
		}
		//ɾ�����������Ѷ�������
		QueueDel(pdataBuf,u8DataSize); 
	}
	return bSuccessed;
}

