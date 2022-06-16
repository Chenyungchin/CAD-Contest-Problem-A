#ifndef COMPARE_PATTERN_H
#define COMPARE_PATTERN_H
#include <bits/stdc++.h>
#include "graph.h"

bool* compare_pattern(vector<int>, vector<Gate*>, vector<Gate*>, vector<int>, long long int, vector<int>*, int);
bool* simulated_function(vector<int>, long long int, int, int, long long int, int, vector<int>*, int);
tuple<vector<int>*, int> get_column_info(int, int);
long long int get_constant(vector<Gate*>, vector<Gate*>, vector<int>);
int get_gate_value(Gate*);
void reset_gate_value(Gate*);

#endif