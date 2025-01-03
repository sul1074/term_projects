module Password(
    input wire [3:0] Reg_1, Reg_2, Reg_3, Reg_4,
    input wire [3:0] Reg_5, Reg_6, Reg_7, Reg_8,
    output wire Correct
);

// 비밀번호 = 26183745
assign Correct = (Reg_8 == 4'b0010) &&
                 (Reg_7 == 4'b0110) &&
                 (Reg_6 == 4'b0001) &&
                 (Reg_5 == 4'b1000) &&
                 (Reg_4 == 4'b0011) &&
                 (Reg_3 == 4'b0111) && 
                 (Reg_2 == 4'b0100) &&                  
                 (Reg_1 == 4'b0101);
endmodule