/**
 * File              : event_fifo.v
 * Author            : zhangzhao <zhangzhao@ihep.ac.cn>
 * Date              : 31.05.2022
 * Last Modified Date: 31.05.2022
 * Last Modified By  : zhangzhao <zhangzhao@ihep.ac.cn>
 * Description       : EVR Event FIFO and Timingstamping instances
 */

`timescale 1ns / 1ps
`default_nettype wire

//***************************** Entity Declaration ****************************
module event_fifo #
    (
        // Parameters of Axi Slave Bus Interface S00_AXI
        parameter integer C_S00_AXI_ADDR_WIDTH  = 8
    )
    (
        //--------------------  Clocking signals  ---------------------------
        input                                  WRCLK_IN,
        input                                  RDCLK_IN,

        //-----------------------  Bus signals  -----------------------------
        input                                  AXI_ARVALID_IN,
        input    [C_S00_AXI_ADDR_WIDTH-1 : 0]  AXI_ARADDR_IN,

        //------------------  Fifo write event code  ------------------------
        input    [7:0]                         EVENT_CODE_IN,

        //------------------  Fifo read event code  -------------------------
        output   [7:0]                         EVENT_CODE_OUT,

        //----------------  Fifo read second register  ----------------------
        output   [31:0]                        SECONDS_COUNTER_OUT,

        //-----------------  Fifo read event counter  -----------------------
        output   [31:0]                        EVENT_COUNTER_OUT,

        //------------------  Event code interrupt  -------------------------
        output                                 INTERRUPT_OUT,

        //----------------------  Reset signal  -----------------------------
        input                                  RST_IN,

        //----------------------  Empty signal  -----------------------------
        output                                 EMPTY_OUT,

        //----------------------  Full signal  ------------------------------
        output                                 FULL_OUT,
        
        //---------------------  Timestamp Latch  ---------------------------
        input                                  LATCH_IN,
        output    [31:0]                       SECONDS_LATCH_OUT,
        output    [31:0]                       TIMESTAMP_LATCH_OUT
        
    );

    //***************************** Wire Declarations *****************************
    // ground and vcc signals
    wire            tied_to_ground_i;
    wire    [63:0]  tied_to_ground_vec_i;
    wire            tied_to_vcc_i;
    wire    [63:0]  tied_to_vcc_vec_i;
    // fifo read enable signal
    wire            rden_i;
    // fifo write enable signal
    wire            wren_i;
    // fifo input/output
    wire    [63:0]  fifo_di;
    wire    [7:0]   fifo_dip;
    wire    [63:0]  fifo_do;
    wire    [7:0]   fifo_dop;
    // almost empty/full
    wire            almost_empty;
    wire            almost_full;

    //*************************** Register Declarations ***************************
    // opposite arvalid
    reg            axi_arvalid_tmp;
    // rden_i delay register
    reg    [11:0]  rden_tmp      = 12'h000;
    // wren_i register
    reg            wren_tmp      = 1'b0;
    // interrupt register
    reg            interrupt;
    // event code delay 1 cycle
    reg    [7:0]   event_code_delay = 8'b00;

    // Timingstamping system
    // 32-bit Timestamp Event Counter
    reg    [31:0]  event_counter = 32'h0;
    // 32-bit Seconds Shift Register
    reg    [31:0]  seconds_shift = 32'h0;
    // 32-bit Seconds Register
    reg    [31:0]  seconds_counter = 32'h0;
    // 32-bit Seconds Latch Register
    reg    [31:0]  seconds_latch = 32'h0;
    // 32-bit Timestamp Latch Register
    reg    [31:0]  timestamp_latch = 32'h0;
    reg            latch_tmp      = 1'b0;

    //***************************** Main Body of Code *****************************
    // -------------------------  Static signal Assigments ---------------------
    assign tied_to_ground_i     = 1'b0;
    assign tied_to_ground_vec_i = 64'h0000000000000000;
    assign tied_to_vcc_i        = 1'b1;
    assign tied_to_vcc_vec_i    = 64'hffffffffffffffff;
    // input fifo RDEN
    assign rden_i               = rden_tmp[11];
    // input fifo WREN
    assign wren_i               = wren_tmp;
    // input fifo DIN
    assign fifo_di              = {seconds_counter[23:0], event_counter, event_code_delay};
//    assign fifo_di              = {56'b0,event_code_delay};
    assign fifo_dip             = seconds_counter[31:24];
    // output event code
    assign EVENT_CODE_OUT       = fifo_do[7:0];
    // output seconds counter
    assign SECONDS_COUNTER_OUT  = fifo_do[39:8];
    // output timingstamping event counter
    assign EVENT_COUNTER_OUT    = {fifo_dop[7:0], fifo_do[63:40]};
    assign INTERRUPT_OUT        = interrupt;
    // output seconds and timestamp latch register
    assign SECONDS_LATCH_OUT    = seconds_latch[31:0];
    assign TIMESTAMP_LATCH_OUT  = timestamp_latch[31:0];
    
    // ----------------------  FIFO READ and WRITE Instances ----------------------
    // Implement rden_i generation
    // When AXI_ARVALID_IN is asserted, determine whether AXI_ARADDR_IN is matched.
    // If AXI_ARADDR_IN is matched, assert rden_i after 36 cycles.
    always @( posedge RDCLK_IN )
    begin
        axi_arvalid_tmp <= ~AXI_ARVALID_IN;
        if ( AXI_ARVALID_IN & axi_arvalid_tmp )
        begin
            if( AXI_ARADDR_IN[7:2] == 6'h04 )
                rden_tmp <= {rden_tmp[10:0],1'b1};
            else
                rden_tmp <= {rden_tmp[10:0],1'b0};
        end
        else
            rden_tmp <= {rden_tmp[10:0],1'b0};
    end

    // Implement event code delay
    // wr_en asserting takes 1 cycle, so the event code is delayed by 1 cycle.
    always @( posedge WRCLK_IN )
    begin
        event_code_delay <= EVENT_CODE_IN;
    end

    // Implement wren_i and interrupt generation
    // wren_i assert when event code comes, except 0x00 and 0xBC.
    always @( posedge WRCLK_IN )
    begin
        if( EVENT_CODE_IN == 8'h00 )
        begin
            wren_tmp <= 1'b0;
            interrupt <= 1'b0;
        end
        else if( EVENT_CODE_IN == 8'hbc )
        begin
            wren_tmp <= 1'b0;
            interrupt <= 1'b0;
        end
        else
        begin
            wren_tmp <= 1'b1;
            interrupt <= 1'b1;
        end
    end

    // ----------------------  Timestamping System Instances ----------------------
    // Implement timestamp event counter
    // counter clock is event clock.
    // reset event_counter and seconds_counter when get 0x7d.
    always @( posedge WRCLK_IN )
    begin
        if( event_code_delay == 8'h7d )
        begin
            event_counter <= 32'h0;
            seconds_counter <= seconds_shift;
        end           
        else
            event_counter <= event_counter + 1'b1;
    end
    
    // Implement seconds shift register
    // shift 32 bit to generate seconds.
    always @( posedge WRCLK_IN )
    begin
        if( EVENT_CODE_IN == 8'h70 )
            seconds_shift <= {seconds_shift[30:0], 1'b0};
        else if( EVENT_CODE_IN == 8'h71 )
            seconds_shift <= {seconds_shift[30:0], 1'b1};
    end
    
    // Implement seconds and nanoseconds latch register
    // latch seconds and nanoseconds when get latch signal
    always @( posedge RDCLK_IN )
        begin
            latch_tmp <= ~LATCH_IN;
            if (LATCH_IN & latch_tmp)
            begin
                 seconds_latch <= seconds_counter;
                 timestamp_latch <= event_counter;
            end    
        end
    
    // // Implement simulate event code generation for every 1s
    // // sim:generate 1s delay
    // reg     [29:0]  delay_1s             = 30'h5f5e100;
    // // sim:simulate event code
    // reg     [7:0]   event_code_tmp       = 8'h00;
    // reg     [7:0]   event_code_tmp_delay = 8'h00;
    // always @( posedge WRCLK_IN )
    // begin
    //     if( delay_1s == 0 )
    //     begin
    //         wren_tmp <= 1'b1;
    //         delay_1s <= 30'h5f5e100;
    //         event_code_tmp_delay <= event_code_tmp + 1;
    //     end
    //     else
    //     begin
    //         wren_tmp <= 1'b0;
    //         event_code_tmp <= event_code_tmp_delay;
    //         delay_1s <= delay_1s - 1;
    //     end
    // end

    // assign fifo_di              = {56'b0, event_code_tmp};
    // assign wren_i               = wren_tmp;

    // // Implement simulate event code generation for every 20ms
    // reg     [23:0]  delay_20ms = 24'b0;
    // reg             wren_tmp_1;
    // reg     [7:0]   event_code_tmp_1 = 8'b0;

    // always @( posedge WRCLK_IN )
    // begin
    //     if(delay_20ms < 10)
    //     begin
    //         wren_tmp_1 <= 1'b1;
    //         delay_20ms <= delay_20ms + 1'b1;
    //         interrupt <= 1'b1;
    //     end
    //     else if( delay_20ms == 24'h186A0 )
    //     begin
    //         wren_tmp_1 <= 1'b0;
    //         delay_20ms <= 1'b0;
    //         interrupt <= 1'b0;
    //         event_code_tmp_1 <= event_code_tmp_1 + 1'b1;
    //     end
    //     else
    //     begin
    //         delay_20ms <= delay_20ms + 1'b1;
    //         wren_tmp_1 <= 1'b0;
    //         interrupt <= 1'b0;
    //     end
    // end

    // assign wren_i  = wren_tmp_1;
    // assign fifo_di = {56'b0, event_code_tmp_1};
    // assign INTERRUPT_OUT = interrupt;
    // assign COUNT = delay_20ms[23:0];

    //---------------------------  Fifo Instances  --------------------------------
    // FIFO36E1: 36Kb FIFO (First-In-First-Out) Block RAM Memory
    FIFO36E1 #(
                 .ALMOST_EMPTY_OFFSET(13'h0080),    // Sets the almost empty threshold
                 .ALMOST_FULL_OFFSET(13'h0080),     // Sets almost full threshold
                 .DATA_WIDTH(72),                   // Sets data width to 4-72
                 .DO_REG(1),                        // Enable output register (1-0) Must be 1 if EN_SYN = FALSE
                 .EN_ECC_READ("FALSE"),             // Enable ECC decoder, FALSE, TRUE
                 .EN_ECC_WRITE("FALSE"),            // Enable ECC encoder, FALSE, TRUE
                 .EN_SYN("FALSE"),                  // Specifies FIFO as Asynchronous (FALSE) or Synchronous (TRUE)
                 .FIFO_MODE("FIFO36_72"),              // Sets mode to "FIFO36" or "FIFO36_72"
                 .FIRST_WORD_FALL_THROUGH("TRUE"),  // Sets the FIFO FWFT to FALSE, TRUE
                 .INIT(72'h000000000000000000),     // Initial values on output port
                 .SIM_DEVICE("7SERIES"),            // Must be set to "7SERIES" for simulation behavior
                 .SRVAL(72'h000000000000000000)     // Set/Reset value for output port
             )
             fifo36e1_i
             (
                 // ECC Signals: 1-bit (each) output: Error Correction Circuitry ports
                 .DBITERR(),                        // 1-bit output: Double bit error status
                 .ECCPARITY(),                      // 8-bit output: Generated error correction parity
                 .SBITERR(),                        // 1-bit output: Single bit error status
                 // Read Data: 64-bit (each) output: Read output data
                 .DO(fifo_do),                      // 64-bit output: Data output
                 .DOP(fifo_dop),                    // 8-bit output: Parity data output
//                 .DOP(),
                 // Status: 1-bit (each) output: Flags and other FIFO status outputs
                 .ALMOSTEMPTY(almost_empty),        // 1-bit output: Almost empty flag
                 .ALMOSTFULL(almost_full),          // 1-bit output: Almost full flag
                 .EMPTY(EMPTY_OUT),                 // 1-bit output: Empty flag
                 .FULL(FULL_OUT),                   // 1-bit output: Full flag
                 .RDCOUNT(),                        // 13-bit output: Read count
                 .RDERR(),                          // 1-bit output: Read error
                 .WRCOUNT(),                        // 13-bit output: Write count
                 .WRERR(),                          // 1-bit output: Write error
                 // ECC Signals: 1-bit (each) input: Error Correction Circuitry ports
                 .INJECTDBITERR(tied_to_ground_i),  // 1-bit input: Inject a double bit error input
                 .INJECTSBITERR(tied_to_ground_i),
                 // Read Control Signals: 1-bit (each) input: Read clock, enable and reset input signals
                 .RDCLK(RDCLK_IN),                  // 1-bit input: Read clock
                 .RDEN(rden_i),                     // 1-bit input: Read enable
                 .REGCE(tied_to_vcc_i),             // 1-bit input: Clock enable
                 .RST(RST_IN),                      // 1-bit input: Reset
                 .RSTREG(tied_to_ground_i),         // 1-bit input: Output register set/reset
                 // Write Control Signals: 1-bit (each) input: Write clock and enable input signals
                 .WRCLK(WRCLK_IN),                  // 1-bit input: Rising edge write clock.
                 .WREN(wren_i),                     // 1-bit input: Write enable
                 // Write Data: 64-bit (each) input: Write input data
                 .DI(fifo_di),                      // 64-bit input: Data input
                 .DIP(fifo_dip)                     // 8-bit input: Parity input
//                 .DIP(tied_to_ground_vec_i[7:0])
             );
    // End of FIFO36E1_inst instantiation

endmodule
