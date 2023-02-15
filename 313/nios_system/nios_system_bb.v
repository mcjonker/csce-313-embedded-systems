
module nios_system (
	clk_clk,
	modes_export,
	reset_reset_n,
	seg0_export,
	seg1_export,
	seg2_export,
	seg3_export,
	seg4_export,
	bcdin_export,
	spcont_export);	

	input		clk_clk;
	input	[1:0]	modes_export;
	input		reset_reset_n;
	output	[7:0]	seg0_export;
	output	[7:0]	seg1_export;
	output	[7:0]	seg2_export;
	output	[7:0]	seg3_export;
	output	[7:0]	seg4_export;
	input	[3:0]	bcdin_export;
	input		spcont_export;
endmodule
