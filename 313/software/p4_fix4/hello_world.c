// Copyright 2023 Mitchell Jonker and Hunter Frady
// p4_fix4

#include "sys/alt_stdio.h"
#include "sys/alt_driver.h"
#include "alt_types.h"
#include "altera_avalon_pio_regs.h"
#include "system.h"
#include "myfile.h"
#include <math.h>
#include <sys/alt_alarm.h>
#include <altera_up_avalon_video_pixel_buffer_dma.h> // pixel buffer dma

void clearScreen() {
	alt_up_pixel_buffer_dma_clear_screen(my_pixel_buffer, 0);
}
void displayScaledImage(float f) {
	for (int i = 0; i < 320; i++) {
		for (int j = 0; j < 240; j++) {
			alt_up_pixel_buffer_dma_draw(my_pixel_buffer,
				(myimage[(i*320*3+j*3+2)]) +
				(myimage[(i*320*3+j*3+1)]<<8) +
				(myimage[(i*320*3+j*3+0)]<<16),j*f,i*f);
		}
	}
}

int main() {

	// Declare the mode variable as alt_u8 and initialize with 0
	alt_putstr("Hunter Frady and Mitchell Jonker - Project 3 - CSCE 313\n");
	alt_u8 mode = 0; // 8-bit mode variable
	float scale = 1.0; // image scaling variable

	// Read pixel buffer (go to no.6 of software requirements in the assignment sheet)
	alt_up_pixel_buffer_dma_dev *my_pixel_buffer;
	my_pixel_buffer = alt_up_pixel_buffer_dma_open_dev("/dev/dma_buffer");

	// check if pixel buffer array contains the image code (part 6 of assignment sheet)
	if(!my_pixel_buffer) {
		printf("Error opening pixel buffer\n");
	}

	// clear the screen (part 7 of assignment sheet)
	clearScreen();

  while (1) {

	mode = IORD_ALTERA_AVALON_PIO_DATA(SYSTEM_MODES_BASE); // mode switches input

	if (mode = 0x00) {
		// display image at 1.0 scale
		scale = 1.0;
		clearScreen();
		displayScaledImage(scale);

	} // end of mode 0

	if (mode == 0x01) {
		// display image at 0.5 scale
		scale = 0.5;
		clearScreen();
		displayScaledImage(scale);

	} // end of mode 1

	// check the mode value. If mode is 2.
	if (mode == 0x02) {
		// display image at 2.0 scale
		scale = 2.0;
		clearScreen();
		displayScaledImage(scale);

	} // end of mode 2

	// check the mode value. If mode is 3.  print the message "Video message" on the console
	if (mode == 0x03) {
	   clearScreen();
	   alt_putstr("Video project message\n");

	} // end of mode 3

  } // end of while loop

  return 0;

}
