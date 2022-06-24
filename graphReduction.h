#ifndef GRAPHREDUCTION_H
#define GRAPHREDUCTION_H

#include <bits/stdc++.h>
#include <array>
#include "graph.h"

using namespace std;

void graphReduction(vector<Gate*> circ_inputs, vector<Gate*> circ_outputs, vector<int> inputs_operand_bit, vector<int> signs, int constant_term, bool delete_gate, int c, int ctrl_value);


#endif