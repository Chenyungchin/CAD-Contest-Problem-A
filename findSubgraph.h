#ifndef FINDSUBGRAPH_H
#define FINDSUBGRAPH_H

#include <bits/stdc++.h>
#include "graph.h"
#include <array>

vector<Gate *> findSubgraph(vector<Gate *> input_gate, vector<tuple<string, Gate *>> primary_inputs, vector<tuple<string, Gate *>> primary_outputs);

#endif 