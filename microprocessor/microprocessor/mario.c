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

unsigned char pic[32]={0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x02, 0x82, 0x42, 0x24, 0x3f, 0x44, 0x44, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00};

volatile uint8_t u8ADF;
volatile uint16_t X, Y;
volatile uint8_t  B;
int loc[10]={0,0,0,0,0,0,0,0,0,0};
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
	CLK_SysTickDelay(10000);
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
		int move_h=0;
		int move=0;
		int move_x=128;
		int move_type=0; 
		int sum=0;
		int error=1;
		int a,b; 
		int trap=0;
    uint32_t u32ADCvalue;
    SYS_Init();
    Init_ADC();
	  init_LCD();
	  clear_LCD();
		
    u8ADF = 0;
		PD14 = 0;
    GPIO_SetMode(PC, BIT0, GPIO_MODE_INPUT); // set PC0 input for button
		PC15=0;
		PC14=0;
		PC13=0;
		PC12=0;
		
    while(1)
		{
			
			switch(error){
				case 1:
					PC15=0;
					PC14=0;
					PC13=0;
					PC12=0;
					break;
				case 2:
					PC14=0;
					PC15=1;
					PC13=0;
					PC12=0;
					break;
				case 3:
					PC15=1;
					PC14=1;
					PC12=0;
					PC13=0;
					break;
				case 4:
					PC15=1;
					PC14=1;
					PC13=1;
					PC12=0;
					break;
				case 5:
					PC15=1;
					PC14=1;
					PC13=1;
					PC12=1;
					break;
			}
			if(error==5){
				clear_LCD();
				print_Line(1,"GAME OVER");	
				break;
			}
	    clear_LCD();
			if(Y<1000){
				move=1;
			}

			if(move==1){
				move_h++;
				if(move_h==15)
					move=0;
			}
			else if(move==0){
				move_h--;
				if(move_h<0)
					move_h=0;
			}
			
			switch(move_type){
				case 1:
					move_x=move_x-5;
					break;
				case 2:
					move_x=move_x-10;
					break;
				case 3:
					move_x=move_x-20;
					break;
			}
			
			if(move_x<2 || move_x==128){
				move_x=127;
				move_type=(rand()%3)+1;
				trap=1;
			}
				
			if(move_x<12 && move_h<5 && trap==1){
				error++;
				trap=0;
			}
			else if(move_x<12 && move_h>5 &&trap==1){
				sum++;
				trap=0;
			}
			
			a=sum%10;
			b=sum/10;
			showSeven(1,a);
			showSeven(2,b);
			
					
			
			
			
			draw_Bmp16x16(0,30-move_h,FG_COLOR,BG_COLOR,pic);
			printC_5x7(move_x,40,'**');
			CLK_SysTickLongDelay(100000);
	
				
    }
}
