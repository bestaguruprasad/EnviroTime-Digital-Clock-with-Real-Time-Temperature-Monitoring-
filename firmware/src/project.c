#include<lpc21xx.h>
#include"project.h"
#include"kpm.h"
#include"lcd_defines.h"
#include"lcd.h"
#include"delay1.h"
#include"types.h"
void alarm(u32 *mins,u32 MINs,u32 *hours,u32 HOURs)
{
	if((*hours==HOURs)&&(*mins==MINs))
		{
		CmdLCD(CLEAR_LCD);
			while(1)
			{
				CmdLCD(DSP_ON_CUR_OFF);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD("  ALARM ON  ");

					IOSET0=1<<15;
					if((((IOPIN0>>11)&1)==0))
				{
					delay_ms(200);
					IOCLR0=1<<15;
					CmdLCD(CLEAR_LCD);
					*hours=0;
					*mins=0;
					break;
				}
			}			      
			CmdLCD(CLEAR_LCD);
		}
}
void print_day(int num)
{
	CmdLCD(GOTO_LINE2_POS0+11);
	switch(num)
		{
			case 0: StrLCD("SUN");
							break;
			case 1: StrLCD("MON");
							break;
			case 2: StrLCD("TUE");
							break;
			case 3: StrLCD("WED");
							break;
			case 4: StrLCD("THU");
							break;
			case 5: StrLCD("FRI");
							break;
			case 6: StrLCD("SAT");
							break;
			default: StrLCD("DAY");
		}//switch
}
int checkpass(int num1)
{
		int num,count=0;
mani:		if(count<3)
		{
		CmdLCD(CLEAR_LCD);
			CmdLCD(DSP_ON_CUR_OFF);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("ENTER PASSWORD");
			num=ReadNum1();
			count++;
	if(num==num1)
	{
	return 1;
	}
	else
	{
			CmdLCD(CLEAR_LCD);
			CmdLCD(DSP_ON_CUR_OFF);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("WRONG PASSWORD");
			delay_ms(1000);


	goto mani;
	}
	}
	CmdLCD(CLEAR_LCD);
	CmdLCD(DSP_ON_CUR_OFF);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("   ATTEMPS IS   ");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("   COMPLETED   ");
	delay_ms(1000);
	return 0;

}
/*void main()
{
		 	CmdLCD(CLEAR_LCD);
			CmdLCD(DSP_ON_CUR_OFF);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("1.PAN.C   2.ATM.C ");
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("3.V.C  4.D.L");
			CmdLCD(GOTO_LINE3_POS0);
			StrLCD("5.EXIT");

} */


