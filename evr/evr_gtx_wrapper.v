`default_nettype wire
`timescale 1ns / 1ps

//***************************** Entity Declaration ****************************

module evr_gtx_wrapper  #
    (
        //reference clock select
        parameter   RX_REFCLKSEL = 0
    )
    (
        //------------------------ Channel - Clocking Ports ------------------------
        input           GTREFCLK1N_IN,
        input           GTREFCLK1P_IN,
        input           GTREFCLK0N_IN,
        input           GTREFCLK0P_IN,

        //-------------------------- RX Datapath signals ---------------------------
        output  [15:0]  RXDATA_OUT,

        //------------- Receive Ports - RX Fabric Output Control Ports -------------
        output          RXOUTCLK_OUT,

        //---------------------- Receive Ports - RX AFE Ports ----------------------
        input           GTXRXP_IN,
        input           GTXRXN_IN,

        output          CPLLLOCK_OUT
        
    );

    //***************************** Wire Declarations *****************************
    // ground and vcc signals
    wire            tied_to_ground_i;
    wire    [63:0]  tied_to_ground_vec_i;
    wire            tied_to_vcc_i;
    wire    [63:0]  tied_to_vcc_vec_i;

    // RX Datapath signals
    wire    [15:0]  rxdata_o;

    // rx reset signal
    wire            gtrxreset;

    // sigals form gtxe2_i to gtx_bitslide
    wire            rxcommadet_o;
    wire            rxbyteisaligned_o;
    wire            rxrstdone_o;
    wire            cplllock_o;

    // recovered clock pass MMCM
    wire            rxusrclk_o;
    wire            rxusrclk_i;

    // sigals form gtx_bitslide to gtxe2_i
    wire            rxslide_i;
    wire            rxcdrrst_i;

    // fix the phase signals
    wire            rx_ready;
    wire            bit_slide_rdy;
    wire    [4:0]   bit_slide_no;

    //*************************** Register Declarations ***************************
    // fix the phase signals
    reg             rst_auto;
    reg     [9:0]   bitslide_count;

    //********************************* Main Body of Code**************************
    // -------------------------  Static signal Assigments -----------------------
    assign tied_to_ground_i     = 1'b0;
    assign tied_to_ground_vec_i = 64'h0000000000000000;
    assign tied_to_vcc_i        = 1'b1;
    assign tied_to_vcc_vec_i    = 64'hffffffffffffffff;
    // recovered clock output
    assign RXOUTCLK_OUT         = rxusrclk_o;
    // RX Datapath signals
    assign RXDATA_OUT           = rxdata_o;

    assign CPLLLOCK_OUT         = cplllock_o;

    //---------------------------- MMCM Instances ---------------------------------
    // use Clocking Wizard IP Core
    clk_wiz_0 clk_wiz_0_inst
              (
                  // Clock out ports
                  .clk_out1(rxusrclk_o),
                  // Status and control signals
                  // input reset
                  .reset(1'b0),
                  // output locked
                  .locked(),
                  // Clock in ports
                  .clk_in1(rxusrclk_i)
              );

    //---------------------------  GTX Instances  ---------------------------------
    evr_gtx evr_gtx_inst
            (
                //------------------------ Channel - Clocking Ports ------------------------
                .GTREFCLK0N_IN                  (GTREFCLK0N_IN),
                .GTREFCLK0P_IN                  (GTREFCLK0P_IN),
                .GTREFCLK1N_IN                  (GTREFCLK1N_IN),
                .GTREFCLK1P_IN                  (GTREFCLK1P_IN),

                //---------------- Receive Ports - FPGA RX interface Ports -----------------
                .RXDATA_OUT                     (rxdata_o),

                //---------------------- Receive Ports - RX AFE Ports ----------------------
                .GTXRXP_IN                      (GTXRXP_IN),
                .GTXRXN_IN                      (GTXRXN_IN),

                //------------- Receive Ports - RX Fabric Output Control Ports -------------
                .RXOUTCLK_OUT                   (rxusrclk_i),

                //-------------------------- Fix The Phase Signals -------------------------
                .GTXRXRESET_IN                  (gtrxreset),
                .RXCDRRESET_IN                  (rxcdrrst_i),
                .RXRESETDONE_OUT                (rxrstdone_o),
                .CPLLLOCK_OUT                   (cplllock_o),
                .RXCOMMADET_OUT                 (rxcommadet_o),
                .RXSLIDE_IN                     (rxslide_i),
                .RXBYTEISALIGNED_OUT            (rxbyteisaligned_o)
            );


    //------------------------ gtx_bitslide Instances -----------------------------
    assign rx_ready = rxrstdone_o & cplllock_o;

    gtx_bitslide gtx_bitslide_inst
                 (
                     .gtp_rst_i                 (gtrxreset),
                     .gtp_rx_clk_i              (rxusrclk_o),
                     .gtp_rx_comma_det_i        (rxcommadet_o),
                     .gtp_rx_byte_is_aligned_i  (rxbyteisaligned_o),
                     .serdes_ready_i            (rx_ready),
                     .gtp_rx_slide_o            (rxslide_i),
                     .gtp_rx_cdr_rst_o          (rxcdrrst_i),
                     .bitslide_o                (bit_slide_no),
                     .synced_o                  (bit_slide_rdy)
                 );

    //---------------------------- gen_rx_outputs ---------------------------------
    // assign rx_enc_err_o = rx_disp_err[0] || rx_disp_err[1] || rx_code_err[0] || rx_code_err[1];

    //fix the phase of recclk
    always @(posedge rxusrclk_o)
        if (bit_slide_rdy == 1'b0)
        begin
            rst_auto    <= 1'b0;
        end
        else if (bitslide_count == 10'b1111111111)
            bitslide_count <= 10'b0000000000;
        else
            if (bit_slide_no != 5'b00010)
            begin
                rst_auto       <= 1'b1;
                bitslide_count <= bitslide_count + 1;
            end
            else
            begin
                rst_auto       <= 1'b0;
                bitslide_count <= bitslide_count;
            end

    assign gtrxreset = rst_auto;

    // assign rst_time_No = bitslide_count;
    // assign rx_ready_o = rx_rst_done & rxpll_lockdet & bit_slide_rdy & !(rst_auto);

endmodule
