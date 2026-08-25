char 
CmdLCD(CLEAR_LCD);
				CmdLCD(DSP_ON_CUR_OFF);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD(" EDIT   1:TIME ");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD(" 2:DATE 3:EXIT ");
				ch=KeyScan();
				delay_ms(200);