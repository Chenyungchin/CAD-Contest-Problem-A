#include "SubCircuitEC.h"

using namespace std;

string std_library[] = {"and", "or", "nand", "nor", "not", "buf", "xor", "xnor"};

vector<string> construct_transitive_fanin(Gate* gate, bool Is_Output){
    if (!gate->transitive_fanin.empty()) return gate->transitive_fanin;
    vector<string> transitive_fanin;
    // base case
    if (!Is_Output && find(begin(std_library), end(std_library), gate->gate_name) == end(std_library)){
        string input_name = gate->gate_name;
        // cout << input_name << endl;
        if (input_name.find('[') != string::npos){
            input_name = input_name.substr(0, input_name.find('['));
        }
        transitive_fanin.push_back(input_name);
        gate->transitive_fanin = transitive_fanin;
        // cout << input_name << endl;
        return transitive_fanin;
    }
    // recursive
    for (auto inp: gate->inputs){
        vector<string> tf = construct_transitive_fanin(get<0>(inp), 0);
        for (auto in: tf){
            if (find(transitive_fanin.begin(), transitive_fanin.end(), in) == transitive_fanin.end()){
                transitive_fanin.push_back(in);
            }
        }
    }
    gate->transitive_fanin = transitive_fanin;
    return transitive_fanin;
}