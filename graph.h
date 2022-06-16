#ifndef GRAPH_H
#define GRAPH_H
#include <vector>

using namespace std;

class Gate{
public:
    vector<tuple<Gate*, int>> inputs;
    vector<vector<tuple<Gate*, int>>> outputs;
    string gate_name;
    vector<int> inputs_operand_bit;
    int no; 
    int traversal;
    int value;
    vector<string> transitive_fanin;
    vector<string> in_wire_idx;
    vector<string> out_wire_idx; // Can be a number (of wire) or a output wire name
    vector<int> signs;
    int num_of_inputs(){
        return inputs.size();
    };
    int num_of_outputs(){
        return outputs.size();
    }

    Gate(): inputs(0), outputs(0), gate_name("undefined"), no(-1), traversal(0), value(-1), transitive_fanin(0){};
    Gate(string s): inputs(0), outputs(0), gate_name(s), no(-1), traversal(0), value(-1), transitive_fanin(0){};
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