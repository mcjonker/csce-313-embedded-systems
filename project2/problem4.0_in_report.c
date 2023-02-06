// Hardware Libraries
#include "sys/alt_stdio.h"
#include "alt_types.h”
#include "system.h"
#include "altera_avalon_pio_regs.h"

// C Libraries
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  
  alt_putstr("\n");
  
  alt_u8 a = 0x00; // switches
  alt_u8 b = 0x00; // green LEDs
  
  while (1) {
    
    if (a == 0x00) {
      alt_putstr("no output\n");
      
    } else if (a == 0x01) {
      
      b = 0x0A;
      IOWR_ALTERA_AVALON_PIO_DATA(SYSTEM_COUNTER_BASE, b);
    }
    
    usleep(1000000);
  }
  
  return 0;
}
