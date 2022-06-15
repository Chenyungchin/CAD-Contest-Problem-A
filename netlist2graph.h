#ifndef NETLIST2GRAPH_H
#define NETLIST2GRAPH_H

#include <bits/stdc++.h>
#include "graph.h"
#include <array>

tuple<vector<tuple<string, Gate *>>, vector<tuple<string, Gate *>>, int> read_file(string file, string *module_name, vector<tuple<string, int>> *module_inputs, vector<tuple<string, int>> *module_outputs);
tuple<int, vector<string>> split_ports(string str);

#endif