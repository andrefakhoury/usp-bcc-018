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

-- DATE "08/23/2018 15:48:06"

-- 
-- Device: Altera EP4CE115F29C7 Package FBGA780
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY ALTERA;
LIBRARY CYCLONEIVE;
LIBRARY IEEE;
USE ALTERA.ALTERA_PRIMITIVES_COMPONENTS.ALL;
USE CYCLONEIVE.CYCLONEIVE_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	shift_register IS
    PORT (
	Q1 : OUT std_logic;
	clk_1mhz : IN std_logic;
	reset : IN std_logic;
	in_data : IN std_logic;
	in_clk : IN std_logic;
	Q2 : OUT std_logic;
	Q3 : OUT std_logic;
	Q : OUT std_logic
	);
END shift_register;

-- Design Ports Information
-- Q1	=>  Location: PIN_E21,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- Q2	=>  Location: PIN_E22,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- Q3	=>  Location: PIN_E25,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- Q	=>  Location: PIN_E24,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- reset	=>  Location: PIN_M23,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- in_clk	=>  Location: PIN_M21,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- in_data	=>  Location: PIN_AB28,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- clk_1mhz	=>  Location: PIN_Y2,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF shift_register IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_Q1 : std_logic;
SIGNAL ww_clk_1mhz : std_logic;
SIGNAL ww_reset : std_logic;
SIGNAL ww_in_data : std_logic;
SIGNAL ww_in_clk : std_logic;
SIGNAL ww_Q2 : std_logic;
SIGNAL ww_Q3 : std_logic;
SIGNAL ww_Q : std_logic;
SIGNAL \clk_1mhz~inputclkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \Q1~output_o\ : std_logic;
SIGNAL \Q2~output_o\ : std_logic;
SIGNAL \Q3~output_o\ : std_logic;
SIGNAL \Q~output_o\ : std_logic;
SIGNAL \reset~input_o\ : std_logic;
SIGNAL \in_clk~input_o\ : std_logic;
SIGNAL \inst5|outb~1_combout\ : std_logic;
SIGNAL \clk_1mhz~input_o\ : std_logic;
SIGNAL \clk_1mhz~inputclkctrl_outclk\ : std_logic;
SIGNAL \inst5|counter[0]~16_combout\ : std_logic;
SIGNAL \inst5|intermediate~1_combout\ : std_logic;
SIGNAL \inst5|intermediate~_emulated_q\ : std_logic;
SIGNAL \inst5|intermediate~0_combout\ : std_logic;
SIGNAL \inst5|always0~0_combout\ : std_logic;
SIGNAL \inst5|counter[0]~17\ : std_logic;
SIGNAL \inst5|counter[1]~18_combout\ : std_logic;
SIGNAL \inst5|outb~5_combout\ : std_logic;
SIGNAL \inst5|counter[1]~19\ : std_logic;
SIGNAL \inst5|counter[2]~20_combout\ : std_logic;
SIGNAL \inst5|counter[2]~21\ : std_logic;
SIGNAL \inst5|counter[3]~22_combout\ : std_logic;
SIGNAL \inst5|counter[3]~23\ : std_logic;
SIGNAL \inst5|counter[4]~24_combout\ : std_logic;
SIGNAL \inst5|counter[4]~25\ : std_logic;
SIGNAL \inst5|counter[5]~26_combout\ : std_logic;
SIGNAL \inst5|counter[5]~27\ : std_logic;
SIGNAL \inst5|counter[6]~28_combout\ : std_logic;
SIGNAL \inst5|counter[6]~29\ : std_logic;
SIGNAL \inst5|counter[7]~30_combout\ : std_logic;
SIGNAL \inst5|counter[7]~31\ : std_logic;
SIGNAL \inst5|counter[8]~32_combout\ : std_logic;
SIGNAL \inst5|counter[8]~33\ : std_logic;
SIGNAL \inst5|counter[9]~34_combout\ : std_logic;
SIGNAL \inst5|outb~6_combout\ : std_logic;
SIGNAL \inst5|counter[9]~35\ : std_logic;
SIGNAL \inst5|counter[10]~36_combout\ : std_logic;
SIGNAL \inst5|counter[10]~37\ : std_logic;
SIGNAL \inst5|counter[11]~38_combout\ : std_logic;
SIGNAL \inst5|counter[11]~39\ : std_logic;
SIGNAL \inst5|counter[12]~40_combout\ : std_logic;
SIGNAL \inst5|counter[12]~41\ : std_logic;
SIGNAL \inst5|counter[13]~42_combout\ : std_logic;
SIGNAL \inst5|counter[13]~43\ : std_logic;
SIGNAL \inst5|counter[14]~44_combout\ : std_logic;
SIGNAL \inst5|counter[14]~45\ : std_logic;
SIGNAL \inst5|counter[15]~46_combout\ : std_logic;
SIGNAL \inst5|outb~7_combout\ : std_logic;
SIGNAL \inst5|outb~8_combout\ : std_logic;
SIGNAL \inst5|outb~9_combout\ : std_logic;
SIGNAL \inst5|outb~10_combout\ : std_logic;
SIGNAL \inst5|outb~3_combout\ : std_logic;
SIGNAL \inst5|outb~_emulated_q\ : std_logic;
SIGNAL \inst5|outb~2_combout\ : std_logic;
SIGNAL \in_data~input_o\ : std_logic;
SIGNAL \inst|outb~1_combout\ : std_logic;
SIGNAL \inst|counter[0]~16_combout\ : std_logic;
SIGNAL \inst|intermediate~1_combout\ : std_logic;
SIGNAL \inst|intermediate~_emulated_q\ : std_logic;
SIGNAL \inst|intermediate~0_combout\ : std_logic;
SIGNAL \inst|always0~0_combout\ : std_logic;
SIGNAL \inst|counter[0]~17\ : std_logic;
SIGNAL \inst|counter[1]~18_combout\ : std_logic;
SIGNAL \inst|counter[1]~19\ : std_logic;
SIGNAL \inst|counter[2]~20_combout\ : std_logic;
SIGNAL \inst|counter[2]~21\ : std_logic;
SIGNAL \inst|counter[3]~22_combout\ : std_logic;
SIGNAL \inst|counter[3]~23\ : std_logic;
SIGNAL \inst|counter[4]~24_combout\ : std_logic;
SIGNAL \inst|counter[4]~25\ : std_logic;
SIGNAL \inst|counter[5]~26_combout\ : std_logic;
SIGNAL \inst|counter[5]~27\ : std_logic;
SIGNAL \inst|counter[6]~28_combout\ : std_logic;
SIGNAL \inst|counter[6]~29\ : std_logic;
SIGNAL \inst|counter[7]~30_combout\ : std_logic;
SIGNAL \inst|counter[7]~31\ : std_logic;
SIGNAL \inst|counter[8]~32_combout\ : std_logic;
SIGNAL \inst|counter[8]~33\ : std_logic;
SIGNAL \inst|counter[9]~34_combout\ : std_logic;
SIGNAL \inst|counter[9]~35\ : std_logic;
SIGNAL \inst|counter[10]~36_combout\ : std_logic;
SIGNAL \inst|counter[10]~37\ : std_logic;
SIGNAL \inst|counter[11]~38_combout\ : std_logic;
SIGNAL \inst|counter[11]~39\ : std_logic;
SIGNAL \inst|counter[12]~40_combout\ : std_logic;
SIGNAL \inst|counter[12]~41\ : std_logic;
SIGNAL \inst|counter[13]~42_combout\ : std_logic;
SIGNAL \inst|outb~6_combout\ : std_logic;
SIGNAL \inst|outb~5_combout\ : std_logic;
SIGNAL \inst|outb~7_combout\ : std_logic;
SIGNAL \inst|counter[13]~43\ : std_logic;
SIGNAL \inst|counter[14]~44_combout\ : std_logic;
SIGNAL \inst|counter[14]~45\ : std_logic;
SIGNAL \inst|counter[15]~46_combout\ : std_logic;
SIGNAL \inst|outb~8_combout\ : std_logic;
SIGNAL \inst|outb~9_combout\ : std_logic;
SIGNAL \inst|outb~10_combout\ : std_logic;
SIGNAL \inst|outb~3_combout\ : std_logic;
SIGNAL \inst|outb~_emulated_q\ : std_logic;
SIGNAL \inst|outb~2_combout\ : std_logic;
SIGNAL \inst34|inst|inst2~1_combout\ : std_logic;
SIGNAL \inst34|inst1|inst2~1_combout\ : std_logic;
SIGNAL \inst2|inst|inst2~1_combout\ : std_logic;
SIGNAL \inst2|inst1|inst2~1_combout\ : std_logic;
SIGNAL \inst3|inst|inst2~1_combout\ : std_logic;
SIGNAL \inst3|inst1|inst2~1_combout\ : std_logic;
SIGNAL \inst4|inst|inst2~1_combout\ : std_logic;
SIGNAL \inst4|inst1|inst2~1_combout\ : std_logic;
SIGNAL \inst5|counter\ : std_logic_vector(15 DOWNTO 0);
SIGNAL \inst|counter\ : std_logic_vector(15 DOWNTO 0);
SIGNAL \inst4|inst1|ALT_INV_inst2~1_combout\ : std_logic;
SIGNAL \inst3|inst1|ALT_INV_inst2~1_combout\ : std_logic;
SIGNAL \inst2|inst1|ALT_INV_inst2~1_combout\ : std_logic;
SIGNAL \inst34|inst1|ALT_INV_inst2~1_combout\ : std_logic;

BEGIN

Q1 <= ww_Q1;
ww_clk_1mhz <= clk_1mhz;
ww_reset <= reset;
ww_in_data <= in_data;
ww_in_clk <= in_clk;
Q2 <= ww_Q2;
Q3 <= ww_Q3;
Q <= ww_Q;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\clk_1mhz~inputclkctrl_INCLK_bus\ <= (vcc & vcc & vcc & \clk_1mhz~input_o\);
\inst4|inst1|ALT_INV_inst2~1_combout\ <= NOT \inst4|inst1|inst2~1_combout\;
\inst3|inst1|ALT_INV_inst2~1_combout\ <= NOT \inst3|inst1|inst2~1_combout\;
\inst2|inst1|ALT_INV_inst2~1_combout\ <= NOT \inst2|inst1|inst2~1_combout\;
\inst34|inst1|ALT_INV_inst2~1_combout\ <= NOT \inst34|inst1|inst2~1_combout\;

-- Location: IOOBUF_X107_Y73_N9
\Q1~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst34|inst1|ALT_INV_inst2~1_combout\,
	devoe => ww_devoe,
	o => \Q1~output_o\);

-- Location: IOOBUF_X111_Y73_N9
\Q2~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst2|inst1|ALT_INV_inst2~1_combout\,
	devoe => ww_devoe,
	o => \Q2~output_o\);

-- Location: IOOBUF_X83_Y73_N2
\Q3~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst3|inst1|ALT_INV_inst2~1_combout\,
	devoe => ww_devoe,
	o => \Q3~output_o\);

-- Location: IOOBUF_X85_Y73_N23
\Q~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst4|inst1|ALT_INV_inst2~1_combout\,
	devoe => ww_devoe,
	o => \Q~output_o\);

-- Location: IOIBUF_X115_Y40_N8
\reset~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_reset,
	o => \reset~input_o\);

-- Location: IOIBUF_X115_Y53_N15
\in_clk~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_in_clk,
	o => \in_clk~input_o\);

-- Location: LCCOMB_X113_Y41_N28
\inst5|outb~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|outb~1_combout\ = (\reset~input_o\ & (\inst5|outb~1_combout\)) # (!\reset~input_o\ & ((\in_clk~input_o\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \inst5|outb~1_combout\,
	datac => \in_clk~input_o\,
	datad => \reset~input_o\,
	combout => \inst5|outb~1_combout\);

-- Location: IOIBUF_X0_Y36_N15
\clk_1mhz~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_clk_1mhz,
	o => \clk_1mhz~input_o\);

-- Location: CLKCTRL_G4
\clk_1mhz~inputclkctrl\ : cycloneive_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \clk_1mhz~inputclkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \clk_1mhz~inputclkctrl_outclk\);

-- Location: LCCOMB_X114_Y41_N0
\inst5|counter[0]~16\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|counter[0]~16_combout\ = \inst5|counter\(0) $ (VCC)
-- \inst5|counter[0]~17\ = CARRY(\inst5|counter\(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001111001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \inst5|counter\(0),
	datad => VCC,
	combout => \inst5|counter[0]~16_combout\,
	cout => \inst5|counter[0]~17\);

-- Location: LCCOMB_X112_Y41_N6
\inst5|intermediate~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|intermediate~1_combout\ = \inst5|outb~1_combout\ $ (\in_clk~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111111110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datac => \inst5|outb~1_combout\,
	datad => \in_clk~input_o\,
	combout => \inst5|intermediate~1_combout\);

-- Location: FF_X113_Y41_N15
\inst5|intermediate~_emulated\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	asdata => \inst5|intermediate~1_combout\,
	clrn => \reset~input_o\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst5|intermediate~_emulated_q\);

-- Location: LCCOMB_X113_Y41_N14
\inst5|intermediate~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|intermediate~0_combout\ = (\reset~input_o\ & ((\inst5|intermediate~_emulated_q\ $ (\inst5|outb~1_combout\)))) # (!\reset~input_o\ & (\in_clk~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0100111011100100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \reset~input_o\,
	datab => \in_clk~input_o\,
	datac => \inst5|intermediate~_emulated_q\,
	datad => \inst5|outb~1_combout\,
	combout => \inst5|intermediate~0_combout\);

-- Location: LCCOMB_X113_Y41_N8
\inst5|always0~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|always0~0_combout\ = \inst5|intermediate~0_combout\ $ (\in_clk~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101010110101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst5|intermediate~0_combout\,
	datad => \in_clk~input_o\,
	combout => \inst5|always0~0_combout\);

-- Location: FF_X114_Y41_N1
\inst5|counter[0]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst5|counter[0]~16_combout\,
	clrn => \reset~input_o\,
	sclr => \inst5|always0~0_combout\,
	ena => \inst5|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst5|counter\(0));

-- Location: LCCOMB_X114_Y41_N2
\inst5|counter[1]~18\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|counter[1]~18_combout\ = (\inst5|counter\(1) & (!\inst5|counter[0]~17\)) # (!\inst5|counter\(1) & ((\inst5|counter[0]~17\) # (GND)))
-- \inst5|counter[1]~19\ = CARRY((!\inst5|counter[0]~17\) # (!\inst5|counter\(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \inst5|counter\(1),
	datad => VCC,
	cin => \inst5|counter[0]~17\,
	combout => \inst5|counter[1]~18_combout\,
	cout => \inst5|counter[1]~19\);

-- Location: FF_X114_Y41_N3
\inst5|counter[1]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst5|counter[1]~18_combout\,
	clrn => \reset~input_o\,
	sclr => \inst5|always0~0_combout\,
	ena => \inst5|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst5|counter\(1));

-- Location: LCCOMB_X113_Y41_N22
\inst5|outb~5\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|outb~5_combout\ = (\inst5|counter\(1) & (\inst5|counter\(0) & (\in_clk~input_o\ $ (!\inst5|intermediate~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst5|counter\(1),
	datab => \in_clk~input_o\,
	datac => \inst5|counter\(0),
	datad => \inst5|intermediate~0_combout\,
	combout => \inst5|outb~5_combout\);

-- Location: LCCOMB_X114_Y41_N4
\inst5|counter[2]~20\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|counter[2]~20_combout\ = (\inst5|counter\(2) & (\inst5|counter[1]~19\ $ (GND))) # (!\inst5|counter\(2) & (!\inst5|counter[1]~19\ & VCC))
-- \inst5|counter[2]~21\ = CARRY((\inst5|counter\(2) & !\inst5|counter[1]~19\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \inst5|counter\(2),
	datad => VCC,
	cin => \inst5|counter[1]~19\,
	combout => \inst5|counter[2]~20_combout\,
	cout => \inst5|counter[2]~21\);

-- Location: FF_X114_Y41_N5
\inst5|counter[2]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst5|counter[2]~20_combout\,
	clrn => \reset~input_o\,
	sclr => \inst5|always0~0_combout\,
	ena => \inst5|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst5|counter\(2));

-- Location: LCCOMB_X114_Y41_N6
\inst5|counter[3]~22\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|counter[3]~22_combout\ = (\inst5|counter\(3) & (!\inst5|counter[2]~21\)) # (!\inst5|counter\(3) & ((\inst5|counter[2]~21\) # (GND)))
-- \inst5|counter[3]~23\ = CARRY((!\inst5|counter[2]~21\) # (!\inst5|counter\(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \inst5|counter\(3),
	datad => VCC,
	cin => \inst5|counter[2]~21\,
	combout => \inst5|counter[3]~22_combout\,
	cout => \inst5|counter[3]~23\);

-- Location: FF_X114_Y41_N7
\inst5|counter[3]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst5|counter[3]~22_combout\,
	clrn => \reset~input_o\,
	sclr => \inst5|always0~0_combout\,
	ena => \inst5|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst5|counter\(3));

-- Location: LCCOMB_X114_Y41_N8
\inst5|counter[4]~24\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|counter[4]~24_combout\ = (\inst5|counter\(4) & (\inst5|counter[3]~23\ $ (GND))) # (!\inst5|counter\(4) & (!\inst5|counter[3]~23\ & VCC))
-- \inst5|counter[4]~25\ = CARRY((\inst5|counter\(4) & !\inst5|counter[3]~23\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \inst5|counter\(4),
	datad => VCC,
	cin => \inst5|counter[3]~23\,
	combout => \inst5|counter[4]~24_combout\,
	cout => \inst5|counter[4]~25\);

-- Location: FF_X114_Y41_N9
\inst5|counter[4]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst5|counter[4]~24_combout\,
	clrn => \reset~input_o\,
	sclr => \inst5|always0~0_combout\,
	ena => \inst5|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst5|counter\(4));

-- Location: LCCOMB_X114_Y41_N10
\inst5|counter[5]~26\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|counter[5]~26_combout\ = (\inst5|counter\(5) & (!\inst5|counter[4]~25\)) # (!\inst5|counter\(5) & ((\inst5|counter[4]~25\) # (GND)))
-- \inst5|counter[5]~27\ = CARRY((!\inst5|counter[4]~25\) # (!\inst5|counter\(5)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \inst5|counter\(5),
	datad => VCC,
	cin => \inst5|counter[4]~25\,
	combout => \inst5|counter[5]~26_combout\,
	cout => \inst5|counter[5]~27\);

-- Location: FF_X114_Y41_N11
\inst5|counter[5]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst5|counter[5]~26_combout\,
	clrn => \reset~input_o\,
	sclr => \inst5|always0~0_combout\,
	ena => \inst5|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst5|counter\(5));

-- Location: LCCOMB_X114_Y41_N12
\inst5|counter[6]~28\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|counter[6]~28_combout\ = (\inst5|counter\(6) & (\inst5|counter[5]~27\ $ (GND))) # (!\inst5|counter\(6) & (!\inst5|counter[5]~27\ & VCC))
-- \inst5|counter[6]~29\ = CARRY((\inst5|counter\(6) & !\inst5|counter[5]~27\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \inst5|counter\(6),
	datad => VCC,
	cin => \inst5|counter[5]~27\,
	combout => \inst5|counter[6]~28_combout\,
	cout => \inst5|counter[6]~29\);

-- Location: FF_X114_Y41_N13
\inst5|counter[6]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst5|counter[6]~28_combout\,
	clrn => \reset~input_o\,
	sclr => \inst5|always0~0_combout\,
	ena => \inst5|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst5|counter\(6));

-- Location: LCCOMB_X114_Y41_N14
\inst5|counter[7]~30\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|counter[7]~30_combout\ = (\inst5|counter\(7) & (!\inst5|counter[6]~29\)) # (!\inst5|counter\(7) & ((\inst5|counter[6]~29\) # (GND)))
-- \inst5|counter[7]~31\ = CARRY((!\inst5|counter[6]~29\) # (!\inst5|counter\(7)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \inst5|counter\(7),
	datad => VCC,
	cin => \inst5|counter[6]~29\,
	combout => \inst5|counter[7]~30_combout\,
	cout => \inst5|counter[7]~31\);

-- Location: FF_X114_Y41_N15
\inst5|counter[7]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst5|counter[7]~30_combout\,
	clrn => \reset~input_o\,
	sclr => \inst5|always0~0_combout\,
	ena => \inst5|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst5|counter\(7));

-- Location: LCCOMB_X114_Y41_N16
\inst5|counter[8]~32\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|counter[8]~32_combout\ = (\inst5|counter\(8) & (\inst5|counter[7]~31\ $ (GND))) # (!\inst5|counter\(8) & (!\inst5|counter[7]~31\ & VCC))
-- \inst5|counter[8]~33\ = CARRY((\inst5|counter\(8) & !\inst5|counter[7]~31\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \inst5|counter\(8),
	datad => VCC,
	cin => \inst5|counter[7]~31\,
	combout => \inst5|counter[8]~32_combout\,
	cout => \inst5|counter[8]~33\);

-- Location: FF_X114_Y41_N17
\inst5|counter[8]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst5|counter[8]~32_combout\,
	clrn => \reset~input_o\,
	sclr => \inst5|always0~0_combout\,
	ena => \inst5|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst5|counter\(8));

-- Location: LCCOMB_X114_Y41_N18
\inst5|counter[9]~34\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|counter[9]~34_combout\ = (\inst5|counter\(9) & (!\inst5|counter[8]~33\)) # (!\inst5|counter\(9) & ((\inst5|counter[8]~33\) # (GND)))
-- \inst5|counter[9]~35\ = CARRY((!\inst5|counter[8]~33\) # (!\inst5|counter\(9)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \inst5|counter\(9),
	datad => VCC,
	cin => \inst5|counter[8]~33\,
	combout => \inst5|counter[9]~34_combout\,
	cout => \inst5|counter[9]~35\);

-- Location: FF_X114_Y41_N19
\inst5|counter[9]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst5|counter[9]~34_combout\,
	clrn => \reset~input_o\,
	sclr => \inst5|always0~0_combout\,
	ena => \inst5|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst5|counter\(9));

-- Location: LCCOMB_X113_Y41_N4
\inst5|outb~6\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|outb~6_combout\ = (\inst5|counter\(6) & (\inst5|counter\(8) & (\inst5|counter\(7) & \inst5|counter\(9))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst5|counter\(6),
	datab => \inst5|counter\(8),
	datac => \inst5|counter\(7),
	datad => \inst5|counter\(9),
	combout => \inst5|outb~6_combout\);

-- Location: LCCOMB_X114_Y41_N20
\inst5|counter[10]~36\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|counter[10]~36_combout\ = (\inst5|counter\(10) & (\inst5|counter[9]~35\ $ (GND))) # (!\inst5|counter\(10) & (!\inst5|counter[9]~35\ & VCC))
-- \inst5|counter[10]~37\ = CARRY((\inst5|counter\(10) & !\inst5|counter[9]~35\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \inst5|counter\(10),
	datad => VCC,
	cin => \inst5|counter[9]~35\,
	combout => \inst5|counter[10]~36_combout\,
	cout => \inst5|counter[10]~37\);

-- Location: FF_X114_Y41_N21
\inst5|counter[10]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst5|counter[10]~36_combout\,
	clrn => \reset~input_o\,
	sclr => \inst5|always0~0_combout\,
	ena => \inst5|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst5|counter\(10));

-- Location: LCCOMB_X114_Y41_N22
\inst5|counter[11]~38\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|counter[11]~38_combout\ = (\inst5|counter\(11) & (!\inst5|counter[10]~37\)) # (!\inst5|counter\(11) & ((\inst5|counter[10]~37\) # (GND)))
-- \inst5|counter[11]~39\ = CARRY((!\inst5|counter[10]~37\) # (!\inst5|counter\(11)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \inst5|counter\(11),
	datad => VCC,
	cin => \inst5|counter[10]~37\,
	combout => \inst5|counter[11]~38_combout\,
	cout => \inst5|counter[11]~39\);

-- Location: FF_X114_Y41_N23
\inst5|counter[11]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst5|counter[11]~38_combout\,
	clrn => \reset~input_o\,
	sclr => \inst5|always0~0_combout\,
	ena => \inst5|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst5|counter\(11));

-- Location: LCCOMB_X114_Y41_N24
\inst5|counter[12]~40\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|counter[12]~40_combout\ = (\inst5|counter\(12) & (\inst5|counter[11]~39\ $ (GND))) # (!\inst5|counter\(12) & (!\inst5|counter[11]~39\ & VCC))
-- \inst5|counter[12]~41\ = CARRY((\inst5|counter\(12) & !\inst5|counter[11]~39\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \inst5|counter\(12),
	datad => VCC,
	cin => \inst5|counter[11]~39\,
	combout => \inst5|counter[12]~40_combout\,
	cout => \inst5|counter[12]~41\);

-- Location: FF_X114_Y41_N25
\inst5|counter[12]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst5|counter[12]~40_combout\,
	clrn => \reset~input_o\,
	sclr => \inst5|always0~0_combout\,
	ena => \inst5|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst5|counter\(12));

-- Location: LCCOMB_X114_Y41_N26
\inst5|counter[13]~42\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|counter[13]~42_combout\ = (\inst5|counter\(13) & (!\inst5|counter[12]~41\)) # (!\inst5|counter\(13) & ((\inst5|counter[12]~41\) # (GND)))
-- \inst5|counter[13]~43\ = CARRY((!\inst5|counter[12]~41\) # (!\inst5|counter\(13)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \inst5|counter\(13),
	datad => VCC,
	cin => \inst5|counter[12]~41\,
	combout => \inst5|counter[13]~42_combout\,
	cout => \inst5|counter[13]~43\);

-- Location: FF_X114_Y41_N27
\inst5|counter[13]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst5|counter[13]~42_combout\,
	clrn => \reset~input_o\,
	sclr => \inst5|always0~0_combout\,
	ena => \inst5|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst5|counter\(13));

-- Location: LCCOMB_X114_Y41_N28
\inst5|counter[14]~44\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|counter[14]~44_combout\ = (\inst5|counter\(14) & (\inst5|counter[13]~43\ $ (GND))) # (!\inst5|counter\(14) & (!\inst5|counter[13]~43\ & VCC))
-- \inst5|counter[14]~45\ = CARRY((\inst5|counter\(14) & !\inst5|counter[13]~43\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \inst5|counter\(14),
	datad => VCC,
	cin => \inst5|counter[13]~43\,
	combout => \inst5|counter[14]~44_combout\,
	cout => \inst5|counter[14]~45\);

-- Location: FF_X114_Y41_N29
\inst5|counter[14]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst5|counter[14]~44_combout\,
	clrn => \reset~input_o\,
	sclr => \inst5|always0~0_combout\,
	ena => \inst5|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst5|counter\(14));

-- Location: LCCOMB_X114_Y41_N30
\inst5|counter[15]~46\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|counter[15]~46_combout\ = \inst5|counter[14]~45\ $ (\inst5|counter\(15))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111111110000",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datad => \inst5|counter\(15),
	cin => \inst5|counter[14]~45\,
	combout => \inst5|counter[15]~46_combout\);

-- Location: FF_X114_Y41_N31
\inst5|counter[15]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst5|counter[15]~46_combout\,
	clrn => \reset~input_o\,
	sclr => \inst5|always0~0_combout\,
	ena => \inst5|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst5|counter\(15));

-- Location: LCCOMB_X113_Y41_N26
\inst5|outb~7\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|outb~7_combout\ = (\inst5|counter\(15) & (\inst5|counter\(13) & (\inst5|counter\(12) & \inst5|counter\(14))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst5|counter\(15),
	datab => \inst5|counter\(13),
	datac => \inst5|counter\(12),
	datad => \inst5|counter\(14),
	combout => \inst5|outb~7_combout\);

-- Location: LCCOMB_X113_Y41_N2
\inst5|outb~8\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|outb~8_combout\ = (\inst5|counter\(2) & (\inst5|counter\(5) & (\inst5|counter\(4) & \inst5|counter\(3))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst5|counter\(2),
	datab => \inst5|counter\(5),
	datac => \inst5|counter\(4),
	datad => \inst5|counter\(3),
	combout => \inst5|outb~8_combout\);

-- Location: LCCOMB_X113_Y41_N24
\inst5|outb~9\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|outb~9_combout\ = (\inst5|counter\(11) & (\inst5|counter\(10) & \inst5|outb~8_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \inst5|counter\(11),
	datac => \inst5|counter\(10),
	datad => \inst5|outb~8_combout\,
	combout => \inst5|outb~9_combout\);

-- Location: LCCOMB_X113_Y41_N0
\inst5|outb~10\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|outb~10_combout\ = (((!\inst5|outb~9_combout\) # (!\inst5|outb~7_combout\)) # (!\inst5|outb~6_combout\)) # (!\inst5|outb~5_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111111111111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst5|outb~5_combout\,
	datab => \inst5|outb~6_combout\,
	datac => \inst5|outb~7_combout\,
	datad => \inst5|outb~9_combout\,
	combout => \inst5|outb~10_combout\);

-- Location: LCCOMB_X113_Y41_N10
\inst5|outb~3\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|outb~3_combout\ = \inst5|outb~1_combout\ $ (((\inst5|outb~10_combout\ & ((\inst5|outb~2_combout\))) # (!\inst5|outb~10_combout\ & (\inst5|intermediate~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011011010011100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst5|outb~10_combout\,
	datab => \inst5|outb~1_combout\,
	datac => \inst5|intermediate~0_combout\,
	datad => \inst5|outb~2_combout\,
	combout => \inst5|outb~3_combout\);

-- Location: FF_X113_Y41_N11
\inst5|outb~_emulated\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~input_o\,
	d => \inst5|outb~3_combout\,
	clrn => \reset~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst5|outb~_emulated_q\);

-- Location: LCCOMB_X113_Y41_N30
\inst5|outb~2\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst5|outb~2_combout\ = (\reset~input_o\ & (\inst5|outb~1_combout\ $ (((\inst5|outb~_emulated_q\))))) # (!\reset~input_o\ & (((\in_clk~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111001011011000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \reset~input_o\,
	datab => \inst5|outb~1_combout\,
	datac => \in_clk~input_o\,
	datad => \inst5|outb~_emulated_q\,
	combout => \inst5|outb~2_combout\);

-- Location: IOIBUF_X115_Y17_N1
\in_data~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_in_data,
	o => \in_data~input_o\);

-- Location: LCCOMB_X114_Y40_N22
\inst|outb~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|outb~1_combout\ = (\reset~input_o\ & (\inst|outb~1_combout\)) # (!\reset~input_o\ & ((\in_data~input_o\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010110010101100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|outb~1_combout\,
	datab => \in_data~input_o\,
	datac => \reset~input_o\,
	combout => \inst|outb~1_combout\);

-- Location: LCCOMB_X113_Y40_N0
\inst|counter[0]~16\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|counter[0]~16_combout\ = \inst|counter\(0) $ (VCC)
-- \inst|counter[0]~17\ = CARRY(\inst|counter\(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001111001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \inst|counter\(0),
	datad => VCC,
	combout => \inst|counter[0]~16_combout\,
	cout => \inst|counter[0]~17\);

-- Location: LCCOMB_X114_Y40_N28
\inst|intermediate~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|intermediate~1_combout\ = \inst|outb~1_combout\ $ (\in_data~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \inst|outb~1_combout\,
	datac => \in_data~input_o\,
	combout => \inst|intermediate~1_combout\);

-- Location: FF_X114_Y40_N25
\inst|intermediate~_emulated\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	asdata => \inst|intermediate~1_combout\,
	clrn => \reset~input_o\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|intermediate~_emulated_q\);

-- Location: LCCOMB_X114_Y40_N24
\inst|intermediate~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|intermediate~0_combout\ = (\reset~input_o\ & ((\inst|intermediate~_emulated_q\ $ (\inst|outb~1_combout\)))) # (!\reset~input_o\ & (\in_data~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0100111011100100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \reset~input_o\,
	datab => \in_data~input_o\,
	datac => \inst|intermediate~_emulated_q\,
	datad => \inst|outb~1_combout\,
	combout => \inst|intermediate~0_combout\);

-- Location: LCCOMB_X114_Y40_N30
\inst|always0~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|always0~0_combout\ = \inst|intermediate~0_combout\ $ (\in_data~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|intermediate~0_combout\,
	datac => \in_data~input_o\,
	combout => \inst|always0~0_combout\);

-- Location: FF_X113_Y40_N1
\inst|counter[0]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst|counter[0]~16_combout\,
	clrn => \reset~input_o\,
	sclr => \inst|always0~0_combout\,
	ena => \inst|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|counter\(0));

-- Location: LCCOMB_X113_Y40_N2
\inst|counter[1]~18\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|counter[1]~18_combout\ = (\inst|counter\(1) & (!\inst|counter[0]~17\)) # (!\inst|counter\(1) & ((\inst|counter[0]~17\) # (GND)))
-- \inst|counter[1]~19\ = CARRY((!\inst|counter[0]~17\) # (!\inst|counter\(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \inst|counter\(1),
	datad => VCC,
	cin => \inst|counter[0]~17\,
	combout => \inst|counter[1]~18_combout\,
	cout => \inst|counter[1]~19\);

-- Location: FF_X113_Y40_N3
\inst|counter[1]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst|counter[1]~18_combout\,
	clrn => \reset~input_o\,
	sclr => \inst|always0~0_combout\,
	ena => \inst|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|counter\(1));

-- Location: LCCOMB_X113_Y40_N4
\inst|counter[2]~20\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|counter[2]~20_combout\ = (\inst|counter\(2) & (\inst|counter[1]~19\ $ (GND))) # (!\inst|counter\(2) & (!\inst|counter[1]~19\ & VCC))
-- \inst|counter[2]~21\ = CARRY((\inst|counter\(2) & !\inst|counter[1]~19\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \inst|counter\(2),
	datad => VCC,
	cin => \inst|counter[1]~19\,
	combout => \inst|counter[2]~20_combout\,
	cout => \inst|counter[2]~21\);

-- Location: FF_X113_Y40_N5
\inst|counter[2]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst|counter[2]~20_combout\,
	clrn => \reset~input_o\,
	sclr => \inst|always0~0_combout\,
	ena => \inst|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|counter\(2));

-- Location: LCCOMB_X113_Y40_N6
\inst|counter[3]~22\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|counter[3]~22_combout\ = (\inst|counter\(3) & (!\inst|counter[2]~21\)) # (!\inst|counter\(3) & ((\inst|counter[2]~21\) # (GND)))
-- \inst|counter[3]~23\ = CARRY((!\inst|counter[2]~21\) # (!\inst|counter\(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \inst|counter\(3),
	datad => VCC,
	cin => \inst|counter[2]~21\,
	combout => \inst|counter[3]~22_combout\,
	cout => \inst|counter[3]~23\);

-- Location: FF_X113_Y40_N7
\inst|counter[3]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst|counter[3]~22_combout\,
	clrn => \reset~input_o\,
	sclr => \inst|always0~0_combout\,
	ena => \inst|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|counter\(3));

-- Location: LCCOMB_X113_Y40_N8
\inst|counter[4]~24\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|counter[4]~24_combout\ = (\inst|counter\(4) & (\inst|counter[3]~23\ $ (GND))) # (!\inst|counter\(4) & (!\inst|counter[3]~23\ & VCC))
-- \inst|counter[4]~25\ = CARRY((\inst|counter\(4) & !\inst|counter[3]~23\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \inst|counter\(4),
	datad => VCC,
	cin => \inst|counter[3]~23\,
	combout => \inst|counter[4]~24_combout\,
	cout => \inst|counter[4]~25\);

-- Location: FF_X113_Y40_N9
\inst|counter[4]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst|counter[4]~24_combout\,
	clrn => \reset~input_o\,
	sclr => \inst|always0~0_combout\,
	ena => \inst|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|counter\(4));

-- Location: LCCOMB_X113_Y40_N10
\inst|counter[5]~26\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|counter[5]~26_combout\ = (\inst|counter\(5) & (!\inst|counter[4]~25\)) # (!\inst|counter\(5) & ((\inst|counter[4]~25\) # (GND)))
-- \inst|counter[5]~27\ = CARRY((!\inst|counter[4]~25\) # (!\inst|counter\(5)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \inst|counter\(5),
	datad => VCC,
	cin => \inst|counter[4]~25\,
	combout => \inst|counter[5]~26_combout\,
	cout => \inst|counter[5]~27\);

-- Location: FF_X113_Y40_N11
\inst|counter[5]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst|counter[5]~26_combout\,
	clrn => \reset~input_o\,
	sclr => \inst|always0~0_combout\,
	ena => \inst|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|counter\(5));

-- Location: LCCOMB_X113_Y40_N12
\inst|counter[6]~28\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|counter[6]~28_combout\ = (\inst|counter\(6) & (\inst|counter[5]~27\ $ (GND))) # (!\inst|counter\(6) & (!\inst|counter[5]~27\ & VCC))
-- \inst|counter[6]~29\ = CARRY((\inst|counter\(6) & !\inst|counter[5]~27\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \inst|counter\(6),
	datad => VCC,
	cin => \inst|counter[5]~27\,
	combout => \inst|counter[6]~28_combout\,
	cout => \inst|counter[6]~29\);

-- Location: FF_X113_Y40_N13
\inst|counter[6]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst|counter[6]~28_combout\,
	clrn => \reset~input_o\,
	sclr => \inst|always0~0_combout\,
	ena => \inst|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|counter\(6));

-- Location: LCCOMB_X113_Y40_N14
\inst|counter[7]~30\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|counter[7]~30_combout\ = (\inst|counter\(7) & (!\inst|counter[6]~29\)) # (!\inst|counter\(7) & ((\inst|counter[6]~29\) # (GND)))
-- \inst|counter[7]~31\ = CARRY((!\inst|counter[6]~29\) # (!\inst|counter\(7)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \inst|counter\(7),
	datad => VCC,
	cin => \inst|counter[6]~29\,
	combout => \inst|counter[7]~30_combout\,
	cout => \inst|counter[7]~31\);

-- Location: FF_X113_Y40_N15
\inst|counter[7]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst|counter[7]~30_combout\,
	clrn => \reset~input_o\,
	sclr => \inst|always0~0_combout\,
	ena => \inst|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|counter\(7));

-- Location: LCCOMB_X113_Y40_N16
\inst|counter[8]~32\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|counter[8]~32_combout\ = (\inst|counter\(8) & (\inst|counter[7]~31\ $ (GND))) # (!\inst|counter\(8) & (!\inst|counter[7]~31\ & VCC))
-- \inst|counter[8]~33\ = CARRY((\inst|counter\(8) & !\inst|counter[7]~31\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \inst|counter\(8),
	datad => VCC,
	cin => \inst|counter[7]~31\,
	combout => \inst|counter[8]~32_combout\,
	cout => \inst|counter[8]~33\);

-- Location: FF_X113_Y40_N17
\inst|counter[8]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst|counter[8]~32_combout\,
	clrn => \reset~input_o\,
	sclr => \inst|always0~0_combout\,
	ena => \inst|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|counter\(8));

-- Location: LCCOMB_X113_Y40_N18
\inst|counter[9]~34\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|counter[9]~34_combout\ = (\inst|counter\(9) & (!\inst|counter[8]~33\)) # (!\inst|counter\(9) & ((\inst|counter[8]~33\) # (GND)))
-- \inst|counter[9]~35\ = CARRY((!\inst|counter[8]~33\) # (!\inst|counter\(9)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \inst|counter\(9),
	datad => VCC,
	cin => \inst|counter[8]~33\,
	combout => \inst|counter[9]~34_combout\,
	cout => \inst|counter[9]~35\);

-- Location: FF_X113_Y40_N19
\inst|counter[9]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst|counter[9]~34_combout\,
	clrn => \reset~input_o\,
	sclr => \inst|always0~0_combout\,
	ena => \inst|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|counter\(9));

-- Location: LCCOMB_X113_Y40_N20
\inst|counter[10]~36\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|counter[10]~36_combout\ = (\inst|counter\(10) & (\inst|counter[9]~35\ $ (GND))) # (!\inst|counter\(10) & (!\inst|counter[9]~35\ & VCC))
-- \inst|counter[10]~37\ = CARRY((\inst|counter\(10) & !\inst|counter[9]~35\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \inst|counter\(10),
	datad => VCC,
	cin => \inst|counter[9]~35\,
	combout => \inst|counter[10]~36_combout\,
	cout => \inst|counter[10]~37\);

-- Location: FF_X113_Y40_N21
\inst|counter[10]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst|counter[10]~36_combout\,
	clrn => \reset~input_o\,
	sclr => \inst|always0~0_combout\,
	ena => \inst|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|counter\(10));

-- Location: LCCOMB_X113_Y40_N22
\inst|counter[11]~38\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|counter[11]~38_combout\ = (\inst|counter\(11) & (!\inst|counter[10]~37\)) # (!\inst|counter\(11) & ((\inst|counter[10]~37\) # (GND)))
-- \inst|counter[11]~39\ = CARRY((!\inst|counter[10]~37\) # (!\inst|counter\(11)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \inst|counter\(11),
	datad => VCC,
	cin => \inst|counter[10]~37\,
	combout => \inst|counter[11]~38_combout\,
	cout => \inst|counter[11]~39\);

-- Location: FF_X113_Y40_N23
\inst|counter[11]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst|counter[11]~38_combout\,
	clrn => \reset~input_o\,
	sclr => \inst|always0~0_combout\,
	ena => \inst|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|counter\(11));

-- Location: LCCOMB_X113_Y40_N24
\inst|counter[12]~40\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|counter[12]~40_combout\ = (\inst|counter\(12) & (\inst|counter[11]~39\ $ (GND))) # (!\inst|counter\(12) & (!\inst|counter[11]~39\ & VCC))
-- \inst|counter[12]~41\ = CARRY((\inst|counter\(12) & !\inst|counter[11]~39\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \inst|counter\(12),
	datad => VCC,
	cin => \inst|counter[11]~39\,
	combout => \inst|counter[12]~40_combout\,
	cout => \inst|counter[12]~41\);

-- Location: FF_X113_Y40_N25
\inst|counter[12]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst|counter[12]~40_combout\,
	clrn => \reset~input_o\,
	sclr => \inst|always0~0_combout\,
	ena => \inst|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|counter\(12));

-- Location: LCCOMB_X113_Y40_N26
\inst|counter[13]~42\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|counter[13]~42_combout\ = (\inst|counter\(13) & (!\inst|counter[12]~41\)) # (!\inst|counter\(13) & ((\inst|counter[12]~41\) # (GND)))
-- \inst|counter[13]~43\ = CARRY((!\inst|counter[12]~41\) # (!\inst|counter\(13)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \inst|counter\(13),
	datad => VCC,
	cin => \inst|counter[12]~41\,
	combout => \inst|counter[13]~42_combout\,
	cout => \inst|counter[13]~43\);

-- Location: FF_X113_Y40_N27
\inst|counter[13]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst|counter[13]~42_combout\,
	clrn => \reset~input_o\,
	sclr => \inst|always0~0_combout\,
	ena => \inst|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|counter\(13));

-- Location: LCCOMB_X114_Y40_N26
\inst|outb~6\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|outb~6_combout\ = (\inst|counter\(13) & (\inst|counter\(10) & (\inst|counter\(11) & \inst|counter\(12))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|counter\(13),
	datab => \inst|counter\(10),
	datac => \inst|counter\(11),
	datad => \inst|counter\(12),
	combout => \inst|outb~6_combout\);

-- Location: LCCOMB_X114_Y40_N16
\inst|outb~5\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|outb~5_combout\ = (\inst|counter\(0) & (\inst|counter\(1) & (\inst|intermediate~0_combout\ $ (!\in_data~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000001000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|counter\(0),
	datab => \inst|intermediate~0_combout\,
	datac => \in_data~input_o\,
	datad => \inst|counter\(1),
	combout => \inst|outb~5_combout\);

-- Location: LCCOMB_X114_Y40_N8
\inst|outb~7\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|outb~7_combout\ = (\inst|counter\(7) & (\inst|counter\(6) & (\inst|counter\(8) & \inst|counter\(9))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|counter\(7),
	datab => \inst|counter\(6),
	datac => \inst|counter\(8),
	datad => \inst|counter\(9),
	combout => \inst|outb~7_combout\);

-- Location: LCCOMB_X113_Y40_N28
\inst|counter[14]~44\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|counter[14]~44_combout\ = (\inst|counter\(14) & (\inst|counter[13]~43\ $ (GND))) # (!\inst|counter\(14) & (!\inst|counter[13]~43\ & VCC))
-- \inst|counter[14]~45\ = CARRY((\inst|counter\(14) & !\inst|counter[13]~43\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \inst|counter\(14),
	datad => VCC,
	cin => \inst|counter[13]~43\,
	combout => \inst|counter[14]~44_combout\,
	cout => \inst|counter[14]~45\);

-- Location: FF_X113_Y40_N29
\inst|counter[14]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst|counter[14]~44_combout\,
	clrn => \reset~input_o\,
	sclr => \inst|always0~0_combout\,
	ena => \inst|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|counter\(14));

-- Location: LCCOMB_X113_Y40_N30
\inst|counter[15]~46\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|counter[15]~46_combout\ = \inst|counter\(15) $ (\inst|counter[14]~45\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \inst|counter\(15),
	cin => \inst|counter[14]~45\,
	combout => \inst|counter[15]~46_combout\);

-- Location: FF_X113_Y40_N31
\inst|counter[15]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst|counter[15]~46_combout\,
	clrn => \reset~input_o\,
	sclr => \inst|always0~0_combout\,
	ena => \inst|outb~10_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|counter\(15));

-- Location: LCCOMB_X114_Y40_N18
\inst|outb~8\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|outb~8_combout\ = (\inst|counter\(5) & (\inst|counter\(3) & (\inst|counter\(2) & \inst|counter\(4))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|counter\(5),
	datab => \inst|counter\(3),
	datac => \inst|counter\(2),
	datad => \inst|counter\(4),
	combout => \inst|outb~8_combout\);

-- Location: LCCOMB_X114_Y40_N12
\inst|outb~9\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|outb~9_combout\ = (\inst|counter\(15) & (\inst|counter\(14) & \inst|outb~8_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \inst|counter\(15),
	datac => \inst|counter\(14),
	datad => \inst|outb~8_combout\,
	combout => \inst|outb~9_combout\);

-- Location: LCCOMB_X114_Y40_N10
\inst|outb~10\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|outb~10_combout\ = (((!\inst|outb~9_combout\) # (!\inst|outb~7_combout\)) # (!\inst|outb~5_combout\)) # (!\inst|outb~6_combout\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111111111111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|outb~6_combout\,
	datab => \inst|outb~5_combout\,
	datac => \inst|outb~7_combout\,
	datad => \inst|outb~9_combout\,
	combout => \inst|outb~10_combout\);

-- Location: LCCOMB_X114_Y40_N20
\inst|outb~3\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|outb~3_combout\ = \inst|outb~1_combout\ $ (((\inst|outb~10_combout\ & ((\inst|outb~2_combout\))) # (!\inst|outb~10_combout\ & (\inst|intermediate~0_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101011010011010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|outb~1_combout\,
	datab => \inst|outb~10_combout\,
	datac => \inst|intermediate~0_combout\,
	datad => \inst|outb~2_combout\,
	combout => \inst|outb~3_combout\);

-- Location: FF_X114_Y40_N21
\inst|outb~_emulated\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_1mhz~inputclkctrl_outclk\,
	d => \inst|outb~3_combout\,
	clrn => \reset~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|outb~_emulated_q\);

-- Location: LCCOMB_X114_Y40_N14
\inst|outb~2\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst|outb~2_combout\ = (\reset~input_o\ & (\inst|outb~1_combout\ $ (((\inst|outb~_emulated_q\))))) # (!\reset~input_o\ & (((\in_data~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101110010101100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst|outb~1_combout\,
	datab => \in_data~input_o\,
	datac => \reset~input_o\,
	datad => \inst|outb~_emulated_q\,
	combout => \inst|outb~2_combout\);

-- Location: LCCOMB_X114_Y40_N2
\inst34|inst|inst2~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst34|inst|inst2~1_combout\ = (\inst5|outb~2_combout\ & ((!\inst|outb~2_combout\))) # (!\inst5|outb~2_combout\ & (\inst34|inst|inst2~1_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111111001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \inst34|inst|inst2~1_combout\,
	datac => \inst|outb~2_combout\,
	datad => \inst5|outb~2_combout\,
	combout => \inst34|inst|inst2~1_combout\);

-- Location: LCCOMB_X114_Y40_N0
\inst34|inst1|inst2~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst34|inst1|inst2~1_combout\ = (\inst5|outb~2_combout\ & (\inst34|inst1|inst2~1_combout\)) # (!\inst5|outb~2_combout\ & ((\inst34|inst|inst2~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100111111000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \inst34|inst1|inst2~1_combout\,
	datac => \inst5|outb~2_combout\,
	datad => \inst34|inst|inst2~1_combout\,
	combout => \inst34|inst1|inst2~1_combout\);

-- Location: LCCOMB_X113_Y41_N12
\inst2|inst|inst2~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|inst|inst2~1_combout\ = (\inst5|outb~2_combout\ & ((\inst34|inst1|inst2~1_combout\))) # (!\inst5|outb~2_combout\ & (\inst2|inst|inst2~1_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110111001000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst5|outb~2_combout\,
	datab => \inst2|inst|inst2~1_combout\,
	datad => \inst34|inst1|inst2~1_combout\,
	combout => \inst2|inst|inst2~1_combout\);

-- Location: LCCOMB_X113_Y41_N16
\inst2|inst1|inst2~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst2|inst1|inst2~1_combout\ = (\inst5|outb~2_combout\ & ((\inst2|inst1|inst2~1_combout\))) # (!\inst5|outb~2_combout\ & (\inst2|inst|inst2~1_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100110010101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst2|inst|inst2~1_combout\,
	datab => \inst2|inst1|inst2~1_combout\,
	datad => \inst5|outb~2_combout\,
	combout => \inst2|inst1|inst2~1_combout\);

-- Location: LCCOMB_X113_Y41_N6
\inst3|inst|inst2~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst3|inst|inst2~1_combout\ = (\inst5|outb~2_combout\ & ((\inst2|inst1|inst2~1_combout\))) # (!\inst5|outb~2_combout\ & (\inst3|inst|inst2~1_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111101000001010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst3|inst|inst2~1_combout\,
	datac => \inst5|outb~2_combout\,
	datad => \inst2|inst1|inst2~1_combout\,
	combout => \inst3|inst|inst2~1_combout\);

-- Location: LCCOMB_X113_Y41_N20
\inst3|inst1|inst2~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst3|inst1|inst2~1_combout\ = (\inst5|outb~2_combout\ & ((\inst3|inst1|inst2~1_combout\))) # (!\inst5|outb~2_combout\ & (\inst3|inst|inst2~1_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000010101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst3|inst|inst2~1_combout\,
	datac => \inst3|inst1|inst2~1_combout\,
	datad => \inst5|outb~2_combout\,
	combout => \inst3|inst1|inst2~1_combout\);

-- Location: LCCOMB_X113_Y41_N18
\inst4|inst|inst2~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst4|inst|inst2~1_combout\ = (\inst5|outb~2_combout\ & ((\inst3|inst1|inst2~1_combout\))) # (!\inst5|outb~2_combout\ & (\inst4|inst|inst2~1_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111110000001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \inst4|inst|inst2~1_combout\,
	datac => \inst5|outb~2_combout\,
	datad => \inst3|inst1|inst2~1_combout\,
	combout => \inst4|inst|inst2~1_combout\);

-- Location: LCCOMB_X112_Y41_N12
\inst4|inst1|inst2~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \inst4|inst1|inst2~1_combout\ = (\inst5|outb~2_combout\ & (\inst4|inst1|inst2~1_combout\)) # (!\inst5|outb~2_combout\ & ((\inst4|inst|inst2~1_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010111110100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \inst4|inst1|inst2~1_combout\,
	datac => \inst5|outb~2_combout\,
	datad => \inst4|inst|inst2~1_combout\,
	combout => \inst4|inst1|inst2~1_combout\);

ww_Q1 <= \Q1~output_o\;

ww_Q2 <= \Q2~output_o\;

ww_Q3 <= \Q3~output_o\;

ww_Q <= \Q~output_o\;
END structure;


