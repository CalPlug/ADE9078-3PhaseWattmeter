# To successfully run this script, make the following change:
# Update the PROJ_DIR with your directory path.

set PROJ_DIR "D:/rd1142_spi_slave_controller/rd1142"

cd $PROJ_DIR/simulation/iCE40/vhdl

if {![file exists timing_vhdl]} {
    vlib timing_vhdl 
}
endif

design create rtl_vhdl .
design open rtl_vhdl
adel -all

cd $PROJ_DIR/simulation/iCE40/vhdl								  



acom -O3 -work rtl_vhdl -2002  $PROJ_DIR/source/VHDL/spi_slave.vhd 

alog -O2 -sve  -work rtl_vhdl $PROJ_DIR/source/Verilog/SPI_Slave_top.v 

acom -work rtl_vhdl -2002 $PROJ_DIR/testbench/vhdl/spi_slave_tb.vhd



##============================================
##sim


asim -O5 -L ovi_ice -L ice +access +r +m+spi_slave_tb rtl_vhdl.spi_slave_tb behave

##============================================
##waves

add wave /spi_slave_tb/*

##============================================ 

run 2400 us
##============================================
##End of Simulation
##============================================