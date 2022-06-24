#include "deleteBuf.h"

using namespace std;

void deleteBuf(vector<tuple<string, Gate *>> primary_inputs, vector<tuple<string, Gate *>> primary_outputs) {
    vector<string> output_list;
    for (auto output : primary_outputs) {
        output_list.push_back(get<0>(output));
    }
    
    int buf_count = 0;

    queue<Gate *> gate_queue;
    vector<int> visited_gate;

    for (auto input : primary_inputs) {
        for (int i=0; i<get<1>(input)->num_of_outputs(); i++) {
            for (int j=0; j<get<1>(input)->outputs[i].size(); j++) {
                if (find(visited_gate.begin(), visited_gate.end(), get<0>(get<1>(input)->outputs[i][j])->no) == visited_gate.end())
                    gate_queue.push(get<0>(get<1>(input)->outputs[i][j]));
                    visited_gate.push_back(get<0>(get<1>(input)->outputs[i][j])->no);
            }
        }
    }

    while (!gate_queue.empty()) {
        Gate* g = gate_queue.front();
        gate_queue.pop();

        for (auto output : g->outputs) {
            for (int i=0; i<output.size(); i++) {
                // if (find(output_list.begin(), output_list.end(), get<0>(output[i])->gate_name) != output_list.end()) {
                //     continue;
                // }
                // else {
                if (find(visited_gate.begin(), visited_gate.end(), get<0>(output[i])->no) == visited_gate.end()) {
                    gate_queue.push(get<0>(output[i]));
                    visited_gate.push_back(get<0>(output[i])->no);
                }
                // }
            }
        }
        if (g->gate_name == "buf") {
            buf_count ++;
            bool dont_delete = false;
            for (auto out : g->outputs) {
                if (get<0>(out[0])->gate_name.substr(0, 3) == "out") {
                    dont_delete = true;
                }
            }
            if (dont_delete) break;
            Gate* g_in = get<0>(g->inputs[0]);
            int g_in_index = get<1>(g->inputs[0]);
            vector<vector<tuple<Gate*, int>>> g_in_outputs_new;
            for (int i=0; i<g_in->num_of_outputs(); i++) {
                if (i != g_in_index) {
                    g_in_outputs_new.push_back(g_in->outputs[i]);
                }
                else {
                    g_in_outputs_new.push_back({});
                }
            }
            for (auto output : g->outputs[0]) {
                Gate* g_out = get<0>(output);
                int g_out_index = get<1>(output);
                g_out->inputs[g_out_index] = make_tuple(g_in, g_in_index);
                g_in_outputs_new[g_in_index].push_back(make_tuple(g_out, g_out_index));
            }
            g_in->outputs = g_in_outputs_new;
        }
    }    
    cout << "deleted buf count: " << buf_count << endl;

}