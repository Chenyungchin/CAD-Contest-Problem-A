#include <bits/stdc++.h>
#include "graph.h"
#include "netlist2graph.h"
#include <array>


using namespace std;


bool write_file(string file, string module_name, map<string, int> module_inputs, map<string, int> module_outputs, map<string, Gate *> primary_inputs) {
    fstream f;
    f.open(file, ios::out | ios::trunc);
    f << module_name << endl;

    vector<pair<string, string>> Gate_pair{ make_pair("not", "~"), 
                                            make_pair("and", "&"), 
                                            make_pair("or", "|"), 
                                            make_pair("nand", "~&"), 
                                            make_pair("nor", "~|"), 
                                            make_pair("xor", "^"), 
                                            make_pair("xnor", "~^"), 
                                            make_pair("buf", "fuck")};
    vector<string> input_list;
    vector<string> output_list;
    int input_num = 0;
    int output_num = 0;
    for (auto input : module_inputs) {
        f << "input wire ";
        if (input.second == 1) {
            input_list.push_back(input.first);
            input_num ++;
        }
        else if (input.second > 1) {
            for (int i=0; i<input.second; i++) {
                input_list.push_back(input.first + "[" + to_string(i) + "]");
            }
            f << "[" << input.second-1 << ":0] ";
        }
        f << input.first << ";" << endl;
    }
    for (auto output : module_outputs) {
        f << "output wire ";
        if (output.second == 1) {
            output_list.push_back(output.first);
            output_num ++;
        }
        else if (output.second > 1) {
            for (int i=0; i<output.second; i++) {
                output_list.push_back(output.first + "[" + to_string(i) + "]");
            }
            f << "[" << output.second-1 << ":0] ";
        }
        f << output.first << ";" << endl;
    }
    
    vector<Gate *> gate_list;
    vector<string> wire_list;
    queue<Gate *> gate_queue;
    int gate_count = 0;
    for (auto input : primary_inputs) {
        // input.second->no = gate_count;
        // gate_count ++;
        for (int i=0; i<input.second->num_of_outputs(); i++) {
            for (int j=0; j<input.second->outputs[i].size(); j++) {
                if (get<0>(input.second->outputs[i][j])->traversal == 0) {
                    // get<0>(input.second->outputs[i][j])->no = gate_count;
                    gate_count ++;
                }
                get<0>(input.second->outputs[i][j])->traversal ++;
                if (get<0>(input.second->outputs[i][j])->traversal == get<0>(input.second->outputs[i][j])->num_of_inputs()) {
                    gate_list.push_back(get<0>(input.second->outputs[i][j]));
                    gate_queue.push(get<0>(input.second->outputs[i][j]));
                }
            }
        }
    }

    int wire_count = 0;
    while (!gate_queue.empty()) {
        Gate* g = gate_queue.front();
        gate_queue.pop();

        // cout << wire_count << endl;
        // cout << g->gate_name;
        // for (int i=0; i<g->num_of_inputs(); i++) {
        //     cout << get<1>(g->inputs[i]);
        // }
        // cout << "\n";

        // f << g->num_of_inputs() << " " << g->num_of_outputs() << " ";
        if (g->traversal == 0) {
            // g->no = gate_count;
            gate_count ++;
        }
        // f << g->gate_name << " g" << g->no << "(";
        string name = g->gate_name;
        vector<pair<string, string>>::iterator op_pair = find_if(Gate_pair.begin(), Gate_pair.end(), [&name](pair<string, string> p){return p.first == name;});
        string op = (*op_pair).second;

        
        f << "assign " ;
        // TODO: a gate with many outputs
        for (auto output : g->outputs) {
            bool in_output_list = false; // Check if there's a fanout is primary output
            int primary_output_fanout_idx;
            for (int i=0; i<output.size(); i++) {
                if (find(output_list.begin(), output_list.end(), get<0>(output[i])->gate_name) != output_list.end()) {
                    in_output_list = true;
                    primary_output_fanout_idx = i;
                }
                else {
                    get<0>(output[i])->traversal ++;
                }
                if (get<0>(output[i])->traversal == get<0>(output[i])->num_of_inputs()) {
                    gate_queue.push(get<0>(output[i]));
                }
            }
            if (in_output_list) {
                f << get<0>(output[primary_output_fanout_idx])->gate_name << " = ";
                g->out_wire_idx.push_back(get<0>(output[primary_output_fanout_idx])->gate_name);
                for (int i=0; i<output.size(); i++) {
                    get<0>(output[i])->in_wire_idx.push_back(get<0>(output[primary_output_fanout_idx])->gate_name);
                }
            }
            else {
                f << "w" << wire_count << " = ";
                g->out_wire_idx.push_back(to_string(wire_count));
                for (int i=0; i<output.size(); i++) {
                    get<0>(output[i])->in_wire_idx.push_back(to_string(wire_count));
                }
                wire_count ++;
            }
        }
        int tmp_count = 0;
        int input_count = 0;
        for (auto input: g->inputs) {
            if (op == "~") {
                f << op;
            }
            if (find(input_list.begin(), input_list.end(), get<0>(input)->gate_name) != input_list.end()) {
                f << get<0>(input)->gate_name;
            }
            else {
                f << "w" << g->in_wire_idx[tmp_count];
                tmp_count ++;
            }
            input_count ++;
            if (input_count != g->num_of_inputs()) {
                f << " " << op << " ";
            }
            else {
                // f << ");" << endl;
                f << ";" << endl;
            }
        }
    }

    f << "wire ";
    for (int i=0; i<wire_count; i++) {
        f << "w" << i;
        if (i < wire_count-1) {
            f << ", ";
        }
    }
    f << ";" << endl;

    f << "endmodule";
    f.close();
    return true;
}



