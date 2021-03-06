#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
sbit g2=P2^2;//南北绿灯
sbit y2=P2^3;//南北黄灯
sbit r2=P2^4;//南北红灯
sbit g1=P2^5;//东西绿灯
sbit y1=P2^6;//东西黄灯
sbit r1=P2^7;//东西红灯
uint t;
void time0(void) interrupt 1
	{
		TH0=0x3c;//定时50mS
		TL0=0xb0;
		t++;
	}

void stateG1R2()
	{
		g2=0;	y2=0;	r2=1;   //南北红
		g1=1;	y1=0;	r1=0;	//东西绿
	}
void g1R2()
	{
		g2=0;	y2=0;	r2=1;   //南北红
				y1=0;	r1=0;	
	}
void stateY1R2()
	{
		g2=0;	y2=0;	r2=1;   //南北红
		g1=0;	y1=1;	r1=0;	//东西黄
	}
void stateR1G2()
	{
		g2=1;	y2=0;	r2=0;   //南北绿
		g1=0;	y1=0;	r1=1;	//东西红
	}
void R1g2()
	{
				y2=0;	r2=0;   
		g1=0;	y1=0;	r1=1;	//东西红
	}
void stateR1Y2()
	{
		g2=0;	y2=1;	r2=0;   //南北黄
		g1=0;	y1=0;	r1=1;	//东西红
	}
void Int_t0(void)  //定时器初始化
{	
		TMOD=0x01;//置T0工作方式1
		TH0=0x3c;//置T0定时初值50mS
		TL0=0xb0;
		EA=1;
		ET0=1;//开中断
		TR0=1;//启动T0    
}
void main(void)
{		
		uchar i;
		P2=0x00;//关闭不相关的LED
		P0=0xff;
		P1=0xff;//未使用的接口都置1
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
