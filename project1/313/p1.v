module p1 (
	// inputs of the top-level-design
	input CLOCK_50,	// clock
	input [3:0] KEY	// reset
);

	nios_system u0 (
		.clk_clk	(CLOCK_50),	// clk.clk
		.reset_reset_n	(KEY[0])	// reset.reset_n	
	);
	
	endmodule
	