#ifndef GRAPH2RTL_H
#define GRAPH2RTL_H

#include <bits/stdc++.h>
#include "graph.h"
#include <array>

bool write_file(string file, string module_name, map<string, int> module_inputs, map<string, int> module_outputs, map<string, Gate *> primary_inputs);

#endif