module four_bit_reg_ce (
    input wire clk,
    input wire rst_n,
    input wire ce,
    input wire [3:0] din,
    output wire [3:0] out
);

    reg [3:0] reg_out;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            reg_out <= 4'b0000;
        end else if (ce) begin
            reg_out <= din;
        end
    end

    assign out = reg_out;

endmodule