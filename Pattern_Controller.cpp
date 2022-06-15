#include "Pattern_controller.h"
#include "Compare_pattern.h"

using namespace std;

vector<int> pattern_generator(int pattern, int bit){
    vector<int> pattern_vec;
    for (int i=0; i<bit; i++){
        pattern_vec.push_back(pattern % 2);
        pattern /= 2;
    }
    return pattern_vec;
}

tuple<vector<bool>, vector<Gate*>, vector<Gate*>> pattern_controller(vector<Gate*> primary_inputs, vector<Gate*> primary_outputs, vector<int> inputs_operand_bit){
    vector<Gate*> circ_inputs = primary_inputs;
    vector<Gate*> circ_outputs = primary_outputs;

    
    // ====== verify which pattern align with the circuit output ======
    int num_of_function_tested = 2;
    vector<bool> same_functions; // adder_tree, mult
    
    
    while (1){
        long long int pattern_num = pow(2, circ_inputs.size());
        // int simulated_num = pattern_num;
        vector<int> pattern;

        // assume every function is valid at first (will be falsified later)
        for (int i=0; i<num_of_function_tested; i++) same_functions.push_back(1);

        for (int i=0; i<pattern_num; i++){
            pattern = pattern_generator(i, circ_inputs.size());
            vector<bool> same_value = compare_pattern(pattern, primary_inputs, primary_outputs, inputs_operand_bit);
            for (int j=0; j<num_of_function_tested; j++){
                same_functions[j] = same_functions[j] & same_value[j]; // if the pattern is inequivalent, falsify the corresponding function
            }
            // early return if every functions is falsified
            if (find(same_value.begin(), same_value.end(), 1) == same_value.end()){
                return make_tuple(same_functions, circ_inputs, circ_outputs);
            }
        }
        
        // for debugging
        return make_tuple(same_functions, circ_inputs, circ_outputs);
        // Todo: 測試不同的output bit數
        // Todo: 更新circ_inputs 和circ_outputs

        
    }
    // Todo: 如果最後都沒找到，回傳找不到
    return make_tuple(same_functions, circ_inputs, circ_outputs);
}