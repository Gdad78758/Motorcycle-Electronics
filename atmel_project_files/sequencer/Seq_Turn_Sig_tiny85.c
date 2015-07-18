/*
 * $safeprojectname$.c
 *
 * Created: 5/15/2015 3:06:46 PM
 *  Author: Roger
 */ 

 
//********** Includes **********

#define F_CPU  1000000UL
#include <avr/io.h>     
#include <util/delay.h>   
#include <avr/interrupt.h>

//********** Definitions **********

// LED Segment Control Outputs

#define Segment1   PB0
#define Segment2   PB1
#define Segment3   PB3
#define Segment4   PB4
#define IO_PORT  PORTB
#define IO_DDR   DDRB


// Turn Signal Control Input Pin

#define TS_SWITCH   PINB2   // bit is clear when turn signal is activated
#define TS_SWITCH_PORT PINB


//********** Function Prototypes **********

void setup( void );
void ts_seq();
void marker_light();


//********** Global Variables **********

volatile uint32_t  timestamp = 0;
volatile uint32_t  old_timestamp = 0;
volatile uint32_t  time_period = 0;
volatile uint8_t   timeout = 0;

/*
ISR(INT0_vect)
{
	timeout = 0;
	TCNT1 = 0x00;
	
}

ISR(TIMER1_OVF_vect)
{
	if (bit_is_clear(TS_SWITCH_PORT, TS_SWITCH))
	{
		marker_light(); 
	}
}
*/


int main(void)
{


setup();



 while(1)
 { 
  
  
  while (bit_is_clear(TS_SWITCH_PORT, TS_SWITCH))
	{  
		ts_seq();  
	}
  
  
  while(bit_is_set(TS_SWITCH_PORT, TS_SWITCH))
	{
		//marker_light();	
	}
  
       
 }
}


//********** Functions **********

void setup(void)
{

 //********* Port Config *********

IO_DDR |= (1 <<Segment4) | (1<<Segment3) | (1<<Segment2) | (1<<Segment1);  // set led segment control pins to "1" for output 
IO_PORT &= ~((1 <<Segment4) | (1<<Segment3) | (1<<Segment2) | (1<<Segment1));   // turn the led segments off

IO_DDR &= ~( 1 << TS_SWITCH );   // set TS_SWITCH pin to 0 for input
//IO_PORT |= ( 1 << TS_SWITCH );   // write a 1 to TS_SWITCH to enable the internal pullup

 //**********Interrupt Enable***************
 
TCCR1 &= ~((1<<CS13) | (1<<CS12) | (1<<CS11) | (1<<CS10));
//TIMSK |= 1<<TOIE1; 
//GIMSK |= 1<<INT0;	// Enable INT0 (input pin B2) 
//MCUCR |= (1<<ISC01) | (1<<ISC00);	// Trigger INT0 on rising edge
//sei();				//Enable Global Interrupts
}


void marker_light()
{
 
	 // low intensity marker light sequencing loop
	 
	 uint16_t on_delay = 100; // delay after turn on
	 uint16_t off_delay = 1000; // delay after turn off
	 
	 IO_PORT |= (1<<Segment4) | (1<<Segment3) | (1<<Segment2) | (1<<Segment1);
	 _delay_us(on_delay);
	 IO_PORT &= ~((1<<Segment4) | (1<<Segment3) | (1<<Segment2) | (1<<Segment1));
	 _delay_us(off_delay);
   
}   

void ts_seq()

{
	uint16_t delay_between_seq = 233; // delay between segments
	uint16_t delay_after_seq = 233; //delay after segments shutoff
	
	//  create the turn signal sequencing with delays between segments

	IO_PORT |= (0<<Segment4) | (0<<Segment3) | (0<<Segment2) | (1<<Segment1);
	_delay_ms(delay_between_seq);
	IO_PORT |= (0<<Segment4) | (0<<Segment3) | (1<<Segment2) | (1<<Segment1);
	_delay_ms(delay_between_seq);
	IO_PORT |= (0<<Segment4) | (1<<Segment3) | (1<<Segment2) | (1<<Segment1);
	_delay_ms(delay_between_seq);
	IO_PORT |= (1<<Segment4) | (1<<Segment3) | (1<<Segment2) | (1<<Segment1);
	_delay_ms(delay_between_seq);
	IO_PORT &= ~((1<<Segment4) | (1<<Segment3) | (1<<Segment2) | (1<<Segment1));
	_delay_ms(delay_after_seq);
}