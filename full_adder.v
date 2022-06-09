module top(a, b, ci, s, co);
    input a,b,ci;
    output s,co;
    wire a,b,ci,s,co;
    wire i1,i2,i3,i4;
    xnor xnor1(i1, a, b);
    and and1(i2, a, b);
    xnor xnor2(i3, i1, ci);
    not i1(s, i3);
    and and2(i4, ci, i1);
    or or1(co, i2, i4);
endmodule