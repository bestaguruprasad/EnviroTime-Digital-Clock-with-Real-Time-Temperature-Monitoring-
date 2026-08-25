//adc_lcd_test.c

#include "adc.h"

#include "lcd_defines.h"

#include "lcd.h"

#include "delay1.h"

u16 dVal[4];

f32 eAR[4];

u8 pos[4]={0x80,0x88,0xc0,0xc8};

main()

{

	u32 chNo;

	Init_ADC();

	InitLCD();

	while(1)

	{

		for(chNo=0;chNo<=3;chNo++)

		{

			CmdLCD(pos[chNo]);

			/*StrLCD("CH");

			CharLCD(chNo+'0');

			CharLCD(':');

			*/

			Read_ADC(chNo,&dVal[chNo],&eAR[chNo]);

			//F32LCD(eAR[chNo],1);	  

			U32LCD(dVal[chNo]);

		}

    delay_ms(100);

		CmdLCD(CLEAR_LCD);

		

	}

}