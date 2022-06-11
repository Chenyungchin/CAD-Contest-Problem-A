module top(a, b, ci, s, co);
input wire a;
input wire b;
input wire ci;
output wire co;
output wire s;
xnor g0(w0, a, b);
and g1(w1, a, b);
xnor g2(w2, w0, ci);
and g3(w3, ci, w0);
not g4(s, w2);
or g5(co, w1, w3);
wire w0, w1, w2, w3;
endmodule