module simon (
    input clk,          // 분주된 클럭
    input rst_n,        // Low-Active Reset 신호
    input Correct,      // 비밀번호 확인 신호
    output reg [7:0] led // 8개의 LED 출력
);

    reg [2:0] pattern_index;  // 패턴 인덱스 (0~7)
    reg active;               // LED 점등 활성 상태 플래그
    reg [1:0] blink_state;    // 깜빡임 상태 (0: OFF, 1: ON, 2: NEXT)

    // LED 점등 순서: 26183745
    reg [2:0] pattern [0:7];
    initial begin
        pattern[0] = 1; // 2번 LED
        pattern[1] = 5; // 6번 LED
        pattern[2] = 0; // 1번 LED
        pattern[3] = 7; // 8번 LED
        pattern[4] = 2; // 3번 LED
        pattern[5] = 6; // 7번 LED
        pattern[6] = 3; // 4번 LED
        pattern[7] = 4; // 5번 LED
    end

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            active <= 1;
            pattern_index <= 0;
            blink_state <= 0;
            led <= 8'b0;
        end else if (Correct) begin
            // 비밀번호 맞추면 모든 LED 켜짐
            active <= 0;
            led <= 8'b11111111;
        end else if (active) begin
            case (blink_state)
                2'b00: begin
                    // OFF 상태
                    led <= 8'b0;
                    blink_state <= 2'b01; // ON 상태로 전환
                end
                2'b01: begin
                    // ON 상태
                    led <= (1 << pattern[pattern_index]); // 현재 패턴 LED 점등
                    blink_state <= 2'b10; // NEXT 상태로 전환
                end
                2'b10: begin
                    // NEXT 상태
                    if (pattern_index < 7) begin
                        pattern_index <= pattern_index + 1; // 다음 패턴으로 이동
                    end else begin
                        pattern_index <= 0; // 패턴 반복
                    end
                    blink_state <= 2'b00; // OFF 상태로 전환
                end
            endcase
        end
    end
endmodule