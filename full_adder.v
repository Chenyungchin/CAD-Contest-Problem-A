module top(a, b, ci, s, co);
    input a,b,ci;
    output s,co;
    wire a,b,ci,s,co;
    wire i1,i2,i3,i4;
    not dao1(i8, a);
    not dao2(i9, i8);
    not dao3(i10, i9);
    not dao4(i11, i10);
    buf buf1(i5, i1);
    not i1(i6, i3);
    not i2(i7, i6);
    xnor xnor1(i1, i11, b);
    and and1(i2, a, b);
    xnor xnor2(i3, i5, ci);
    not i3(s, i7);
    and and2(i4, ci, i5);
    or or1(co, i2, i4);
endmodule