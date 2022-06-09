#include <bits/stdc++.h>
#include <array>
#include "graph.h"
#include "netlist2graph.h"
#include "graph2rtl.h"


int main() {
    string file_path = "full_adder.v";
    // string file_path = "top_primitive.v";
    string file_out_path = "out.v";
    string module_name;
    map<string, int> module_inputs;
    map<string, int> module_outputs;
    tuple<map<string, Gate *>, map<string, Gate *>> primary = read_file(file_path, &module_name, &module_inputs, &module_outputs);
    map<string, Gate *> primary_inputs = get<0>(primary);
    map<string, Gate *> primary_outputs = get<1>(primary);
    cout << module_name << endl;
    for (auto input : module_inputs) {
        cout << input.first << " " << input.second << endl;
    }
    for (auto output : module_outputs) {
        cout << output.first << " " << output.second << endl;
    }
    for (auto input : primary_inputs) {
        cout << input.first << " " << input.second->gate_name << " ";
        cout << input.second->num_of_inputs() << " " <<  input.second->num_of_outputs() << endl;
        // cout << input.second->outputs[0]->gate_name << " " << input.second->outputs[0]->inputs[0]->gate_name << " " << input.second->outputs[0]->inputs[1]->gate_name << endl;
        // cout << input.second->outputs[1]->gate_name << " " << input.second->outputs[1]->inputs[0]->gate_name << " " << input.second->outputs[1]->inputs[1]->gate_name << endl;
    }
    for (auto output : primary_outputs) {
        cout << output.first << " " << output.second->gate_name << " ";
        cout << output.second->num_of_inputs() << " " <<  output.second->num_of_outputs() << endl;
    }

    bool write_complete = write_file(file_out_path, module_name, module_inputs, module_outputs, primary_inputs);

    if (write_complete = true) {
        cout << "Write Completed" << endl;
    }

    return 0;
}