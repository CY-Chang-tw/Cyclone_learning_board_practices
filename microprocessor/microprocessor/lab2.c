#include <stdio.h>
#include <stdlib.h>
#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "LCD.h"
#include "Scankey.h"
#include "Seven_Segment.h"
#include <string.h>

int a = 0;
int b = 0;
int sum;
void oper(char sym) {
	switch(sym) {
		case '+':
			sum =a+b;
		break;
		case '-':
			sum =a-b;
		break;
		case '*':
			sum =a*b;
		break;
		case '/':
			sum =a/b;
		break;
		case '%':
			sum =a%b;
		break;
	}
}
int32_t main(void)
{
	
	char sum5[4];
	int ke = 0, input;
	int step = 1;
	char a1[10];
	char b1[10];
	char sys;
    SYS_Init();
	  init_LCD();
	  clear_LCD();
		PD14 = 0;
	OpenKeyPad();
	while(1) {
			
			switch(step) {
				case 0:
					while(ke == 0)
						ke = ScanKey();
					input = ke;	
					while(ke != 0)
						ke = ScanKey();
					CLK_SysTickDelay(700000);
					step++;
					clear_LCD();
					a=0;b=0;
					break;
				case 1:
					PA12 = 0; PA13 = 1; PA14 = 0;
					while(ke == 0)
						ke = ScanKey();
					input = ke;	
					while(ke != 0)
						ke = ScanKey();
					CLK_SysTickDelay(800000);
					switch(input){
						case 1:
							step++;
							break;
						default:
							if(a<100){
							a=a*10+input;
							sprintf(a1,"%d",a);}
							print_Line(0,a1);
							break;	
					}
					break;
					
					case 2:
					PA12 = 1; PA13 = 0; PA14 = 0;
					while(ke == 0)
						ke = ScanKey();
					input = ke;
					while(ke != 0)
						ke = ScanKey();
					CLK_SysTickDelay(800000);
					switch(input){
						case 1:
							step++;
							break;
						case 5:
						sys = '+';	
						strcat(a1,"+");
						print_Line(0,a1);
						break;
						case 6:
						sys = '-';	
						strcat(a1,"-");
						print_Line(0,a1);
						break;
						case 7:
						sys = '*';	
						strcat(a1,"*");
						print_Line(0,a1);
						break;
						case 8:
						sys = '/';	
						strcat(a1,"/");
						print_Line(0,a1);
						break;
						case 9:
						sys = '%';	
						strcat(a1,"%");
						print_Line(0,a1);
						break;
					}
					break;
					
					case 3:
					PA12 = 0; PA13 = 0; PA14 = 1;
					while(ke == 0)
						ke = ScanKey();
					input = ke;
					while(ke != 0)
						ke = ScanKey();
					CLK_SysTickDelay(800000);
					switch(input){
						case 1:
							strcat(a1," = ");
							print_Line(0,a1);
							oper(sys);
							sprintf(sum5,"%d",sum);
							strcat(a1,sum5);
							print_Line(0,a1);
							PA12 = 0; PA13 = 0; PA14 = 0;
						step = 0;
							break;
						default:
							b=b*10+input;
							sprintf(b1,"%d",input);
							strcat(a1,b1);
							print_Line(0,a1);
							break;
					}
					break;
			}
	}
}
