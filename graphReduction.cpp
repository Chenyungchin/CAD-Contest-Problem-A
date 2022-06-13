#include "graphReduction.h"

void graphReduction(bool found, vector<Gate*> circ_inputs, vector<Gate*> circ_outputs, vector<int> inputs_operand_bit) {
    if (!found) return;

    int input_num = 0;
    for (auto n : inputs_operand_bit) {
        input_num += n;
    }
    if (input_num != circ_inputs.size()) {
        cout << "Circ_inputs wrong!";
        return;
    }

    Gate *newGate = new Gate("++");
    newGate->inputs_operand_bit = inputs_operand_bit;
    int in_gate_count = 0;
    for (auto g_in : circ_inputs) {
        newGate->inputs.push_back(make_tuple(g_in, 0));
        g_in->outputs = {{}};
        g_in->outputs[0].push_back(make_tuple(newGate, in_gate_count));
        in_gate_count ++;
    }
    int out_gate_count = 0;
    for (auto g_out : circ_outputs) {
        newGate->outputs.push_back({make_tuple(g_out, 0)});
        g_out->inputs = {};
        g_out->inputs.push_back(make_tuple(newGate, out_gate_count));
        out_gate_count ++;
    }

}