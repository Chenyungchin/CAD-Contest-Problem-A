#include <bits/stdc++.h>
#include "graph.h"
#include "netlist2graph.h"
#include <array>


using namespace std;

bool write_file(string file, string module_name, map<string, int> module_inputs, map<string, int> module_outputs, map<string, Gate *> primary_inputs) {
    fstream f;
    f.open(file, ios::out | ios::trunc);
    f << module_name << endl ;
    
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
            if (input.second->outputs[i]->no < 0) {
                input.second->outputs[i]->no = gate_count;
                gate_count ++;
            }
            input.second->outputs[i]->traversal ++;
            if (input.second->outputs[i]->traversal == input.second->outputs[i]->num_of_inputs()) {
                gate_list.push_back(input.second->outputs[i]);
                gate_queue.push(input.second->outputs[i]);
            }
        }
    }

    int wire_count = 0;
    while (!gate_queue.empty()) {
        Gate* g = gate_queue.front();
        gate_queue.pop();
        // f << g->num_of_inputs() << " " << g->num_of_outputs() << " ";
        if (g->no < 0) {
            g->no = gate_count;
            gate_count ++;
        }
        f << g->gate_name << " g" << g->no << "(";
        for (auto output : g->outputs) {
            if (find(output_list.begin(), output_list.end(), output->gate_name) != output_list.end()) {
                f << output->gate_name << ", ";
            }
            else {
                output->traversal ++;
                output->in_wire_idx.push_back(wire_count);
                g->out_wire_idx.push_back(wire_count);
                f << "w" << wire_count << ", ";
                wire_count ++;
            }
            if (output->traversal == output->num_of_inputs()) {
                gate_queue.push(output);
            }
        }
        int tmp_count = 0;
        int input_count = 0;
        for (auto input: g->inputs) {
            if (find(input_list.begin(), input_list.end(), input->gate_name) != input_list.end()) {
                f << input->gate_name;
            }
            else {
                f << "w" << g->in_wire_idx[tmp_count];
                tmp_count ++;
            }
            input_count ++;
            if (input_count != g->num_of_inputs()) {
                f << ", ";
            }
            else {
                f << ");" << endl;
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




// int main() {

//     string file_path = "full_adder.v";
//     string module_name;
//     map<string, int> module_inputs;
//     map<string, int> module_outputs;
//     map<string, Gate *> primary_inputs = read_file(file_path, &module_name, &module_inputs, &module_outputs);
//     cout << module_name << endl;
//     for (auto input : module_inputs) {
//         cout << input.first << " " << input.second << endl;
//     }
//     for (auto output : module_outputs) {
//         cout << output.first << " " << output.second << endl;
//     }
//     for (auto input : primary_inputs) {
//         cout << input.first << " " << input.second->gate_name << " ";
//         cout << input.second->num_of_inputs() << " " <<  input.second->num_of_outputs() << endl;
//     }

//     bool write_complete = write_file(file_path, module_name, module_inputs, module_outputs, primary_inputs);

//     if (write_complete = true) {
//         cout << "Write in completed" << endl;
//     }

//     return 0;
// }