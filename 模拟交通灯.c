#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
sbit g2=P2^2;//�ϱ��̵�
sbit y2=P2^3;//�ϱ��Ƶ�
sbit r2=P2^4;//�ϱ����
sbit g1=P2^5;//�����̵�
sbit y1=P2^6;//�����Ƶ�
sbit r1=P2^7;//�������
uint t;
void time0(void) interrupt 1
	{
		TH0=0x3c;//��ʱ50mS
		TL0=0xb0;
		t++;
	}

void stateG1R2()
	{
		g2=0;	y2=0;	r2=1;   //�ϱ���
		g1=1;	y1=0;	r1=0;	//������
	}
void g1R2()
	{
		g2=0;	y2=0;	r2=1;   //�ϱ���
				y1=0;	r1=0;	
	}
void stateY1R2()
	{
		g2=0;	y2=0;	r2=1;   //�ϱ���
		g1=0;	y1=1;	r1=0;	//������
	}
void stateR1G2()
	{
		g2=1;	y2=0;	r2=0;   //�ϱ���
		g1=0;	y1=0;	r1=1;	//������
	}
void R1g2()
	{
				y2=0;	r2=0;   
		g1=0;	y1=0;	r1=1;	//������
	}
void stateR1Y2()
	{
		g2=0;	y2=1;	r2=0;   //�ϱ���
		g1=0;	y1=0;	r1=1;	//������
	}
void Int_t0(void)  //��ʱ����ʼ��
{	
		TMOD=0x01;//��T0������ʽ1
		TH0=0x3c;//��T0��ʱ��ֵ50mS
		TL0=0xb0;
		EA=1;
		ET0=1;//���ж�
		TR0=1;//����T0    
}
void main(void)
{		
		uchar i;
		P2=0x00;//�رղ���ص�LED
		P0=0xff;
		P1=0xff;//δʹ�õĽӿڶ���1
		while(1)
	{	
		stateG1R2();
		Int_t0();
		if (t==20*5)	
			t=0;

		for(i=0;i<10;i++)
		{	
			g1R2();
			Int_t0();
			g1=~g1;
			if (t==4)		
				t=0;
		}

		stateY1R2();
		Int_t0();	
		if (t==20*2)	
			t=0;

		
		stateR1G2();
		Int_t0();
		if (t==20*5)	
			t=0;

		for(i=0;i<10;i++)
		{	
			R1g2();
			Int_t0();
			g2=~g2;
			if (t==4)		
				t=0;
		}

		stateR1Y2();
		Int_t0();
		if (t==20*2)	
			t=0;
	}
}
