`timescale 1ns/10ps
`define CYCLE   10

module tb;

reg clk = 0;

initial begin
    $dumpfile("dao.vcd");
	$dumpvars;
end

always begin
    #(`CYCLE/2) clk = ~clk;
end

reg  [3:0] in1, in2, in3;
wire [3:0] out1;

top top0(
    .in1(in1),
    .in2(in2),
    .in3(in3),
    .out1(out1)
);

// test pattern
integer i, j, k;
initial begin
    for (i=0; i<16; i=i+1) begin
        for (j=0; j<16; j++) begin
            for (k=0; k<16; k++) begin
                in1 <= i;
                in2 <= j;
                in3 <= k;
                @(posedge clk);
            end
        end
    end
    $finish;
end


endmodule
