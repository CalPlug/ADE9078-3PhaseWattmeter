
-------------------------------------------------------------------------------
			RD1142 SPI_Slave Source Files Setup:

	To load pre-compiled project in icecube2:
		1. Open iCEcube2 and select "Open Project".
		2. Browse to  the directory "rd1142_spi_slave_controller\rd1142\project\iCE40\vhdl\iCE40_vhdl".
		3. Select the project file "iCE40_vhdl_sbt.project" to load the project in iCEcube2.

	To Synthesize with iCEcube2:
		1. Create a new Project in the iCEcube2 software, choose appropriate Device
		   (Select "iCE40 LP1K CM121" for this project).
		2. To add design source files add files from the directory "rd1142\source".
		3. Select the files 
			a.vhdl/spi_slave.vhd
			b.Verilog/spi_slave_top.v
		4. Launch Synthesis tool, RUN synthesis in LSE/Synplify and close upon successful completion.

---------------------------------------------------------------------------------

---------------------------------------------------------------------------------------------------

                                ReadMe File for Simulation

  	Simulation Set-up:
	
	Note: Run the project and generate .vhd (netlist) and sdf files before running the timing.do files.
	
    1. Open Standalone Active HDL software from the iCEcube2 Installation:
		IMP NOTE: USE iCEcube2 VERSION- "2012.06" or ABOVE.		
		a. Go to "Start>All Programs>Lattice iCEcube2>" and select "AVHDL"
		b. The Active HDL software will open.
   	2. To successfully run the script, make the following change:
		a. Open the scripts "rtl_vhdl.do" for functional simulation and timing_vhdl.do for timing simulation script from path "rd1142\simulation\iCE40\vhdl".
		b. Update the .do file with the path  rd1142\simulation\iCE40\vhdl" line, with your directory path.		
	3. Open the pull down menu "Tools" and select  "Execute Macro". 
	4. Browse to "rd1142\simulation\iCE40\vhdl".
	5. Select the macro rtl_vhdl.do for functional simulation and timing_vhdl.do for timing simulation. This will automatically complete the simulation.
	6. A new simulation directory iCE40_vhdl_rtl will be create for functional simulation and iCE40_vhdl_timing for timing simulation in the simulation folder.

---------------------------------------------------------------------------------------------------  
