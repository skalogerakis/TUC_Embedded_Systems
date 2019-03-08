/*
 * COURSE: EMBEDDED SYSTEMS, HRY411 
 * 
 * Lab1_Loop.c
 *
 * Lab1: BLINKING LED EVERY SEC USING LOOPS
 * 
 * Created at : ATMELSTUDIO
 * Created: 3/8/2019 12:06:57 AM
 * Authors : Stefanos Kalogerakis, Aris Zervakis
 */ 

#include <avr/io.h>

void loopCounter(){
	//Initialize port for the LED
	DDRB = 0b00000001;
	PORTB = 0b00000000;
	
	
	/*
		Setup a counter that will turn on and off the led in every second.
		As we have noticed from the link below in order to make this right we need to 
		take into consideration the cycles in each loop and the delay we want based on
		the following equation: Tdelay = (Num_of_cycles_loop * number_of_loop_times -1)*period_of_machine_cycle.
		We looked the assembly code and we determined that we have 6 cycles/loop for 1MHz clock frequency.
		We solved the equation and we came up with the number of times that we need to loop(1666666).
		*** The timer is not 100% accurate as we needed to subtract all the procedures that take cycles from our clock.
		So we lose 2 cycles in each loop but it is translated in some ìs of time.
		http://web.csulb.edu/~hill/ee346/Lectures/06%20AVR%20Looping.pdf
	*/
	while(1){
		for(uint32_t i= 0; i< 166666; i++){
			if(i == 166666-1){
				PORTB ^= 1 << PINB0;
			}
		}
	}
}


int main(void)
{
    //The following code will produce a blinking led every second in the same output.
	
	loopCounter();
	
}

