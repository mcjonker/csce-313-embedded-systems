// Copyright 2023 Mitchell Jonker and Hunter Frady


#include "sys/alt_stdio.h"
#include "sys/alt_driver.h"
#include "alt_types.h"
#include "altera_avalon_pio_regs.h"
#include "altera_up_avalon_video_pixel_buffer.h"
#include "system.h"
#include "myfile.h"
#include <math.h>
#include <sys/alt_alarm.h>
//#include "altera_up_avalon_video_pixel_buffer_dma.h" // pixel buffer dma



int main()
{

  // declare the mode variable as alt_u8 and initialize with 0



  // Read pixel buffer (go to no.6 of software requirements in the assignment sheet)


  // Check if the pixel array contains the image (go to no.7 of software requirements in the assignment sheet)


 // Clear the screen (go to no.8 of software requirements in the assignment sheet)


  while(1) {

  // Read the mode value using IORD_ALTERA_AVALON_PIO_DATA();




   // check the mode value. if mode is 0.
   {

      //Clear the screen (go to no.8 of software requirements in the assignment sheet)

    // display the image (go to no.9 of software requirements in the assignment sheet)

    }

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
