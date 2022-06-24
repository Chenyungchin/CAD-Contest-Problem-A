#include "graphReduction.h"

void graphReduction(vector<Gate*> circ_inputs, vector<Gate*> circ_outputs, vector<int> inputs_operand_bit, vector<int> signs, int constant_term, bool delete_gate, int c, int ctrl_value) {
    
    int input_num = 0;
    for (auto n : inputs_operand_bit) {
        input_num += n;
    }
    // if (input_num != circ_inputs.size()) {
    //     cout << "Circ_inputs wrong!" << endl;
    //     return;
    // }

    Gate *newGate = new Gate("func");
    newGate->signs = signs;
    newGate->constant_term = constant_term;
    // for (auto sign : signs) {
    //     cout << sign << " ";
    // }
    // cout << endl;
    if (c >= 0) {
        newGate->c = c;
        newGate->ctrl_value = ctrl_value;
        // cout << c << " " << ctrl_value << endl;
    }

    newGate->inputs_operand_bit = inputs_operand_bit;
    int in_gate_count = 0;
    for (auto g_in : circ_inputs) {
        newGate->inputs.push_back(make_tuple(g_in, 0));
        if (delete_gate) g_in->outputs = {{}};
        g_in->outputs[0].push_back(make_tuple(newGate, in_gate_count));
        in_gate_count ++;
    }
    int out_gate_count = 0;
    for (auto g_out : circ_outputs) {
        newGate->outputs.push_back({make_tuple(g_out, 0)});
        if (delete_gate) g_out->inputs = {};
        g_out->inputs.push_back(make_tuple(newGate, out_gate_count));
        out_gate_count ++;
    }

}