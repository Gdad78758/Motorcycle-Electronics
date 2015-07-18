/*
Program Description:

This program controls an array of LED lights such that when
a flasher output is applied the a series of 4 light control
signals are triggered.



Filename: TS_Sequencer_MLP_revXX.c
Author: ML Porter
2015.6.14

Int. RC Osc. 8 MHz; Start-up time PWRDWN/RESET: 6 CK/14 CK + 64 ms

*/


//********** Includes **********

#define F_CPU  1000000UL
#include <avr/io.h>     
#include <util/delay.h>   
#include <avr/interrupt.h>
#include <avr/wdt.h>

//********** Definitions **********

// LED Segment Control Outputs

#define Segment1   PB0
#define Segment2   PB1
#define Segment3   PB3
#define Segment4   PB4
#define SEGMENT_PORT  PORTB
#define SEGMENT_DDR   DDRB


// Flasher Control Input Pin

#define FLASHER   PINB2   // bit is clear when Flasher is activated
#define FLASHER_PORT PORTB

// Define the delay timings
#define LONG_DELAY_MS    500
#define SHORT_DELAY_MS    10

// Define helper macros

// write digital "high" to pin <pn> on port <prt>
#define DIGIWRITE_H(prt, pn) prt |= (1<<pn)

// write digital "low" to pin <pn> on port <prt>
#define DIGIWRITE_L(prt, pn) prt &= ~(1<<pn)

// Define long delay function

void long_delay_ms(uint16_t ms) {
    for(ms /= 10; ms>0; ms--) _delay_ms(10);
}

//********** Function Prototypes **********

void setup( void );


//********** Global Variables **********




{
	setup();
	
	while(1)
	{ 
		if ( bit_is_set( FLASHER_PORT, FLASHER ) )  // if a FLASHER pulse is applied
		{
			_delay_ms( 1 ); // filter time aka debounce
			if ( bit_is_set( FLASHER_PORT, FLASHER ) )  // if a FLASHER pulse is actually applied
			{  
// code the segments
// Segment 1
                DIGIWRITE_H(SEGMENT_PORT, Segment1);
				long_delay_ms(LONG_DELAY_MS);
				DIGIWRITE_L(SEGMENT_PORT, Segment1);
				long_delay_ms(SHORT_DELAY_MS);
				
// Segment 2
                DIGIWRITE_H(SEGMENT_PORT, Segment2);
				long_delay_ms(LONG_DELAY_MS);
				DIGIWRITE_L(SEGMENT_PORT, Segment2);
				long_delay_ms(SHORT_DELAY_MS);
				
// Segment 3
                DIGIWRITE_H(SEGMENT_PORT, Segment3);
				long_delay_ms(LONG_DELAY_MS);
				DIGIWRITE_L(SEGMENT_PORT, Segment3);
				long_delay_ms(SHORT_DELAY_MS);
				
// Segment 4
                DIGIWRITE_H(SEGMENT_PORT, Segment4);
				long_delay_ms(LONG_DELAY_MS);
				DIGIWRITE_L(SEGMENT_PORT, Segment4);
				long_delay_ms(SHORT_DELAY_MS);
			} // endif bit_is_set after debounce  
		}  // endif bit_is_set the first time
		// delay 
		// test for flasher at 12v
		// if not, then set marker
		
		
		
	}  //end while(1)
}  // end main()


//********** Functions **********

void setup(void)
{
	//********* Port Config *********

	SEGMENT_DDR |= ( 1 << Segment1);   // set PB0 to "1" for output 
	/* ( 1 << Segment1) is building a bit mask.  since the Segment1 is on pin PB0, represented
	                     by bit 1, ( 1 << 1) takes 00000001 and moves the 1 bit left 1 place,
						 yielding 00000010.  This is the mask we want. Now we perform a bitwise
						 or to place the '1' in bit 1 in the DDR register associated with FLASH_OUT
						 which happens to be defined as DDRB
	*/
	// Now do the same for the segments 2, 3, and 4
	SEGMENT_DDR |= ( 1 << Segment2);
	SEGMENT_DDR |= ( 1 << Segment3);
	SEGMENT_DDR |= ( 1 << Segment4);
	
	SEGMENT_PORT &= ~( 1 << Segment1 );   // turn the segment1 mosfet off
	/* this is taking the same bit mask above (00000010) and taking the negative of it (11111101)
	   and bitwise anding it with the SEGMENT_PORT - this sets a zero in the SEGMENT_PORT bit 1 without
	   disturbing the other bits
	*/
	// Now do the same for the segments 2, 3, and 4
	SEGMENT_PORT &= ~( 1 << Segment2 );
	SEGMENT_PORT &= ~( 1 << Segment3 );
	SEGMENT_PORT &= ~( 1 << Segment4 );

	
	FLASHER_DDR &= ~( 1 << FLASHER );   // set FLASHER pin to 0 for input
	FLASHER_PORT |= ( 1 << FLASHER );   // write a 1 to FLASHER to enable the internal pullup

}