module eight_digit_shift_register(
    input wire clk,
    input wire rst_n,
    input wire ce,
    input wire [3:0] din,
    output wire [3:0] reg1,
    output wire [3:0] reg2,
    output wire [3:0] reg3,
    output wire [3:0] reg4,
    output wire [3:0] reg5,
    output wire [3:0] reg6,
    output wire [3:0] reg7,
    output wire [3:0] reg8
);

wire [3:0] inter1, inter2, inter3, inter4, inter5, inter6, inter7;

four_bit_reg_ce reg1_inst(.clk(clk), .rst_n(rst_n), .ce(ce), .din(din), .out(inter1));
four_bit_reg_ce reg2_inst(.clk(clk), .rst_n(rst_n), .ce(ce), .din(inter1), .out(inter2));
four_bit_reg_ce reg3_inst(.clk(clk), .rst_n(rst_n), .ce(ce), .din(inter2), .out(inter3));
four_bit_reg_ce reg4_inst(.clk(clk), .rst_n(rst_n), .ce(ce), .din(inter3), .out(inter4));
four_bit_reg_ce reg5_inst(.clk(clk), .rst_n(rst_n), .ce(ce), .din(inter4), .out(inter5));
four_bit_reg_ce reg6_inst(.clk(clk), .rst_n(rst_n), .ce(ce), .din(inter5), .out(inter6));
four_bit_reg_ce reg7_inst(.clk(clk), .rst_n(rst_n), .ce(ce), .din(inter6), .out(inter7));
four_bit_reg_ce reg8_inst(.clk(clk), .rst_n(rst_n), .ce(ce), .din(inter7), .out(reg8));

assign reg1 = inter1;
assign reg2 = inter2;
assign reg3 = inter3;
assign reg4 = inter4;
assign reg5 = inter5;
assign reg6 = inter6;
assign reg7 = inter7;

endmodule