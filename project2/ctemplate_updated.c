//library to use altera i/o functions
#include "sys/alt_stdio.h"

//library to use altera variable types
#include "alt_types.h"

//library to get all hardware definitions
#include "system.h"

//library that has the definition of pio functions
#include "altera_avalon_pio_regs.h"

//C standard libraries
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>



int main()
{
  alt_putstr("Project2 - CSCE 313\n");


  // declare the mode variable as alt_u8 and initialize with 0x0
  alt_u8 mode = 0x00; 

  // declare the counter variable as alt_u8 and initialize with 0x0
   


  // declare the random variable as alt_u8 and initialize with 0x0

  

  // declare number of random patterns as int. You can initialize it with any number you wish:


  /* Event loop never exits. */
  while (1){


	// read the mode values from system_modes using the function: 
IORD_ALTERA_AVALON_PIO_DATA
	modes = IORD_ALTERA_AVALON_PIO_DATA(SYSTEM_MODES_BASE);



	// check If the mode is 1 so all LEDs must light up
		if(mode == 0x1){
			alt_putstr("LEDs light \n");

			// Example to how light pattern_Base LEDs. Do the 
same to light other leds
			IOWR_ALTERA_AVALON_PIO_DATA(pattern_BASE, 0xFF);
				:


		}


	 // check if the mode is 2 so system counter starts counting
		:
				alt_putstr("System counter \n");

				// First, reset all LEDs as shown in the 
example below
		  	  	  
IOWR_ALTERA_AVALON_PIO_DATA(pattern_BASE, 0x00);
				    :

				// Counter starts counting from 0 (0x00) 
to 255 (0xFF)
				for(int i=0; i<256; i++){

					// always keep checking If the 
mode values changed. If mode changes, break the loop. See the below code
						modes = 
IORD_ALTERA_AVALON_PIO_DATA(SYSTEM_MODES_BASE);
						if(modes != 0x2) break;

					// display the counter value onto 
the system-counter LEDs using IOWR_ALTERA_AVALON_PIO_DATA
					
IOWR_ALTERA_AVALON_PIO_DATA(coubter_base, counter); 

					// increment counter by 1
					couter= counter+0x1;

					// time the display period of each 
counter value using usleep()
					usleep(1000); // time for 1 
million micro seconds


				}


	// check if the mode is 3 so random pattern starts
	 :
				alt_putstr("Random pattern \n");

				// First, reset all LEDs as shown in the 
example below
		  	  	  
IOWR_ALTERA_AVALON_PIO_DATA(pattern_Base, 0x0000);

		  		  :


		  		for(int i=0; i<num_pattern; i++){

					// always keep checking If the 
mode values changed. If mode changes, break the loop. (as code shown in 
mode=1 code)
					:

					// generate random pattern using 
rand() function

					
					// display the random value onto 
the random-pattern LEDs using IOWR_ALTERA_AVALON_PIO_DATA



		 			// time the display period of each 
counter value using usleep()
					usleep(1000000); // time for 1 
million micro seconds

		  		  }



}
  return 0;
}
