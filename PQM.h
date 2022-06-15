#ifndef PQM_H
#define PQM_H
#include <bits/stdc++.h>
#include <array>
#include "graph.h"

using namespace std;

vector<int> PQM(bool** table, int num_of_minterm, int num_of_pattern);
bool complete_cover(vector<bool> cover);

#endif