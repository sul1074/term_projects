module display_controller(
    input wire [2:0] count, // 3��Ʈ ���� �Է�
    output reg [7:0] com // 8���� ���÷��� ���� ��ȣ
);

always @(*) begin
    com = 8'b11111111; // �⺻������ ��� ���÷��� ��Ȱ��ȭ
    case (count)
        3'b000: com[7] = 0; // com8 활성화
        3'b001: com[6] = 0; // com7 활성화
        3'b010: com[5] = 0; // com6 활성화
        3'b011: com[4] = 0; // com5 활성화
        3'b100: com[3] = 0; // com4 활성화
        3'b101: com[2] = 0; // com3 활성화
        3'b110: com[1] = 0; // com2 활성화
        3'b111: com[0] = 0; // com1 활성화
    endcase
end

endmodule