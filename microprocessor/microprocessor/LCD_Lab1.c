
#include <stdio.h>
#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "LCD.h"
#include "ScanKey.h"


void int2str(int i, char *s) {
  sprintf(s,"%04d",i);
}

int main(void)
{
	int8_t x=0,y=0;
	int keyin;
	int flag = 0;
	int num = 0;
	char strNum[20];
	char str[30] = "Owen Chang D0745560";

	SYS_Init();
	  
	init_LCD();
	clear_LCD();
	
	PD14=0; //Enable LCD's Backlight
	
	while (1) {
		flag = 0;
	
		if (keyin == 2 || keyin == 3) {
			flag = 1;
		} 
			keyin = ScanKey();
		while (keyin != 0)
			keyin = ScanKey();
		while (keyin == 0)
			keyin = ScanKey();
		
		switch (keyin) {
			case 1:
				clear_LCD();
				printS_5x7(0, 0 , str);
				break;
			case 2:
				if (!flag)
					clear_LCD();
				printS_5x7(0, 0, "S");
				printS(20, 10, "S");
				printC_5x7(40, 35, 'C');
				printC(60, 40, 'C');
				break;
			case 3:
				if (!flag)
					clear_LCD();
				//printS_5x7(0, 0, "S");
				//printS(20, 10, "S");
				printC(0, 10, '@');
				printC_5x7(0, 35, '@');
				printC_5x7(20, 35, '@');
				//printC_5x7(40, 35, 'C');
				printC(0, 40, '@');
				printC(20, 40, '@');
				printC(40, 40, '@');
				//printC(60, 40, 'C');
				break;
			case 4:
				break;
			case 5:
				clear_LCD();
				printS(0, 0, "Counter started:");
				CLK_SysTickDelay(100000);
				CLK_SysTickDelay(100000);
			  CLK_SysTickDelay(100000);
				CLK_SysTickDelay(100000);
				clear_LCD();
				
				
				int2str(num, strNum);
				printS(0, 0, "Now:");
				print_Line(1, strNum);
				break;
			case 6:
				clear_LCD();
				break;
			case 7:
				clear_LCD();
				CLK_SysTickDelay(100000);
				CLK_SysTickDelay(10000);
				if (num - 1 < 0) {
					num = 9999;
				} else {
					num = num - 1;
				}
				CLK_SysTickDelay(100000);
				CLK_SysTickDelay(10000);
				int2str(num, strNum);
				printS(0, 0, "Now:");
				print_Line(1, strNum);
				CLK_SysTickDelay(100000);
				CLK_SysTickDelay(10000);
				CLK_SysTickDelay(100000);
				CLK_SysTickDelay(10000);
				clear_LCD();
				break;
			case 8:
				clear_LCD();
			CLK_SysTickDelay(100000);
				CLK_SysTickDelay(10000);
			
				int2str(num, strNum);
				printS(0, 0, "Now:");
				print_Line(1, strNum);
			break;
			case 9:
				clear_LCD();
				CLK_SysTickDelay(100000);
				CLK_SysTickDelay(10000);
				if (num + 1 > 9999) {
					num = 0;
				} else {
					num = num + 1;
				}
				CLK_SysTickDelay(100000);
				CLK_SysTickDelay(10000);
				int2str(num, strNum);
				printS(0, 0, "Now:");
				print_Line(1, strNum);
				CLK_SysTickDelay(100000);
				CLK_SysTickDelay(10000);
				CLK_SysTickDelay(100000);
				CLK_SysTickDelay(10000);
				clear_LCD();
				break;
		}
	}
}

