//--------------------------------------------------------------------------------------------------

module SPI_Master_top (
                           i_sys_clk,
                           i_sys_rst,
                           i_csn,
                           i_data,
                           i_wr,
                           i_rd,
                           o_data,
                           o_tx_ready,
                           o_rx_ready,
                           o_tx_error,
                           o_rx_error,
                           i_slave_addr,
                           i_cpol,
                           i_cpha,
                           i_lsb_first,
                           i_spi_start,
                           i_clk_period,
                           i_setup_cycles,
                           i_hold_cycles,
                           i_tx2tx_cycles,
                           o_slave_csn,
                           o_mosi,
                           i_miso,
                           o_sclk,
                           o_intr
                           );
    
    input i_sys_clk ;
    input i_sys_rst ;
    input i_csn ;
    input [15:0] i_data ;
    input        i_wr ;
    input        i_rd ;
    output [15:0] o_data ;
    output        o_tx_ready ;
    output        o_rx_ready ;
    output        o_tx_error ;
    output        o_rx_error ;
    input [1:0]   i_slave_addr ;
    input         i_cpol ;
    input         i_cpha ;
    input         i_lsb_first ;
    input         i_spi_start ;
    input [7:0]   i_clk_period ;
    input [7:0]   i_setup_cycles ;
    input [7:0]   i_hold_cycles ;
    input [7:0]   i_tx2tx_cycles ;
    output [3:0]  o_slave_csn ;
    output        o_mosi ;
    input         i_miso ;
    output        o_sclk ;
    output        o_intr;
    
    
    wire          mosi_tri_en;
    parameter wgnd = 1'b0;
    parameter wvcc = 1'b1;
    wire          mosi_i;

    parameter DATA_SIZE = 16;
    parameter FIFO_REQ = 1'b1;
    
    spi_master
        #(
          .DATA_SIZE(DATA_SIZE),
          .FIFO_REQ(FIFO_REQ)
          )    
    spi_master_u1 (
                   .i_sys_clk(i_sys_clk),
                   .i_sys_rst(i_sys_rst),
                   .i_csn(i_csn),
                   .i_data(i_data),
                   .i_wr(i_wr),
                   .i_rd(i_rd),
                   .o_data(o_data),
                   .o_tx_ready(o_tx_ready),
                   .o_rx_ready(o_rx_ready),
                   .o_tx_error(o_tx_error),
                   .o_rx_error(o_rx_error),
                   .i_slave_addr(i_slave_addr),
                   .i_cpol(i_cpol),
                   .i_cpha(i_cpha),
                   .i_lsb_first(i_lsb_first),
                   .i_spi_start(i_spi_start),
                   .i_clk_period(i_clk_period),
                   .i_setup_cycles(i_setup_cycles),
                   .i_hold_cycles(i_hold_cycles),
                   .i_tx2tx_cycles(i_tx2tx_cycles),
                   .o_slave_csn(o_slave_csn),
                   .o_mosi(mosi_i),
                   .i_miso(i_miso),
                   .o_sclk(o_sclk),
                   .o_intr(o_intr),
                   .mosi_tri_en(mosi_tri_en)
                   );

    SB_IO #( .PIN_TYPE(6'b1010_01))
    SB_IO_Inst (
                .PACKAGE_PIN(o_mosi), 
                .LATCH_INPUT_VALUE(GND),
                .CLOCK_ENABLE(GND),
                .INPUT_CLK(GND),
                .OUTPUT_CLK(GND),
                .OUTPUT_ENABLE(~mosi_tri_en), 
                .D_OUT_1(GND),
                .D_OUT_0(mosi_i), 
                .D_IN_1(),
                .D_IN_0()
                );

   
    
    
endmodule
