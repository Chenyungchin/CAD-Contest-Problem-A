#include "deleteNot.h"

using namespace std;


void deleteNot(map<string, Gate *> primary_inputs, map<string, Gate *> primary_outputs) {
    vector<string> output_list;
    for (auto output : primary_outputs) {
        output_list.push_back(output.first);
    }
    
    int buf_count = 0;

    queue<Gate *> gate_queue;
    vector<int> visited_gate;

    for (auto input : primary_inputs) {
        for (int i=0; i<input.second->num_of_outputs(); i++) {
            for (int j=0; j<input.second->outputs[i].size(); j++) {
                if (find(visited_gate.begin(), visited_gate.end(), get<0>(input.second->outputs[i][j])->no) == visited_gate.end())
                    gate_queue.push(get<0>(input.second->outputs[i][j]));
                    visited_gate.push_back(get<0>(input.second->outputs[i][j])->no);
            }
        }
    }

    int dummy_not_count = 0;
    int gate_count = 0;
    while (!gate_queue.empty()) {
        gate_count ++;
        Gate* g = gate_queue.front();
        gate_queue.pop();

        // cout << g->gate_name <<endl;
        bool dummy_not = true;
        // for (int i=0; i<g->num_of_inputs(); i++){
        //     cout << get<0>(g->inputs[i])->gate_name << " " << get<0>(g->inputs[i])->outputs[0].size() << endl;
        // }

        if (g->gate_name == "not") {
            for (auto output : g->outputs[0]) {
                if (get<0>(output)->gate_name != "not") {
                    dummy_not = false;
                    // cout << get<0>(output)->gate_name << endl;
                }
            }
            if (dummy_not) {
                // cout << "fuck" << endl;
                Gate* g_in = get<0>(g->inputs[0]);
                int g_in_index = get<1>(g->inputs[0]);
                vector<vector<tuple<Gate*, int>>> g_in_outputs_new;
                for (int i=0; i<g_in->num_of_outputs(); i++) {
                    // cout << "i " << i << endl;
                    if (i != g_in_index) {
                        g_in_outputs_new.push_back(g_in->outputs[i]);
                    }
                    else {
                        g_in_outputs_new.push_back({});
                        for (int j=0; j<g_in->outputs[i].size(); j++) {
                            // cout << "j " << j << endl;
                            if (get<0>(g_in->outputs[i][j]) != g) {        
                                // cout << "hi" << endl;
                                g_in_outputs_new[i].push_back(g_in->outputs[i][j]);
                            }
                        }
                    }
                }
                for (auto output1 : g->outputs[0]) {
                    for (auto output2 : get<0>(output1)->outputs[0]) {
                        dummy_not_count ++;
                        Gate* g_out = get<0>(output2);
                        int g_out_index = get<1>(output2);
                        g_out->inputs[g_out_index] = make_tuple(g_in, g_in_index);
                        g_in_outputs_new[g_in_index].push_back(make_tuple(g_out, g_out_index));

                        if (find(visited_gate.begin(), visited_gate.end(), g_out->no) == visited_gate.end()) {
                            gate_queue.push(g_out);
                            visited_gate.push_back(g_out->no);
                        }
                    }
                }
                g_in->outputs = g_in_outputs_new;
            }
        }        

        if (g->gate_name != "not" || !dummy_not) {
            for (auto output : g->outputs) {
                for (int i=0; i<output.size(); i++) {
                    if (find(visited_gate.begin(), visited_gate.end(), get<0>(output[i])->no) == visited_gate.end()) {
                        gate_queue.push(get<0>(output[i]));
                        visited_gate.push_back(get<0>(output[i])->no);
                    }
                }
            }
        }

    }
    cout << "dummy not count: " << dummy_not_count << endl;
    // cout << "gate count: " << gate_count <<endl;

}