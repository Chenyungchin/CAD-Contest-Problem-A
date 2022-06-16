#include "SubCircuitEC.h"

using namespace std;

string std_library[] = {"and", "or", "nand", "nor", "not", "buf", "xor", "xnor"};

void construct_transitive_fanin(Gate* gate){
    vector<string> transitive_fanin;
    if (find(begin(std_library), end(std_library), gate->gate_name) == end(std_library)){
        if (gate->transitive_fanin.empty()) return;
        string input_name = gate->gate_name;
        if (input_name.find('[') != string::npos){
            input_name = input_name.substr(0, input_name.find('[') - 1);
        }
        transitive_fanin.push_back(input_name);
        return;
    }
    for (auto inp: gate->inputs){
        for (auto tf: get<0>(inp)->transitive_fanin){
            if (find(transitive_fanin.begin(), transitive_fanin.end(), tf) == transitive_fanin.end()){
                transitive_fanin.push_back(tf);
            }
        }
    }
    gate->transitive_fanin = transitive_fanin;
}