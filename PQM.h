#ifndef PQM_H
#define PQM_H
#include <bits/stdc++.h>
#include <array>
#include "graph.h"

using namespace std;

vector<int> PQM(bool** table, int num_of_minterm, int num_of_pattern, vector<int>* column_signs);
bool complete_cover(vector<bool> cover);
vector<int> get_ctrl(vector<int> cover, vector<tuple<string, int>> module_inputs, vector<int>* column_signs);

#endif