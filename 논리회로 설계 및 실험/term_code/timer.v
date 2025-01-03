module timer(
    input wire clk,
    input wire rst_n,
    input wire enable,
    output reg [6:0] time_count // 7비트로 최대 127까지 카운트
);

    reg [19:0] count; // 클럭 분주용 카운터

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            count <= 0;
            time_count <= 7'b0;
        end else if (enable) begin
            if (count < 1_000_000) begin // 1MHz에서 1초 분주
                count <= count + 1;
            end else begin
                count <= 0;
                if (time_count < 7'b1111111) // 시간 증가
                    time_count <= time_count + 1;
            end
        end
    end

endmodule