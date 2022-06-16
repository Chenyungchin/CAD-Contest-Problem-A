#include <bits/stdc++.h>
#include "graph.h"

tuple<bool*, vector<int>*, int> compare_pattern(vector<int>, vector<Gate*>, vector<Gate*>, vector<int>, int);
tuple<bool*, vector<int>*, int> simulated_function(vector<int>, int, int, int, int, int);
int get_constant(vector<Gate*>, vector<Gate*>, vector<int>);
int get_gate_value(Gate*);
void reset_gate_value(Gate*);