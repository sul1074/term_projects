module count_8(
    input wire clk,
    input wire rst_n,
    output reg [2:0] Q // 3비트 상태 출력 (8단계)
);

always @(posedge clk or negedge rst_n) begin
    if (!rst_n)
        Q <= 3'b000;
    else
        Q <= Q + 1;
end

endmodule