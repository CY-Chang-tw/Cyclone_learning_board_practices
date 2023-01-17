/*
	請勿修改以下部分
	Do not edit the following lines.
	#include <stdio.h>
	#include "NUC100Series.h"
	#include "MCU_init.h"
	#include "GPIO.h"
	#include "SYS_init.h"
*/
#include <stdio.h>
#include "NUC100Series.h"
#include "MCU_init.h"
#include "GPIO.h"
#include "SYS_init.h"
#include "Seven_Segment.h"
#include "Scankey.h"
// ASCII
#define S 83
#define E 69
#define t 116
#define F 70
#define A 65
#define L 76
#define r 114


void OpenAll(){// Setmode for all GPIO that is needed
	
	// KeyPad
	OpenKeyPad();
	// Seven_Segment
	OpenSevenSegment();
	// LED
	GPIO_SetMode(PC, BIT12, GPIO_PMD_OUTPUT);
	GPIO_SetMode(PC, BIT13, GPIO_PMD_OUTPUT);
	GPIO_SetMode(PC, BIT14, GPIO_PMD_OUTPUT);
	GPIO_SetMode(PC, BIT15, GPIO_PMD_OUTPUT);
	// Buzzer
	GPIO_SetMode(PB, BIT11, GPIO_PMD_OUTPUT);
	// RGB
	GPIO_SetMode(PA, BIT12, GPIO_PMD_OUTPUT);
	GPIO_SetMode(PA, BIT13, GPIO_PMD_OUTPUT);
	GPIO_SetMode(PA, BIT14, GPIO_PMD_OUTPUT);
}

void Buzz(int num){
	//Buzz
	int i;
	for (i=0; i<num; i++) {
		PB11 = 0;
		CLK_SysTickDelay(100000);
		PB11 = 1;
		CLK_SysTickDelay(100000);
	}
}

void LongBuzz(int num){
	//LongBuzz
	int i;
	for (i=0; i<num; i++) {
		PB11 = 0;
		CLK_SysTickDelay(100000000);
		PB11 = 1;
	}
}
void ShowSevenDetail(int no, int num){
	
		
	//Init All 4 PC
	CLK_SysTickDelay(1000);
	PC4 = PC5 = PC6 = PC7 = 0;
	switch (no) {
		case 0:
			PC4 = 1;
			break;
		case 1:
			PC5 = 1;
			break;
		case 2:
			PC6 = 1;
			break;
		case 3:
			PC7 = 1;
			break;
	}
	//Set 7-Segment's PC
	
	/* 
	PE Number
			3
			- 
	2 |   | 4				
			- 7
	6 |   | 0
			-     .1
			5
	*/
	
	//Init All 8 
	PE0 = 1; PE1 = 1; PE2 = 1; PE3 = 1; PE4 = 1; PE5 = 1; PE6 = 1; PE7 = 1;
	//Set 7-Segment's PE
	if (num == S || num == A || num == 0 || num == 1 || num == 3 || num == 4 || num == 5 || num == 6 || num == 7 || num == 8 || num == 9)
		PE0 = 0;
	if (num == S || num == E || num == t || num == F || num == A || num == L || num == 0 || num == 4 || num == 5 || num == 6 || num == 8 || num == 9)
		PE2 = 0;
	if (num == S || num == E || num == F || num == A || num == 0 || num == 2 || num == 3 || num == 5 || num == 6 || num == 7 || num == 8 || num == 9)
		PE3 = 0;
	if (num == A || num == 0 || num == 1 || num == 2 || num == 3 || num == 4 || num == 7 || num == 8 || num == 9)
		PE4 = 0;
	if (num == S || num == E || num == t || num == L || num == 0 || num == 2 || num == 3 || num == 5 || num == 6 || num == 8)
		PE5 = 0;
	if (num == E || num == t || num == F || num == A || num == L || num == r || num == 0 || num == 2 || num == 6 || num == 8)
		PE6 = 0;
	if (num == S || num == E || num == t || num == F || num == A || num == r || num == 2 || num == 3 || num == 4 || num == 5 || num == 6 || num == 8 || num == 9)
		PE7 = 0;
}

void ShowNumber(int sum){
	
	//Show 3 types of number 
	int i, num[4];
	for (i=0; i<4; i++) {
		num[i] = sum % 10;
		sum = sum / 10;
	}
	for (i=0; i<100; i++) {
		ShowSevenDetail(0, num[0]);
		ShowSevenDetail(1, num[1]);
		ShowSevenDetail(2, num[2]);
		ShowSevenDetail(3, num[3]);
	}
	CloseSevenSegment();
}

void ShowFalse(int num){
	
	//False 跑馬燈
	
	//RGB 3 times	
	int i, j, k, wrong[14] = {0, 0, 0, 0, F, A, L, S, E, 0, num, 0, 0, 0};
	for (i=0; i<2; i++) {
		for (j=0; j<11; j++) {
			for (k=0; k<100; k++) {
				
				if (wrong[j] != 0) ShowSevenDetail(3, wrong[j]);
				if (wrong[j + 1] != 0) ShowSevenDetail(2, wrong[j + 1]);
				if (wrong[j + 2] != 0) ShowSevenDetail(1, wrong[j + 2]);
				if (wrong[j + 3] != 0) ShowSevenDetail(0, wrong[j + 3]);
			}
		}
	}
	CloseSevenSegment();
	
	for (i=0; i<3; i++) {
		CLK_SysTickDelay(100000);
		PA14 = 0;
		CLK_SysTickDelay(100000);
		PA14 = 1;
	}
}

void ShowIncrement(int input, int sum[]){
	
		int i;
		//Blink increased number while using Buzz
		if (input == 1 || input == 3) {
			if (input == 1) sum[0]--;
			else sum[0]++;
			
			for (i=0; i<2; i++) {
				ShowNumber(sum[0]);
				LongBuzz(1);
				ShowNumber(sum[0]);
				Buzz(1);
				ShowNumber(sum[0]);
			}
		}
		else if (input == 4 || input == 6) {
			if (input == 4) sum[1]--;
			else sum[1]++;
			
			for (i=0; i<2; i++) {
				ShowNumber(sum[1]);
				LongBuzz(1);
				ShowNumber(sum[1]);
				Buzz(1);
				ShowNumber(sum[1]);
			}
		}
		else if (input == 7 || input == 9) {
			if (input == 7) sum[2]--;
			else sum[2]++;
			
			for (i=0; i<2; i++) {
				ShowNumber(sum[2]);
				LongBuzz(1);
				ShowNumber(sum[2]);
				Buzz(1);
				ShowNumber(sum[2]);
			}
		}
		//RGB 3 times
		for (i=0; i<3; i++) {
			CLK_SysTickDelay(100000);
			PA13 = 0;
			CLK_SysTickDelay(100000);
			PA13 = 1;
		}
		
}
int main(void)
{
/*
  請勿修改以下部分
	Do not edit the following lines.
	SYS_Init();
	SYS_LockReg();
	LOCKREG();
*/	
	//Declaration
	int i, j, tmp = 0, input;
	int sum[3] = {0, 0, 0};
	int flag[3] = {0, 0, 0};
	

	SYS_Init();
	SYS_LockReg();
	LOCKREG();
	
	OpenAll();
	//Scankey(While) & Show Number & Set 1/2/3
	for (i=0; i<3; i++) {
		for (j=0; j<4; j++) {
			while (tmp == 0) 
				tmp = ScanKey();
			sum[i] = sum[i] * 10 + tmp;
			while (tmp != 0)
				tmp = ScanKey();
			ShowNumber(sum[i]);
		}
		for (j=0; j<100; j++) {
			ShowSevenDetail(3, S);
			ShowSevenDetail(2, E);
			ShowSevenDetail(1, t);
			ShowSevenDetail(0, i+1);
		}
		CloseSevenSegment();
	}
	//Keypad Settings
	while(1){
			//Scankey(While)
			while (tmp == 0)
				tmp = ScanKey();
			input = tmp;
			while (tmp != 0)
				tmp = ScanKey();
			//Check Scankey
					//Check Lock
							//Unlock if lock, lock if unlock
			if (input == 2) {
				if (flag[0] == 0) {
					flag[0] = 1;
					PC12 = 0;
				}
				else {
					flag[0] = 0;
					PC12 = 1;
				}
				CLK_SysTickDelay(100000);
			}
			else if (input == 5) {
				if (flag[1] == 0) {
					flag[1] = 1;
					PC13 = 0;
				}
				else {
					flag[1] = 0;
					PC13 = 1;
				}
				CLK_SysTickDelay(100000);
			}
			else if (input == 8) {
				if (flag[2] == 0) {
					flag[2] = 1;
					PC14 = 0;
				}
				else {
					flag[2] = 0;
					PC14 = 1;
				}
				CLK_SysTickDelay(100000);
			}
			//Increase or Decrease
					//Not Lock
			else if ( ((input == 1 || input == 3) && flag[0] == 0) ||
								((input == 4 || input == 6) && flag[1] == 0) ||
								((input == 7 || input == 9) && flag[2] == 0)) {
									ShowIncrement(input, sum);
			}
								
					//Locked
			else {
				if (input == 1 || input == 3) input = 1;
				if (input == 4 || input == 6) input = 2;
				if (input == 7 || input == 9) input = 3;
				ShowFalse(input);
				
			}
}
	
	
	
	
}

