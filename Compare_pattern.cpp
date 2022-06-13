// #include <bits/stdc++.h>
// #include "graph.h"
#include "Compare_pattern.h"


using namespace std;


bool compare_pattern(vector<int> pattern, vector<Gate*> inputs, vector<Gate*> outputs, vector<int> inputs_operand_bit){
    // ==== traversing the graph to get output ====
    // stream in the given pattern
    for (int i=0; i<inputs.size(); i++){
        inputs[i]->value = pattern[i];
    }
    // calc gate value by top down DP from output
    vector<int> output_vals;
    for (auto outp: outputs){
        int gate_val = get_gate_value(outp);
        output_vals.push_back(gate_val);
    }
    int output_dec = 0;
    int k = 1;
    for (auto outp: output_vals){
        cout << outp << endl;
        output_dec += outp * k;
        k *= 2;
    }

    cout << "circuit: " << output_dec << endl;

    // ==== calculate output using the formula ====
    vector<int> words;
    int word = 0;
    int tmp = 1;
    int start_index = 0;
    for (auto bits: inputs_operand_bit){
        // calc word val
        for (int i=start_index; i<start_index+bits; i++){
            word += pattern[i] * tmp;
            tmp *= 2;
        }
        words.push_back(word);
        tmp = 1;
        word = 0;
        start_index += bits;
    }
    
    int output_adder_tree = 0;
    int output_mult = 1;
    for (auto word: words){
        output_adder_tree += word;
        output_mult *= word;
    }

    cout << "calculated: " << output_adder_tree << endl;
    int mod_num = pow(2, (outputs.size()));

    // check equivalence
    return (output_dec == (output_adder_tree % mod_num));
    // return (output_dec == (output_mult % mod_num));
}

int get_gate_value(Gate* gate){
    cout << "debug  " << gate->gate_name << " " << gate->value << endl;
    if (gate->value != -1) return gate->value;
    string oper = gate->gate_name;
    cout << oper << endl;
    if (oper == "and"){
        int val1 = get_gate_value(get<0>(gate->inputs[0]));
        int val2 = get_gate_value(get<0>(gate->inputs[1]));
        gate->value = val1 * val2;
        return gate->value;
    }
    else if (oper == "or"){
        int val1 = get_gate_value(get<0>(gate->inputs[0]));
        int val2 = get_gate_value(get<0>(gate->inputs[1]));
        gate->value = (val1 + val2 > 0) ? 1 : 0;
        return gate->value;
    }
    else if (oper == "nand"){
        int val1 = get_gate_value(get<0>(gate->inputs[0]));
        int val2 = get_gate_value(get<0>(gate->inputs[1]));
        gate->value = (val1 * val2 == 1) ? 0 : 1;
        return gate->value;
    }
    else if (oper == "nor"){
        int val1 = get_gate_value(get<0>(gate->inputs[0]));
        int val2 = get_gate_value(get<0>(gate->inputs[1]));
        gate->value = (val1 + val2 > 0) ? 0 : 1;
        return gate->value;
    }
    else if (oper == "not"){
        int val = get_gate_value(get<0>(gate->inputs[0]));
        gate->value = (val == 1) ? 0 : 1;
        return gate->value;
    }
    else if (oper == "buf"){
        int val = get_gate_value(get<0>(gate->inputs[0]));
        gate->value = val;
        return gate->value;
    }
    else if (oper == "xor"){
        int val1 = get_gate_value(get<0>(gate->inputs[0]));
        int val2 = get_gate_value(get<0>(gate->inputs[1]));
        gate->value = (val1 + val2 == 1) ? 1 : 0;
        return gate->value;
    }
    else if (oper == "xnor"){
        int val1 = get_gate_value(get<0>(gate->inputs[0]));
        int val2 = get_gate_value(get<0>(gate->inputs[1]));
        gate->value = (val1 + val2 == 1) ? 0 : 1;
        return gate->value;
    }
    else{
        int val = get_gate_value(get<0>(gate->inputs[0]));
        gate->value = val;
        return gate->value;
    }
}