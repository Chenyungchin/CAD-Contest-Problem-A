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
#include "evaluate.h"
#include "PQM.h"

int main()
{
    // string file_path = "full_adder.v";
    string file_path = "release/test10/top_primitive.v";
    
    string file_out_path = "out2.v";
    string module_name;
    vector<tuple<string, int>> module_inputs;
    vector<tuple<string, int>> module_outputs;
    tuple<vector<tuple<string, Gate *>>, vector<tuple<string, Gate *>>, int> primary = read_file(file_path, &module_name, &module_inputs, &module_outputs);
    vector<tuple<string, Gate *>> primary_inputs = get<0>(primary);
    vector<tuple<string, Gate *>> primary_outputs = get<1>(primary);
    int gate_count = get<2>(primary);
    cout << gate_count << endl;
    float reduction_rate = evaluate(file_out_path, gate_count);
    cout << "reduction rate: " << reduction_rate << endl;


    // cout << module_name << endl;
    // for (auto input : module_inputs) {
    //     cout << get<0>(input) << " " << get<1>(input) << endl;
    // }
    // for (auto output : module_outputs) {
    //     cout << get<0>(output) << " " << get<1>(output) << endl;
    // }
    // int out_num = 0;
    // for (auto input : primary_inputs) {
    //     cout << get<0>(input) << " " << get<1>(input)->gate_name << " ";
    //     cout << get<1>(input)->num_of_inputs() << " " <<  get<1>(input)->num_of_outputs() << endl;
    //     for (auto dao: get<1>(input)->outputs){ // iterate every output gate
    //         out_num ++;
    //         cout << "out_num: " << out_num << endl;
    //         for (auto daodao: dao){// iterate every fanout of the gate
    //             cout << "gate fanout: " << get<0>(daodao)->gate_name << " " << get<1>(daodao) << endl;
    //             cout << "gate index: " << get<0>(daodao)->no << endl;
    //         }
    //     }
    //     out_num = 0;
    //     // cout << get<1>(input)->outputs[0]->gate_name << " " << get<1>(input)->outputs[0]->inputs[0]->gate_name << " " << get<1>(input)->outputs[0]->inputs[1]->gate_name << endl;
    //     // cout << get<1>(input)->outputs[1]->gate_name << " " << get<1>(input)->outputs[1]->inputs[0]->gate_name << " " << get<1>(input)->outputs[1]->inputs[1]->gate_name << endl;
    // }
    // for (auto output : primary_outputs) {
    //     cout << get<0>(output) << " " << get<1>(output)->gate_name << " ";
    //     cout << get<1>(output)->num_of_inputs() << " " <<  get<1>(output)->num_of_outputs() << endl;
    // }

    // test constant inputs
    // Gate* dao = primary_inputs.find("1'b0")->second;
    // for (auto d: dao->outputs[0]){
    //     cout << get<0>(d)->gate_name << endl;
    // }

    
    deleteBuf(primary_inputs, primary_outputs);
    deleteNot(primary_inputs, primary_outputs);

    
    vector<Gate*> inputs;
    vector<vector<Gate*>> outputs;
    for (auto inp: primary_inputs){
        // inputs.push_back(inp.second);
        inputs.push_back(get<1>(inp));
    }
    
    int node_cnt = 0;
    // cout << "module output " << module_outputs.size() << endl;
    for (int i=0; i<module_outputs.size(); i++){
        int word_len = get<1>(module_outputs[i]);
        vector<Gate*> output;
        for (int j=0; j<word_len;j++){
            output.push_back(get<1>(primary_outputs[node_cnt+j]));
        }
        outputs.push_back(output);
        node_cnt += word_len;
        // cout << "len: " << outputs.size() << endl;
    }

    // cout << outputs.size() << " " << outputs[0].size() << endl;

    // for (int i=0; i<outputs.size(); i++){
    //     for (int j=0; j<outputs[i].size(); j++){
    //         cout << outputs[i][j]->gate_name << " ";
    //     }
    //     cout << endl;
    // }


    vector<int> inputs_operand_bit;

    for (auto inp: module_inputs){
        inputs_operand_bit.push_back(get<1>(inp));
    }

    // for (int i=0; i<inputs_operand_bit.size(); i++) cout << inputs_operand_bit[i] << " ";

    int num_of_pattern = 10;
    // cout << "dao" << endl;
    // cout << "dao2" << endl;
    
    int num_of_inputs = inputs_operand_bit.size();

    int num_of_function_terms = (num_of_inputs == 2) ? 5 :
                                (num_of_inputs == 3) ? 10 : 
                                (num_of_inputs == 4) ? 10 : num_of_inputs;
    int num_of_function_tested = pow(3, num_of_function_terms);


    // debug
    int bias = 0;
    for (int i=0; i<num_of_function_terms; i++) bias += pow(3, i);
    // cout << bias << endl;


    // for (int i=0; i<num_of_pattern; i++){
    //     for (int j=0; j<num_of_function_tested; j++){
    //         if (j > bias + 30 && j < bias + 45) cout << table[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    for (int i=0; i<outputs.size(); i++){
        auto table = pattern_controller(inputs, outputs[i], inputs_operand_bit, num_of_pattern);

        vector<int> cover = PQM(table, num_of_function_tested, num_of_pattern);
        for (int i=0; i<cover.size(); i++){
            vector<int> signs;

            // calc signs
            int index = cover[i];
            // cout << index << endl;
            for (int j=0; j<num_of_function_terms; j++){
                int sign = (index % 3) - 1;
                signs.push_back(sign);
                index /= 3;
            }

            // debug
            for (int sign: signs){
                cout << sign << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // graphReduction(found, circ_inputs, circ_outputs, inputs_operand_bit);
    bool write_complete = write_file(file_out_path, module_name, module_inputs, module_outputs, primary_inputs);

    // if (write_complete = true) {
    //     cout << "Write Completed" << endl;
    // }

    

    return 0;
}