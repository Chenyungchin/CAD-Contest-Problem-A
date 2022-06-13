#ifndef FINDSUBGRAPH_H
#define FINDSUBGRAPH_H

#include <bits/stdc++.h>
#include "graph.h"
#include <array>

vector<Gate *> findSubgraph(int input_num, int output_num, int least_gate, map<string, Gate *> primary_inputs, map<string, Gate *> primary_outputs);

#endif 