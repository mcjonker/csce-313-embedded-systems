// Project 6 Mitchell Jonker and Hunter Frady
// /project6/partb

// call header files
#include "sys/alt_stdio.h"
#include "sys/alt_driver.h"
#include "alt_types.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <altera_up_avalon_video_pixel_buffer_dma.h>
#include "system.h"
//#include <sys/alt_alarm.h> // from p5.pdf
#include <altera_avalon_performance_counter.h>
#include "myfile.h"
//#include "myfile.c" // if ref error uncomment
//#define PERFORMANCE_COUNTER_0_BASE 0x203000;

// declare global variables
float theta;
float shifted_row;
float shifted_col;
float original_row, original_col;
alt_up_pixel_buffer_dma_dev *my_pixel_buffer;
unsigned long long start_cycles, end_cycles, total_cycles;

void pixel_code(int i, int j) {
	shifted_row = i-240/2;
	// calculate shifted_col
	shifted_col = j - 320/2;
	// calculate original_row
	original_row = round((shifted_row*cosf(theta) - shifted_col*sinf(theta)) + 240/2);
	//calculate original_col
	original_col = round((shifted_row*sinf(theta) + shifted_col*cosf(theta)) + 320/2);
	// check if the image is out of boundary
	if ((i>=240) || (j>=320) || (i<0) || (j<0)) {
		// if original_row is out of bound
		if (original_row >= 0 && original_row < 1) {
			// set i to 0
			i = 0;
		}
		// if original_col is out of bound
		if (original_col >=0 && original_col < 1) {
			// set j to 0
			j = 0;
		}
	}
	// display the image based on the values of original_row and original_col
	alt_up_pixel_buffer_dma_draw(my_pixel_buffer,
	(myimage[(i*320*3+j*3+2)]) +
	(myimage[(i*320*3+j*3+1)]<<8) +
	(myimage[(i*320*3+j*3+0)]<<16),original_col,original_row);

}
void frame_function() {
	// frame code
	// for loop that rotates over image rows
	for (int i = 0; i < 240; i++) {
	// for loop that rotates over image cols
		for (int j = 0; j < 360; j++) {
			start_cycles = perf_get_total_time((void*) 0x203000); // PERFORMANCE_COUNTER_0_BASE
			PERF_START_MEASURING(0x203000); // PERFORMANCE_COUNTER_0_BASE
			pixel_code(i,j);
			end_cycles = perf_get_total_time((void*) 0x203000); // PERFORMANCE_COUNTER_0_BASE
			PERF_START_MEASURING(0x203000); // PERFORMANCE_COUNTER_0_BASE
			total_cycles = end_cycles - start_cycles;
			printf("Estimate performance cycle = %llu \n", total_cycles);
		}
	}
}

int main() {
	alt_putstr("Project 6 (Part B) Mitchell Jonker and Hunter Frady\n");

	//int ticks_per_second, ticks_start, ticks_end, ticks_delta;
	//ticks_per_second = alt_ticks_per_second();
	//printf("TPS: %d \n", ticks_per_second);


	my_pixel_buffer = alt_up_pixel_buffer_dma_open_dev("/dev/dma_buffer");

	if(!my_pixel_buffer) {
		printf("Error opening pixel buffer\n");
	}

	alt_up_pixel_buffer_dma_clear_screen(my_pixel_buffer, 0);

	//int ticks_current = alt_nticks(); // starting number of ticks
	//printf("Current Tic: %d \n", ticks_current);

	while (1) {
		//unsigned long long fps_avg = 0;
		// for loop that rotates over four frames on 0, 90, 180, 270 degree
		for (int t = 0; t > -360; t = t-90) { // -360
			// calculate theta

			theta = (t*3.14)/180;
			alt_up_pixel_buffer_dma_clear_screen(my_pixel_buffer,0);

			//
			//ticks_start = alt_nticks(); // starting number of ticks
			//printf("Start Tic: %d \n", ticks_start);
			frame_function();
			//
			//ticks_end = alt_nticks();
			//ticks_delta = ticks_end - ticks_start;
			//printf("End Tic: %d \n", ticks_end);
			//printf("Delta Tics: %d \n", ticks_delta);
			//unsigned long long time_delta = (unsigned long long) ticks_delta / (unsigned long long) ticks_per_second;
			//printf("Total duration: %llu seconds\n", time_delta);
			//fps_avg += time_delta;
		}
		//fps_avg = 4/fps_avg; // divide by four frames
		//printf("FPS avg over previous 4 frames: %llu fps\n\n", fps_avg);

	}

//	ticks_delta = ticks_end - ticks_start;
//	duration = ticks_delta / ticks_per_second;
//	printf("Total duration %llu seconds \n\n", duration);

	return 0;
}


