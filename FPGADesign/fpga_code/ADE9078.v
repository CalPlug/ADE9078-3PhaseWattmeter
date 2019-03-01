module getVersion(
);
return ADE9078_spialg16_read inst(.address(VERSION_16));
endmodule

module getPowerFactorA(
);
reg shortint value;
assign value = 0;
assign value = ADE9078_spialg16_read inst(.address(PFA_16));
assign decimal = decimalize inst(.input1(value) .factor(327.67) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module getPowerFactorB(
);
reg shortint value;
assign value = 0;
assign value = ADE9078_spialg16_read inst(.address(PFB_16));
assign decimal = decimalize inst(.input1(value) .factor(327.67) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module getPowerFactorC(
);
reg shortint value;
assign value = 0;
assign value = ADE9078_spialg16_read inst(.address(PFC_16));
assign decimal = decimalize inst(.input1(value) .factor(327.67) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module getPhaseCalibA(
);
reg int value;
assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(APHCAL0_32));
return value;
endmodule

module getPhaseCalibB(
);
reg int value;
assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(BPHCAL0_32));
return value;
endmodule

module getPhaseCalibC(
);
reg int value;
assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(CPHCAL0_32));
return value;
endmodule

module getPHNOLOAD(
);
reg unsigned shortint value;
assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(PHNOLOAD_32));
return value;
endmodule

module getInstVoltageA(
);
reg int value;
assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(AV_PCF_32));
return value;
endmodule

module getInstVoltageB(
);
reg int value;
assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(BV_PCF_32));
return value;
endmodule

module getInstVoltageC(
);
reg int value;
assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(CV_PCF_32));
return value;
endmodule

module getAVrms(
);
reg int unsigned value;
reg real decimal;

assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(AVRMS_32));
assign decimal = decimalize inst(.input1(value) .factor(19090) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module getBVrms(
);
reg int unsigned value;
reg real decimal;

assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(BVRMS_32));
assign decimal = decimalize inst(.input1(value) .factor(19090) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module getCVrms(
);
reg int unsigned value;
reg real decimal;

assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(CVRMS_32));
assign decimal = decimalize inst(.input1(value) .factor(19090) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module getInstCurrentA(
);
reg int value;
assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(AI_PCF_32));
return value;
endmodule

module getInstCurrentB(
);
reg int value;
assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(BI_PCF_32));
return value;
endmodule

module getInstCurrentC(
);
reg int value;
assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(CI_PCF_32));
return value;
endmodule

module getIrmsA(
);
reg int unsigned value;
reg real decimal;

assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(AIRMS_32));
assign decimal = decimalize inst(.input1(value) .factor(1327) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module getIrmsB(
);
reg int unsigned value;
reg real decimal;

assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(BIRMS_32));
assign decimal = decimalize inst(.input1(value) .factor(1327) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module getIrmsC(
);
reg int unsigned value;
reg real decimal;

assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(CIRMS_32));
assign decimal = decimalize inst(.input1(value) .factor(1327) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module getVpeak(
);
  reg unsigned int value;
  assign value = 0;
  assign value = ADE9078_spialg32_read inst(.address(VPEAK_32));
  return value;
  endmodule

module getIpeak(
);
reg unsigned int value;
assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(IPEAK_32));
return value;
endmodule

module getEnergyA(
);
reg int value;
assign value = 0;
assign value = ADE9078_spialg16_read inst(.address(ACCMODE_16));
return value;
endmodule

module getInstApparentPowerA(
);
reg int value;
reg real decimal;

assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(AVA_32));
assign decimal = decimalize inst(.input1(value) .factor(1.502) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module getInstApparentPowerB(
);
reg int value;
reg real decimal;

assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(BVA_32));
assign decimal = decimalize inst(.input1(value) .factor(1.502) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module getInstApparentPowerC(
);
reg int value;
reg real decimal;

assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(CVA_32));
assign decimal = decimalize inst(.input1(value) .factor(1.502) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module getInstActivePowerA(
);
reg int value;
reg real decimal;

assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(AWATT_32));
assign decimal = decimalize inst(.input1(value) .factor(1.502) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module getInstActivePowerB(
);
reg int value;
reg real decimal;

assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(BWATT_32));
assign decimal = decimalize inst(.input1(value) .factor(1.502) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module getInstActivePowerC(
);
reg int value;
reg real decimal;

assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(CWATT_32));
assign decimal = decimalize inst(.input1(value) .factor(1.502) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module getInstReactivePowerA(
);

reg int value;
reg real decimal;

assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(AVAR_32));
assign decimal = decimalize inst(.input1(value) .factor(1.502) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module getInstReactivePowerB(
);

reg int value;
reg real decimal;

assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(BVAR_32));
assign decimal = decimalize inst(.input1(value) .factor(1.502) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module getInstReactivePowerC(
);

reg int value;
reg real decimal;

assign value = 0;
assign value = ADE9078_spialg32_read inst(.address(CVAR_32));
assign decimal = decimalize inst(.input1(value) .factor(1.502) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module read32Bit(
  input shortint unsigned readRegister,
);
reg int value,
reg real decimal
assign data = ADE9078_spialg32_read inst(.address(readRegister));
assign decimal = decimalize inst(.input1(data) .factor(1.502) .offset(0));

if (signed(decimal) < 0)
 out = -signed(decimal);
else
 out = in;
decimal = out;
return decimal;
endmodule

module checkBit(
  input int data;
  input int i
  );
  return ((data) & (1 << i)) > 0;
endmodule

const int SPI_freq = 1000000;

module ADE9078_init(
  input int ss,
  input int SPI_freq,
  input mystruct* is
);
struct mystruct {
  // All gains are 2 bits. Options: 1, 2, 3, 4
  unsigned byte vAGain;
  unsigned byte vBGain;
  unsigned byte vCGain;

  unsigned byte iAGain;
  unsigned byte iBGain;
  unsigned byte iCGain;
  unsigned byte iNGain;

  unsigned int powerAGain;
  unsigned int powerBGain;
  unsigned int powerCGain;

  unsigned byte vConsel;
  unsigned byte iConsel;
};

reg _SS;
reg _SPI_freq;
reg mystruct* is;
reg unsigned shortint pgaGain;
reg unsigned shortint settingsACCMODE;

_SS=SS;
_SPI_freq=SPI_freq;
this->is = is;

int status1Data = read32Bit inst(.readRegister(STATUS1_32));
if (!checkBit inst(.data(status1Data), .i(16)) {
  $display("WARNING, POWER UP MAY NOT BE FINISHED");
}

ADE9078_spialg32_write inst(.address(APGAIN_32) .data(is->powerAGain));
ADE9078_spialg32_write inst(.address(BPGAIN_32) .data(is->powerBGain));
ADE9078_spialg32_write inst(.address(CPGAIN_32) .data(is->powerCGain));

pgaGain = (is->vCGain << 12) + (is->vBGain << 10) + (is->vCGain << 8) + (is->iNGain << 6) + (is->iCGain << 4) + (is->iBGain << 2) + is->iAGain;

ADE9078_spialg32_write inst(.address(VLEVEL_32) .data(0x117514));
ADE9078_spialg16_write inst(.address(CONFIG0_32) .data(0x00000000));

settingsACCMODE = (is->iConsel << 6) + (is->vConsel << 5);

ADE9078_spialg16_write inst(.address(ACCMODE_16) .data(settingsACCMODE));
ADE9078_spialg16_write inst(.address(RUN_16) .data(1));
ADE9078_spialg16_write inst(.address(EP_CFG_16) .data(1));
ADE9078_spialg16_write inst(.address(CONFIG1_16) .data(0x0000));
ADE9078_spialg16_write inst(.address(CONFIG2_16) .data(0x0000));
ADE9078_spialg16_write inst(.address(CONFIG3_16) .data(0x0000));
ADE9078_spialg32_write inst(.address(DICOEFF_32) .data(0xFFFFE000));
endmodule

module ADE9078_spialg16_read(
  input shortint unsigned address,
);
wire byte unsigned isRead;
wire byte unsigned commandHeader1;
wire byte unsigned commandHeader2;
byte one, two;
byte dummyWrite = 0x00;

assign isRead = 1;
assign commandHeader1 = (address >> 4);
assign commandHeader2 = ((address & 0xF) << 4) | (isRead << 3);

assign ss = 1'b1;
spi(.i_data(commandHeader1));
spi(.i_data(commandHeader2));

one = spi(.i_data(dummyWrite));
two = spi(.i_data(dummyWrite));
assign ss = 1'b0;
return (((unsigned int) one << 8) + ((unsigned int) two));

endmodule

module ADE9078_spialg16_write(
  input shortint unsigned address,
  input shortint unsigned data
  );

wire byte unsigned isRead;
wire byte unsigned commandHeader1;
wire byte unsigned commandHeader2;
wire byte unsigned MSB_data;
wire byte unsigned LSB_data;

assign isRead = 0;
assign commandHeader1 = (address >> 4);
assign commandHeader2 = ((address & 0xF) << 4) | (isRead << 3);
assign MSB_data = (data >> 8);
assign LSB_data = (data & 0xFF);

assign ss = 1'b1;
spi(.i_data(commandHeader1));
spi(.i_data(commandHeader2));

spi(.i_data(MSB_data));
spi(.i_data(LSB_data));
assign ss = 1'b0;

endmodule

module ADE9078_spialg32_read(
input shortint unsigned address
);

wire byte unsigned isRead;
wire byte unsigned commandHeader1;
wire byte unsigned commandHeader2;

assign isRead = 1;
assign commandHeader1 = (address >> 4);
assign commandHeader2 = ((address & 0xF) << 4) | (isRead << 3);
byte one, two, three, four;
byte dummyWrite = 0x00;

assign ss = 1'b1;
spi(.i_data(commandHeader1));
spi(.i_data(commandHeader2));

one = spi(.i_data(dummyWrite));
two = spi(.i_data(dummyWrite));
three = spi(.i_data(dummyWrite));
four = spi(.i_data(dummyWrite));
assign ss = 1'b0;

return ((unsigned int) one << 24) + ((unsigned int) two << 16) + ((unsigned int) three << 8) + (unsigned int) four;

endmodule

module ADE9078_spialg32_write(
input shortint unsigned address,
input int unsigned data
);

wire byte unsigned isRead;
wire byte unsigned commandHeader1;
wire byte unsigned commandHeader2;
wire byte unsigned byteFour;
wire byte unsigned byteThree;
wire byte unsigned byteTwo;
wire byte unsigned byteOne;

assign isRead = 0;
assign commandHeader1 = (address >> 4);
assign commandHeader2 = ((address & 0xF) << 4) | (isRead << 3);
assign byteFour = (data >> 24);
assign byteThree = (data & 0xFFFFFF) >> 16;
assign byteTwo = (data & 0xFFFF) >> 8;
assign byteOne = (data & 0xFF);

assign ss = 1'b1;
spi(.i_data(commandHeader1));
spi(.i_data(commandHeader2));

spi(.i_data(byteFour));
spi(.i_data(byteThree));
spi(.i_data(byteTwo));
spi(.i_data(byteOne));
assign ss = 1'b0;

endmodule

module decimalize(
  input long input1,
  input real factor,
  input real offset,
  );
return ((real)input1/factor)+offset;
endmodule

module spi(
    inout MOSI,
    input wire clk,
    input [23:0] address,
    inout wire SCK,
    input [31:0] i_data,
    inout reg MISO,
    input [1:0] WR_en,
    output [31:0] o_data,
    input good,
    output reg data_ready
    );

    wire spi_enable;
    wire ctrl;
    wire [7:0] spi_read;
    reg [7:0] ctrl_reg;
    reg [31:0] read_data;
    reg data_ready;
    wire mi;
    wire so;
    wire soe;
    wire si;
    wire mo;
    wire moe;
    wire scki;
    wire scko;
    wire sckoe;

    wire mcsno3,mcsno2,mcsno1,mcsno0;
    wire mcsnoe3,mcsnoe2,mcsnoe1,mcsnoe0;

    assign spi_enable = (address[23:16] = 8'h03);
    assign ctrl = (address[23:16] == 8'h10);

    always(@posedge clk)
    begin
    if(!good)
    data_ready <= 1'b0;
    if(!data_ready && good)
    begin
    data_ready <= 1'b1;
    read_data <= 31'b0;
    end
    else if(!data_ready && ctrl && good)
    begin
    ready <= 1'b1;
    if(WR_en[0])
      ctrl_reg <= i_data;
    read_data <= {24'h0, ctrl_reg};
    end
    if (!data_ready && spi_enable && good)
    begin
    data_ready <=1'b1;
    read_data <= spi_read;
    end
    end

    assign o_data = read_data;

    SB_SPI #(
      .BUS_ADDR74("0b0000")
    )
    spi_slave (
                  .SBRWI(WR_en[0]),
                  .SBSTBI(good && spi_en && !data_ready),
                  .SBADRI0(address[2]),
                  .SBADRI1(address[3]),
                  .SBADRI2(address[4]),
                  .SBADRI3(address[5]),
                  .SBADRI4(address[6]),
                  .SBADRI5(address[7]),
                  .SBADRI6(address[8]),
                  .SBADRI7(address[9]),
                  .SBDATO0(spi_read[0]),
                  .SBDATO1(spi_read[1]),
                  .SBDATO2(spi_read[2]),
                  .SBDATO3(spi_read[3]),
                  .SBDATO4(spi_read[4]),
                  .SBDATO5(spi_read[5]),
                  .SBDATO6(spi_read[6]),
                  .SBDATO7(spi_read[7]),
                  .SBCLKI(clk),
                  .SBDATI0(i_data[0]),
                  .SBDATI1(i_data[1]),
                  .SBDATI2(i_data[2]),
                  .SBDATI3(i_data[3]),
                  .SBDATI4(i_data[4]),
                  .SBDATI5(i_data[5]),
                  .SBDATI6(i_data[6]),
                  .SBDATI7(i_data[7]),
                  .SPI1_MISO(MISO),
                  .SPI1_MOSI(MOSI),
                  .SCKI(SCK),
                  .SCSNI(1'b1),
                  .MI(mi),
                  .SO(so),
                  .SOE(soe),
                  .SI(si),
                  .MO(mo),
                  .MOE(moe),
                  .SCKI(scki),
                  .SCKO(scko),
                  .SCKOE(sckoe),
                  .SBACKO(spi_ack),
                  .SPIIRQ(),
                  .SPIWKUP(),
                  .MCSNO3(mcsno3),
                  .MCSNO2(mcsno2),
                  .MCSNO1(mcsno1),
                  .MCSNO0(mcsno0),
                  .MCSNOE3(mcsnoe3),
                  .MCSNOE2(mcsnoe2),
                  .MCSNOE1(mcsnoe1),
                  .MCSNOE0(mcsnoe0)
                  );

                  SB_IO #(
  .PIN_TYPE(6'b101001),
) miso_io (
  .PACKAGE_PIN(MISO),
  .OUTPUT_ENABLE(soe),
  .D_OUT_0(so),
  .D_IN_0(mi)
);

SB_IO #(
  .PIN_TYPE(6'b101001),
) mosi_io (
  .PACKAGE_PIN(MOSI),
  .OUTPUT_ENABLE(moe),
  .D_OUT_0(mo),
  .D_IN_0(si)
);

SB_IO #(
  .PIN_TYPE(6'b101001),
  .PULLUP(1'b1)
) sck_io (
  .PACKAGE_PIN(SCK),
  .OUTPUT_ENABLE(sckoe),
  .D_OUT_0(scko),
  .D_IN_0(scki)
);
    endmodule
