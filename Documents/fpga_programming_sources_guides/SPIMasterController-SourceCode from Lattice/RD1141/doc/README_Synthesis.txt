-------------------------------------------------------------------------------
			RD1141 SPI_Master Source Files Setup:

	To load pre-compiled project in icecube2:
		1. Open iCEcube2 and select "Open Project".
		2. Browse to  the directory "RD1141\Project\SPI_Master".
		3. Select the project file "SPI_Master_sbt.project" to load the project in iCEcube2.

	To Synthesize with iCEcube2:
		1. Create a new Project in the iCEcube2 software, choose appropriate Device
		   (Select "iCE40 LP1K CM121" for this project).
		2. To add design source files add files from the directory "RD1141\Source".
		3. Select the files 
			a.VHDL/asyn_fifo.vhd
			b.VHDL/gray_counter.vhd
			c.VHDL/sclk_gen.vhd
			d.VHDL/spi_data_path.vhd
			e.VHDL/spi_master
			f.Verilog/spi_master_top.v
		4. Launch Synthesis tool, RUN synthesis in Synplify and close upon successful completion.

---------------------------------------------------------------------------------
