// Hunter Frady and Mitchell Jonker
// library to use altera i/o functions
#include "sys/alt_stdio.h"

// library to use altera variable types
#include "alt_types.h"

// library to get all hardware definitions
#include "system.h"

// library that has the definition of pio functions
#include "altera_avalon_pio_regs.h"

// C standard libraries
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

// Needed Definitions
// IOWR - IO Write Register
// IORD - IO Read Data
// SYSTEM_MODES_BASE
// SYSTEM_COUNTER_BASE
// RANDOM_PATTERN_BASE
// IOWR_ALTERA_AVALON_PIO_DATA(baseAddress, value);
// x = IORD_ALTERA_AVALON_PIO_DATA(baseAddress);
// recording in BB if needed


int main() {
  alt_putstr("Hunter Frady and Mitchell Jonker - Project2 - CSCE 313\n");

  // declare the mode variable as alt_u8 and initialize with 0:
	alt_u8 mode = 0x00;
  // declare the counter variable as alt_u8 and initialize with 0:
	alt_u8 counter = 0x00;

  // declare the random variable as alt_u8 and initialize with 0:
	alt_u8 rand_var = 0x00;
  
  // declare number of random patterns as int. You can initialize it with any number you wish:
	int num_pattern = 5;

  /* Event loop never exits. */
  while (1) {

    // read the mode values from system_modes using the function:
    mode = IORD_ALTERA_AVALON_PIO_DATA(SYSTEM_MODES_BASE);

    //:

    // check if the mode is 1 so all LEDs must light up:
    // Both red and green LEDs light up
		if (mode == 0x1) {
      alt_putstr("All LEDs Light Up\n");

			// Example to how light Decoder_output LEDs. Do the same to light other leds
			IOWR_ALTERA_AVALON_PIO_DATA(SYSTEM_COUNTER_BASE, 0xFF);
      //IOWR_ALTERA_AVALON_PIO_DATA(RANDOM_PATTERN_BASE, 0xFFFFF);

		} // end mode 0x1

    // check if the mode is 2 so system counter starts counting:
    // A counter starts incrementing from 0 to 255
    // and the value is displayed on Green LED [7:0].
		if (mode == 0x2) {
			alt_putstr("System Counter Mode\n");

      // First, reset all LEDs as shown in the example below

      IOWR_ALTERA_AVALON_PIO_DATA(DECODER_OUTPUT_BASE, 0x0000);
          //:

      // Counter starts counting from 0 (0x00) to 255 (0xFF)
      for (int i=0; i<256; i++) {

        // always keep checking If the mode values changed. If mode changes, break the loop. See the below code
        mode = IORD_ALTERA_AVALON_PIO_DATA(SYSTEM_MODES_BASE);
        if (mode != 0x2) {
          break;
        }
        // IOWR - IO Write Register
        // IORD - IO Read Data
        // display the counter value onto the system-counter LEDs using IOWR_ALTERA_AVALON_PIO_DATA:
        IOWR_ALTERA_AVALON_PIO_DATA(SYSTEM_COUNTER_BASE, counter);
        // increment counter by 1:
        counter = counter + 0x1;
        // time the display period of each counter value using usleep()
        // sleep time for 1 million micro seconds
        // adjust as necessary
        usleep(1000000);

      } // end for loop
		} // end mode 0x2

    // check if the mode is 3 so random pattern starts:
    // A random pattern starts is displayed on Red LED [17:0].
    // If the mode changes, the pattern stops on latest value.
    if (mode == 0x3) {
      alt_putstr("Random Pattern Mode\n");

      // First, reset all LEDs as shown in the example below:
      IOWR_ALTERA_AVALON_PIO_DATA(DECODER_OUTPUT_BASE, 0x0000);


      for (int i=0; i<num_pattern; i++) {

        // always keep checking If the mode values changed. If mode changes, break the loop. (as code shown in mode=1 code):
        if (mode != 3) {
          break;
        }
        // generate random pattern using rand() function:
        rand_var = rand();
        // display the random value onto the random-pattern LEDs using IOWR_ALTERA_AVALON_PIO_DATA:

        // time the display period of each counter value using usleep()
        usleep(1000000); // time for 1 million micro seconds

      }


    } // end mode 0x3
				

  } // end while loop
  
  return 0;
}
