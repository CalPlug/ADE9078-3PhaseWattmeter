---------------------------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity spi_master_tb is
end spi_master_tb;

architecture behave of spi_master_tb is
    constant DATA_SIZE : integer   := 16;
    constant FIFO_REQ  : Boolean   := True;

    component spi_master_top
        port(
            i_sys_clk  : in  std_logic;  -- system clock
            i_sys_rst  : in  std_logic;  -- system reset
            i_csn      : in  std_logic;  -- SPI Master chip select
            i_data     : in  std_logic_vector(15 downto 0);  -- Input data
            i_wr       : in  std_logic;  -- Active Low Write, Active High Read
            i_rd       : in  std_logic;  -- Active Low Write, Active High Read
            o_data     : out std_logic_vector(15 downto 0);  --output data
            o_tx_ready : out std_logic;  -- Transmitter ready, can write another 
  					-- data
            o_rx_ready : out std_logic;  -- Receiver ready, can read data
            o_tx_error : out std_logic;  -- Transmitter error
            o_rx_error : out std_logic;  -- Receiver error

            i_slave_addr   : in  std_logic_vector(1 downto 0);  -- Slave Address
            i_cpol         : in  std_logic;  -- CPOL value - 0 or 1
            i_cpha         : in  std_logic;  -- CPHA value - 0 or 1 
            i_lsb_first    : in  std_logic;  -- lsb first when '1' /msb first when 
            i_spi_start    : in  std_logic;  -- START SPI Master Transactions
            i_clk_period   : in  std_logic_vector(7 downto 0);  -- SCL clock period in terms of i_sys_clk
            i_setup_cycles : in  std_logic_vector(7 downto 0);  -- SPIM setup time  in terms of i_sys_clk
            i_hold_cycles  : in  std_logic_vector(7 downto 0);  -- SPIM hold time  in terms of i_sys_clk
            i_tx2tx_cycles : in  std_logic_vector(7 downto 0);  -- SPIM interval between data transactions in terms of i_sys_clk
            o_slave_csn    : out std_logic_vector(3 downto 0);  -- SPI Slave select (chip select) active low
            o_mosi         : out std_logic;  -- Master output to Slave
            i_miso         : in  std_logic;  -- Master input from Slave
            o_sclk         : out std_logic  -- Master clock
            );
    end component;

    signal   sys_clk_i       : std_logic                     := '0';  -- system clock
    signal   sys_rst_i       : std_logic                     := '1';  -- system reset
    signal   csn_i           : std_logic                     := '1';  -- SPI Master chip select
    signal   data_i          : std_logic_vector(15 downto 0) := (others => '0');  -- Input data
    signal   slave_data_i    : std_logic_vector(15 downto 0) := (others => '0');  -- Input data
    signal   wr_i            : std_logic                     := '0';  -- Active Low Write, Active High Read
    signal   rd_i            : std_logic                     := '0';  -- Active Low Write, Active High Read
    signal   spim_data_i     : std_logic_vector(15 downto 0);  --output data
    signal   spim_tx_ready_i : std_logic                     := '0';  -- Transmitter ready, can write another 
    signal   spim_rx_ready_i : std_logic                     := '0';  -- Receiver ready, can read data
    signal   spim_tx_error_i : std_logic                     := '0';  -- Transmitter error
    signal   spim_rx_error_i : std_logic                     := '0';  -- Receiver error
    signal   slave_addr_i    : std_logic_vector(1 downto 0)  := "00";  -- Slave Address
    signal   cpol_i          : std_logic                     := '0';  -- CPOL value - 0 or 1
    signal   cpha_i          : std_logic                     := '0';  -- CPHA value - 0 or 1 
    signal   lsb_first_i     : std_logic                     := '1';  -- lsb first when '1' /msb first when 
    signal   spi_start_i     : std_logic                     := '0';  -- START SPI Master Transactions
    signal   clk_period_i    : std_logic_vector(7 downto 0);  -- SCL clock period in terms of i_sys_clk
    signal   setup_cycles_i  : std_logic_vector(7 downto 0);  -- SPIM setup time  in terms of i_sys_clk
    signal   hold_cycles_i   : std_logic_vector(7 downto 0);  -- SPIM hold time  in terms of i_sys_clk
    signal   tx2tx_cycles_i  : std_logic_vector(7 downto 0);  -- SPIM interval between data transactions in terms of i_sys_clk
    signal   slave_csn_i     : std_logic_vector(3 downto 0);  -- SPI Slave select (chip select) active low
    signal   mosi_i          : std_logic                     := '0';  -- Master output to Slave
    signal   miso_00_i       : std_logic                     := '1';  -- Master input from Slave
    signal   miso_01_i       : std_logic                     := '1';  -- Master input from Slave
    signal   miso_10_i       : std_logic                     := '1';  -- Master input from Slave
    signal   miso_11_i       : std_logic                     := '1';  -- Master input from Slave
    signal   miso            : std_logic                     := '1';  -- Master input from Slave
    signal   sclk_i          : std_logic                     := '0';  -- Master clock
    signal   ss_i            : std_logic;  -- Master
    signal   count           : integer                       := 0;
    constant TIME_PERIOD_CLK : time                          := 256 ns;
    shared variable cnt      : integer                       := 0;
    type input_data_type is array (integer range 0 to 15) of std_logic_vector(15 downto 0);
    type delay_type is array (integer range 0 to 3) of std_logic_vector(7 downto 0);
    type period_type is array (integer range 0 to 3) of std_logic_vector(7 downto 0);
    type four_values is array (integer range 0 to 3) of std_logic_vector(1 downto 0);


    constant input_data : input_data_type := ("0011100000011000",
                                              "0000000000000001",
                                              "1000000000000000",
                                              "1111111111111111",
                                              "0010101010101010",
                                              "0100110011001101",
                                              "1111000011111111",
                                              "1111111111111110",
                                              "0111111111110000",
                                              "0000111111110001",
                                              "1111111111111111",
                                              "1000000000000000",
                                              "0010101010101010",
                                              "1111111111111111",
                                              "1111000011100000",
                                              "1111111111111110"
                                              );

    constant period_cycles : delay_type  := ( "00000100", "00001000", "00010000", "00100000");
    constant delay_cycles  : delay_type  := ( "00000111", "00001110", "00011000", "00110000");
    constant four_data     : four_values := ( "00", "10", "01", "11");

begin

    u0_spim_inst : spi_master_top
        port map(
            i_sys_clk      => sys_clk_i,
            i_sys_rst      => sys_rst_i,
            i_csn          => csn_i,
            i_data         => data_i,
            i_wr           => wr_i,
            i_rd           => rd_i,
            o_data         => spim_data_i,
            o_tx_ready     => spim_tx_ready_i,
            o_rx_ready     => spim_rx_ready_i,
            o_tx_error     => spim_tx_error_i,
            o_rx_error     => spim_rx_error_i,
            i_slave_addr   => slave_addr_i,
            i_cpol         => cpol_i,
            i_cpha         => cpha_i,
            i_lsb_first    => lsb_first_i,
            i_spi_start    => spi_start_i,
            i_clk_period   => clk_period_i,
            i_setup_cycles => setup_cycles_i,
            i_hold_cycles  => hold_cycles_i,
            i_tx2tx_cycles => tx2tx_cycles_i,
            o_slave_csn    => slave_csn_i,
            o_mosi         => mosi_i,
            i_miso         => miso,
            o_sclk         => sclk_i
            );

    ss_i      <= slave_csn_i(0) and slave_csn_i(1) and slave_csn_i(2) and slave_csn_i(3);
    sys_clk_i <= not sys_clk_i after TIME_PERIOD_CLK/2;
    sys_rst_i <= '0'           after 10 * TIME_PERIOD_CLK;


    process
    begin
        wait for 100 * TIME_PERIOD_CLK;
        if FIFO_REQ = True then
            wr_i       <= '1';
            csn_i      <= '0';
            for i in 0 to 15 loop
                wait until rising_edge(sys_clk_i);
                data_i <= input_data(i);
            end loop;  -- i
            wr_i       <= '0';
            csn_i      <= '1';
        end if;

        wait for TIME_PERIOD_CLK*20;


        for j in 0 to 3 loop
            cpol_i          <= four_data(j)(1);
            cpha_i          <= four_data(j)(0);
            if FIFO_REQ = False then
                csn_i       <= '0';
                data_i      <= input_data(j);
                wr_i        <= '1';
                spi_start_i <= '0';
                wait until rising_edge(sys_clk_i);
                wait for TIME_PERIOD_CLK/2;
                csn_i       <= '1';
                wr_i        <= '0';
            end if;
            spi_start_i     <= '0';

            wait until rising_edge(sys_clk_i);
            wait for TIME_PERIOD_CLK/2;
            for i in 0 to 3 loop
                clk_period_i   <= period_cycles(i);
                setup_cycles_i <= delay_cycles(i);
                hold_cycles_i  <= delay_cycles(i) + 7;
                tx2tx_cycles_i <= delay_cycles(i) + 15;
                slave_addr_i   <= four_data(i);
                lsb_first_i    <= four_data(i)(0);
                wait until rising_edge(sys_clk_i);
                wait until rising_edge(sys_clk_i);
                wait for TIME_PERIOD_CLK/2;

                spi_start_i <= '1';
                wait until rising_edge(sys_clk_i);

                wait for TIME_PERIOD_CLK/2;
                spi_start_i <= '0';
                wait for 2048 * TIME_PERIOD_CLK;
                wait for TIME_PERIOD_CLK/2;
                csn_i       <= '0';
                rd_i        <= '1';
                wait until rising_edge(sys_clk_i);
                wait for TIME_PERIOD_CLK/2;
                csn_i       <= '1';
                rd_i        <= '0';
                wait for 64 * TIME_PERIOD_CLK;
            end loop;
        end loop;
        wait;
    end process;

    process
    begin
        for k in 0 to DATA_SIZE - 1 loop
            wait until rising_edge(spi_start_i );
            count        <= count + 1;
            slave_data_i <= input_data(count);
        end loop;  -- k
    end process;


    process

    begin
        wait for 10 * TIME_PERIOD_CLK;
        cnt         := 0;
        wait until falling_edge(ss_i);
        miso_00_i <= '1';
        miso_01_i <= '1';
        miso_10_i <= '1';
        miso_11_i <= '1';
        if(cpol_i = '0') then
            if(cpha_i = '0') then
                cnt := DATA_SIZE - 1;

                for i in DATA_SIZE - 1 downto 0 loop
                    if cnt >= 0 then
                        if(lsb_first_i = '1') then
                            miso_00_i <= slave_data_i(conv_integer(DATA_SIZE-cnt-1));
                        else

                            miso_00_i <= slave_data_i(conv_integer(cnt));
                        end if;
                        wait until falling_edge(sclk_i);
                    end if;

                    if cnt > 0 then
                        cnt := cnt - 1;
                    elsif cnt = 0 then
                        cnt := DATA_SIZE - 1;
                        miso_00_i <= '1';
                    end if;

                end loop;
                if cnt = DATA_SIZE - 1 then
                    miso_00_i     <= '1';
                end if;
            else
                cnt     := 0;
                for i in DATA_SIZE - 1 downto 0 loop
                    wait until rising_edge(sclk_i);
                    if((lsb_first_i = '1')) then
                        miso_01_i <= slave_data_i(cnt);
                    else
                        miso_01_i <= slave_data_i(DATA_SIZE-cnt-1);
                    end if;
                    cnt := cnt+1;
                end loop;

            end if;
        else
            if(cpha_i = '0') then
                cnt := 0;
                for i in DATA_SIZE - 1 downto 0 loop
                    if(lsb_first_i = '1') then
                        miso_10_i <= slave_data_i(cnt);
                    else
                        miso_10_i <= slave_data_i(DATA_SIZE-cnt-1);
                    end if;

                    wait until rising_edge(sclk_i);
                    cnt := cnt+1;
                end loop;

            else
                cnt     := 0;
                for i in DATA_SIZE - 1 downto 0 loop
                    wait until falling_edge(sclk_i);
                    if((lsb_first_i = '1')) then
                        miso_11_i <= slave_data_i(cnt);
                    else
                        miso_11_i <= slave_data_i(DATA_SIZE-cnt-1);
                    end if;
                    cnt := cnt+1;
                end loop;

            end if;
        end if;
    end process;

    miso <= miso_00_i when (cpol_i = '0' and cpha_i = '0' and ss_i = '0') else
            miso_01_i when (cpol_i = '0' and cpha_i = '1' and ss_i = '0') else
            miso_10_i when (cpol_i = '1' and cpha_i = '0' and ss_i = '0') else
            miso_11_i when (cpol_i = '1' and cpha_i = '1' and ss_i = '0') else
            'Z';

end behave;
