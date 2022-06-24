#include <bits/stdc++.h>
#include "graph.h"
#include "netlist2graph.h"
#include <array>


using namespace std;


bool write_file(string file, string module_name, vector<tuple<string, int>> module_inputs, vector<tuple<string, int>> module_outputs, vector<tuple<string, Gate*>> primary_inputs) {
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
                                            make_pair("buf", "b"), 
                                            make_pair("++", "++")};
    vector<string> input_list;
    vector<string> output_list;
    int input_num = 0;
    int output_num = 0;
    for (auto input : module_inputs) {
        f << "input wire ";
        if (get<1>(input) == 1) {
            input_list.push_back(get<0>(input));
            input_num ++;
        }
        else if (get<1>(input) > 1) {
            for (int i=0; i<get<1>(input); i++) {
                input_list.push_back(get<0>(input) + "[" + to_string(i) + "]");
            }
            f << "[" << get<1>(input)-1 << ":0] ";
        }
        f << get<0>(input) << ";" << endl;
    }
    input_list.push_back("1'b0");
    input_list.push_back("1'b1");
    for (auto output : module_outputs) {
        f << "output wire ";
        if (get<1>(output) == 1) {
            output_list.push_back(get<0>(output));
            output_num ++;
        }
        else if (get<1>(output) > 1) {
            for (int i=0; i<get<1>(output); i++) {
                output_list.push_back(get<0>(output) + "[" + to_string(i) + "]");
            }
            f << "[" << get<1>(output)-1 << ":0] ";
        }
        f << get<0>(output) << ";" << endl;
    }
    
    vector<Gate *> gate_list;
    vector<string> wire_list;
    queue<Gate *> gate_queue;
    int gate_count = 0;
    for (auto input : primary_inputs) {
        // get<1>(input)->no = gate_count;
        // gate_count ++;
        for (int i=0; i<get<1>(input)->num_of_outputs(); i++) {
            for (int j=0; j<get<1>(input)->outputs[i].size(); j++) {
                if (get<0>(get<1>(input)->outputs[i][j])->traversal == 0) {
                    // get<0>(get<1>(input)->outputs[i][j])->no = gate_count;
                    gate_count ++;
                }
                get<0>(get<1>(input)->outputs[i][j])->traversal ++;
                if (get<0>(get<1>(input)->outputs[i][j])->traversal == get<0>(get<1>(input)->outputs[i][j])->num_of_inputs()) {
                    gate_list.push_back(get<0>(get<1>(input)->outputs[i][j]));
                    gate_queue.push(get<0>(get<1>(input)->outputs[i][j]));
                }
            }
        }
    }
    vector<long long int> term_vals;
    vector<vector<int>> func;
    if (module_inputs.size() == 2){
        // long long int tmp[] = {a, b, a*b, a*a, b*b, a*a*a, b*b*b};
        func = {{0}, {1}, {0, 1}, {0, 0}, {1, 1}, {0, 0, 0}, {1, 1, 1}};
    }
    else if (module_inputs.size() == 3){
        // long long int tmp[] = {a, b, c, a*b, b*c, c*a, a*a, b*b, c*c, a*b*c, a*a*a, b*b*b, c*c*c};
        func = {{0}, {1}, {2}, {0, 1}, {1, 2}, {0, 2}, {0, 0}, {1, 1}, {2, 2}, {0, 1, 2}, {0, 0, 0}, {1, 1, 1}, {2, 2, 2}};
    }
    else if (module_inputs.size() == 4){
        // long long int tmp[] = {a, b, c, d, a*b, a*c, a*d, b*c, b*d, c*d};
        func = {{0}, {1}, {2}, {3}, {0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}};
    }
    else if(module_inputs.size() == 5){
        // long long int tmp[] = {a, b, c, d, e, a*b, a*c, a*d, a*e, b*c, b*d, b*e, c*d, c*e, d*e};
        func = {{0}, {1}, {2}, {3}, {4}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}};
    }
    else{
        for (int i=0; i<module_inputs.size(); i++) {
            vector<int> tmp = {i};
            func.push_back(tmp);
        }
    }


    int wire_count = 0;
    int ctrl_count = 0;
    while (!gate_queue.empty()) {
        Gate* g = gate_queue.front();
        gate_queue.pop();

        // cout << g->gate_name << endl;
        // cout << wire_count << endl;
        // cout << g->gate_name;
        // for (int i=0; i<g->num_of_inputs(); i++) {
        //     cout << get<0>(g->inputs[i])->gate_name;
        // }
        // cout << "\n";

        // f << g->num_of_inputs() << " " << g->num_of_outputs() <<endl;
        // if (g->traversal == 0) {
            // g->no = gate_count;
            // gate_count ++;
        // }
        // cout << g->gate_name;
        string name = g->gate_name;
        vector<pair<string, string>>::iterator op_pair;
        string op;
        if (g->gate_name != "func" && g->gate_name != "buf") {
            op_pair = find_if(Gate_pair.begin(), Gate_pair.end(), [&name](pair<string, string> p){return p.first == name;});
            op = (*op_pair).second;
        }
        if (g->gate_name == "buf") {
            op = "buf_op";
        }
        if (ctrl_count == 0) {
            f << "assign " ;
            // TODO: a gate with many outputs
            if (g->gate_name == "func") {
                f << get<0>(g->outputs[0][0])->gate_name.substr(0, 4);
            }
            // if (g->outputs.size() > 1) f << "{";
            else {
                int output_count = 0;
                for (auto output : g->outputs) {
                    output_count ++;
                    if (output_count > 1) f << " , ";
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
                        f << get<0>(output[primary_output_fanout_idx])->gate_name;
                        g->out_wire_idx.push_back(get<0>(output[primary_output_fanout_idx])->gate_name);
                        for (int i=0; i<output.size(); i++) {
                            get<0>(output[i])->in_wire_idx.push_back(get<0>(output[primary_output_fanout_idx])->gate_name);
                        }
                    }
                    else {
                        f << "w" << wire_count;
                        g->out_wire_idx.push_back(to_string(wire_count));
                        for (int i=0; i<output.size(); i++) {
                            get<0>(output[i])->in_wire_idx.push_back(to_string(wire_count));
                        }
                        wire_count ++;
                    }
                }
            }
            // if (g->outputs.size() > 1) f << "} = ";
            f << " = ";
        }
        int tmp_count = 0;
        int input_count = 0;
        if (g->gate_name == "func") {
            // for (auto n : g->inputs_operand_bit) {
            //     f << "{";
            //     for (int i=0; i<n; i++) {
            //         f << get<0>(g->inputs[input_count+i])->gate_name;
            //         if (i != n-1) f << ", ";
            //     }
            //     f << "}";
            //     input_count += n;
            //     if (input_count < g->num_of_inputs()) f << " + ";
            //     else f << ";" << endl;
            // }
            
            if (g->c >= 0) {
                f << "(in" << g->c + 1 << " == " << g->ctrl_value << ") ? ";
                ctrl_count ++;
            }
            cout << "output functions" << endl;
            bool start = true;
            bool all_0 = true;
            for (int i=0; i<func.size(); i++) {
                // cout << "this is iteration " << i <<", sign is " << g->signs[i] << endl;
                if (g->signs[i] != 0) {
                    all_0 = false;
                    if (g->signs[i] == 1 && !start) f << " + ";
                    else if (g->signs[i] == -1) f << " - ";
                    for (int j=0; j<func[i].size(); j++) {
                        f << get<0>(module_inputs[func[i][j]]);
                        if (j < func[i].size() - 1){
                            f << " * ";
                        }
                    }
                    start = false;
                }
            }
            if (all_0) {
                f << g->constant_term;
            }
            else if (g->constant_term > 0) {
                f << " + " << g->constant_term;
            }
            else if (g->constant_term < 0) {
                f << " - " << -1 * g->constant_term;
            }
            if (g->c >= 0 && ctrl_count < 4) {
                f << ":" << endl;
            }
            else {
                f << ";" << endl;
            }
        }
        else {
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
            // cout << g->gate_name;
        }
    }
    if (wire_count > 0) {
        f << "wire ";
        for (int i=0; i<wire_count; i++) {
            f << "w" << i;
            if (i < wire_count-1) {
                f << ", ";
            }
        }
        f << ";" << endl;
    }

    f << "endmodule";
    f.close();
    return true;
}



