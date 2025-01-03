module count_8(
    input wire clk,
    input wire rst_n,
    output reg [2:0] Q // 3��Ʈ ���� ��� (8�ܰ�)
);

always @(posedge clk or negedge rst_n) begin
    if (!rst_n)
        Q <= 3'b000;
    else
        Q <= Q + 1;
end

endmodule