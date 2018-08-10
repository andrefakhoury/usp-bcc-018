-- Copyright (C) 1991-2014 Altera Corporation. All rights reserved.
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, the Altera Quartus II License Agreement,
-- the Altera MegaCore Function License Agreement, or other 
-- applicable license agreement, including, without limitation, 
-- that your use is for the sole purpose of programming logic 
-- devices manufactured by Altera and sold by Altera or its 
-- authorized distributors.  Please refer to the applicable 
-- agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus II 64-Bit"
-- VERSION "Version 14.1.0 Build 186 12/03/2014 SJ Web Edition"

-- DATE "08/09/2018 15:34:25"

-- 
-- Device: Altera EP4CE115F29C7 Package FBGA780
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY CYCLONEIVE;
LIBRARY IEEE;
USE CYCLONEIVE.CYCLONEIVE_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	ff_D_MS IS
    PORT (
	Qm : OUT std_logic;
	D : IN std_logic;
	Clock : IN std_logic;
	Qs : OUT std_logic;
	nQs : OUT std_logic
	);
END ff_D_MS;

-- Design Ports Information
-- Qm	=>  Location: PIN_G2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- Qs	=>  Location: PIN_K1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- nQs	=>  Location: PIN_G1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- Clock	=>  Location: PIN_J1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- D	=>  Location: PIN_K2,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF ff_D_MS IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_Qm : std_logic;
SIGNAL ww_D : std_logic;
SIGNAL ww_Clock : std_logic;
SIGNAL ww_Qs : std_logic;
SIGNAL ww_nQs : std_logic;
SIGNAL \Clock~inputclkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \Qm~output_o\ : std_logic;
SIGNAL \Qs~output_o\ : std_logic;
SIGNAL \nQs~output_o\ : std_logic;
SIGNAL \D~input_o\ : std_logic;
SIGNAL \Clock~input_o\ : std_logic;
SIGNAL \Clock~inputclkctrl_outclk\ : std_logic;
SIGNAL \inst|inst2~1_combout\ : std_logic;
SIGNAL \inst1|inst2~1_combout\ : std_logic;
SIGNAL \inst1|inst3~combout\ : std_logic;
SIGNAL \inst1|ALT_INV_inst2~1_combout\ : std_logic;
SIGNAL \inst|ALT_INV_inst2~1_combout\ : std_logic;

BEGIN

Qm <= ww_Qm;
ww_D <= D;
ww_Clock <= Clock;
Qs <= ww_Qs;
nQs <= ww_nQs;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\Clock~inputclkctrl_INCLK_bus\ <= (vcc & vcc & vcc & \Clock~input_o\);
\inst1|ALT_INV_inst2~1_combout\ <= NOT \inst1|inst2~1_combout\;
\inst|ALT_INV_inst2~1_combout\ <= NOT \inst|inst2~1_combout\;

-- Location: IOOBUF_X0_Y55_N9
\Qm~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|ALT_INV_inst2~1_combout\,
	devoe => ww_devoe,
	o => \Qm~output_o\);

-- Location: IOOBUF_X0_Y54_N9
\Qs~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst1|ALT_INV_inst2~1_combout\,
	devoe => ww_devoe,
	o => \Qs~output_o\);

-- Location: IOOBUF_X0_Y55_N16
\nQs~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst1|inst3~combout\,
	devoe => ww_devoe,
	o => \nQs~output_o\);

-- Location: IOIBUF_X0_Y55_N22
\D~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_D,
	o => \D~input_o\);

-- Location: IOIBUF_X0_Y36_N8
\Clock~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_Clock,
	o => \Clock~input_o\);

-- Location: CLKCTRL_G2
\Clock~inputclkctrl\ : cycloneive_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \Clock~inputclkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \Clock~inputclkctrl_outclk\);

-- Location: LCCOMB_X1_Y55_N18
\inst|inst2~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|inst2~1_combout\ = (GLOBAL(\Clock~inputclkctrl_outclk\) & ((!\D~input_o\))) # (!GLOBAL(\Clock~inputclkctrl_outclk\) & (\inst|inst2~1_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001110101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|inst2~1_combout\,
	datab => \D~input_o\,
	datad => \Clock~inputclkctrl_outclk\,
	combout => \inst|inst2~1_combout\);

-- Location: LCCOMB_X1_Y55_N24
\inst1|inst2~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst1|inst2~1_combout\ = (GLOBAL(\Clock~inputclkctrl_outclk\) & (\inst1|inst2~1_combout\)) # (!GLOBAL(\Clock~inputclkctrl_outclk\) & ((\inst|inst2~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100111111000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \inst1|inst2~1_combout\,
	datac => \Clock~inputclkctrl_outclk\,
	datad => \inst|inst2~1_combout\,
	combout => \inst1|inst2~1_combout\);

-- Location: LCCOMB_X1_Y55_N16
\inst1|inst3\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst1|inst3~combout\ = (\inst1|inst2~1_combout\) # ((\inst|inst2~1_combout\ & !\Clock~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111100001010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|inst2~1_combout\,
	datac => \Clock~input_o\,
	datad => \inst1|inst2~1_combout\,
	combout => \inst1|inst3~combout\);

ww_Qm <= \Qm~output_o\;

ww_Qs <= \Qs~output_o\;

ww_nQs <= \nQs~output_o\;
END structure;


