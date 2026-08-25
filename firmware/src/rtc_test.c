#include <LPC21xx.h>
#include"kpm_defines.h"
#include"delay1.h"
#include"kpm.h"
#include"defines.h"
#include "lcd.h"
#include "lcd_defines.h"
#include"project.h"
#include"types.h"
#include"LM35.h"
#include "adc.h"
int main()
{
	u8 ch;
	u32 num,num1=1234,hour=20,mins=15;
	f32 tempC,tempF;
	
	//reset clock tick counter using CCR registe
	CCR = 1<<1;//0x02
	//set the 1 second tick rate using
  //PREINT & PREFRAC registers
	PREINT = 456;
	PREFRAC = 25024;

	//enable the clock using CCR register

	CCR = 1<<0;//0x01
	 IODIR0=1<<15;
	 //IOCLR0=1<<15;

	InitLCD();
	InitKPM();
	Init_ADC();
	

	//set the RTC info

	HOUR = 20;

	MIN = 12;

	SEC = 0;

	DOM = 20;

	MONTH = 5;

	YEAR = 2026;

	DOW = 1;
	//CharLCD('m');	
	while(1)
	{
		//display time info
	
		Read_LM35(&tempC,&tempF);
		CmdLCD(GOTO_LINE1_POS0);
		CharLCD((HOUR/10)+48);
		CharLCD((HOUR%10)+48);
		CharLCD(':');
		CmdLCD(GOTO_LINE1_POS0+3);
		CharLCD((MIN/10)+0x30);
		CharLCD((MIN%10)+0x30);
		CharLCD(':');
		CmdLCD(GOTO_LINE1_POS0+6);
		CharLCD((SEC/10)+'0');
		CharLCD((SEC%10)+'0');
		//temp
		CmdLCD(GOTO_LINE1_POS0+10);
		F32LCD(tempC,1);
		CharLCD('c');
		//display date info
		CmdLCD(GOTO_LINE2_POS0);
		CharLCD((DOM/10)+48);
		CharLCD((DOM%10)+48);
		CharLCD('/');
		CmdLCD(GOTO_LINE2_POS0+3);
		CharLCD((MONTH/10)+0x30);
		CharLCD((MONTH%10)+0x30);
		CharLCD('/');
		CmdLCD(GOTO_LINE2_POS0+6);
		U32LCD(YEAR);
		//display day info
		print_day(DOW);
		delay_s(1);
		alarm(&mins,MIN,&hour,HOUR);
	if(((IOPIN0>>5)&1)==0)
		{
			if(checkpass(num1))
			{
				while(1)
				{
				CmdLCD(CLEAR_LCD);
				CmdLCD(DSP_ON_CUR_OFF);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD(" 1:TIME 2:DATE");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD(" 3:ALARM 4:EXIT ");
				ch=KeyScan();
				delay_ms(200);
				switch(ch)
				{
				case '1':while(1)
				{
					CmdLCD(CLEAR_LCD);
					CmdLCD(GOTO_LINE1_POS0);
					StrLCD(" 1:HOUR  2:MIN ");
					CmdLCD(GOTO_LINE2_POS0 );
					StrLCD(" 3:SEC  4:EXIT ");
		 			ch=KeyScan();
					delay_ms(200);
					switch(ch)
					{
						case '1':hr:CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("ENTER HOUR");
								CmdLCD(GOTO_LINE1_POS0+12);
								CharLCD((HOUR/10)+48);
								CharLCD((HOUR%10)+48);
								num=ReadNum();
								if(num<25)
								{
								HOUR=num;
								break;
								}
								else
								{
								CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("WRONG HOURS");
								delay_ms(1000);
								goto hr;
								}
						case '2':mn:CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("ENTER MINS");
								CmdLCD(GOTO_LINE1_POS0+13);
								CharLCD((MIN/10)+0x30);
								CharLCD((MIN%10)+0x30);
								num=ReadNum();
								if(num<60)
								{
								MIN=num;
								break;
								}
								else
								{
								CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("WRONG MINS");
								delay_ms(1000);
								goto mn;
								}
						case '3':se:CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("ENTER SECS");
								CmdLCD(GOTO_LINE1_POS0+13);
								CharLCD((SEC/10)+'0');
								CharLCD((SEC%10)+'0');
								num=ReadNum();
								if(num<60)
								{
								SEC=num;
								break;
								}
								else
								{
								CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("WRONG SECS");
								delay_ms(1000);
								goto se;
								}
						case '4':goto label;
					}
					
					}
					label:break;
									 
				case '2':
					while(1)
					{
					CmdLCD(CLEAR_LCD);
					CmdLCD(GOTO_LINE1_POS0);
					StrLCD("1:DATE 2:MONTH");
					CmdLCD(GOTO_LINE2_POS0);
					StrLCD("3:YEAR 4:DAY 5:EX");
		 			ch=KeyScan();
					delay_ms(200);
					switch(ch)
					{
						case '1':CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("ENTER DATE");
								CmdLCD(GOTO_LINE1_POS0+13);
								CharLCD((DOM/10)+48);
								CharLCD((DOM%10)+48);
								num=ReadNum();
								DOM=num;
								break;
						case '2':mnt:CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("ENTER MONTH");
								CmdLCD(GOTO_LINE1_POS0+13);
								CharLCD((MONTH/10)+0x30);
								CharLCD((MONTH%10)+0x30);
								num=ReadNum();
								if(num<13)
								{
								MONTH=num;
								break;
								}
								else
								{
								CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("WRONG MONTH");
								delay_ms(1000);
								goto mnt;
								}
						case '3':y:CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("ENTER YEAR");
								CmdLCD(GOTO_LINE1_POS0+13);
								U32LCD(YEAR);
								num=ReadNum();
								if(num<4040)
								{
								YEAR=num;
								break;
								}
								else
								{
								CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("WRONG YEAR");
								delay_ms(1000);
								goto y;
								}	
						case '4':CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("enter DAY");
								num=ReadNum();
								//delay_ms(200);
								//CharLCD(ch);
								//ch=ch-48;
								DOW=num;
								break;
						case '5':goto guru;
					}
					}
					guru:break;
				case '3':while(1)
				{
					CmdLCD(CLEAR_LCD);
					CmdLCD(GOTO_LINE1_POS0);
					StrLCD(" 1:HOUR  2:MIN ");
					CmdLCD(GOTO_LINE2_POS0 );
					StrLCD("  3:EXIT  ");
		 			ch=KeyScan();
					delay_ms(200);
					switch(ch)
					{
						case '1':h:CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("enter hours");
								CmdLCD(GOTO_LINE1_POS0+12);
								CharLCD((HOUR/10)+48);
								CharLCD((HOUR%10)+48);
								num=ReadNum();
								if(num<25)
								{
								hour=num;
								break;
								}
								else
								{
								CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("WRONG HOURS");
								delay_ms(1000);
								goto h;
								}
						case '2':m:CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("enter mins");
								CmdLCD(GOTO_LINE1_POS0+13);
								CharLCD((MIN/10)+0x30);
								CharLCD((MIN%10)+0x30);
								num=ReadNum();
								if(num<60)
								{
								mins=num;
								break;
								}
								else
								{
								CmdLCD(CLEAR_LCD);
								CmdLCD(GOTO_LINE1_POS0);
								StrLCD("WRONG MINS");
								delay_ms(1000);
								goto m;
								}
						case '3':goto prasad;
					}
					
					}
					prasad:break;
				case '4':goto mani;
				}
				 }
				 mani:;
					
			
			//delay_ms(50);
			
			//while(((IOPIN0>>4)&1)!=0);
				//delay_ms(500);	
				//CmdLCD(CLEAR_LCD);

				}//if inner
				else
				{
					CmdLCD(CLEAR_LCD);
					CmdLCD(GOTO_LINE1_POS0);
					StrLCD("wrong password");
											
				} 
				delay_ms(500);	
				CmdLCD(CLEAR_LCD);


			}
	
	}//while
}//main
