module top(in1, in2, in3, in4, in5, out1, out2, out3);
input wire [15:0] in1;
input wire [15:0] in2;
input wire [15:0] in3;
input wire [15:0] in4;
input wire [15:0] in5;
output wire [16:0] out1;
output wire [16:0] out2;
output wire [33:0] out3;
assign out3 = in5 + in1 * in2 + in1 * in3 + in1 * in4;
endmodule