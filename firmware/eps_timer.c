#include <msp430.h>
#include "eps_timer.h"
#include "eps_onewire.h"
#include "eps_i2c.h"
#include "watchdog.h"
#include "ADS1248.h"
#include "pid.h"
#include <stdlib.h>

volatile unsigned int cont = 0;
volatile float duty_cycle = 0;
volatile long t = 0;
volatile float temperature = 0;
volatile extern char EPS_Data[23];

struct Pid parameters = {0, 0, 1, 250, 20, 0 , INT_MAX, 150};


/********** INTERRUPTS **********/

#pragma vector=TIMER0_A0_VECTOR
__interrupt void vtimer0_a0_isr(void){

    P1OUT ^= 0x01;		// Toggle P1.0
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void vtimer1_a0_isr(void){

	P3OUT ^= 0x01;		// Toggle P3.0
}


/*
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
	__bis_SR_register(GIE);
	if(cont==9){												// period = CCR0 * 2 * cont / clock => 1 = 50000*2*cont/(10^6) => cont = 9 (starts at 0)
		cont = 0;												// reset cont


		measurement_data_DS2775();
		wdt_reset_counter();
		read_ADS1248(6);
		wdt_reset_counter();
		temperature = (read_ADS1248(6)*0.00111342/8 - 1000)/3.85;
		duty_cycle = Pid_Control(42,temperature,parameters);
		TBCCR3 = (1-duty_cycle)*PWM_PERIOD/2;
		wdt_reset_counter();
		make_frame();
		wdt_reset_counter();
	}else{
		cont ++;											// increments cont to achieve desired output period
		wdt_reset_counter();
	}
}
*/
void make_frame(void)
{
	EPSData[0] = '{';
	EPSData[1] = '{';
	EPSData[2] = '{';
	EPSData[3] = cr_msb;
	EPSData[4] = cr_lsb;
	EPSData[5] = vr_msb1;
	EPSData[6] = vr_lsb1;
	EPSData[7] = vr_msb2;
	EPSData[8] = vr_lsb2;
	EPSData[9] = tr_msb;
	EPSData[10] = tr_lsb;
	EPSData[11] = acr_msb;
	EPSData[12] = acr_lsb;
	EPSData[13] =  RG_Protection;
//	EPSData[14] = temp[0];
//	EPSData[15] = temp[1];
//	EPSData[16] = temp[2];
	EPSData[17] = 0;
	EPSData[18] = 0;
	EPSData[19] = 0;
	EPSData[20] = '}';
	EPSData[21] = '\n';
	EPSData[22] = '\r';
}
