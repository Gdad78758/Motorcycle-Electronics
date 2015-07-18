/*
 * $safeprojectname$.c
 *
 * Created: 6/9/2015 4:25:26 PM
 *  Author: Roger
 */ 


#define F_CPU  1000000UL

#include <avr/io.h>
#include <util/delay.h> 
#include <avr/interrupt.h>
//#include <avr/wdt.h>  

//********** Definitions **********


// Flasher Output pins

#define TS_FLASHER  PB4

// Control Ports

#define IO_PORT  PORTB
#define IO_DDR   DDRB


// Flasher Control Comparator Input Pins

#define POS_PIN  PINB0   // positive comparator input pin
#define NEG_PIN  PINB1   // negative comparator input pin

// Control Ports
 
#define IN_PORT  PINB



//********** Function Prototypes **********

void setup( void );



//********** Main Loop **************

int main(void)
{
	
	setup();
	
	//wdt_enable(2);
	
	
 while(1)
	
	{
		
		//wdt_reset();
	
    
		if(bit_is_clear(ACSR, ACO))
		
			{
				_delay_ms( 40 ); // filter time aka debounce
			}
			
			if(bit_is_clear(ACSR, ACO))
						
					
					{	IO_PORT |= (1<<TS_FLASHER);  // hold flasher output high for 1/2 period						
						_delay_ms(333);
						IO_PORT &= ~(1<<TS_FLASHER);  // hold flasher output low for 1/2 period
						_delay_ms(333);
					}
				
				
				
		
		 	
		if(bit_is_set(ACSR, ACO))
		
			{
				_delay_ms( 40 ); // filter time aka debounce
					
			}
			
			if(bit_is_set(ACSR, ACO))
			
				
					
					{
						IO_PORT &= ~(1<<TS_FLASHER);  // hold flasher output constant low
						_delay_ms(333);
					}
	  
				
				
			}
			
			
	}


//********** Functions **********

void setup(void)
{

 //********* Port Config *********
 
MCUCR |= (1<<PUD); // disable all pullups

IO_DDR |=  (1<<TS_FLASHER);  // set TS flasher output pin DDR to "1"  
IO_PORT &=  ~(1<<TS_FLASHER);   // force TS flasher output low

IO_DDR &= ~((1<<NEG_PIN) | (1<<POS_PIN));   // set pin B0 and pin B1 comparator pins DDR to 0 for input
//IO_PORT |= (1<<TS_FLASHER_CNTRL);   // write a 1 to TS flasher control pin to enable internal pullup (currently masked by MCUCR PUD bit)

DIDR0 |= (1<<AIN1D) | (1<<AIN0D);  // disable digital input buffer on comparator input pins 

//OCR1B = 0x4F;  // set timer 1 50% duty cycle match value
//OCR1C = 0x9D;  // set timer 1 max value (pwm freq ~ 1.5Hz)

//TCCR1 |= (1<<CS13) | (1<<CS12) | (1<<CS10);    // enable timer clock prescaler
//GTCCR |= (1<<PWM1B) | (1<<COM1B1) | (1<<COM1B0);  //  enable pwm compare match output on pin PB4 and output phasing

}