#ifndef FINDSUBGRAPH_H
#define FINDSUBGRAPH_H

#include <bits/stdc++.h>
#include "graph.h"
#include <array>

tuple<vector<Gate *>, vector<Gate *>> findSubgraph(vector<int> input_name, map<string, Gate *> primary_inputs, map<string, Gate *> primary_outputs);

#endif 