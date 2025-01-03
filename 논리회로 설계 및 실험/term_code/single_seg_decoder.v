module single_seg_decoder(
    input wire [3:0] bcd_in, // 4비트 BCD 입력
    output reg [6:0] seg // 7-Segment 제어 (a-g)
);

    always @(*) begin
        case (bcd_in)
            4'b0000: seg = 7'b1111110; // 0
            4'b0001: seg = 7'b0110000; // 1
            4'b0010: seg = 7'b1101101; // 2
            4'b0011: seg = 7'b1111001; // 3
            4'b0100: seg = 7'b0110011; // 4
            4'b0101: seg = 7'b1011011; // 5
            4'b0110: seg = 7'b1011111; // 6
            4'b0111: seg = 7'b1110000; // 7
            4'b1000: seg = 7'b1111111; // 8
            4'b1001: seg = 7'b1111011; // 9
            default: seg = 7'b0000000; // OFF
        endcase
    end

endmodule