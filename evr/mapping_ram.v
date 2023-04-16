/**
 * File              : mapping_ram.v
 * Author            : zhangzhao <zhangzhao@ihep.ac.cn>
 * Date              : 31.05.2022
 * Last Modified Date: 07.10.2022
 * Last Modified By  : zhangzhao <zhangzhao@ihep.ac.cn>
 * Description       : EVR mappingRAM instances
 */

`timescale 1ns / 1ps
`default_nettype wire

//***************************** Entity Declaration ****************************
module mapping_ram #
    (
        // Parameters of Axi Slave Bus Interface S00_AXI
        parameter integer C_S00_AXI_ADDR_WIDTH = 8
    )
    (
        //---------------------  Clocking signal  ---------------------------
        input                                     WR_CLK_IN,       /* write clock.               */
        input                                     RD_CLK_IN,       /* read clock.                */
        //---------------------  Control signals  ---------------------------
        input                                     RAM_EN_IN,       /* enable RAM.                */
        input                                     RAM_RDSEL_IN,    /* select which RAM to read.  */
        input                                     RAM_WRSEL_IN,    /* select which RAM to write. */
        input                                     RAM_CLR_IN,      /* clear RAM.                 */
        //----------------------  Data signals  -----------------------------
        input       [7:0]                         WR_ADDR_IN,      /* write address.             */
        input       [15:0]                        WR_DATA_IN,      /* write data.                */
        input       [7:0]                         RD_ADDR_IN,      /* read address.              */
        output reg  [15:0]                        RD_DATA_OUT,     /* read data.                 */
        //-----------------------  Bus signals  -----------------------------
        input                                     AXI_AWVALID_IN,  /* AXI write operation.       */
        input     [C_S00_AXI_ADDR_WIDTH-1 : 0]    AXI_AWADDR_IN    /* AXI write address.         */
    );

    //***************************** Wire Declarations *****************************
    // ground and vcc signals
    wire            tied_to_ground_i;
    wire    [63:0]  tied_to_ground_vec_i;
    wire            tied_to_vcc_i;
    wire    [63:0]  tied_to_vcc_vec_i;
    // BRAM data outputs
    wire    [15:0]  ram0_data_o;
    wire    [15:0]  ram1_data_o;

    //*************************** Register Declarations ***************************
    // BRAM enable registers
    reg            ram0_wr_en;
    reg            ram1_wr_en;
    reg            ram0_rd_en;
    reg            ram1_rd_en;
    // BRAM write registers
    reg            wr_en;
    reg    [7:0]   wr_addr;
    reg    [15:0]  wr_data;
    // clear state machine registers
    reg            clr_tmp   = 1'b0;
    reg    [1:0]   clr_state = 2'b0;
    reg    [7:0]   clr_addr  = 8'h0;
    reg            clr_en    = 1'b0;
    reg            clr_flg   = 1'b0;
    // AXI tmp registers
    reg            awvalid_tmp;
    reg    [9:0]   wren_tmp  = 10'b0;

    //************************* Parameter Declarations ****************************
    // state machine
    localparam [1:0]
               IDLE     = 2'b00,
               PAUSE    = 2'b01,
               WRITE    = 2'b10,
               INCREASE = 2'b11;

    //***************************** Main Body of Code *****************************
    // ----------------------  Static signal Assigments  -----------------------
    assign tied_to_ground_i     = 1'b0;
    assign tied_to_ground_vec_i = 64'h0000000000000000;
    assign tied_to_vcc_i        = 1'b1;
    assign tied_to_vcc_vec_i    = 64'hffffffffffffffff;

    // -------------------  mappingRAM CLEAR FSM Instances  --------------------
    always @( posedge WR_CLK_IN )
    begin
        case(clr_state)
            IDLE:  /* detect the clear signal */
            begin
                clr_tmp <= ~RAM_CLR_IN;
                if(RAM_CLR_IN & clr_tmp)
                begin
                    clr_state <= PAUSE;
                    clr_addr <= 8'h00;
                    clr_en <= 1'b0;
                    clr_flg <= 1'b1;
                end
                else
                begin
                    clr_state <= IDLE;
                    clr_addr <= 8'h00;
                    clr_en <= 1'b0;
                    clr_flg <= 1'b0;
                end
            end
            PAUSE:  /* delay for switching ports */
            begin
                clr_tmp <= ~RAM_CLR_IN;
                clr_state <= WRITE;
                clr_addr <= 8'h00;
                clr_en <= 1'b0;
                clr_flg <= 1'b1;
            end
            WRITE:  /* clear RAM */
            begin
                clr_tmp <= ~RAM_CLR_IN;
                clr_state <= INCREASE;
                clr_addr <= clr_addr;
                clr_en <= 1'b1;
                clr_flg <= 1'b1;
            end
            INCREASE:  /* increase the address */
            begin
                clr_tmp <= ~RAM_CLR_IN;
                if( clr_addr == 8'hFF )
                begin
                    clr_state <= IDLE;
                    clr_addr <= clr_addr;
                    clr_en <= 1'b0;
                    clr_flg <= 1'b0;
                end
                else
                begin
                    clr_state <= WRITE;
                    clr_addr <= clr_addr + 1;
                    clr_en <= 1'b0;
                    clr_flg <= 1'b1;
                end
            end
        endcase
    end

    // -------------------  mappingRAM Write Enable Instances  --------------------
    // Implement wren generation
    // When AXI_AWVALID_IN is asserted, determine whether AXI_AWADDR_IN is matched.
    // If AXI_AWADDR_IN is matched, assert wea port after 10 cycles
    always @( posedge WR_CLK_IN )
    begin
        awvalid_tmp <= ~AXI_AWVALID_IN;
        if( AXI_AWVALID_IN & awvalid_tmp )
        begin
            if( AXI_AWADDR_IN[7:2] == 6'h02 )
                wren_tmp <= {wren_tmp[8:0],1'b1};
            else
                wren_tmp <= {wren_tmp[8:0],1'b0};
        end
        else
            wren_tmp <= {wren_tmp[8:0],1'b0};
    end

    // ------------------------  Switch the Ports of BRAM  ------------------------
    always @ *
    begin
        if ( clr_flg == 1'b1 )  /* to clear */
        begin
            wr_en = clr_en;
            wr_addr = clr_addr;
            wr_data = 16'h0000;
        end
        else                    /* to write */
        begin
            wr_en   = wren_tmp[9];
            wr_addr = WR_ADDR_IN;
            wr_data = WR_DATA_IN;
        end
    end

    // -----------------------  Select which BRAM to write  -----------------------
    always @ *
    begin
        if( RAM_EN_IN == 1'b0)
        begin
            ram0_wr_en = 1'b0;
            ram1_wr_en = 1'b0;
        end
        else
            if( RAM_WRSEL_IN == 1'b0 )  /* select BRAM 0 to write */
            begin
                ram0_wr_en = 1'b1;
                ram1_wr_en = 1'b0;
            end
            else                        /* select BRAM 1 to write */
            begin
                ram0_wr_en = 1'b0;
                ram1_wr_en = 1'b1;
            end
    end

    // -----------------------  Select which BRAM to read  ------------------------
    always @ *
    begin
        if( RAM_EN_IN == 1'b0)
        begin
            ram0_rd_en = 1'b0;
            ram1_rd_en = 1'b0;
            RD_DATA_OUT = 16'b0;
        end
        else
            if( RAM_RDSEL_IN == 1'b0 )  /* select BRAM 0 to read */
            begin
                ram0_rd_en = 1'b1;
                ram1_rd_en = 1'b0;
                RD_DATA_OUT = ram0_data_o;
            end
            else                        /* select BRAM 1 to read */
            begin
                ram0_rd_en = 1'b0;
                ram1_rd_en = 1'b1;
                RD_DATA_OUT = ram1_data_o;
            end
    end

    //---------------------------  BRAM Instances  --------------------------------
    // Only RAM0 or RAM1 is enabled at the same time
    blk_mem_gen_0 mappingRAM0 (
                      .clka   (WR_CLK_IN),
                      .ena    (ram0_wr_en),
                      .wea    (wr_en),
                      .addra  (wr_addr),
                      .dina   (wr_data),
                      .clkb   (RD_CLK_IN),
                      .enb    (ram0_rd_en),
                      .addrb  (RD_ADDR_IN),
                      .doutb  (ram0_data_o)
                  );

    blk_mem_gen_0 mappingRAM1 (
                      .clka   (WR_CLK_IN),
                      .ena    (ram1_wr_en),
                      .wea    (wr_en),
                      .addra  (wr_addr),
                      .dina   (wr_data),
                      .clkb   (RD_CLK_IN),
                      .enb    (ram1_rd_en),
                      .addrb  (RD_ADDR_IN),
                      .doutb  (ram1_data_o)
                  );

endmodule
