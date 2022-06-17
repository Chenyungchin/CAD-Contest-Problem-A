#ifndef FIND_CTRL_H
#define FIND_CTRL_H
#include <bits/stdc++.h>
#include "graph.h"
#include <array>

vector<vector<tuple<int, int>>> find_ctrl(vector<vector<int>> functions, vector<Gate*> primary_inputs, vector<Gate*> primary_outputs, vector<int> inputs_operand_bit, int num_of_pattern, vector<int> ctrl);

#endif 