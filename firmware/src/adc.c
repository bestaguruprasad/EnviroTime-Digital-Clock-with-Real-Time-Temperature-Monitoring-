//adc.c

#include "types.h"

#include <LPC21xx.h>

#include "adc_defines.h"

#include "delay1.h"


void Init_ADC(void)

{

	//cfg pins p0.27 to p0.30 

	//using connect block for

	//AIN0-AIN1 pin functions

	//PINSEL1&=~(0xFF<<((27-16)*2));

	PINSEL1|=0x15400000;

	        // AIN1_FUNC|

	         //AIN2_FUNC|

	        // AIN3_FUNC;

	

	//cfg ADCR

	ADCR|=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BITS);

}	


void Read_ADC(u8 chNo,u16 *dVal,f32 *eAR)
{

  //clear any prev channel selection	

	ADCR&=0xFFFFFF00;

	//update on req channel selection

	//& start sample for adc conversion

	ADCR|=(1<<ADC_CONV_START_BIT)|(1<<chNo);

	//wait for conv time

	delay_us(3);
	//check status of conv

		ADCR&=~(1<<ADC_CONV_START_BIT);
//	while((((ADDR>>DONE_BIT)&1))==0);
	while(((ADDR>>DONE_BIT)&1)==0);

	//stop sampling & conv

//	ADCR&=~(1<<ADC_CONV_START_BIT);

	//read/extract digital data

	*dVal=((ADDR>>DIGITAL_DATA_BITS)&1023);

	

	*eAR=*dVal*(3.3/1023);
}

