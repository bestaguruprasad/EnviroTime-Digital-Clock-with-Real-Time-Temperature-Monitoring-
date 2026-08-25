//lm35.c

#include "types.h"

#include "adc.h"

void Read_LM35(f32 *tDegC,f32 *tDegF)
{

	static s32 flag;

	u16 dVal;

	f32 eAR;

	if(flag==0)
	{	

	 // Init_ADC();

		flag=1;

	}	

	Read_ADC(1,&dVal,&eAR);

	*tDegC=(eAR * 100);

	*tDegF=(*tDegC *1.8) + 32;		

}


void Read_LM35NP(f32 *tDegC,f32 *tDegF)

{

	u16 dVal1,dVal2;

	f32 eAR1,eAR2;

	static s32 flag;	

	if(flag==0)

	{	

	  Init_ADC();

		flag=1;

	}		

	Read_ADC(0,&dVal1,&eAR1);

	Read_ADC(1,&dVal2,&eAR2);	

	*tDegC=((eAR1-eAR2) * 100);

	*tDegF=(*tDegC * (9/5.0)) + 32;		

}

