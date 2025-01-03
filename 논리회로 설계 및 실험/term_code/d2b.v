module d2b(
	d0,
	d1,
	d2,
	d3,
	d4,
	d5,
	d6,
	d7,
	d8,
	d9,
	b0,
	b1,
	b2,
	b3
);


input wire	d0;
input wire	d1;
input wire	d2;
input wire	d3;
input wire	d4;
input wire	d5;
input wire	d6;
input wire	d7;
input wire	d8;
input wire	d9;
output wire	b0;
output wire	b1;
output wire	b2;
output wire	b3;

wire	SYNTHESIZED_WIRE_15;
wire	SYNTHESIZED_WIRE_1;
wire	SYNTHESIZED_WIRE_3;
wire	SYNTHESIZED_WIRE_5;
wire	SYNTHESIZED_WIRE_7;
wire	SYNTHESIZED_WIRE_8;
wire	SYNTHESIZED_WIRE_9;
wire	SYNTHESIZED_WIRE_10;
wire	SYNTHESIZED_WIRE_11;
wire	SYNTHESIZED_WIRE_12;
wire	SYNTHESIZED_WIRE_13;
wire	SYNTHESIZED_WIRE_14;




assign	SYNTHESIZED_WIRE_14 = d3 | d1;

assign	b0 = SYNTHESIZED_WIRE_15 & SYNTHESIZED_WIRE_1;

assign	b1 = SYNTHESIZED_WIRE_15 & SYNTHESIZED_WIRE_3;

assign	b2 = SYNTHESIZED_WIRE_15 & SYNTHESIZED_WIRE_5;

assign	b3 = SYNTHESIZED_WIRE_15 & SYNTHESIZED_WIRE_7;

assign	SYNTHESIZED_WIRE_10 = d7 | d6;

assign	SYNTHESIZED_WIRE_11 = d3 | d2;

assign	SYNTHESIZED_WIRE_9 = d5 | d4;

assign	SYNTHESIZED_WIRE_8 = d7 | d6;

assign	SYNTHESIZED_WIRE_5 = SYNTHESIZED_WIRE_8 | SYNTHESIZED_WIRE_9;

assign	SYNTHESIZED_WIRE_3 = SYNTHESIZED_WIRE_10 | SYNTHESIZED_WIRE_11;

assign	SYNTHESIZED_WIRE_15 =  ~d0;

assign	SYNTHESIZED_WIRE_13 = d9 | SYNTHESIZED_WIRE_12;

assign	SYNTHESIZED_WIRE_1 = SYNTHESIZED_WIRE_13 | SYNTHESIZED_WIRE_14;

assign	SYNTHESIZED_WIRE_7 = d9 | d8;

assign	SYNTHESIZED_WIRE_12 = d7 | d5;


endmodule
