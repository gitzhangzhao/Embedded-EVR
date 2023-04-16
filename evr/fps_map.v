
module fps_map
    (
        input   wire [13: 0] pulses,
        input   wire [ 7: 0] Databus,
        output  reg  [ 5: 0] FrontOut,

        input   wire [ 5: 0] FPS1,//reg32
        input   wire [ 5: 0] FPS2,//reg33
        input   wire [ 5: 0] FPS3,//reg34
        input   wire [ 5: 0] FPS4,//reg35
        input   wire [ 5: 0] FPS5,//reg36
        input   wire [ 5: 0] FPS6 //reg37
    );

    always @ *
    begin
        case(FPS1)
            6'b001011: FrontOut[0] = pulses[0];
            6'b001100: FrontOut[0] = pulses[1];
            6'b001101: FrontOut[0] = pulses[2];
            6'b001110: FrontOut[0] = pulses[3];
            6'b001111: FrontOut[0] = pulses[4];
            6'b010000: FrontOut[0] = pulses[5];
            6'b010001: FrontOut[0] = pulses[6];
            6'b010010: FrontOut[0] = pulses[7];
            6'b010011: FrontOut[0] = pulses[8];
            6'b010100: FrontOut[0] = pulses[9];
            6'b010101: FrontOut[0] = pulses[10];
            6'b010110: FrontOut[0] = pulses[11];
            6'b010111: FrontOut[0] = pulses[12];
            6'b011000: FrontOut[0] = pulses[13];
            6'b100000: FrontOut[0] = Databus[0];
            6'b100001: FrontOut[0] = Databus[1];
            6'b100010: FrontOut[0] = Databus[2];
            6'b100011: FrontOut[0] = Databus[3];
            6'b100100: FrontOut[0] = Databus[4];
            6'b100101: FrontOut[0] = Databus[5];
            6'b100110: FrontOut[0] = Databus[6];
            6'b100111: FrontOut[0] = Databus[7];
            default:   FrontOut[0] = 1'b0;
        endcase
    end

    always @ *
    begin
        case(FPS2)
            6'b001011: FrontOut[1] = pulses[0];
            6'b001100: FrontOut[1] = pulses[1];
            6'b001101: FrontOut[1] = pulses[2];
            6'b001110: FrontOut[1] = pulses[3];
            6'b001111: FrontOut[1] = pulses[4];
            6'b010000: FrontOut[1] = pulses[5];
            6'b010001: FrontOut[1] = pulses[6];
            6'b010010: FrontOut[1] = pulses[7];
            6'b010011: FrontOut[1] = pulses[8];
            6'b010100: FrontOut[1] = pulses[9];
            6'b010101: FrontOut[1] = pulses[10];
            6'b010110: FrontOut[1] = pulses[11];
            6'b010111: FrontOut[1] = pulses[12];
            6'b011000: FrontOut[1] = pulses[13];
            6'b100000: FrontOut[1] = Databus[0];
            6'b100001: FrontOut[1] = Databus[1];
            6'b100010: FrontOut[1] = Databus[2];
            6'b100011: FrontOut[1] = Databus[3];
            6'b100100: FrontOut[1] = Databus[4];
            6'b100101: FrontOut[1] = Databus[5];
            6'b100110: FrontOut[1] = Databus[6];
            6'b100111: FrontOut[1] = Databus[7];
            default:   FrontOut[1] = 1'b0;
        endcase
    end


    always @ *
    begin
        case(FPS3)
            6'b001011: FrontOut[2] = pulses[0];
            6'b001100: FrontOut[2] = pulses[1];
            6'b001101: FrontOut[2] = pulses[2];
            6'b001110: FrontOut[2] = pulses[3];
            6'b001111: FrontOut[2] = pulses[4];
            6'b010000: FrontOut[2] = pulses[5];
            6'b010001: FrontOut[2] = pulses[6];
            6'b010010: FrontOut[2] = pulses[7];
            6'b010011: FrontOut[2] = pulses[8];
            6'b010100: FrontOut[2] = pulses[9];
            6'b010101: FrontOut[2] = pulses[10];
            6'b010110: FrontOut[2] = pulses[11];
            6'b010111: FrontOut[2] = pulses[12];
            6'b011000: FrontOut[2] = pulses[13];
            6'b100000: FrontOut[2] = Databus[0];
            6'b100001: FrontOut[2] = Databus[1];
            6'b100010: FrontOut[2] = Databus[2];
            6'b100011: FrontOut[2] = Databus[3];
            6'b100100: FrontOut[2] = Databus[4];
            6'b100101: FrontOut[2] = Databus[5];
            6'b100110: FrontOut[2] = Databus[6];
            6'b100111: FrontOut[2] = Databus[7];
            default:   FrontOut[2] = 1'b0;
        endcase
    end


    always @ *
    begin
        case(FPS4)
            6'b001011: FrontOut[3] = pulses[0];
            6'b001100: FrontOut[3] = pulses[1];
            6'b001101: FrontOut[3] = pulses[2];
            6'b001110: FrontOut[3] = pulses[3];
            6'b001111: FrontOut[3] = pulses[4];
            6'b010000: FrontOut[3] = pulses[5];
            6'b010001: FrontOut[3] = pulses[6];
            6'b010010: FrontOut[3] = pulses[7];
            6'b010011: FrontOut[3] = pulses[8];
            6'b010100: FrontOut[3] = pulses[9];
            6'b010101: FrontOut[3] = pulses[10];
            6'b010110: FrontOut[3] = pulses[11];
            6'b010111: FrontOut[3] = pulses[12];
            6'b011000: FrontOut[3] = pulses[13];
            6'b100000: FrontOut[3] = Databus[0];
            6'b100001: FrontOut[3] = Databus[1];
            6'b100010: FrontOut[3] = Databus[2];
            6'b100011: FrontOut[3] = Databus[3];
            6'b100100: FrontOut[3] = Databus[4];
            6'b100101: FrontOut[3] = Databus[5];
            6'b100110: FrontOut[3] = Databus[6];
            6'b100111: FrontOut[3] = Databus[7];
            default:   FrontOut[3] = 1'b0;
        endcase
    end


    always @ *
    begin
        case(FPS5)
            6'b001011: FrontOut[4] = pulses[0];
            6'b001100: FrontOut[4] = pulses[1];
            6'b001101: FrontOut[4] = pulses[2];
            6'b001110: FrontOut[4] = pulses[3];
            6'b001111: FrontOut[4] = pulses[4];
            6'b010000: FrontOut[4] = pulses[5];
            6'b010001: FrontOut[4] = pulses[6];
            6'b010010: FrontOut[4] = pulses[7];
            6'b010011: FrontOut[4] = pulses[8];
            6'b010100: FrontOut[4] = pulses[9];
            6'b010101: FrontOut[4] = pulses[10];
            6'b010110: FrontOut[4] = pulses[11];
            6'b010111: FrontOut[4] = pulses[12];
            6'b011000: FrontOut[4] = pulses[13];
            6'b100000: FrontOut[4] = Databus[0];
            6'b100001: FrontOut[4] = Databus[1];
            6'b100010: FrontOut[4] = Databus[2];
            6'b100011: FrontOut[4] = Databus[3];
            6'b100100: FrontOut[4] = Databus[4];
            6'b100101: FrontOut[4] = Databus[5];
            6'b100110: FrontOut[4] = Databus[6];
            6'b100111: FrontOut[4] = Databus[7];
            default:   FrontOut[4] = 1'b0;
        endcase
    end


    always @ *
    begin
        case(FPS6)
            6'b001011: FrontOut[5] = pulses[0];
            6'b001100: FrontOut[5] = pulses[1];
            6'b001101: FrontOut[5] = pulses[2];
            6'b001110: FrontOut[5] = pulses[3];
            6'b001111: FrontOut[5] = pulses[4];
            6'b010000: FrontOut[5] = pulses[5];
            6'b010001: FrontOut[5] = pulses[6];
            6'b010010: FrontOut[5] = pulses[7];
            6'b010011: FrontOut[5] = pulses[8];
            6'b010100: FrontOut[5] = pulses[9];
            6'b010101: FrontOut[5] = pulses[10];
            6'b010110: FrontOut[5] = pulses[11];
            6'b010111: FrontOut[5] = pulses[12];
            6'b011000: FrontOut[5] = pulses[13];
            6'b100000: FrontOut[5] = Databus[0];
            6'b100001: FrontOut[5] = Databus[1];
            6'b100010: FrontOut[5] = Databus[2];
            6'b100011: FrontOut[5] = Databus[3];
            6'b100100: FrontOut[5] = Databus[4];
            6'b100101: FrontOut[5] = Databus[5];
            6'b100110: FrontOut[5] = Databus[6];
            6'b100111: FrontOut[5] = Databus[7];
            default:   FrontOut[5] = 1'b0;
        endcase
    end

endmodule
