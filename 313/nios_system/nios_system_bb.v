
module nios_system (
	clk_clk,
	reset_reset_n,
	modes_export,
	cout_export,
	pattern_export);	

	input		clk_clk;
	input		reset_reset_n;
	input	[1:0]	modes_export;
	output	[7:0]	cout_export;
	output	[17:0]	pattern_export;
endmodule
