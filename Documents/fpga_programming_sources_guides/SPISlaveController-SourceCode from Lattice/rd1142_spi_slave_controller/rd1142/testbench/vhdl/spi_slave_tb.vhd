


--   ==================================================================
--   >>>>>>>>>>>>>>>>>>>>>>> COPYRIGHT NOTICE <<<<<<<<<<<<<<<<<<<<<<<<<
--   ------------------------------------------------------------------
--   Copyright (c) 2013 by Lattice Semiconductor Corporation
--   ALL RIGHTS RESERVED 
--   ------------------------------------------------------------------
--
--   Permission:
--
--      Lattice SG Pte. Ltd. grants permission to use this code
--      pursuant to the terms of the Lattice Reference Design License Agreement. 
--
--
--   Disclaimer:
--
--      This VHDL or Verilog source code is intended as a design reference
--      which illustrates how these types of functions can be implemented.
--      It is the user's responsibility to verify their design for
--      consistency and functionality through the use of formal
--      verification methods.  Lattice provides no warranty
--      regarding the use or functionality of this code.
--
--   --------------------------------------------------------------------
--
--                  Lattice SG Pte. Ltd.
--                  101 Thomson Road, United Square #07-02 
--                  Singapore 307591
--
--
--                  TEL: 1-800-Lattice (USA and Canada)
--                       +65-6631-2000 (Singapore)
--                       +1-503-268-8001 (other locations)
--
--                  web: http://www.latticesemi.com/
--                  email: techsupport@latticesemi.com
--
--   --------------------------------------------------------------------
--
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_textio.all;

entity spi_slave_tb is
end spi_slave_tb;

architecture behave of spi_slave_tb is
    constant DATA_SIZE : natural := 16;

    component spi_slave_top
        port (
            i_sys_clk  : in  std_logic;  -- system clock		        
            i_sys_rst  : in  std_logic;  -- system reset
            i_csn      : in  std_logic;  -- Slave Enable/select
            i_data     : in  std_logic_vector(15 downto 0);  -- Input data
            i_wr       : in  std_logic;  -- Active Low Write, Active High Read
            i_rd       : in  std_logic;  -- Active Low Write, Active High Read
            o_data     : out std_logic_vector(15 downto 0);  --output data
            o_tx_ready : out std_logic;  -- Transmitter ready, can write another 
  					-- data
            o_rx_ready : out std_logic;  -- Receiver ready, can read data
            o_tx_error : out std_logic;  -- Transmitter error
            o_rx_error : out std_logic;  -- Receiver error

            i_cpol      : in std_logic;  -- CPOL value - 0 or 1
            i_cpha      : in std_logic;  -- CPHA value - 0 or 1 
            i_lsb_first : in std_logic;  -- lsb first when '1' /msb first when 
  					 -- '0'

            o_miso : out std_logic;  	-- Slave output to Master
            i_mosi : in  std_logic;  	-- Slave input from Master
            i_ssn  : in  std_logic;  	-- Slave Slect Active low
            i_sclk : in  std_logic;  	-- Clock from SPI Master
	    o_tx_ack : out std_logic;
	    o_tx_no_ack : out std_logic
            );
    end component;


    signal i_sys_clk  : std_logic                                := '0';  -- system clock
    signal i_sys_rst  : std_logic                                := '1';  -- system reset
    signal i_csn      : std_logic                                := '1';  -- SPI Master chip select
    signal i_data     : std_logic_vector(15 downto 0) := (others => '0');  -- Input data
    signal i_wr       : std_logic                                := '0';  -- Active Low Write, Active High Read
    signal i_rd       : std_logic                                := '0';  -- Active Low Write, Active High Read
    signal o_data     : std_logic_vector(15 downto 0);  --output data
    signal o_tx_ready : std_logic;  	-- Transmitter ready, can write another 
    signal o_rx_ready : std_logic;  	-- Receiver ready, can read data
    signal o_tx_error : std_logic;  	-- Transmitter error
    signal o_rx_error : std_logic;  	-- Receiver error

    signal i_cpol      : std_logic := '0';  -- CPOL value - 0 or 1
    signal i_cpha      : std_logic := '1';  -- CPHA value - 0 or 1 
    signal i_lsb_first : std_logic := '0';  -- lsb first when '1' /msb first when 

    signal i_mosi : std_logic := '0';  	-- Input for the slave
    signal o_miso : std_logic;  	-- Output from Slave

    signal i_sclk : std_logic := '0';  	-- Master clock
    signal i_ssn  : std_logic := '1';  	-- Slave Select

    signal o_tx_ack : std_logic;
    signal o_tx_no_ack : std_logic;
	signal error : integer:=0;
    constant TIME_PERIOD_CLK : time := 256 ns;

    type input_data_type is array (integer range 0 to 3) of std_logic_vector(15 downto 0);

    type four_values is array (integer range 0 to 3) of std_logic_vector(1 downto 0);

    constant input_data : input_data_type := ("0111111101111110",
                                              "1000111111111110",
                                              "0111111111110001",
                                              "1000111101110011");

    constant four_data : four_values := ( "00", "10", "01", "11");   

    constant sclk_cycle : time := 512 ns;




begin


    u0_spis0_inst : spi_slave_top
        port map(
            i_sys_clk   => i_sys_clk,
            i_sys_rst   => i_sys_rst,
            i_csn       => i_csn,
            i_data      => i_data,
            i_wr        => i_wr,
            i_rd        => i_rd,
            o_data      => o_data,
            o_tx_ready  => o_tx_ready,
            o_rx_ready  => o_rx_ready,
            o_tx_error  => o_tx_error,
            o_rx_error  => o_rx_error,
            i_cpol      => i_cpol,
            i_cpha      => i_cpha,
            i_lsb_first => i_lsb_first,
            i_ssn       => i_ssn,
            i_mosi      => i_mosi,
            o_miso      => o_miso,
            i_sclk      => i_sclk,
	    o_tx_ack    => o_tx_ack,
	    o_tx_no_ack => o_tx_no_ack
            );


    i_sys_clk <= not i_sys_clk after TIME_PERIOD_CLK/2;
    i_sys_rst <= '0'           after 10 * TIME_PERIOD_CLK;

    
    process
    begin
        wait for 100 * TIME_PERIOD_CLK;

        for j in 0 to 3 loop
			report ("setting clock polarity")	;
            i_cpol      <= four_data(j)(1);	
			report ("setting clock phase") ;
            i_cpha      <= four_data(j)(0);
			report ("setting lsb/msb first") ;
            i_lsb_first <= four_data(j)(1);	
			report ("Reading the data from the processor"); 
            i_data      <= input_data(j);
			wait until rising_edge(i_sys_clk);
            wait until rising_edge(i_sys_clk); 
			wait for TIME_PERIOD_CLK /2;
			
			i_csn       <= '0';	
			report("Processor chip select assrted by selecting the slave controller") ;
			
			i_ssn       <= '0';
			report ("Master chip select asserted selecting the Slave controller") ;
            
																       
           
            i_wr        <= '1';	 
			
			
            wait until rising_edge(i_sys_clk);
            wait for TIME_PERIOD_CLK/2;
            i_wr        <= '0';	 
			report ("write enable asserted");
            wait until rising_edge(i_sys_clk);
            if DATA_SIZE = 16 then
                wait for TIME_PERIOD_CLK *200;
            else
                wait for TIME_PERIOD_CLK * 150;
            end if;

            i_ssn <= '1';
            i_wr  <= '0';

            wait for 2048 * TIME_PERIOD_CLK;
            wait for TIME_PERIOD_CLK/2;
            i_csn <= '0';
            i_rd  <= '1';
            wait until rising_edge(i_sys_clk);
            wait for TIME_PERIOD_CLK/2;
            i_csn <= '1';
            i_rd  <= '0';
            wait for 32 * TIME_PERIOD_CLK;	  
			
		 end loop;  	
		
		
	wait;	
    end process;

    

    process
        variable cnt : integer := 0;
    begin
        wait for 100 * TIME_PERIOD_CLK;
        if(i_cpol = '0') then
            if(i_cpha = '0') then	 
				report ("cpol = '0' and cpha = '0'");
                cnt            := 0;
                for i in DATA_SIZE - 1 downto 0 loop

                    if(i_lsb_first = '1') then
                        i_mosi     <= i_data(cnt);
                    else
                        i_mosi     <= i_data(DATA_SIZE-cnt-1);
                    end if;
                    if i_ssn = '0' then
                        wait for sclk_cycle;
                        i_sclk     <= '1';
                        wait for sclk_cycle;
                        i_sclk     <= '0';
                    else
                        i_sclk     <= i_cpol;
                    end if;
                    cnt     := cnt+1;
                end loop;
                wait for TIME_PERIOD_CLK;
            else
				report ("cpol = '0' and cpha = '1'");
                cnt         := 0;
                for i in DATA_SIZE - 1 downto 0 loop
                    if i_ssn = '0' then
                        wait for sclk_cycle;
                        i_sclk     <= '1';
                        if(i_lsb_first = '1') then
                            i_mosi <= i_data(cnt);
                        else
                            i_mosi <= i_data(DATA_SIZE-cnt-1);
                        end if;
                        cnt := cnt+1;
                        wait for sclk_cycle;
                        i_sclk     <= '0';
                    else
                        i_sclk     <= i_cpol;
                    end if;
                end loop;
                if DATA_SIZE = 16 then
                    wait for TIME_PERIOD_CLK /2;
                else
                    wait for TIME_PERIOD_CLK;
                end if;

            end if;



        else
            if(i_cpha = '0') then
				report ("cpol = '1' and cpha = '0'");
                cnt     := 0;
                for i in DATA_SIZE - 1 downto 0 loop
                    if(i_lsb_first = '1') then
                        i_mosi <= i_data(cnt);
                    else
                        i_mosi <= i_data(DATA_SIZE-cnt-1);
                    end if;
                    if i_ssn = '0' then
                        wait for sclk_cycle;
                        i_sclk <= '0';
                        wait for sclk_cycle;
                        i_sclk <= '1';
                    else
                        i_sclk <= i_cpol;
                    end if;
                    cnt := cnt+1;
                end loop;
                wait for TIME_PERIOD_CLK;


            else 
				report ("cpol = '1' and cpha = '1'");
                cnt         := 0;
                for i in DATA_SIZE - 1 downto 0 loop
                    if i_ssn = '0' then
                        wait for sclk_cycle;
                        i_sclk     <= '0';
                        if(i_lsb_first = '1') then
                            i_mosi <= i_data(cnt);
                        else
                            i_mosi <= i_data(DATA_SIZE-cnt-1);
                        end if;
                        cnt := cnt+1;
                        wait for sclk_cycle;
                        i_sclk     <= '1';
                    else
                        i_sclk     <= i_cpol;
                    end if;
                end loop;
                wait for TIME_PERIOD_CLK;
				report "NO OF ERRORS = " & integer'image(error);
				if (error=0) then
				report "SIMULATION SUCCESSFUL";
				else
				REPORT "SIMULATION FAILED";		  
				end if;
				wait;
				
            end if;						   
			 
        end if;
    end process;


process (o_rx_ready) begin
if(o_rx_ready ='1') then
if(i_data = o_data) then
--report ("success");
error <= error;
else
error <= error + 1;
--report ("fail");
end if;
end if;
end process;



end behave;
