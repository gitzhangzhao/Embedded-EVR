/**
 * File              : pulse_set.v
 * Author            : zhangzhao <zhangzhao@ihep.ac.cn>
 * Date              : 03.11.2022
 * Last Modified Date: 03.11.2022
 * Last Modified By  : zhangzhao <zhangzhao@ihep.ac.cn>
 * Description       : pulse output setting instances
 */

`timescale 1ns / 1ps
`default_nettype wire

module pulse_set (
        input          clk,

        input   [13:0] start,

        input   [31:0] PulseSelect_reg,  //reg13,0x34
        input   [31:0] PulseWidth_reg,   //reg15,0x3c
        input   [31:0] PulseDelay_reg,   //reg48,0xc0
        input   [31:0] PulsePolarity_reg,//reg47,0xbc,bit11-bit24
        input   [31:0] OutputPulseEnables_reg,//reg03,0x0c,bit0-bit13
        output         pulse0,
        output         pulse1,
        output         pulse2,
        output         pulse3,
        output         pulse4,
        output         pulse5,
        output         pulse6,
        output         pulse7,
        output         pulse8,
        output         pulse9,
        output         pulse10,
        output         pulse11,
        output         pulse12,
        output         pulse13

    );

    reg  [31:0] pulsedelay0;
    reg  [31:0] pulsewide0;

    reg  [31:0] pulsedelay1;
    reg  [31:0] pulsewide1;

    reg  [31:0] pulsedelay2;
    reg  [31:0] pulsewide2;

    reg  [31:0] pulsedelay3;
    reg  [31:0] pulsewide3;

    reg  [31:0] pulsedelay4;
    reg  [31:0] pulsewide4;

    reg  [31:0] pulsedelay5;
    reg  [31:0] pulsewide5;

    reg  [31:0] pulsedelay6;
    reg  [31:0] pulsewide6;

    reg  [31:0] pulsedelay7;
    reg  [31:0] pulsewide7;

    reg  [31:0] pulsedelay8;
    reg  [31:0] pulsewide8;

    reg  [31:0] pulsedelay9;
    reg  [31:0] pulsewide9;

    reg  [31:0] pulsedelay10;
    reg  [31:0] pulsewide10;

    reg  [31:0] pulsedelay11;
    reg  [31:0] pulsewide11;

    reg  [31:0] pulsedelay12;
    reg  [31:0] pulsewide12;

    reg  [31:0] pulsedelay13;
    reg  [31:0] pulsewide13;


    always @ (posedge clk)
    begin
        case(PulseSelect_reg[4:0])
            5'b10000:
            begin
                pulsedelay0 <= PulseDelay_reg;
                pulsewide0  <= PulseWidth_reg;
            end
            5'b10001:
            begin
                pulsedelay1 <= PulseDelay_reg;
                pulsewide1  <= PulseWidth_reg;
            end
            5'b10010:
            begin
                pulsedelay2 <= PulseDelay_reg;
                pulsewide2  <= PulseWidth_reg;
            end
            5'b10011:
            begin
                pulsedelay3 <= PulseDelay_reg;
                pulsewide3  <= PulseWidth_reg;
            end
            5'b10100:
            begin
                pulsedelay4 <= PulseDelay_reg;
                pulsewide4  <= PulseWidth_reg;
            end
            5'b10101:
            begin
                pulsedelay5 <= PulseDelay_reg;
                pulsewide5  <= PulseWidth_reg;
            end
            5'b10110:
            begin
                pulsedelay6 <= PulseDelay_reg;
                pulsewide6  <= PulseWidth_reg;
            end
            5'b10111:
            begin
                pulsedelay7 <= PulseDelay_reg;
                pulsewide7  <= PulseWidth_reg;
            end
            5'b11000:
            begin
                pulsedelay8 <= PulseDelay_reg;
                pulsewide8  <= PulseWidth_reg;
            end
            5'b11001:
            begin
                pulsedelay9 <= PulseDelay_reg;
                pulsewide9  <= PulseWidth_reg;
            end
            5'b11010:
            begin
                pulsedelay10 <= PulseDelay_reg;
                pulsewide10  <= PulseWidth_reg;
            end
            5'b11011:
            begin
                pulsedelay11 <= PulseDelay_reg;
                pulsewide11  <= PulseWidth_reg;
            end
            5'b11100:
            begin
                pulsedelay12 <= PulseDelay_reg;
                pulsewide12  <= PulseWidth_reg;
            end
            5'b11101:
            begin
                pulsedelay13 <= PulseDelay_reg;
                pulsewide13  <= PulseWidth_reg;
            end

            default:;
        endcase
    end


    programable_pulse pulse_out0 (
                          .clk          (clk),
                          .reset        (OutputPulseEnables_reg[0]),
                          .polarity     (PulsePolarity_reg[0]),
                          .start        (start[0]),
                          .pulsedelay   (pulsedelay0),
                          .pulsewide    (pulsewide0),
                          .pulse        (pulse0)
                      );

    programable_pulse pulse_out1 (
                          .clk          (clk),
                          .reset        (OutputPulseEnables_reg[1]),
                          .polarity     (PulsePolarity_reg[1]),
                          .start        (start[1]),
                          .pulsedelay   (pulsedelay1),
                          .pulsewide    (pulsewide1),
                          .pulse        (pulse1)
                      );

    programable_pulse pulse_out2 (
                          .clk          (clk),
                          .reset        (OutputPulseEnables_reg[2]),
                          .polarity     (PulsePolarity_reg[2]),
                          .start        (start[2]),
                          .pulsedelay   (pulsedelay2),
                          .pulsewide    (pulsewide2),
                          .pulse        (pulse2)
                      );

    programable_pulse pulse_out3 (
                          .clk          (clk),
                          .reset        (OutputPulseEnables_reg[3]),
                          .polarity     (PulsePolarity_reg[3]),
                          .start        (start[3]),
                          .pulsedelay   (pulsedelay3),
                          .pulsewide    (pulsewide3),
                          .pulse        (pulse3)
                      );

    programable_pulse pulse_out4 (
                          .clk          (clk),
                          .reset        (OutputPulseEnables_reg[4]),
                          .polarity     (PulsePolarity_reg[4]),
                          .start        (start[4]),
                          .pulsedelay   (pulsedelay4),
                          .pulsewide    (pulsewide4),
                          .pulse        (pulse4)
                      );

    programable_pulse pulse_out5 (
                          .clk          (clk),
                          .reset        (OutputPulseEnables_reg[5]),
                          .polarity     (PulsePolarity_reg[5]),
                          .start        (start[5]),
                          .pulsedelay   (pulsedelay5),
                          .pulsewide    (pulsewide5),
                          .pulse        (pulse5)
                      );

    programable_pulse pulse_out6 (
                          .clk          (clk),
                          .reset        (OutputPulseEnables_reg[6]),
                          .polarity     (PulsePolarity_reg[6]),
                          .start        (start[6]),
                          .pulsedelay   (pulsedelay6),
                          .pulsewide    (pulsewide6),
                          .pulse        (pulse6)
                      );

    programable_pulse pulse_out7 (
                          .clk          (clk),
                          .reset        (OutputPulseEnables_reg[7]),
                          .polarity     (PulsePolarity_reg[7]),
                          .start        (start[7]),
                          .pulsedelay   (pulsedelay7),
                          .pulsewide    (pulsewide7),
                          .pulse        (pulse7)
                      );

    programable_pulse pulse_out8 (
                          .clk          (clk),
                          .reset        (OutputPulseEnables_reg[8]),
                          .polarity     (PulsePolarity_reg[8]),
                          .start        (start[8]),
                          .pulsedelay   (pulsedelay8),
                          .pulsewide    (pulsewide8),
                          .pulse        (pulse8)
                      );

    programable_pulse pulse_out9 (
                          .clk          (clk),
                          .reset        (OutputPulseEnables_reg[9]),
                          .polarity     (PulsePolarity_reg[9]),
                          .start        (start[9]),
                          .pulsedelay   (pulsedelay9),
                          .pulsewide    (pulsewide9),
                          .pulse        (pulse9)
                      );

    programable_pulse pulse_out10 (
                          .clk          (clk),
                          .reset        (OutputPulseEnables_reg[10]),
                          .polarity     (PulsePolarity_reg[10]),
                          .start        (start[10]),
                          .pulsedelay   (pulsedelay10),
                          .pulsewide    (pulsewide10),
                          .pulse        (pulse10)
                      );

    programable_pulse pulse_out11 (
                          .clk          (clk),
                          .reset        (OutputPulseEnables_reg[11]),
                          .polarity     (PulsePolarity_reg[11]),
                          .start        (start[11]),
                          .pulsedelay   (pulsedelay11),
                          .pulsewide    (pulsewide11),
                          .pulse        (pulse11)
                      );

    programable_pulse pulse_out12 (
                          .clk          (clk),
                          .reset        (OutputPulseEnables_reg[12]),
                          .polarity     (PulsePolarity_reg[12]),
                          .start        (start[12]),
                          .pulsedelay   (pulsedelay12),
                          .pulsewide    (pulsewide12),
                          .pulse        (pulse12)
                      );

    programable_pulse pulse_out13 (
                          .clk          (clk),
                          .reset        (OutputPulseEnables_reg[13]),
                          .polarity     (PulsePolarity_reg[13]),
                          .start        (start[13]),
                          .pulsedelay   (pulsedelay13),
                          .pulsewide    (pulsewide13),
                          .pulse        (pulse13)
                      );


endmodule
