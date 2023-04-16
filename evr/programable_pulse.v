/**
 * File              : programable_pulse.v
 * Author            : zhangzhao <zhangzhao@ihep.ac.cn>
 * Date              : 02.11.2022
 * Last Modified Date: 02.11.2022
 * Last Modified By  : zhangzhao <zhangzhao@ihep.ac.cn>
 * Description       : output programable pulse instances
 */

`timescale 1ns / 1ps
`default_nettype wire

//***************************** Entity Declaration ****************************
module programable_pulse (
        input clk,
        input reset,
        input polarity,
        input start,
        input [31:0] pulsedelay,
        input [31:0] pulsewide,
        output pulse
    );

    //*************************** Register Declarations ***************************
    reg pulse, w_pulse;
    reg pulsedelay_count_en;
    reg pulsewide_start;
    reg pulsewide_count_en;
    reg [31:0] pulsedelay_count;
    reg [31:0] pulsewide_count;

    //***************************** Main Body of Code *****************************
    always @ ( posedge clk )
    begin
        if ( reset == 'b1 )
            pulsedelay_count_en <= 'b0;
        else
        begin
            if ( start == 'b1 )
                pulsedelay_count_en <= 'b1;
            else if ( start == 'b0 && pulsedelay_count > pulsedelay )
                pulsedelay_count_en <= 'b0;
        end
    end

    always @ ( posedge clk )
    begin
        if ( reset == 'b1 )
            pulsedelay_count <= 'h00000000;
        else
        begin
            if ( pulsedelay_count_en == 'b0 )
                pulsedelay_count <= 'h00000000;
            else if ( pulsedelay_count_en == 'b1 && pulsedelay_count <= pulsedelay )
                pulsedelay_count <= pulsedelay_count + 1;
            else if ( pulsedelay_count_en == 'b0 && start == 'b0 )
                pulsedelay_count <= 'h00000000;
        end
    end

    always @ ( posedge clk )
    begin
        if ( reset == 'b1 )
            pulsewide_start <= 'b0;
        else if ( pulsedelay_count == pulsedelay )
            pulsewide_start <= 'b1;
        else
            pulsewide_start <= 'b0;
    end



    always @ ( posedge clk )
    begin
        if ( reset == 'b1 )
            pulsewide_count_en <= 'b0;
        else
        begin
            if ( pulsewide_start == 'b1 )
                pulsewide_count_en <= 'b1;
            else if ( pulsewide_start == 'b0 && pulsewide_count > pulsewide )
                pulsewide_count_en <= 'b0;
        end
    end

    always @ ( posedge clk )
    begin
        if ( reset == 'b1 )
            pulsewide_count <= 'h00000000;
        else
        begin
            if ( pulsewide_count_en == 'b0 )
                pulsewide_count <= 'h00000000;
            else if ( pulsewide_count_en == 'b1 && pulsewide_count <= pulsewide )
                pulsewide_count <= pulsewide_count + 1;
            else if ( pulsewide_count_en == 'b0 && pulsewide_start == 'b0 )
                pulsewide_count <= 'h00000000;
        end
    end

    always @ ( posedge clk )
    begin
        if ( reset == 'b1 || pulsewide_count >= pulsewide )
            w_pulse <= 'b0;
        else if ( pulsewide_count_en == 'b1 )
            w_pulse <= 'b1;
    end

    always @ *
    begin
        if (polarity == 1'b1)
            pulse = !w_pulse;
        else
            pulse = w_pulse;
    end


endmodule
