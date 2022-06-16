`timescale 1ns/10ps
`define CYCLE   10

module tb;

reg clk = 0;

initial begin
    $dumpfile("dao.vcd");
    // $dumpfile("dao.fsdb");
	$dumpvars;
end

always begin
    #(`CYCLE/2) clk = ~clk;
end

reg  [15:0] in1, in2, in3, in4, in5;
wire [16:0] out1, out2;
wire [33:0] out3;

top top0(
    .in1(in1),
    .in2(in2),
    .in3(in3),
    .in4(in4),
    .in5(in5),
    .out1(out1),
    .out2(out2),
    .out3(out3)
);

// test pattern
integer i, j, k, l, m;
initial begin
    for (i=0; i<8; i=i+1) begin
        for (j=0; j<8; j++) begin
            for (k=0; k<8; k++) begin
                for (l=0; l<8; l++) begin
                    for (m=0; m<8; m++) begin
                in1 <= i;
                in2 <= j;
                in3 <= k;
                in4 <= l;
                in5 <= m;
                @(posedge clk);
                    end
                end
            end
        end
    end
    $finish;
end


endmodule
