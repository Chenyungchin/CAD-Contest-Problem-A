#ifndef GRAPH2RTL_H
#define GRAPH2RTL_H

#include <bits/stdc++.h>
#include "graph.h"
#include <array>

bool write_file(string file, string module_name, vector<tuple<string, int>> module_inputs, vector<tuple<string, int>> module_outputs, vector<tuple<string, Gate *>> primary_inputs);

#endif