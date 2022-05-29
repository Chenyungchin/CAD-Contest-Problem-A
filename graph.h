#include <vector>

using namespace std;

class Gate{
public:
    vector<Gate*> inputs;
    vector<Gate*> outputs;
    string gate_name;
    int num_of_inputs(){
        return inputs.size();
    };
    int num_of_outputs(){
        return outputs.size();
    }

    Gate(): inputs(0), outputs(0), gate_name("undefined"){};
    Gate(string s): inputs(0), outputs(0), gate_name(s){};
};