/* 
 * "Small Hello World" example. 
 * 
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example 
 * designs. It requires a STDOUT  device in your system's hardware. 
 *
 * The purpose of this example is to demonstrate the smallest possible Hello 
 * World application, using the Nios II HAL library.  The memory footprint
 * of this hosted application is ~332 bytes by default using the standard 
 * reference design.  For a more fully featured Hello World application
 * example, see the example titled "Hello World".
 *
 * The memory footprint of this example has been reduced by making the
 * following changes to the normal "Hello World" example.
 * Check in the Nios II Software Developers Manual for a more complete 
 * description.
 * 
 * In the SW Application project (small_hello_world):
 *
 *  - In the C/C++ Build page
 * 
 *    - Set the Optimization Level to -Os
 * 
 * In System Library project (small_hello_world_syslib):
 *  - In the C/C++ Build page
 * 
 *    - Set the Optimization Level to -Os
 * 
 *    - Define the preprocessor option ALT_NO_INSTRUCTION_EMULATION 
 *      This removes software exception handling, which means that you cannot 
 *      run code compiled for Nios II cpu with a hardware multiplier on a core 
 *      without a the multiply unit. Check the Nios II Software Developers 
 *      Manual for more details.
 *
 *  - In the System Library page:
 *    - Set Periodic system timer and Timestamp timer to none
 *      This prevents the automatic inclusion of the timer driver.
 *
 *    - Set Max file descriptors to 4
 *      This reduces the size of the file handle pool.
 *
 *    - Check Main function does not exit
 *    - Uncheck Clean exit (flush buffers)
 *      This removes the unneeded call to exit when main returns, since it
 *      won't.
 *
 *    - Check Don't use C++
 *      This builds without the C++ support code.
 *
 *    - Check Small C library
 *      This uses a reduced functionality C library, which lacks  
 *      support for buffering, file IO, floating point and getch(), etc. 
 *      Check the Nios II Software Developers Manual for a complete list.
 *
 *    - Check Reduced device drivers
 *      This uses reduced functionality drivers if they're available. For the
 *      standard design this means you get polled UART and JTAG UART drivers,
 *      no support for the LCD driver and you lose the ability to program 
 *      CFI compliant flash devices.
 *
 *    - Check Access device drivers directly
 *      This bypasses the device file system to access device drivers directly.
 *      This eliminates the space required for the device file system services.
 *      It also provides a HAL version of libc services that access the drivers
 *      directly, further reducing space. Only a limited number of libc
 *      functions are available in this configuration.
 *
 *    - Use ALT versions of stdio routines:
 *
 *           Function                  Description
 *        ===============  =====================================
 *        alt_printf       Only supports %s, %x, and %c ( < 1 Kbyte)
 *        alt_putstr       Smaller overhead than puts with direct drivers
 *                         Note this function doesn't add a newline.
 *        alt_putchar      Smaller overhead than putchar with direct drivers
 *        alt_getchar      Smaller overhead than getchar with direct drivers
 *
 */
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

// * * * Definitions * * *
// IOWR - IO Write Register
// IORD - IO Read Data
// SYSTEM_MODES_BASE - switches
// SYSTEM_COUNTER_BASE - green
// RANDOM_PATTERN_BASE - red
// IOWR_ALTERA_AVALON_PIO_DATA(baseAddress, value);
// x = IORD_ALTERA_AVALON_PIO_DATA(baseAddress);
// recording in BB if needed
// alt_putstr(""); -> altera push string

int main() {
  alt_putstr("Hunter Frady and Mitchell Jonker - Project2 - CSCE 313\n");

  // declare the mode variable as alt_u8 and initialize with 0:
	alt_u8 mode = 0x00;
  // declare the counter variable as alt_u8 and initialize with 0:
	alt_u8 counter = 0x00;

  // declare the random variable as alt_u8 and initialize with 0:
	alt_u8 rand_var = 0x00;

  // declare number of random patterns as int. You can initialize it with any number you wish:
	int num_pattern = 2; //5

  /* Event loop never exits. */
  while (1) {

    // read the mode values from system_modes using the function:
    mode = IORD_ALTERA_AVALON_PIO_DATA(SYSTEM_MODES_BASE);

    if (mode == 0x00) {
    	IOWR_ALTERA_AVALON_PIO_DATA(SYSTEM_COUNTER_BASE, 0x00);
    	IOWR_ALTERA_AVALON_PIO_DATA(RANDOM_PATTERN_BASE, 0x00000);

    }

    // check if the mode is 1 so all LEDs must light up:
    // Both red and green LEDs light up
    if (mode == 0x1) {
      alt_putstr("All LEDs Light Up\n");
      // Example to how light Decoder_output LEDs. Do the same to light other leds
      IOWR_ALTERA_AVALON_PIO_DATA(SYSTEM_COUNTER_BASE, 0xFF);
      IOWR_ALTERA_AVALON_PIO_DATA(RANDOM_PATTERN_BASE, 0xFFFFF);
      counter = 0x00;

    } // end mode 0x1

    // check if the mode is 2 so system counter starts counting:
    // A counter starts incrementing from 0 to 255
    // and the value is displayed on Green LED [7:0].
	if (mode == 0x2) {
		alt_putstr("System Counter Mode\n");

      // First, reset all LEDs as shown in the example below
	  //IOWR_ALTERA_AVALON_PIO_DATA(RANDOM_PATTERN_BASE , 0x00000);
	  //IOWR_ALTERA_AVALON_PIO_DATA(SYSTEM_COUNTER_BASE , 0x00);


      // Counter starts counting from 0 (0x00) to 255 (0xFF)
      for (int i=0; i<255; i++) {

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
        usleep(500000);

      } // end for loop
      //counter = 0x00;
	} // end mode 0x2

    // check if the mode is 3 so random pattern starts:
    // A random pattern starts is displayed on Red LED [17:0].
    // If the mode changes, the pattern stops on latest value.
    if (mode == 0x3) {
      alt_putstr("Random Pattern Mode\n");

      // First, reset all LEDs as shown in the example below:
      //IOWR_ALTERA_AVALON_PIO_DATA(RANDOM_PATTERN_BASE , 0x00000);
      //IOWR_ALTERA_AVALON_PIO_DATA(SYSTEM_COUNTER_BASE , 0x00);


      for (int i=0; i<num_pattern; i++) {

        // always keep checking If the mode values changed. If mode changes, break the loop. (as code shown in mode=1 code):
        if (mode != 0x3) {
          break;
        }
        // generate random pattern using rand() function:
        rand_var = rand();
        // display the random value onto the random-pattern LEDs using IOWR_ALTERA_AVALON_PIO_DATA:
        IOWR_ALTERA_AVALON_PIO_DATA(RANDOM_PATTERN_BASE, rand_var); // Green LEDS
        // time the display period of each counter value using usleep()
        usleep(1000000); // time for 1 million micro seconds

      }


    } // end mode 0x3


  } // end while loop

  return 0;
}
