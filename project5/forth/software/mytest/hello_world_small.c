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
#include "sys/alt_driver.h"
#include "alt_types.h"
#include "altera_avalon_pio_regs.h"
#include "system.h"
#include <math.h>
#include <sys/alt_alarm.h>
#include "myfile.h"
#include <stdio.h>
#include <altera_up_avalon_video_pixel_buffer_dma.h>

// add the pixel buffer dma as shown in no.5 of the software requirements in the assignment sheet



int main()
{

  // declare the mode variable as alt_u8 and initialize with 0

	alt_u8 modes = 0x0;
	alt_u8 pre = 0x0;
	float f = 1;
  // Read pixel buffer (go to no.6 of software requirements in the assignment sheet)
	alt_up_pixel_buffer_dma_dev *my_pixel_buffer;
	my_pixel_buffer = alt_up_pixel_buffer_dma_open_dev("/dev/dma_buffer");
  // Check if the pixel array contains the image (go to no.7 of software requirements in the assignment sheet)

	if(!my_pixel_buffer) {
		alt_putstr("Error opening pixel buffer\n");
	}
	alt_putstr("Hello from Nios II!\n");
 // Clear the screen (go to no.8 of software requirements in the assignment sheet)
		alt_up_pixel_buffer_dma_clear_screen(my_pixel_buffer,0);

  while(1) {

  // Read the mode value using IORD_ALTERA_AVALON_PIO_DATA();


	  modes = IORD_ALTERA_AVALON_PIO_DATA(SYSTEM_MODES_BASE);

 	// check the mode value. if mode is 0.
    	//Clear the screen (go to no.8 of software requirements in the assignment sheet)
//	   alt_up_pixel_buffer_dma_clear_screen(my_pixel_buffer,0);
	  if (modes == 0x0){
		  if (pre != modes){
		  alt_up_pixel_buffer_dma_clear_screen(my_pixel_buffer,0);
		  pre = modes;
		  }
		  f = 1;
	  }
	  else if (modes == 0x1){
		  if (pre != modes){
		  		  alt_up_pixel_buffer_dma_clear_screen(my_pixel_buffer,0);
		  		pre = modes;
		  		 }
		  f = 0.5;
	  }
	  else if (modes == 0x2){
		  if (pre != modes){
		  		  alt_up_pixel_buffer_dma_clear_screen(my_pixel_buffer,0);
		  		pre = modes;
		  		  }
		  f = 2;
	  }
	  else
	  {
		  alt_putstr("Video project”!\n");
	  }
	   for (int i= 0; i<240; i++){
		   for (int j = 0; j<320; j++ )
		   {
			   alt_up_pixel_buffer_dma_draw(my_pixel_buffer,
			   	   (myimage[(i*320*3+j*3+2)]) +
			   	   (myimage[(i*320*3+j*3+1)]<<8) +
			   	   (myimage[(i*320*3+j*3+0)]<<16),j*f,i*f);
		   }
	   }
//	   alt_putstr("Hello!\n");
		// display the image (go to no.9 of software requirements in the assignment sheet)


	// check the mode value. If mode is 1


		//Clear the screen (go to no.8 of software requirements in the assignment sheet)


    	// Resize the image by 0.5 and display the image (go to no.10 of software requirements in the assignment sheet)



   // check the mode value. If mode is 2.


		//Clear the screen (go to no.8 of software requirements in the assignment sheet)


    	// Resize the image by 2 and display the image (go to no.10 of software requirements in the assignment sheet)



   // check the mode value. If mode is 3.  print the message "Video message" on the console

  }
  return 0;
  }

