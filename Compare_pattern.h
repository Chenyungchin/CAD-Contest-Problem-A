#include <bits/stdc++.h>
#include "graph.h"

bool* compare_pattern(vector<int>, vector<Gate*>, vector<Gate*>, vector<int>, int);
int get_constant(vector<Gate*>, vector<Gate*>, vector<int>);
int get_gate_value(Gate*);
void reset_gate_value(Gate*);