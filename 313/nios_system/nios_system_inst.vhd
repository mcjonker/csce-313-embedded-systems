	component nios_system is
		port (
			clk_clk       : in  std_logic                    := 'X';             -- clk
			modes_export  : in  std_logic_vector(1 downto 0) := (others => 'X'); -- export
			reset_reset_n : in  std_logic                    := 'X';             -- reset_n
			seg0_export   : out std_logic_vector(7 downto 0);                    -- export
			seg1_export   : out std_logic_vector(7 downto 0);                    -- export
			seg2_export   : out std_logic_vector(7 downto 0);                    -- export
			seg3_export   : out std_logic_vector(7 downto 0);                    -- export
			seg4_export   : out std_logic_vector(7 downto 0);                    -- export
			bcdin_export  : in  std_logic_vector(3 downto 0) := (others => 'X'); -- export
			spcont_export : in  std_logic                    := 'X'              -- export
		);
	end component nios_system;

	u0 : component nios_system
		port map (
			clk_clk       => CONNECTED_TO_clk_clk,       --    clk.clk
			modes_export  => CONNECTED_TO_modes_export,  --  modes.export
			reset_reset_n => CONNECTED_TO_reset_reset_n, --  reset.reset_n
			seg0_export   => CONNECTED_TO_seg0_export,   --   seg0.export
			seg1_export   => CONNECTED_TO_seg1_export,   --   seg1.export
			seg2_export   => CONNECTED_TO_seg2_export,   --   seg2.export
			seg3_export   => CONNECTED_TO_seg3_export,   --   seg3.export
			seg4_export   => CONNECTED_TO_seg4_export,   --   seg4.export
			bcdin_export  => CONNECTED_TO_bcdin_export,  --  bcdin.export
			spcont_export => CONNECTED_TO_spcont_export  -- spcont.export
		);

