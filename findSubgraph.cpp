#include "findSubgraph.h"

using namespace std;

vector<Gate *> findSubgraph(vector<Gate *> input_gate, vector<tuple<string, Gate *>> primary_inputs, vector<tuple<string, Gate *>> primary_outputs) {
    // vector<Gate *> subgraph_input_gate;
    vector<Gate *> output_gate;
    queue<Gate *> gate_queue;
    vector<string> field;
    for (auto in : input_gate) {
        // cout << "in_gate: " << in->gate_name << endl;
        for (auto fanin : in->transitive_fanin) {
            field.push_back(fanin);
            // cout << "field: " << fanin << endl;
        }
    }
    for (auto input : primary_inputs) {
        Gate* g = get<1>(input);
        bool in_subgraph = true;
        for (auto f : g->transitive_fanin) {
            if (find(field.begin(), field.end(), f) == field.end()) {
                in_subgraph = false;
            }
        }
        if (in_subgraph) {
            gate_queue.push(g);
            // cout << "primary input: " << g->gate_name << endl;
        }
    }

    while (!gate_queue.empty()) {
        Gate* g = gate_queue.front();
        gate_queue.pop();
        for (auto output : g->outputs) {
            for (auto fanout : output) {
                bool in_subgraph = true;
                for (auto f : get<0>(fanout)->transitive_fanin)
                    if (find(field.begin(), field.end(), f) == field.end()) {
                        in_subgraph = false;
                    }
                if (in_subgraph) {
                    gate_queue.push(get<0>(fanout));
                }
                else {
                    if (find(output_gate.begin(), output_gate.end(), g) == output_gate.end()) {
                        output_gate.push_back(g);
                    }
                }
            }
        }

    }

    return output_gate;
}
