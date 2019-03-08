
/*
 * COURSE: EMBEDDED SYSTEMS, HRY411 
 * 
 * Lab1_Timer.c
 *
 * Lab1: BLINKING LED EVERY SEC USING LOOPS
 * 
 * Created at : ATMELSTUDIO
 * Created: 3/6/2019 11:48:44 AM
 * Authors : Stefanos Kalogerakis, Aris Zervakis
 */ 

#include <avr/io.h>

//#define F_CPU 1000000UL	//Define cpu clock
//#define PRESCALER 64

void timerEnabler(){
	//Initialize port for the LED's
	DDRB = 0b00000001;
	PORTB = 0b00000000;
	
	//unsigned int delay = 1;
	/*
		We use 16bit TIMER1. We also want to prescale clock so we need to choose Timer/Counter1 Control Register B.
		Prescale with 64 so we need to activate cs11 and cs10( More info in atmega16A datasheet)
	*/
	TCCR1B |= 1<<CS10 | 1<<CS11;
	
    while (1) 
    {
		/*
			To compute our TCNT(our counter basically) we first find clock period( Clock_period = 1/clock frequency ). 
			Also in order to use prescaler just divide clock frequency with prescaler 
			The we use the following formula found in the link below to adjust our counter Timer_Count = Delay/clock_period) - 1 = 15,624 for a 64 prescaler, 1s delay and 1Mh clock frequency.
			http://maxembedded.com/2011/06/introduction-to-avr-timers/
			
			We could also set the counter dynamically but we avoid that to compute less calculations as we meet the requirements as is
		*/
		if(TCNT1 > 15624){
			TCNT1 = 0;	//Reset TCNT
			PORTB ^= 1 << PINB0;
		}
		
    }
}


int main(void)
{
    //The following code will produce a blinking led every second in the same output.
	timerEnabler();
	
}

