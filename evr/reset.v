/**
 * File              : reset.v
 * Author            : zhangzhao <zhangzhao@ihep.ac.cn>
 * Date              : 31.05.2022
 * Last Modified Date: 06.06.2022
 * Last Modified By  : zhangzhao <zhangzhao@ihep.ac.cn>
 * Description       : generate a global reset signal for all modules
 */

`timescale 1ns / 1ps
`default_nettype wire

//***************************** Entity Declaration ****************************
module reset
    (
        //---------------------  Clocking signal  ---------------------------
        input                                   CLK_IN,

        //--------------------  Bus reset signal  ---------------------------
        input                                   RST_IN,

        //--------------------  Fifo reset signal  --------------------------
        output                                  FIFO_RST_OUT

    );

    //***************************** Wire Declarations *****************************
    // ground and vcc signals
    wire            tied_to_ground_i;
    wire    [63:0]  tied_to_ground_vec_i;
    wire            tied_to_vcc_i;
    wire    [63:0]  tied_to_vcc_vec_i;

    //*************************** Register Declarations ***************************
    reg             rst_tmp;
    reg     [35:0]  rst_pipe = 36'h000000000;

    //***************************** Main Body of Code *****************************
    // static sigals
    assign tied_to_ground_i     = 1'b0;
    assign tied_to_ground_vec_i = 64'h0000000000000000;
    assign tied_to_vcc_i        = 1'b1;
    assign tied_to_vcc_vec_i    = 64'hffffffffffffffff;

    // output reset fifo signal
    assign FIFO_RST_OUT         = rst_pipe[35];

    //---------------------------  Fifo reset Instances  --------------------------------
    // Implement reset_pipe generation
    always @( posedge CLK_IN )
    begin
        rst_tmp <= ~RST_IN;
        if (RST_IN & rst_tmp)
            rst_pipe <= 36'h0000000ff;
        else
            rst_pipe <= {rst_pipe[34:0], 1'b0};
    end

endmodule
