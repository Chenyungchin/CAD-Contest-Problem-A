`timescale 1ns/10ps
`define CYCLE   10

module tb;

reg clk = 0;
reg out2;

initial begin
    $dumpfile("dao.fsdb");
	$dumpvars;
end

always begin
    #(`CYCLE/2) clk = ~clk;
end

reg  [15:0] in1, in2, in3, in4;
wire [33:0] out1;

top top0(
    .in1(in1),
    .in2(in2),
    .in3(in3),
    .in4(in4), 
    .out1(out1)
);

// test pattern
integer i, j, k, l;
initial begin
    for (i=0; i<8; i=i+1) begin
        for (j=0; j<8; j=j+1) begin
            for (k=0; k<8; k=k+1) begin
                for (l=0; l<8; l=l+1) begin
                in1 <= i;
                in2 <= j;
                in3 <= k;
                in4 <= l;
                @(posedge clk);
                end
            end
        end
    end
    $finish;
end


endmodule
