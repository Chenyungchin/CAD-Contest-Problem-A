#include "findSubgraph.h"

using namespace std;

tuple<vector<Gate *>, vector<Gate *>> findSubgraph(vector<int> input_name, map<string, Gate *> primary_inputs, map<string, Gate *> primary_outputs) {
    vector<Gate *> subgraph_input_gate;
    vector<Gate *> subgraph_output_gate;
    for (auto output : primary_outputs) {
        
    }




    return make_tuple(subgraph_input_gate, subgraph_output_gate);
}