// CSCE-313 Mitchell Jonker & Hunter Frady Project 3

// p3

// Altera and hardware libraries
#include "sys/alt_stdio.h"
#include "alt_types.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
// C standard libraries
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

// * * * Definitions * * *
// * * * * * * * * * * * *
// IOWR - IO Write Data
// IOWR_ALTERA_AVALON_PIO_DATA(baseAddress, value);
// - - - - - - - - - -
// IORD - IO Read Data
// x = IORD_ALTERA_AVALON_PIO_DATA(baseAddress);
// - - - - - - - - - -
// SYSTEM_MODES_BASE - switches
// BCD_INPUT_BASE - four-bit binary switch input
// SPEED_CONTROLLER_BASE - speed switch
// SEGMENT4_BASE - "5th seg display"
// RANDOM_PATTERN_BASE - red LEDs
// - - - - - - - - - -
// alt_putstr(""); -> altera push string
// * * * * * * * * * * * *

alt_u8 bcdEncode(alt_u8 bcd_input) {
  switch (bcd_input) {
    // This function encodes the switch input
    // to display the correct # on the 7seg
  	// active low BCD to 7seg encoder
    case 0x00: return 0xC0; // 0 on 7seg
    case 0x01: return 0xF9; // 1 on 7seg
    case 0x02: return 0xA4; // 2 on 7seg
    case 0x03: return 0xB0; // 3 on 7seg
    case 0x04: return 0x99; // 4 on 7seg
    case 0x05: return 0x92; // 5 on 7seg
    case 0x06: return 0x82; // 6 on 7seg
    case 0x07: return 0xF8; // 7 on 7seg
    case 0x08: return 0x80; // 8 on 7seg
    case 0x09: return 0x98; // 9 on 7seg
    case 0x0A: return 0x88; // A on 7seg
    case 0x0B: return 0x83; // B on 7seg
    case 0x0C: return 0xC6; // C on 7seg
    case 0x0D: return 0xA1; // D on 7seg
    case 0x0E: return 0x86; // E on 7seg
    case 0x0F: return 0x8E; // F on 7seg
    default: return 0xFF;

  }
}

int main() {

	alt_putstr("Hunter Frady and Mitchell Jonker - Project 3 - CSCE 313\n");
	alt_u8 mode = 0; // 8-bit mode variable
	alt_u8 rand_var = 0; // 8-bit random variable
	alt_u8 speed_swc = 0; // 8-bit speed condition variable
	alt_u8 bcd_input = 0; // 8-bit bcd input variable
	int delay = 300000; // usleep variable
	int counter_var = 0;

	/* Event loop never exits. */
	while (1) {
    // read necessary variables
    mode = IORD_ALTERA_AVALON_PIO_DATA(SYSTEM_MODES_BASE); // mode switches input
    speed_swc = IORD_ALTERA_AVALON_PIO_DATA(SPEED_CONTROLLER_BASE); // speed switch input
    bcd_input = IORD_ALTERA_AVALON_PIO_DATA(BCD_INPUT_BASE); // 4 bcd_input switches input

	// speed controller switch
    // (checking at top of loop so all functions follow switch-defiled speed)
	if (speed_swc == 0x1) {
      alt_putstr("Speed Updated to: 300ms");
      delay = 300000;

	} else { // assign default speed
      alt_putstr("Speed Updated to: 125ms");
      delay = 125000;

	}

	if (mode == 0x00) {
		// Turn off all 7-segment displays
		alt_putstr("Operations Reset\n");
		counter_var = 0;
		rand_var = 0;
		IOWR_ALTERA_AVALON_PIO_DATA(SEGMENT0_BASE, 0xFF);
		IOWR_ALTERA_AVALON_PIO_DATA(SEGMENT1_BASE, 0xFF);
		IOWR_ALTERA_AVALON_PIO_DATA(SEGMENT2_BASE, 0xFF);
		IOWR_ALTERA_AVALON_PIO_DATA(SEGMENT3_BASE, 0xFF);
		IOWR_ALTERA_AVALON_PIO_DATA(SEGMENT4_BASE, 0xFF);

	} // end mode 0x0

	if (mode == 0x1) {
	  alt_putstr("Decoder Mode\n");
	  // if mode changes to 1, counter from mode 2 restarts
	  // set counter to 0, and display zeros on the displays
	  counter_var = 0;
	  IOWR_ALTERA_AVALON_PIO_DATA(SEGMENT0_BASE, 0xC0); // or 0xFF?
	  IOWR_ALTERA_AVALON_PIO_DATA(SEGMENT1_BASE, 0xC0); // or 0xFF?

	  // Send encoded input to 7-segment display
	  IOWR_ALTERA_AVALON_PIO_DATA(SEGMENT4_BASE, bcdEncode(bcd_input));

	} // end mode 0x1

	if (mode == 0x2) {
		alt_putstr("Incrementing Counter Mode\n");
		// increment values to display on 7-segs
		// using bitwise operator ">>" for a rightward shift
		// this makes sure the 10's place 7-seg doesnt increment for every cycle.
		alt_u8 seg0_value = counter_var & 0x0F;
		alt_u8 seg1_value = (counter_var & 0xF0) >> 4;
		IOWR_ALTERA_AVALON_PIO_DATA(SEGMENT0_BASE, bcdEncode(seg0_value));
		IOWR_ALTERA_AVALON_PIO_DATA(SEGMENT1_BASE, bcdEncode(seg1_value));
		// Reset counter if max is reached.
		if (counter_var == 255) {
    	  counter_var = 0;
		} else {
    	  counter_var++;
      }
      usleep(delay); // speed setting

	} // end mode 0x2

    if (mode == 0x3) {
      alt_putstr("Random Pattern Mode\n");
      // generate random number then display to 7-segs
      rand_var = rand();
      alt_u8 seg2_value = rand_var & 0x0F;
      alt_u8 seg3_value = (rand_var & 0xF0) >> 4;
      IOWR_ALTERA_AVALON_PIO_DATA(SEGMENT2_BASE, bcdEncode(seg2_value));
      IOWR_ALTERA_AVALON_PIO_DATA(SEGMENT3_BASE, bcdEncode(seg3_value));
      usleep(delay); // speed setting

    } // end mode 0x3

  } // end function loop

  return 0;
}
