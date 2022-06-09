#ifndef NETLIST2GRAPH_H
#define NETLIST2GRAPH_H

#include <bits/stdc++.h>
#include "graph.h"
#include <array>

tuple<map<string, Gate *>, map<string, Gate *>> read_file(string file, string *module_name, map<string, int> *module_inputs, map<string, int> *module_outputs);
tuple<int, vector<string>> split_ports(string str);

#endif