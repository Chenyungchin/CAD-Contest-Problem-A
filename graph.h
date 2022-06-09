#ifndef GRAPH_H
#define GRAPH_H
#include <vector>

using namespace std;

class Gate{
public:
    vector<Gate*> inputs;
    vector<Gate*> outputs;
    string gate_name;
    int no; 
    int traversal;
    vector<int> in_wire_idx;
    vector<int> out_wire_idx;
    int num_of_inputs(){
        return inputs.size();
    };
    int num_of_outputs(){
        return outputs.size();
    }

    Gate(): inputs(0), outputs(0), gate_name("undefined"), no(-1), traversal(0){};
    Gate(string s): inputs(0), outputs(0), gate_name(s), no(-1), traversal(0){};
};

class Wire {
public:
    string wire_name;
    int wire_length;
    int no;

    Wire(): wire_name("undefined"), wire_length(1), no(-1){};
    Wire(string s): wire_name(s), wire_length(1), no(-1){};
};

#endif