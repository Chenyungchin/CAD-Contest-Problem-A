#ifndef COMPARE_PATTERN_CTRL_H
#define COMPARE_PATTERN_CTRL_H
#include <bits/stdc++.h>
#include "graph.h"

tuple<bool*, vector<int>*, int> compare_pattern_ctrl(vector<int>, vector<Gate*>, vector<Gate*>, vector<int>, long long int, vector<vector<int>>);
tuple<bool*, vector<int>*, int> simulated_function_ctrl(vector<int>, long long int, int, int, long long int, vector<vector<int>>, int);
// long long int get_constant(vector<Gate*>, vector<Gate*>, vector<int>);
// int get_gate_value(Gate*);
// void reset_gate_value(Gate*);

#endif