module top(in1, in2, in3, in4, out1);
input wire [15:0] in1;
input wire [15:0] in2;
input wire [15:0] in3;
input wire [1:0] in4;
output wire [31:0] out1;
assign out1 = (in4 == 2) ? in1 * in3:
(in4 == 3) ? in1 * in2:
(in4 == 1) ? in2 * in3:
(in4 == 0) ? 0;
endmodule