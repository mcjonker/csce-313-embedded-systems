	component nios_system is
		port (
			clk_clk        : in  std_logic                     := 'X';             -- clk
			reset_reset_n  : in  std_logic                     := 'X';             -- reset_n
			modes_export   : in  std_logic_vector(1 downto 0)  := (others => 'X'); -- export
			cout_export    : out std_logic_vector(7 downto 0);                     -- export
			pattern_export : out std_logic_vector(17 downto 0)                     -- export
		);
	end component nios_system;

	u0 : component nios_system
		port map (
			clk_clk        => CONNECTED_TO_clk_clk,        --     clk.clk
			reset_reset_n  => CONNECTED_TO_reset_reset_n,  --   reset.reset_n
			modes_export   => CONNECTED_TO_modes_export,   --   modes.export
			cout_export    => CONNECTED_TO_cout_export,    --    cout.export
			pattern_export => CONNECTED_TO_pattern_export  -- pattern.export
		);

