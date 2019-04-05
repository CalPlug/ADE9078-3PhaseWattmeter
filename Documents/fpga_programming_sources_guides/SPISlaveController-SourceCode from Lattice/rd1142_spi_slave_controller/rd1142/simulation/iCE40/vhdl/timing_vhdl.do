# To successfully run this script, make the following change:
# Update the PROJ_DIR with your directory path.

set PROJ_DIR "D:/rd1142_spi_slave_controller/rd1142"

cd $PROJ_DIR/simulation/iCE40/vhdl

if {![file exists timing_vhdl]} {
    vlib timing_vhdl 
}
endif

design create timing_vhdl .
design open timing_vhdl
adel -all

cd $PROJ_DIR/simulation/iCE40/vhdl

acom -O2 -sve  -work timing_vhdl $PROJ_DIR/project/iCE40/vhdl/iCE40_vhdl/iCE40_vhdl_Implmnt/sbt/outputs/simulation_netlist/SPI_Slave_top_sbt.vhd
acom -work timing_vhdl -2002 $PROJ_DIR/testbench/vhdl/spi_slave_tb.vhd


#vlog -dbg -work timing_vhdl $PROJ_DIR/project/ecp2/verilog/ecp2_verilog/ecp2_verilog_ecp2_verilog_vo.vo
#vlog -dbg +incdir+"$PROJ_DIR/source/verilog/ecp2" -work timing_vhdl $PROJ_DIR/testbench/verilog/ads6424.v
#vlog -dbg +define+TIMING_SIM +define+SYNP_SIM +incdir+"$PROJ_DIR/source/verilog/ecp2" -work timing_vhdl $PROJ_DIR/testbench/verilog/adc_tb.v -y $LIB_DIR/cae_library/simulation/verilog/ecp2 +libext+.v
#vlog -dbg +incdir+"$PROJ_DIR/source/verilog/ecp2" -work timing_vhdl $PROJ_DIR/testbench/verilog/IDDRX2D1.v

module spi_slave_tb

#vsim +access +r -L ovi_ecp2 -PL pmi_work adc_tb -noglitch +no_tchk_msg -sdfmax /adc_tb/adc_inst="$PROJ_DIR/project/ecp2/verilog/ecp2_verilog/ecp2_verilog_ecp2_verilog_vo.sdf" +transport_path_delays +transport_int_delays
asim -O5 -L ovi_ice -L ice +access +r +m+spi_slave_tb -sdfmax /spi_slave_tb/u0_spis0_inst="$PROJ_DIR//project/iCE40/vhdl/iCE40_vhdl/iCE40_vhdl_Implmnt/sbt/outputs/simulation_netlist/SPI_Slave_top_sbt_vital.sdf" timing_vhdl.spi_slave_tb behave

add wave /spi_slave_tb/*
#add wave -named_row "System Signal" -bold -height 36 -color 255,0,0
#add wave -noreg -logic {/adc_tb/adc_inst/clk2}
#add wave -noreg -logic {/adc_tb/adc_inst/rstn}
#add wave -named_row "FPGA Output Parallel Interface" -bold -height 36 -color 255,0,0
#add wave -noreg -logic {/adc_tb/adc_inst/word_cap}
#add wave -noreg -hexadecimal -literal {/adc_tb/adc_inst/frame_word}
#add wave -noreg -hexadecimal -literal {/adc_tb/adc_inst/DA_word}
#add wave -named_row "ADC Interface" -bold -height 36 -color 255,0,0
#add wave -noreg -logic {/adc_tb/adc_inst/bit_clk}
#add wave -noreg -logic {/adc_tb/adc_inst/frame}
#add wave -noreg -logic {/adc_tb/adc_inst/DA0}
#add wave -noreg -logic {/adc_tb/adc_inst/DA1}
#add wave -noreg -logic {/adc_tb/adc_inst/adc_sen}
#add wave -noreg -logic {/adc_tb/adc_inst/adc_sclk}
#add wave -noreg -logic {/adc_tb/adc_inst/adc_sdata}
#add wave -noreg -logic {/adc_tb/adc_inst/adc_cfg1}
#add wave -noreg -logic {/adc_tb/adc_inst/adc_cfg2}
#add wave -noreg -logic {/adc_tb/adc_inst/adc_cfg3}
#add wave -noreg -logic {/adc_tb/adc_inst/adc_cfg4}

run 2400 us