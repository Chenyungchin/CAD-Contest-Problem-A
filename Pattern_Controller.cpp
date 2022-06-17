#include "Pattern_controller.h"
#include "Compare_pattern.h"

using namespace std;

vector<int> pattern_generator(vector<int> inputs_operand_bits){
    vector<int> pattern_vec;
    for (auto bit: inputs_operand_bits){
        int random_num = rand() % int(pow(2, bit));
        pattern_vec.push_back(random_num);
    }
    return pattern_vec;
}

// tuple<vector<bool>, vector<Gate*>, vector<Gate*>> 
tuple<bool**, vector<int>*, int, int> pattern_controller(vector<Gate*> primary_inputs, vector<Gate*> primary_outputs, vector<int> inputs_operand_bit, int num_of_pattern){
    // vector<Gate*> circ_inputs = primary_inputs;
    // vector<Gate*> circ_outputs = primary_outputs;

    // int num_of_pattern = 10;
    bool** bool_table = new bool*[num_of_pattern];

    int pattern_len = primary_inputs.size() - 2; // constant 0, 1 do not need pattern

    
    // get constant
    long long int constant_term = get_constant(primary_inputs, primary_outputs, inputs_operand_bit);
    cout << "constant term: " << constant_term << endl;

    auto column_info = get_column_info(inputs_operand_bit.size(), 4);    

    vector<int>* column_signs = get<0>(column_info);
    int num_of_columns = get<1>(column_info);
    cout << "num of columns: " << num_of_columns << endl;
    // int num_of_function_terms;

    for (int i=0; i<num_of_pattern; i++){
        vector<int> pattern = pattern_generator(inputs_operand_bit);
        // cout << "daodao" << endl;
        auto bool_row = compare_pattern(pattern, primary_inputs, primary_outputs, inputs_operand_bit, constant_term, column_signs, num_of_columns);

        bool_table[i] = bool_row;
        cout << "iteration " << i << endl;
    }


    return make_tuple(bool_table, column_signs, num_of_columns, constant_term);
    
    
    // while (1){
    //     long long int pattern_num = pow(2, circ_inputs.size());
    //     // int simulated_num = pattern_num;
    //     vector<int> pattern;

    //     // assume every function is valid at first (will be falsified later)
    //     for (int i=0; i<num_of_function_tested; i++) same_functions.push_back(1);

    //     for (int i=0; i<pattern_num; i++){
    //         pattern = pattern_generator(i, circ_inputs.size());
    //         vector<bool> same_value = compare_pattern(pattern, primary_inputs, primary_outputs, inputs_operand_bit);
    //         for (int j=0; j<num_of_function_tested; j++){
    //             same_functions[j] = same_functions[j] & same_value[j]; // if the pattern is inequivalent, falsify the corresponding function
    //         }
    //         // early return if every functions is falsified
    //         if (find(same_value.begin(), same_value.end(), 1) == same_value.end()){
    //             return make_tuple(same_functions, circ_inputs, circ_outputs);
    //         }
    //     }
        
    //     // for debugging
    //     return make_tuple(same_functions, circ_inputs, circ_outputs);
    //     // Todo: 測試不同的output bit數
    //     // Todo: 更新circ_inputs 和circ_outputs

        
    // }
    // // Todo: 如果最後都沒找到，回傳找不到
    // return make_tuple(same_functions, circ_inputs, circ_outputs);
}