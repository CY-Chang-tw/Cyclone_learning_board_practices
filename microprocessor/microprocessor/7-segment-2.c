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
	
	
	/*PC4 = 0;   	
	PC5 = 0;
	PC6 = 0;
	PC7 = 1;
	PE0 = 0;
	PE4 = 0;*/
	
	
				 /*case 0: PE0=1; break;   // c     PE0
				 case 1: PE1=1; break;     // .		  PE1
				 case 2: PE2=1; break;     // f		  PE2
				 case 3: PE3=1; break;     // a		  PE3
				 case 4: PE4=1; break;     // b     PE4
				 case 5: PE5=1; break;     // d     PE5
				 case 6: PE6=1; break;     // e     PE6
				 case 7: PE7=1; break;     // g     PE7 */
	
	while (1) {
		PC4 = 1;   	
		PC5 = 0;
		PC6 = 0;
		PC7 = 0;
		for (k=0; k<=9; k++) {
			switch (k) {
				case 0:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 0;
					PE7 = 1;
					break;
				case 1:
					PE0 = 0;
					PE1 = 1;
					PE2 = 1;
					PE3 = 1;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 1;
					break;
				case 2:
					PE0 = 1;
					PE1 = 1;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 0;
					PE7 = 0;
					break;
				case 3:
					PE0 = 0;
					PE1 = 1;
					PE2 = 1;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 1;
					PE7 = 0;
					break;
				case 4:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 1;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 0;
					break;
				case 5:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 1;
					PE5 = 0;
					PE6 = 1;
					PE7 = 0;
					break;
				case 6:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 1;
					PE5 = 0;
					PE6 = 0;
					PE7 = 0;
					break;
				case 7:
					PE0 = 0;
					PE1 = 1;
					PE2 = 1;
					PE3 = 0;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 1;
					break;
				case 8:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 0;
					PE7 = 0;
					break;
				case 9:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 0;
					break;
			}
			
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
			
			PC4 = 0;   	
			PC5 = 0;
			PC6 = 0;
			PC7 = 1;
			switch (i) {
				case 0:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 0;
					PE7 = 1;
					break;
				case 1:
					PE0 = 0;
					PE1 = 1;
					PE2 = 1;
					PE3 = 1;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 1;
					break;
				case 2:
					PE0 = 1;
					PE1 = 1;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 0;
					PE7 = 0;
					break;
				case 3:
					PE0 = 0;
					PE1 = 1;
					PE2 = 1;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 1;
					PE7 = 0;
					break;
				case 4:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 1;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 0;
					break;
				case 5:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 1;
					PE5 = 0;
					PE6 = 1;
					PE7 = 0;
					break;
				case 6:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 1;
					PE5 = 0;
					PE6 = 0;
					PE7 = 0;
					break;
				case 7:
					PE0 = 0;
					PE1 = 1;
					PE2 = 1;
					PE3 = 0;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 1;
					break;
				case 8:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 0;
					PE7 = 0;
					break;
				case 9:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 0;
					break;
			}                                        //ShowSevenSegment(3,i);
			CLK_SysTickDelay(5000);
			PC4 = 0;   	
			PC5 = 0;
			PC6 = 0;
			PC7 = 0;
			
			
			PC4 = 0;   	
			PC5 = 0;
			PC6 = 1;
			PC7 = 0;
			
			switch (j) {
				case 0:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 0;
					PE7 = 1;
					break;
				case 1:
					PE0 = 0;
					PE1 = 1;
					PE2 = 1;
					PE3 = 1;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 1;
					break;
				case 2:
					PE0 = 1;
					PE1 = 1;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 0;
					PE7 = 0;
					break;
				case 3:
					PE0 = 0;
					PE1 = 1;
					PE2 = 1;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 1;
					PE7 = 0;
					break;
				case 4:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 1;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 0;
					break;
				case 5:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 1;
					PE5 = 0;
					PE6 = 1;
					PE7 = 0;
					break;
				case 6:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 1;
					PE5 = 0;
					PE6 = 0;
					PE7 = 0;
					break;
				case 7:
					PE0 = 0;
					PE1 = 1;
					PE2 = 1;
					PE3 = 0;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 1;
					break;
				case 8:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 0;
					PE7 = 0;
					break;
				case 9:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 0;
					break;
			}    								 //ShowSevenSegment(2,j);
			CLK_SysTickDelay(5000);                
			PC4 = 0;   	
			PC5 = 0;
			PC6 = 0;
			PC7 = 0;
			
			
			PC4 = 0;   	
			PC5 = 1;
			PC6 = 0;
			PC7 = 0;
			
			switch (m) {
				case 0:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 0;
					PE7 = 1;
					break;
				case 1:
					PE0 = 0;
					PE1 = 1;
					PE2 = 1;
					PE3 = 1;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 1;
					break;
				case 2:
					PE0 = 1;
					PE1 = 1;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 0;
					PE7 = 0;
					break;
				case 3:
					PE0 = 0;
					PE1 = 1;
					PE2 = 1;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 1;
					PE7 = 0;
					break;
				case 4:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 1;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 0;
					break;
				case 5:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 1;
					PE5 = 0;
					PE6 = 1;
					PE7 = 0;
					break;
				case 6:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 1;
					PE5 = 0;
					PE6 = 0;
					PE7 = 0;
					break;
				case 7:
					PE0 = 0;
					PE1 = 1;
					PE2 = 1;
					PE3 = 0;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 1;
					break;
				case 8:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 0;
					PE7 = 0;
					break;
				case 9:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 0;
					break;
			}  				//ShowSevenSegment(1,m);
			CLK_SysTickDelay(5000);
			PC4 = 0;   	
			PC5 = 0;
			PC6 = 0;
			PC7 = 0;
			
			
			PC4 = 1;   	
			PC5 = 0;
			PC6 = 0;
			PC7 = 0;
			switch (n) {
				case 0:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 0;
					PE7 = 1;
					break;
				case 1:
					PE0 = 0;
					PE1 = 1;
					PE2 = 1;
					PE3 = 1;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 1;
					break;
				case 2:
					PE0 = 1;
					PE1 = 1;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 0;
					PE7 = 0;
					break;
				case 3:
					PE0 = 0;
					PE1 = 1;
					PE2 = 1;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 1;
					PE7 = 0;
					break;
				case 4:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 1;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 0;
					break;
				case 5:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 1;
					PE5 = 0;
					PE6 = 1;
					PE7 = 0;
					break;
				case 6:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 1;
					PE5 = 0;
					PE6 = 0;
					PE7 = 0;
					break;
				case 7:
					PE0 = 0;
					PE1 = 1;
					PE2 = 1;
					PE3 = 0;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 1;
					break;
				case 8:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 0;
					PE5 = 0;
					PE6 = 0;
					PE7 = 0;
					break;
				case 9:
					PE0 = 0;
					PE1 = 1;
					PE2 = 0;
					PE3 = 0;
					PE4 = 0;
					PE5 = 1;
					PE6 = 1;
					PE7 = 0;
					break;
			} //ShowSevenSegment(0,n);

			CLK_SysTickDelay(5000);				
			PC4 = 0;   	
			PC5 = 0;
			PC6 = 0;
			PC7 = 0;
			
			
			
			if (i == 0 && j == 0 && m == 0 && n == 0) {
					PB11=0; // PB11 = 0 to turn on Buzzer
					CLK_SysTickDelay(1000000);
					CLK_SysTickDelay(1000000);				// Delay 
					PB11=1; // PB11 = 1 to turn off Buzzer
			}
		}
	}*/
	
	

}

