/**
 * File              : TOP.v
 * Author            : zhangzhao <zhangzhao@ihep.ac.cn>
 * Date              : 06.06.2022
 * Last Modified Date: 06.06.2022
 * Last Modified By  : zhangzhao <zhangzhao@ihep.ac.cn>
 * Description       : evr wrapper
 */

`timescale 1ns / 1ps

module TOP #
    (
        // Users to add parameters here
        // User parameters ends
        // Do not modify the parameters beyond this line
        // Parameters of Axi Slave Bus Interface S00_AXI
        parameter integer C_S00_AXI_DATA_WIDTH	= 32,
        parameter integer C_S00_AXI_ADDR_WIDTH	= 8
    )
    (
        // bus ports
        s00_axi_0_araddr,
        s00_axi_0_arprot,
        s00_axi_0_arready,
        s00_axi_0_arvalid,
        s00_axi_0_awaddr,
        s00_axi_0_awprot,
        s00_axi_0_awready,
        s00_axi_0_awvalid,
        s00_axi_0_bready,
        s00_axi_0_bresp,
        s00_axi_0_bvalid,
        s00_axi_0_rdata,
        s00_axi_0_rready,
        s00_axi_0_rresp,
        s00_axi_0_rvalid,
        s00_axi_0_wdata,
        s00_axi_0_wready,
        s00_axi_0_wstrb,
        s00_axi_0_wvalid,
        s00_axi_aclk_0,
        s00_axi_aresetn_0,

        // Users to add ports here
        // gtx ports
        GTREFCLK1N_IN,
        GTREFCLK1P_IN,
        GTREFCLK0N_IN,
        GTREFCLK0P_IN,
        GTXRXP_IN,
        GTXRXN_IN,
        // ramout
        // clkout_p,
        // clkout_n,
        // clkout1_p,
        // clkout1_n,
        // clkout2_p,
        // clkout2_n,
        // clkout3_p,
        // clkout3_n
        // cpllclk_out
        // testirq
        INTERRUPT_OUT
        // RECCLK_OUT
        // User ports ends
    );

    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 ARADDR" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s00_axi_0, ADDR_WIDTH 8, ARUSER_WIDTH 0, AWUSER_WIDTH 0, BUSER_WIDTH 0, CLK_DOMAIN EVR_s00_axi_aclk_0, DATA_WIDTH 32, FREQ_HZ 100000000, HAS_BRESP 1, HAS_BURST 0, HAS_CACHE 0, HAS_LOCK 0, HAS_PROT 1, HAS_QOS 0, HAS_REGION 0, HAS_RRESP 1, HAS_WSTRB 1, ID_WIDTH 0, MAX_BURST_LENGTH 1, NUM_READ_OUTSTANDING 1, NUM_READ_THREADS 1, NUM_WRITE_OUTSTANDING 1, NUM_WRITE_THREADS 1, PHASE 0.000, PROTOCOL AXI4LITE, READ_WRITE_MODE READ_WRITE, RUSER_BITS_PER_BYTE 0, RUSER_WIDTH 0, SUPPORTS_NARROW_BURST 0, WUSER_BITS_PER_BYTE 0, WUSER_WIDTH 0" *) input [7:0]s00_axi_0_araddr;
    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 ARPROT" *) input [2:0]s00_axi_0_arprot;
    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 ARREADY" *) output s00_axi_0_arready;
    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 ARVALID" *) input s00_axi_0_arvalid;
    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 AWADDR" *) input [7:0]s00_axi_0_awaddr;
    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 AWPROT" *) input [2:0]s00_axi_0_awprot;
    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 AWREADY" *) output s00_axi_0_awready;
    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 AWVALID" *) input s00_axi_0_awvalid;
    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 BREADY" *) input s00_axi_0_bready;
    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 BRESP" *) output [1:0]s00_axi_0_bresp;
    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 BVALID" *) output s00_axi_0_bvalid;
    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 RDATA" *) output [31:0]s00_axi_0_rdata;
    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 RREADY" *) input s00_axi_0_rready;
    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 RRESP" *) output [1:0]s00_axi_0_rresp;
    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 RVALID" *) output s00_axi_0_rvalid;
    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 WDATA" *) input [31:0]s00_axi_0_wdata;
    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 WREADY" *) output s00_axi_0_wready;
    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 WSTRB" *) input [3:0]s00_axi_0_wstrb;
    (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s00_axi_0 WVALID" *) input s00_axi_0_wvalid;
    (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.S00_AXI_ACLK_0 CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.S00_AXI_ACLK_0, ASSOCIATED_BUSIF s00_axi_0, ASSOCIATED_RESET s00_axi_aresetn_0, CLK_DOMAIN EVR_s00_axi_aclk_0, FREQ_HZ 100000000, PHASE 0.000" *) input s00_axi_aclk_0;
    (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 RST.S00_AXI_ARESETN_0 RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME RST.S00_AXI_ARESETN_0, POLARITY ACTIVE_LOW" *) input s00_axi_aresetn_0;

    // Users to add ports here
    // gtx ports
    input    GTREFCLK1N_IN;
    input    GTREFCLK1P_IN;
    input    GTREFCLK0N_IN;
    input    GTREFCLK0P_IN;
    input    GTXRXP_IN;
    input    GTXRXN_IN;
    // output ramout;
    // output clkout_p;
    // output clkout_n;
    // output clkout1_p;
    // output clkout1_n;
    // output clkout2_p;
    // output clkout2_n;
    // output clkout3_p;
    // output clkout3_n;
    // output clkout;
    // output clkout1;
    // output clkout2;
    // output clkout3;
    output    INTERRUPT_OUT;
    //output    RECCLK_OUT;
    // User ports ends

    //***************************** Wire Declarations *****************************
    // ground and vcc signals
    wire            tied_to_ground_i;
    wire    [63:0]  tied_to_ground_vec_i;
    wire            tied_to_vcc_i;
    wire    [63:0]  tied_to_vcc_vec_i;

    // Users to add wires here
    // axi registers output
    wire    [31:0]  AXI_Lite_register00;
    wire    [31:0]  AXI_Lite_register01;
    wire    [31:0]  AXI_Lite_register02;
    wire    [31:0]  AXI_Lite_register03;
    wire    [31:0]  AXI_Lite_register04;
    wire    [31:0]  AXI_Lite_register05;
    wire    [31:0]  AXI_Lite_register06;
    wire    [31:0]  AXI_Lite_register07;
    wire    [31:0]  AXI_Lite_register08;
    wire    [31:0]  AXI_Lite_register09;
    wire    [31:0]  AXI_Lite_register10;
    wire    [31:0]  AXI_Lite_register11;
    wire    [31:0]  AXI_Lite_register12;
    wire    [31:0]  AXI_Lite_register13;
    wire    [31:0]  AXI_Lite_register14;
    wire    [31:0]  AXI_Lite_register15;
    wire    [31:0]  AXI_Lite_register16;
    wire    [31:0]  AXI_Lite_register17;
    wire    [31:0]  AXI_Lite_register18;
    wire    [31:0]  AXI_Lite_register19;
    wire    [31:0]  AXI_Lite_register20;
    wire    [31:0]  AXI_Lite_register21;
    wire    [31:0]  AXI_Lite_register22;
    wire    [31:0]  AXI_Lite_register23;
    wire    [31:0]  AXI_Lite_register24;
    wire    [31:0]  AXI_Lite_register25;
    wire    [31:0]  AXI_Lite_register26;
    wire    [31:0]  AXI_Lite_register27;
    wire    [31:0]  AXI_Lite_register28;
    wire    [31:0]  AXI_Lite_register29;
    wire    [31:0]  AXI_Lite_register30;
    wire    [31:0]  AXI_Lite_register31;
    wire    [31:0]  AXI_Lite_register32;
    wire    [31:0]  AXI_Lite_register33;
    wire    [31:0]  AXI_Lite_register34;
    wire    [31:0]  AXI_Lite_register35;
    wire    [31:0]  AXI_Lite_register36;
    wire    [31:0]  AXI_Lite_register37;
    wire    [31:0]  AXI_Lite_register38;
    wire    [31:0]  AXI_Lite_register39;
    wire    [31:0]  AXI_Lite_register40;
    wire    [31:0]  AXI_Lite_register41;
    wire    [31:0]  AXI_Lite_register42;
    wire    [31:0]  AXI_Lite_register43;
    wire    [31:0]  AXI_Lite_register44;
    wire    [31:0]  AXI_Lite_register45;
    wire    [31:0]  AXI_Lite_register46;
    wire    [31:0]  AXI_Lite_register47;
    wire    [31:0]  AXI_Lite_register48;
    wire    [31:0]  AXI_Lite_register49;
    wire    [31:0]  AXI_Lite_register50;
    wire    [31:0]  AXI_Lite_register51;
    wire    [31:0]  AXI_Lite_register52;
    wire    [31:0]  AXI_Lite_register53;
    wire    [31:0]  AXI_Lite_register54;
    wire    [31:0]  AXI_Lite_register55;
    wire    [31:0]  AXI_Lite_register56;
    wire    [31:0]  AXI_Lite_register57;
    wire    [31:0]  AXI_Lite_register58;
    wire    [31:0]  AXI_Lite_register59;
    // axi registers input
    wire    [31:0]  AXI_Lite_register00_in;
    wire    [31:0]  AXI_Lite_register04_in;
    wire    [31:0]  AXI_Lite_register05_in;
    wire    [31:0]  AXI_Lite_register06_in;
    wire    [31:0]  AXI_Lite_register07_in;
    wire    [31:0]  AXI_Lite_register08_in;
    // global reset signal
    wire            rst_in;
    // clock port from gtx to other modules
    wire            recclk_in;
    // event code and dbus from gtx to other modules
    wire    [15:0]  rxdata_in;
    // mappingRAM output
    wire    [15:0]  mapping_out;
    // pulse output
    wire    [13:0]  pulse_out;
    // fps output
    wire    [5:0]   front_out;
    // event code and timestamp from event_fifo to axi-lite
    // wire [63:0]  event_code_out;
    // wire [15:0]w_ramout;
    // wire clkout;
    // wire clkout1;
    // wire clkout2;
    // wire clkout3;
    // wire REFCLK1;
    // User wire ends

    wire    [7:0]   s00_axi_0_1_ARADDR;
    wire    [2:0]   s00_axi_0_1_ARPROT;
    wire            s00_axi_0_1_ARREADY;
    wire            s00_axi_0_1_ARVALID;
    wire    [7:0]   s00_axi_0_1_AWADDR;
    wire    [2:0]   s00_axi_0_1_AWPROT;
    wire            s00_axi_0_1_AWREADY;
    wire            s00_axi_0_1_AWVALID;
    wire            s00_axi_0_1_BREADY;
    wire    [1:0]   s00_axi_0_1_BRESP;
    wire            s00_axi_0_1_BVALID;
    wire    [31:0]  s00_axi_0_1_RDATA;
    wire            s00_axi_0_1_RREADY;
    wire    [1:0]   s00_axi_0_1_RRESP;
    wire            s00_axi_0_1_RVALID;
    wire    [31:0]  s00_axi_0_1_WDATA;
    wire            s00_axi_0_1_WREADY;
    wire    [3:0]   s00_axi_0_1_WSTRB;
    wire            s00_axi_0_1_WVALID;
    wire            s00_axi_aclk_0_1;
    wire            s00_axi_aresetn_0_1;

    //***************************** Main Body of Code *****************************
    assign tied_to_ground_i     = 1'b0;
    // -------------------------  Static signal Assigments ---------------------
    assign tied_to_ground_vec_i = 64'h0000000000000000;
    assign tied_to_vcc_i        = 1'b1;
    assign tied_to_vcc_vec_i    = 64'hffffffffffffffff;

    // bus signals
    assign s00_axi_0_1_ARADDR    = s00_axi_0_araddr[7:0];
    assign s00_axi_0_1_ARPROT    = s00_axi_0_arprot[2:0];
    assign s00_axi_0_1_ARVALID   = s00_axi_0_arvalid;
    assign s00_axi_0_1_AWADDR    = s00_axi_0_awaddr[7:0];
    assign s00_axi_0_1_AWPROT    = s00_axi_0_awprot[2:0];
    assign s00_axi_0_1_AWVALID   = s00_axi_0_awvalid;
    assign s00_axi_0_1_BREADY    = s00_axi_0_bready;
    assign s00_axi_0_1_RREADY    = s00_axi_0_rready;
    assign s00_axi_0_1_WDATA     = s00_axi_0_wdata[31:0];
    assign s00_axi_0_1_WSTRB     = s00_axi_0_wstrb[3:0];
    assign s00_axi_0_1_WVALID    = s00_axi_0_wvalid;
    assign s00_axi_0_arready     = s00_axi_0_1_ARREADY;
    assign s00_axi_0_awready     = s00_axi_0_1_AWREADY;
    assign s00_axi_0_bresp[1:0]  = s00_axi_0_1_BRESP;
    assign s00_axi_0_bvalid      = s00_axi_0_1_BVALID;
    assign s00_axi_0_rdata[31:0] = s00_axi_0_1_RDATA;
    assign s00_axi_0_rresp[1:0]  = s00_axi_0_1_RRESP;
    assign s00_axi_0_rvalid      = s00_axi_0_1_RVALID;
    assign s00_axi_0_wready      = s00_axi_0_1_WREADY;
    assign s00_axi_aclk_0_1      = s00_axi_aclk_0;
    assign s00_axi_aresetn_0_1   = s00_axi_aresetn_0;

    // Users to add route here
    // assign ramout = w_ramout[0];
    // assign testirq = AXI_Lite_register00[0];
    // assign RECCLK_OUT=recclk_in;
    // User route ends

    //------------------------------  AXI_Lite  -----------------------------------
    AXI_Lite axi_lite
             (
                 // register output
                 .register00(AXI_Lite_register00),
                 .register01(AXI_Lite_register01),
                 .register02(AXI_Lite_register02),
                 .register03(AXI_Lite_register03),
                 .register04(AXI_Lite_register04),
                 .register05(AXI_Lite_register05),
                 .register06(AXI_Lite_register06),
                 .register07(AXI_Lite_register07),
                 .register08(AXI_Lite_register08),
                 .register09(AXI_Lite_register09),
                 .register10(AXI_Lite_register10),
                 .register11(AXI_Lite_register11),
                 .register12(AXI_Lite_register12),
                 .register13(AXI_Lite_register13),
                 .register14(AXI_Lite_register14),
                 .register15(AXI_Lite_register15),
                 .register16(AXI_Lite_register16),
                 .register17(AXI_Lite_register17),
                 .register18(AXI_Lite_register18),
                 .register19(AXI_Lite_register19),
                 .register20(AXI_Lite_register20),
                 .register21(AXI_Lite_register21),
                 .register22(AXI_Lite_register22),
                 .register23(AXI_Lite_register23),
                 .register24(AXI_Lite_register24),
                 .register25(AXI_Lite_register25),
                 .register26(AXI_Lite_register26),
                 .register27(AXI_Lite_register27),
                 .register28(AXI_Lite_register28),
                 .register29(AXI_Lite_register29),
                 .register30(AXI_Lite_register30),
                 .register31(AXI_Lite_register31),
                 .register32(AXI_Lite_register32),
                 .register33(AXI_Lite_register33),
                 .register34(AXI_Lite_register34),
                 .register35(AXI_Lite_register35),
                 .register36(AXI_Lite_register36),
                 .register37(AXI_Lite_register37),
                 .register38(AXI_Lite_register38),
                 .register39(AXI_Lite_register39),
                 .register40(AXI_Lite_register40),
                 .register41(AXI_Lite_register41),
                 .register42(AXI_Lite_register42),
                 .register43(AXI_Lite_register43),
                 .register44(AXI_Lite_register44),
                 .register45(AXI_Lite_register45),
                 .register46(AXI_Lite_register46),
                 .register47(AXI_Lite_register47),
                 .register48(AXI_Lite_register48),
                 .register49(AXI_Lite_register49),
                 .register50(AXI_Lite_register50),
                 .register51(AXI_Lite_register51),
                 .register52(AXI_Lite_register52),
                 .register53(AXI_Lite_register53),
                 .register54(AXI_Lite_register54),
                 .register55(AXI_Lite_register55),
                 .register56(AXI_Lite_register56),
                 .register57(AXI_Lite_register57),
                 .register58(AXI_Lite_register58),
                 .register59(AXI_Lite_register59),

                 // register input
                 .register00_in(AXI_Lite_register00_in),
                 .register04_in(AXI_Lite_register04_in),
                 .register05_in(AXI_Lite_register05_in),
                 .register06_in(AXI_Lite_register06_in),
                 .register07_in(AXI_Lite_register07_in),
                 .register08_in(AXI_Lite_register08_in),

                 // axi bus signals
                 .s00_axi_aclk(s00_axi_aclk_0_1),
                 .s00_axi_araddr(s00_axi_0_1_ARADDR),
                 .s00_axi_aresetn(s00_axi_aresetn_0_1),
                 .s00_axi_arprot(s00_axi_0_1_ARPROT),
                 .s00_axi_arready(s00_axi_0_1_ARREADY),
                 .s00_axi_arvalid(s00_axi_0_1_ARVALID),
                 .s00_axi_awaddr(s00_axi_0_1_AWADDR),
                 .s00_axi_awprot(s00_axi_0_1_AWPROT),
                 .s00_axi_awready(s00_axi_0_1_AWREADY),
                 .s00_axi_awvalid(s00_axi_0_1_AWVALID),
                 .s00_axi_bready(s00_axi_0_1_BREADY),
                 .s00_axi_bresp(s00_axi_0_1_BRESP),
                 .s00_axi_bvalid(s00_axi_0_1_BVALID),
                 .s00_axi_rdata(s00_axi_0_1_RDATA),
                 .s00_axi_rready(s00_axi_0_1_RREADY),
                 .s00_axi_rresp(s00_axi_0_1_RRESP),
                 .s00_axi_rvalid(s00_axi_0_1_RVALID),
                 .s00_axi_wdata(s00_axi_0_1_WDATA),
                 .s00_axi_wready(s00_axi_0_1_WREADY),
                 .s00_axi_wstrb(s00_axi_0_1_WSTRB),
                 .s00_axi_wvalid(s00_axi_0_1_WVALID)
             );


    //-----------------------------  MappingRAM  ----------------------------------
    //MappingRAM mappingRAM
    //    (
    //       .RAMout(w_ramout[15:0]),
    //       .clk_i(s00_axi_aclk_0_1),
    //       .wraddr(AXI_Lite_register01[7:0]),
    //       .wrdata(AXI_Lite_register02[15:0]),
    //       .rdaddr(AXI_Lite_register03[7:0]));

    //   EVR_xlslice_8_0 xlslice_8
    //        (.Din(AXI_Lite_register03),
    //         .Dout(xlslice_8_Dout));

    //    freq_divider test_divider
    //    (
    //        .clk(s00_axi_aclk_0_1),
    //        .rst(1'b0),
    //        .divide_data(32'h2),
    //        .clkout(clkout)
    //    );

    //OBUFDS
    ////( .IOSTANDARD("TMDS_33")//SpecifytheoutputI/Ostandard            )
    //      OBUFDS_inst0(
    //        .O  (clkout_p),//Diff_poutput(connectdirectlytotop-levelport)
    //        .OB (clkout_n),//Diff_noutput(connectdirectlytotop-levelport)
    //         //.I  (r_external_trig)
    //         .I  (clkout)//Bufferinput
    //        );

    // freq_divider test_divider1
    //              (
    //                  .clk(s00_axi_aclk_0_1),
    //                  .rst(1'b0),
    //                  .divide_data(32'h3),
    //                  .clkout(clkout1)
    //              );
    //
    //  OBUFDS
    ////#(
    ////                .IOSTANDARD("TMDS_33")//SpecifytheoutputI/Ostandard
    ////                )
    //          OBUFDS_inst1(
    //            .O  (clkout1_p),//Diff_poutput(connectdirectlytotop-levelport)
    //            .OB (clkout1_n),//Diff_noutput(connectdirectlytotop-levelport)
    //             //.I  (r_external_trig)
    //             .I  (clkout1)//Bufferinput
    //            );


    //     freq_divider test_divider2
    //       (
    //           .clk(s00_axi_aclk_0_1),
    //           .rst(1'b0),
    //           .divide_data(32'h3e8),
    //           .clkout(clkout2)
    //       );

    //       OBUFDS#(
    //                   .IOSTANDARD("DEFAULT")//SpecifytheoutputI/Ostandard
    //                   )
    //             OBUFDS_inst2(
    //               .O  (clkout2_p),//Diff_poutput(connectdirectlytotop-levelport)
    //               .OB (clkout2_n),//Diff_noutput(connectdirectlytotop-levelport)
    //                //.I  (r_external_trig)
    //                .I  (clkout2)//Bufferinput
    //               );

    //     freq_divider test_divider3
    //          (
    //              .clk(s00_axi_aclk_0_1),
    //              .rst(1'b0),
    //              .divide_data(32'h186a0),
    //              .clkout(clkout3)
    //          );
    //assign clkout3 = s00_axi_aclk_0_1;

    //          OBUFDS#(
    //                      .IOSTANDARD("DEFAULT")//SpecifytheoutputI/Ostandard
    //                      )
    //                OBUFDS_inst3(
    //                  .O  (clkout3_p),//Diff_poutput(connectdirectlytotop-levelport)
    //                  .OB (clkout3_n),//Diff_noutput(connectdirectlytotop-levelport)
    //                   //.I  (r_external_trig)
    //                   .I  (clkout3)//Bufferinput
    //                  );

    // bram_wrapper mappingRAM
    //              (
    //                  .BRAM_PORTA_0_addr(AXI_Lite_register01[7:0]),
    //                  .BRAM_PORTA_0_clk(s00_axi_aclk_0_1),
    //                  .BRAM_PORTA_0_din(AXI_Lite_register02[15:0]),
    //                  .BRAM_PORTA_0_en(1'b1),
    //                  .BRAM_PORTA_0_we(1'b1),
    //                  .BRAM_PORTB_0_addr(AXI_Lite_register03[7:0]),
    //                  .BRAM_PORTB_0_clk(s00_axi_aclk_0_1),
    //                  .BRAM_PORTB_0_dout(AXI_Lite_register04_in[15:0]),
    //                  .BRAM_PORTB_0_en(1'b1)
    //              );


    //-----------------------------  gtx_wrapper  -----------------------------------
    evr_gtx_wrapper evr_gtx_wrapper_inst
                    (
                        .GTREFCLK1N_IN(GTREFCLK1N_IN),
                        .GTREFCLK1P_IN(GTREFCLK1P_IN),
                        .GTREFCLK0N_IN(GTREFCLK0N_IN),
                        .GTREFCLK0P_IN(GTREFCLK0P_IN),
                        .RXDATA_OUT(rxdata_in),
                        .RXOUTCLK_OUT(recclk_in),
                        .GTXRXP_IN(GTXRXP_IN),
                        .GTXRXN_IN(GTXRXN_IN),
                        .CPLLLOCK_OUT(AXI_Lite_register00_in[3])
                    );

    //-----------------------------  event_fifo  ----------------------------------
    event_fifo event_fifo_inst
               (
                   .WRCLK_IN(recclk_in),
                   .RDCLK_IN(s00_axi_aclk_0_1),
                   .AXI_ARVALID_IN(s00_axi_0_1_ARVALID),
                   .AXI_ARADDR_IN(s00_axi_0_1_ARADDR),
                   .EVENT_CODE_IN(rxdata_in[7:0]),
                   .EVENT_CODE_OUT(AXI_Lite_register04_in[7:0]),
                   .SECONDS_COUNTER_OUT(AXI_Lite_register05_in),
                   .EVENT_COUNTER_OUT(AXI_Lite_register06_in),
                   .INTERRUPT_OUT(INTERRUPT_OUT),
                   .RST_IN(rst_in),
                   .EMPTY_OUT(AXI_Lite_register00_in[1]),
                   .FULL_OUT(AXI_Lite_register00_in[2]),
                   .LATCH_IN(AXI_Lite_register00[4]),
                   .SECONDS_LATCH_OUT(AXI_Lite_register07_in),
                   .TIMESTAMP_LATCH_OUT(AXI_Lite_register08_in)
               );

    //-----------------------------  MappingRAM  ----------------------------------
    mapping_ram mapping_ram_inst
                (
                    .WR_CLK_IN(s00_axi_aclk_0_1),
                    .RD_CLK_IN(recclk_in),
                    //---------------------  Control signals  ---------------------------
                    .RAM_EN_IN(AXI_Lite_register00[5]),
                    .RAM_RDSEL_IN(AXI_Lite_register00[6]),
                    .RAM_WRSEL_IN(AXI_Lite_register00[7]),
                    .RAM_CLR_IN(AXI_Lite_register00[8]),
                    //----------------------  Data signals  -----------------------------
                    .WR_ADDR_IN(AXI_Lite_register01[7:0]),
                    .WR_DATA_IN(AXI_Lite_register02[15:0]),
                    .RD_ADDR_IN(rxdata_in[7:0]),
                    .RD_DATA_OUT(mapping_out[15:0]),
                    //-----------------------  Bus signals  -----------------------------
                    .AXI_AWVALID_IN(s00_axi_0_1_AWVALID),  /* AXI write operation.       */
                    .AXI_AWADDR_IN(s00_axi_0_1_AWADDR)
                );

    //-----------------------------  Pluse out  -----------------------------------
    pulse_set pulse_set_inst
              (
                  .clk(recclk_in),
                  .start(mapping_out[13:0]),
                  .PulseSelect_reg(AXI_Lite_register09),
                  .PulseWidth_reg(AXI_Lite_register10),
                  .PulseDelay_reg(AXI_Lite_register11),
                  .PulsePolarity_reg(AXI_Lite_register12),//bit11-bit24
                  .OutputPulseEnables_reg(AXI_Lite_register13),//bit0-d
                  .pulse0(pulse_out[0]),
                  .pulse1(pulse_out[1]),
                  .pulse2(pulse_out[2]),
                  .pulse3(pulse_out[3]),
                  .pulse4(pulse_out[4]),
                  .pulse5(pulse_out[5]),
                  .pulse6(pulse_out[6]),
                  .pulse7(pulse_out[7]),
                  .pulse8(pulse_out[8]),
                  .pulse9(pulse_out[9]),
                  .pulse10(pulse_out[10]),
                  .pulse11(pulse_out[11]),
                  .pulse12(pulse_out[12]),
                  .pulse13(pulse_out[13])
              );
    //-----------------------------  Pluse out  -----------------------------------
    fps_map fps_map_inst
            (
                .pulses(pulse_out),
                .Databus(rxdata_in[15:8]),
                .FrontOut(front_out),
                .FPS1(AXI_Lite_register14),
                .FPS2(AXI_Lite_register15),
                .FPS3(AXI_Lite_register16),
                .FPS4(AXI_Lite_register17),
                .FPS5(AXI_Lite_register18),
                .FPS6(AXI_Lite_register19)
            );

    //--------------------------------  reset  ------------------------------------
    reset reset_inst
          (
              .CLK_IN(s00_axi_aclk_0_1),
              .RST_IN(AXI_Lite_register00[0]),
              .FIFO_RST_OUT(rst_in)
          );
endmodule
