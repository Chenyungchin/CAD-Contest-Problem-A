module top(a, b, ci, s, co);
input wire a;
input wire b;
input wire ci;
output wire co;
output wire s;
xnor g0(w0, w1, a, b);
and g1(w2, a, b);
xnor g2(w3, w0, ci);
and g3(w4, ci, w1);
not g4(s, w3);
or g5(co, w2, w4);
wire w0, w1, w2, w3, w4;
endmodule