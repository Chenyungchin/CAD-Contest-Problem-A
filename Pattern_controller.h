#ifndef PATTERN_CONTROLLER_H
#define PATTERN_CONTROLLER_H
#include <bits/stdc++.h>
#include "graph.h"

// tuple<vector<bool>, vector<Gate*>, vector<Gate*>> pattern_controller(vector<Gate*>, vector<Gate*>, vector<int>);
tuple<bool**, vector<int>*, int, int> pattern_controller(vector<Gate*>, vector<Gate*>, vector<int>, int);
vector<int> pattern_generator(vector<int>);

#endif