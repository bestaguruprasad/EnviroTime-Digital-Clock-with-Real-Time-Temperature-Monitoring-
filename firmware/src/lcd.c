#include<lpc21xx.h>
#include"types.h"
#include"defines.h"
#include"lcd_defines.h"
#include"lcd.h"
#include"delay1.h"
void WriteLCD(u8 byte)
{
IOCLR0=1<<LCD_RW;
WRITEBYTE(IOPIN0,LCD_DATA,byte);
IOSET0=1<<LCD_EN;
delay_us(1);
IOCLR0=1<<LCD_EN;
delay_ms(2);
}
void CmdLCD(u8 cmd)
{
IOCLR0=1<<LCD_RS;
WriteLCD(cmd);
}
void InitLCD(void)
{
WRITEBYTE(IODIR0,LCD_DATA,0XFF);
SETBIT(IODIR0,LCD_RS);
SETBIT(IODIR0,LCD_RW);
SETBIT(IODIR0,LCD_EN);
delay_ms(15);
CmdLCD(0x30);
delay_ms(4);
delay_ms(100);
CmdLCD(0x30);
delay_us(100);
CmdLCD(0x30);
CmdLCD(MODE_8BIT_2LINE);
CmdLCD(DSP_ON_CUR_BLINK);
CmdLCD(SHIFT_CUR_RIGHT);
}
void CharLCD(u8 asciival)
{
IOSET0=1<<LCD_RS;
WriteLCD(asciival);
}
void StrLCD(s8 *s)
{
while(*s)
CharLCD(*s++);
}
void U32LCD(u32 n)
{
s32 i=0;
u8 a[10];
if(n==0)
{
CharLCD('0');
}
else
{
while(n>0)
{
a[i++]=(n%10)+48;
n/=10;
}
for(--i;i>=0;i--)
{
CharLCD(a[i]);
}
}
}
void S32LCD(s32 n)
{
if(n>0)
{
CharLCD('-');
n=-n;
}
U32LCD(n);
}
void F32LCD(f32 fn,u8 nDP)
{
u32 n,i;
if(fn<0.0)
{
CharLCD('-');
fn=-fn;
}
n=fn;
U32LCD(n);
CharLCD('.');
for(i=0;i<nDP;i++)
{				       
fn=(fn-n)*10;
n=fn;
CharLCD(n+48);
}
}
void BUILDCGRAM(u8 *p,u8 nbytes)
{
u32 i;
CmdLCD(GOTO_CGRAM_START);
IOCLR0=1<<LCD_RW;
IOSET0=1<<LCD_RS;
for(i=0;i<nbytes;i++)
{
WriteLCD(p[i]);
}
CmdLCD(GOTO_LINE1_POS0);
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            