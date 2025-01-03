module week11(
    input wire clk,
    input wire rst,
    input wire keypad_0,
    input wire keypad_1,
    input wire keypad_2,
    input wire keypad_3,
    input wire keypad_4,
    input wire keypad_5,
    input wire keypad_6,
    input wire keypad_7,
    input wire keypad_8,
    input wire keypad_9,
    output wire a, b, c, d, e, f, g, // 7-Segment Display segments
    output wire com1, com2, com3, com4, com5, com6, com7, com8, // Display selects
    output wire SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G, // 1?ûêÎ¶? 7-Segment Display segments
    output wire green_1, green_2, green_3, green_4,
    output wire red_1, red_2, red_3, red_4,
    output wire [7:0] led
);

// **Internal Wires**
wire [3:0] din; // Binary keypad value
wire [3:0] reg1, reg2, reg3, reg4, reg5, reg6, reg7, reg8; // Shift register outputs
wire [2:0] count_8; // Counter for 8-state operations
wire [6:0] time_count; // score_count_timer
wire [3:0] score; // game score
wire [6:0] seg_output; // single seven seg decoder
wire correct; // Password match signal
wire simon_clk; // Clock for Simon LED pattern
wire slow_clk; // Slow clock for 7-segment control
wire debounced_key; // Debounced keypad signal

// **Debouncing Module**
trigger debouncer(
    .CLK(clk),
    .Din(keypad_0 | keypad_1 | keypad_2 | keypad_3 | keypad_4 |
         keypad_5 | keypad_6 | keypad_7 | keypad_8 | keypad_9),
    .rst_n(~rst & ~correct),
    .Dout(debounced_key)
);

// **Keypad to Binary Conversion**
d2b keypad_to_binary(
    .d0(keypad_0), .d1(keypad_1), .d2(keypad_2), .d3(keypad_3),
    .d4(keypad_4), .d5(keypad_5), .d6(keypad_6), .d7(keypad_7),
    .d8(keypad_8), .d9(keypad_9),
    .b0(din[0]), .b1(din[1]), .b2(din[2]), .b3(din[3])
);

// **Shift Register**
eight_digit_shift_register shift_register(
    .clk(clk),
    .rst_n(~rst),
    .ce(debounced_key & ~correct),
    .din(din),
    .reg1(reg1), .reg2(reg2), .reg3(reg3), .reg4(reg4),
    .reg5(reg5), .reg6(reg6), .reg7(reg7), .reg8(reg8)
);

// **Password Verification**
Password password_check(
    .Reg_1(reg1), .Reg_2(reg2), .Reg_3(reg3), .Reg_4(reg4),
    .Reg_5(reg5), .Reg_6(reg6), .Reg_7(reg7), .Reg_8(reg8),
    .Correct(correct)
);

// **Full Color LED Control**
LED led_control(
    .Correct(correct),
    .Green1(green_1), .Green2(green_2), .Green3(green_3), .Green4(green_4),
    .Red1(red_1), .Red2(red_2), .Red3(red_3), .Red4(red_4)
);

// **7-Segment Display Decoder**
b2seg_bus seven_seg_decoder(
    .b_in({count_8 == 3'b000 ? reg1 :
           count_8 == 3'b001 ? reg2 :
           count_8 == 3'b010 ? reg3 :
           count_8 == 3'b011 ? reg4 :
           count_8 == 3'b100 ? reg5 :
           count_8 == 3'b101 ? reg6 :
           count_8 == 3'b110 ? reg7 : reg8}),
    .a(a), .b(b), .c(c), .d(d), .e(e), .f(f), .g(g)
);

// **Display Select Logic**
display_controller display_control(
    .count(count_8),
    .com({com8, com7, com6, com5, com4, com3, com2, com1})
);

// Timer Module
timer game_timer(
    .clk(clk),
    .rst_n(~rst),
    .enable(~correct), // Timer starts when correct signal is low
    .time_count(time_count)
);

// Score Calculator
score_calculator score_calc(
    .time_count(time_count),
    .score(score)
);

// Single 7-Segment Decoder for Score
single_seg_decoder seg_decoder(
    .bcd_in(score),
    .seg(seg_output)
);

// 1-Digit 7-Segment Pin Assignments
assign SEG_A = seg_output[6];
assign SEG_B = seg_output[5];
assign SEG_C = seg_output[4];
assign SEG_D = seg_output[3];
assign SEG_E = seg_output[2];
assign SEG_F = seg_output[1];
assign SEG_G = seg_output[0];

// **8-State Counter**
count_8 state_counter(
    .clk(slow_clk),
    .rst_n(~rst),
    .Q(count_8)
);

// **Clock Divider for Slow Clock**
PNU_CLK_DIV slow_clk_div(
    .clk(clk),
    .rst_n(~rst),
    .en(1'b1),
    .div_clk(slow_clk)
);
defparam slow_clk_div.cnt_num = 1250;

// **Clock Divider for Simon Module**
PNU_CLK_DIV simon_clk_div(
    .clk(clk),
    .rst_n(~rst),
    .en(1'b1),
    .div_clk(simon_clk)
);
defparam simon_clk_div.cnt_num = 250_000;

// **Simon LED Pattern**
simon simon_led_pattern(
    .clk(simon_clk),
    .rst_n(~rst),
    .Correct(correct), // ÎπÑÔøΩ?Î≤àÌò∏ ÎßûÏ∂§ ?ÔøΩÔøΩ?ÔøΩÔøΩ ?ÔøΩÔøΩÔø??
    .led(led)
);

endmodule