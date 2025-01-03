module trigger(
	CLK,
	Din,
	rst_n,
	Dout
);


input wire	CLK;
input wire	Din;
input wire	rst_n;
output wire	Dout;

reg	SYNTHESIZED_WIRE_1;
wire	SYNTHESIZED_WIRE_0;
reg	DFF_inst3;




assign	Dout = SYNTHESIZED_WIRE_1 & SYNTHESIZED_WIRE_0;


always@(posedge CLK or negedge rst_n)
begin
if (!rst_n)
	begin
	SYNTHESIZED_WIRE_1 <= 0;
	end
else
	begin
	SYNTHESIZED_WIRE_1 <= Din;
	end
end


always@(posedge CLK or negedge rst_n)
begin
if (!rst_n)
	begin
	DFF_inst3 <= 0;
	end
else
	begin
	DFF_inst3 <= SYNTHESIZED_WIRE_1;
	end
end

assign	SYNTHESIZED_WIRE_0 =  ~DFF_inst3;


endmodule
