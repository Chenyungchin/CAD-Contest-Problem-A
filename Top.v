module top(in1, in2, in3, out1);
input wire [3:0] in1;
input wire [3:0] in2;
input wire [3:0] in3;
output wire [3:0] out1;
assign out1 = in1 + in2 + in3;
endmodule