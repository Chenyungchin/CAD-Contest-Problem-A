module top(a, b, ci, s, co);
input wire a;
input wire b;
input wire ci;
output wire co;
output wire s;
assign w0 = a ~^ b;
assign w1 = a & b;
assign w2 = w0 ~^ ci;
assign w3 = ci & w0;
assign s = ~w2;
assign co = w1 | w3;
wire w0, w1, w2, w3;
endmodule