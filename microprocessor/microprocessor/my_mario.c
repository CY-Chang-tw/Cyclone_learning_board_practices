//
// TMR_Capture_SR04 : usi[ng Timer Capture to read Ultrasound Ranger SR-04
//
// EVB : Nu-LB-NUC140 (need to manually switch RSTCAPSEL)
// MCU : NUC140VE3CN
// Sensor: SR-04

// SR-04 connection
// Trig connected to PB8
// Echo connected to TC2/PB2 (TC0_PB15, TC1_PE5, TC2_PB2, TC3_PB3)

#include <stdio.h>
#include <stdlib.h>
#include "NUC100Series.h"
#include "MCU_init.h"
#include "SYS_init.h"
#include "LCD.h"


unsigned char player[32]={0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x02, 0x82, 0x42, 0x24, 0x3f, 0x44, 0x44, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char box[32] = {0x00, 0xfc, 0xfa, 0xf6, 0xee, 0xde, 0xbe, 0x7e, 0x7e, 0xbe, 0xde, 0xee, 0xf6, 0xfa, 0xfc, 0x00, 
0x00, 0x3f, 0x5f, 0x6f, 0x77, 0x7b, 0x7d, 0x7e, 0x7e, 0x7d, 0x7b, 0x77, 0x6f, 0x5f, 0x3f, 0x00};

char Text0[16];
char Text1[16];
char Text2[16];
volatile uint8_t u8ADF;
volatile uint16_t X, Y;
volatile uint8_t  B;

int x = 0;                  // player
int y = 45;
int x_box = 120;            // box
int y_box = 45;
int r = 0;                  // random integer
int life = 4;
int score = 0;
int score_flag = 0;
int game_over = 0;          // game over flag
int a = 0; int b = 0;             // seven segment score



void box_transition(void){
	
	draw_Bmp16x16(x_box, y_box, FG_COLOR, BG_COLOR, box);
	x_box = x_box - 5;
}

void collision(void){              // detect collision
	if (x + 5 == x_box && y + 10 >= y_box) {
		printS_5x7(0, 20, "Oops!");
		life = life - 1;
		score_flag = 0;
		if (life == -1) {
			game_over = 1;
		}
		CLK_SysTickDelay(50000);
	} else if (x_box <= 0 && y + 10 <= y_box) {
		score_flag = 1;
		
	}
}

void led(life){
	switch(life) {
		case 4:
			PC15=0;
			PC14=0;
			PC13=0;
			PC12=0;
			break;
		case 3:
			PC15=1;
			PC14=0;
			PC13=0;
			PC12=0;
			break;
		case 2:
			PC15=1;
			PC14=1;
			PC12=0;
			PC13=0;
			break;
		case 1:
			PC15=1;
			PC14=1;
			PC13=1;
			PC12=0;
			break;
		case 0:
			PC15=1;
			PC14=1;
			PC13=1;
			PC12=1;
			break;
	}
}

void ADC_IRQHandler(void)
{
    uint32_t u32Flag;

    // Get ADC conversion finish interrupt flag
    u32Flag = ADC_GET_INT_FLAG(ADC, ADC_ADF_INT);

    if(u32Flag & ADC_ADF_INT) {
        X = ADC_GET_CONVERSION_DATA(ADC, 0);
        Y = ADC_GET_CONVERSION_DATA(ADC, 1);
    }
    ADC_CLR_INT_FLAG(ADC, u32Flag);
}

void showSeven(int no, int word){
	
	//7Seg PLEASE LOOK AT THIS STOP USING STRANGE METHOD

	PC4=0;PC5=0;PC6=0;PC7=0;
	switch(no){
		case 1: PC4=1; break;
		case 2: PC5=1; break;
		case 3: PC6=1; break;
		case 4: PC7=1; break;
	}
	
	PE0=1;PE1=1;PE2=1;PE3=1;PE4=1;PE5=1;PE6=1;PE7=1;
	if(word==0 || word==1 || word==3 || word==4 || word==5 || word==6 || word==7 || word==8 || word==9 )
		PE0=0;
	if(word==0 || word==4 || word==5 || word==6 || word==8 || word==9)
		PE2=0;
	if(word==0 || word==2 || word==3 || word==5 || word==6 || word==7 || word==8 || word==9)
		PE3=0;
	if(word==0 || word==1 || word==2 || word==3 || word==4 || word==7 || word==8 || word==9)
		PE4=0;
	if(word==0 || word==2 || word==3 || word==5 || word==6 || word==8)
		PE5=0;
	if(word==0 || word==2 || word==6 || word==8 )
		PE6=0;
	if(word==2 || word==3 || word==4 || word==5 || word==6 || word==8 || word==9 )
		PE7=0;
	CLK_SysTickDelay(20000);
}


void Init_ADC(void)
{
    ADC_Open(ADC, ADC_INPUT_MODE, ADC_OPERATION_MODE, ADC_CHANNEL_MASK );
    ADC_POWER_ON(ADC);
    ADC_EnableInt(ADC, ADC_ADF_INT);
    NVIC_EnableIRQ(ADC_IRQn);
    ADC_START_CONV(ADC);	
}

int32_t main (void)
{
    uint32_t u32ADCvalue;
    SYS_Init();
    Init_ADC();
	  init_LCD();
	  clear_LCD();
	
    u8ADF = 0;
		PD14 = 0;
    GPIO_SetMode(PC, BIT0, GPIO_MODE_INPUT); // set PC0 input for button
	
		//print_Line(0, "Joystick");

    while(1)
		{
			B = PC0;
	    /*sprintf(Text0, "%d", X);
	    sprintf(Text1, "%d", Y);
			sprintf(Text2, "%d", B);
	    print_Line(1, Text0);
	    print_Line(2, Text1);
			print_Line(3, Text2);*/
			
			clear_LCD();
			draw_Bmp16x16(x, y, FG_COLOR, BG_COLOR, player);
			
			if (x_box <= 0) {                   // random box
				r = (rand() % 3) + 1;
				if (r == 1) {
					x_box = 120;
				} else if (r == 2) {
					x_box = 80;
				} else if (r == 3) {
					x_box = 60;
				}
			}
			
			
			if (Y < 2800) {
				while (y > 21) {
					clear_LCD();
					draw_Bmp16x16(x, y, FG_COLOR, BG_COLOR, player);
					y = y - 3;
					box_transition();
					collision();
					showSeven(1, a);
					showSeven(2, b);
					led(life);
					CLK_SysTickDelay(10000);
				}
				while (y < 45) {
					clear_LCD();
					draw_Bmp16x16(x, y, FG_COLOR, BG_COLOR, player);
					y = y + 3;
					box_transition();
					collision();
					showSeven(1, a);
					showSeven(2, b);
					led(life);
					CLK_SysTickDelay(10000);
				}
			} else {
				clear_LCD();
				draw_Bmp16x16(x, y, FG_COLOR, BG_COLOR, player);
				box_transition();
				collision();
				showSeven(1, a);
				showSeven(2, b);
				led(life);
				CLK_SysTickDelay(10000);
			}
			if (score_flag == 1 && y == 45) {
				score = score + 1;
				a = score % 10;
				b = score / 10;
				score_flag = 0;
			}
			if (game_over == 1) {
				printS_5x7(50, 25, "GAME OVER!");
				break;
			}
			
    }
}