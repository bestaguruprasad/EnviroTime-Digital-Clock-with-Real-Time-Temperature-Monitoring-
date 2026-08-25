#include"types.h"
void WriteLCD(u8 type);
void CmdLCD(u8 cmd);
void InitLCD(void);
void CharLCD(u8 asciival);
void StrLCD(s8*);
void U32LCD(u32);
void S32LCD(s32);
void F32LCD(f32 fn,u8 nDP);
void BuildCGRAM(u8*p,u8 nbytes);
//void Edit();
