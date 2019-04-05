// Source https://github.com/mmicko/mikrobus-upduino/blob/master/src/

module spi(
    inout MOSI,
    input wire clk,
    input [23:0] address,
    inout wire SCK,
    input [31:0] i_data,
    inout reg MISO,
    input WR_en,
    output [31:0] o_data,
    input good,
    inout ss,
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
    read_data <= 32'b0;
    end
    else if(!data_ready && ctrl && good)
    begin
    ready <= 1'b1;
    if(WR_en == 1'b0)
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
