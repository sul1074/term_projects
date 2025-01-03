module score_calculator(
    input [6:0] time_count, // Timer에서 전달된 시간 값
    output reg [3:0] score // 계산된 점수 (4비트로 충분)
);

    always @(*) begin
        if (time_count < 10)
            score = 9; // 0~9초: 9점
        else if (time_count < 20)
            score = 8; // 10~19초: 8점
        else if (time_count < 30)
            score = 7; // 20~29초: 7점
        else if (time_count < 40)
            score = 6; // 30~39초: 6점
        else if (time_count < 50)
            score = 5; // 40~49초: 5점
        else if (time_count < 60)
            score = 4; // 50~59초: 4점
        else if (time_count < 70)
            score = 3; // 60~69초: 3점
        else if (time_count < 80)
            score = 2; // 70~79초: 2점
        else
            score = 1; // 80~90초: 1점
    end

endmodule