#include "find_ctrl.h"
#include "Pattern_controller.h"
#include "Compare_pattern.h"
#include "compare_pattern_ctrl.h"

vector<map<string, int>> find_ctrl(vector<vector<int>> functions, vector<Gate*> inputs, vector<Gate*> outputs, vector<int> inputs_operand_bit, int num_of_pattern) {

    bool** bool_table = new bool*[num_of_pattern];
    int pattern_len = inputs.size() - 2; // constant 0, 1 do not need pattern
    long long int constant_term = get_constant(inputs, outputs, inputs_operand_bit);

    vector<int>* column_signs;
    int num_of_columns;
    int num_of_function_terms;

    for (int i=0; i<num_of_pattern; i++){
        vector<int> pattern = pattern_generator(inputs_operand_bit);
        auto func_tuple = compare_pattern_ctrl(pattern, inputs, outputs, inputs_operand_bit, constant_term, functions);
        bool* bool_row = get<0>(func_tuple);
        column_signs = get<1>(func_tuple);
        num_of_columns = get<2>(func_tuple);

        bool_table[i] = bool_row;
        cout << "iteration " << i << endl;
    }


    vector<map<string, int>> dao;
    return dao;

}