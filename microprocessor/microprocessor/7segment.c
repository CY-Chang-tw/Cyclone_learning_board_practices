//
// GPIO_7seg : counting from 0 to 9999 and display on 7-segment LEDs
//
#include <stdio.h>
#include <stdbool.h>
#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "Seven_Segment.h"

void Buzz(int number)
{
	int i;
	for (i=0; i<number; i++) {
    PB11=0; // PB11 = 0 to turn on Buzzer
	  CLK_SysTickDelay(100000);	 // Delay 
	  PB11=1; // PB11 = 1 to turn off Buzzer	
	  CLK_SysTickDelay(100000);	 // Delay 
	}
}


int main(void)
{	
	int k;
	int sum = 0;
	int binary = 0;
	int i = 0;
	int j = 0;
	int m = 0;
	int n = 0;

	
  SYS_Init();
	
	while (1) {
		for (k=0; k<=9; k++) {
			OpenSevenSegment();
			ShowSevenSegment(0,k);
			
			switch (k) {
				case 1:
					PC15 = 0;
					PC14 = 1;
					PC13 = 1;
					PC12 = 1;
					break;
				case 2:
					PC15 = 1;
					PC14 = 0;
					PC13 = 1;
					PC12 = 1;
					break;
				case 3:
					PC15 = 0;
					PC14 = 0;
					PC13 = 1;
					PC12 = 1;
					break;
				case 4:
					PC15 = 1;
					PC14 = 1;
					PC13 = 0;
					PC12 = 1;
					break;
				case 5:
					PC15 = 0;
					PC14 = 1;
					PC13 = 0;
					PC12 = 1;
					break;
				case 6:
					PC15 = 1;
					PC14 = 0;
					PC13 = 0;
					PC12 = 1;
					break;
				case 7:
					PC15 = 0;
					PC14 = 0;
					PC13 = 0;
					PC12 = 1;
					break;
				case 8:
					PC15 = 1;
					PC14 = 1;
					PC13 = 1;
					PC12 = 0;
					break;
				case 9:
					PC15 = 0;
					PC14 = 1;
					PC13 = 1;
					PC12 = 0;
					break;
				default:
					PC15 = 1;
					PC14 = 1;
					PC13 = 1;
					PC12 = 1;
					break;
			}
			CLK_SysTickDelay(1000000);
			CLK_SysTickDelay(1000000);
			CloseSevenSegment();
		}
	}
	/*while (1) {
		for (sum=0; sum<=9999; sum++) {
			i = sum / 1000;
			j = sum % 1000 / 100;
			m = sum % 1000 % 100 / 10;
			n = sum %1000 % 100 % 10;
			
			if (i == j && m == j && m == n && i != 0) {
				Buzz(1);
			} else if (sum % 1221 == 0 && sum != 0) {
				Buzz(2);
			}
			
			OpenSevenSegment();
			ShowSevenSegment(3,i);
			CLK_SysTickDelay(5000);
			CloseSevenSegment();
			
			OpenSevenSegment();
			ShowSevenSegment(2,j);
			CLK_SysTickDelay(5000);
			CloseSevenSegment();
			
			OpenSevenSegment();
			ShowSevenSegment(1,m);
			CLK_SysTickDelay(5000);
			CloseSevenSegment();
			
			OpenSevenSegment();
			ShowSevenSegment(0,n);
			CLK_SysTickDelay(5000);
			CloseSevenSegment();
			
			
			if (i == 0 && j == 0 && m == 0 && n == 0) {
					PB11=0; // PB11 = 0 to turn on Buzzer
					CLK_SysTickDelay(1000000);
					CLK_SysTickDelay(1000000);				// Delay 
					PB11=1; // PB11 = 1 to turn off Buzzer
			}
		}
	}*/
	
	

}

