module top(in1, in2, in3, out1, out2, out3, out4, out5, out6);
input wire [30:0] in1;
input wire [31:0] in2;
input wire [31:0] in3;
output wire [32:0] out1;
output wire [32:0] out4;
output wire out2;
output wire out3;
output wire out5;
output wire out6;
assign out1 =  - in1 + in2 - 2;
assign out4 =  - in1 + in3 - 2;
endmodule