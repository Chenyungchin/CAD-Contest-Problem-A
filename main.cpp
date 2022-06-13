#include <bits/stdc++.h>
#include <array>
#include "graph.h"
#include "netlist2graph.h"
#include "graph2rtl.h"
#include "deleteBuf.h"
#include "deleteNot.h"
#include "Compare_pattern.h"
#include "Pattern_controller.h"
#include "graphReduction.h"


int main() {
    // string file_path = "full_adder.v";
    string file_path = "top_primitive.v";
    // string file_path = "20.v";
    string file_out_path = "out.v";
    string module_name;
    map<string, int> module_inputs;
    map<string, int> module_outputs;
    tuple<map<string, Gate *>, map<string, Gate *>> primary = read_file(file_path, &module_name, &module_inputs, &module_outputs);
    map<string, Gate *> primary_inputs = get<0>(primary);
    map<string, Gate *> primary_outputs = get<1>(primary);
    // cout << module_name << endl;
    // for (auto input : module_inputs) {
    //     cout << input.first << " " << input.second << endl;
    // }
    // for (auto output : module_outputs) {
    //     cout << output.first << " " << output.second << endl;
    // }
    // int out_num = 0;
    // for (auto input : primary_inputs) {
    //     cout << input.first << " " << input.second->gate_name << " ";
    //     cout << input.second->num_of_inputs() << " " <<  input.second->num_of_outputs() << endl;
    //     for (auto dao: input.second->outputs){ // iterate every output gate
    //         out_num ++;
    //         cout << "out_num: " << out_num << endl;
    //         for (auto daodao: dao){// iterate every fanout of the gate
    //             cout << "gate fanout: " << get<0>(daodao)->gate_name << " " << get<1>(daodao) << endl;
    //             cout << "gate index: " << get<0>(daodao)->no << endl;
    //         } 
    //     }
    //     out_num = 0;
    //     // cout << input.second->outputs[0]->gate_name << " " << input.second->outputs[0]->inputs[0]->gate_name << " " << input.second->outputs[0]->inputs[1]->gate_name << endl;
    //     // cout << input.second->outputs[1]->gate_name << " " << input.second->outputs[1]->inputs[0]->gate_name << " " << input.second->outputs[1]->inputs[1]->gate_name << endl;
    // }
    // for (auto output : primary_outputs) {
    //     cout << output.first << " " << output.second->gate_name << " ";
    //     cout << output.second->num_of_inputs() << " " <<  output.second->num_of_outputs() << endl;
    // }


    deleteBuf(primary_inputs, primary_outputs);
    deleteNot(primary_inputs, primary_outputs);

    
    vector<Gate*> inputs, outputs;
    for (auto inp: primary_inputs){
        inputs.push_back(inp.second);
    }
    for (auto oup: primary_outputs){
        outputs.push_back(oup.second);
    }
    vector<int> inputs_operand_bit = {4, 4, 4};
    // bool dao = compare_pattern(pattern, inputs, outputs, inputs_operand_bit);
    auto tmp = pattern_controller(inputs, outputs, inputs_operand_bit);
    bool found = get<0>(tmp);
    vector<Gate*> circ_inputs = get<1>(tmp); 
    vector<Gate*> circ_outputs = get<2>(tmp);
    cout << found << endl;
    graphReduction(found, circ_inputs, circ_outputs, inputs_operand_bit);
    bool write_complete = write_file(file_out_path, module_name, module_inputs, module_outputs, primary_inputs);

    // if (write_complete = true) {
    //     cout << "Write Completed" << endl;
    // }

    return 0;
}