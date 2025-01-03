module PNU_CLK_DIV(
    input clk,          // 입력 클럭
    input rst_n,        // 리셋 신호 (active low)
    input en,           // 활성화 신호
    output reg div_clk  // 분주된 클럭 출력
);

    parameter cnt_num = 2; // 분주 설정값

    reg [19:0] cnt; // 카운터

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cnt <= 0;
            div_clk <= 0;
        end else if (en) begin
            if (cnt < cnt_num - 1) begin
                cnt <= cnt + 1;
            end else begin
                cnt <= 0;
                div_clk <= ~div_clk; // 분주 클럭 반전
            end
        end else begin
            cnt <= 0;
            div_clk <= 0;
        end
    end

endmodule