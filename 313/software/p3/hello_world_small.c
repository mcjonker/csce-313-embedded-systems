// CSCE-313 Mitchell Jonker & Hunter Frady Project 3

// p3

// Altera libraries
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
// IOWR - IO Write Register
// IORD - IO Read Data
// SYSTEM_MODES_BASE - switches
// BCD_INPUT_BASE - four switches thing
// SPEED_CONTROLLER_BASE - speed switch
// SEGMENT4_BASE - "5th seg display"
// RANDOM_PATTERN_BASE - red
// IOWR_ALTERA_AVALON_PIO_DATA(baseAddress, value);
// x = IORD_ALTERA_AVALON_PIO_DATA(baseAddress);
// recording in BB if needed
// alt_putstr(""); -> altera push string

int main() {

	alt_putstr("Hunter Frady and Mitchell Jonker - Project 3 - CSCE 313\n");

  	// declare the mode variable as alt_u8 and initialize with 0:
	alt_u8 mode = 0x00;

	// declare the random variable as alt_u8 and initialize with 0:
	alt_u8 rand_var = 0x00;

	// declare the speed condition variable
	int speed_var = 0;

	// declare the bcd input variable
	alt_u8 bcd_input = 0x00;

	// usleep variable
	int delay = 300000;

	/* Event loop never exits. */
	while (1) {
		speed_var = IORD_ALTERA_AVALON_PIO_DATA(SPEED_CONTROLLER_BASE);
		// speed controller switch
		if (speed_var == 1) {
			delay = 300000;
		} else {
			delay = 125000;
		}

		// read the mode values from system_modes using the function:
		mode = IORD_ALTERA_AVALON_PIO_DATA(SYSTEM_MODES_BASE);

		if (mode == 0x00) {
			alt_putstr("MODE 0\n");

		}
		if (mode == 0x1) {
		  alt_putstr("MODE 1\n");
		  bcd_input = IORD_ALTERA_AVALON_PIO_DATA(BCD_INPUT_BASE);

		  if(bcd_input == 0x00) {
			  IOWR_ALTERA_AVALON_PIO_DATA(SEGMENT4_BASE, 0x11000000);
		  }
		  if(bcd_input == 0x01) {
			  IOWR_ALTERA_AVALON_PIO_DATA(SEGMENT4_BASE, 0x11111001);
		  }
		  if(bcd_input == 0x02) {
			  IOWR_ALTERA_AVALON_PIO_DATA(SEGMENT4_BASE, 0x101010100);
		  }
		  if(bcd_input == 0x03) {
			  IOWR_ALTERA_AVALON_PIO_DATA(SEGMENT4_BASE, 0x10100100);
		  }
		  if(bcd_input == 0x04) {

		  }
		  if(bcd_input == 0x05) {

		  }
		  if(bcd_input == 0x06) {

		  }
		  if(bcd_input == 0x07) {

		  }
		  if(bcd_input == 0x08) {

		  }
		  if(bcd_input == 0x09) {

		  }

		} // end mode 0x1
		if (mode == 0x2) {
			alt_putstr("MODE 2\n");

		  // Counter starts counting from 0 (0x00) to 255 (0xFF)
		  for (; ; ) {

			// always keep checking If the mode values changed. If mode changes, break the loop. See the below code
			//mode = IORD_ALTERA_AVALON_PIO_DATA(SYSTEM_MODES_BASE);
			if (mode != 0x2) {
			  break;
			}
		  } // end for loop
		} // end mode 0x2

	if (mode == 0x3) {
	  alt_putstr("MODE 3\n");

	} // end mode 0x3

  } // end while loop

  return 0;
}
