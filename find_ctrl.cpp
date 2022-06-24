#include "find_ctrl.h"
#include "Pattern_controller.h"
#include "Compare_pattern.h"
#include "compare_pattern_ctrl.h"

vector<vector<tuple<int, int>>> find_ctrl(vector<vector<int>> functions, vector<Gate*> inputs, vector<Gate*> outputs, vector<int> inputs_operand_bit, int num_of_pattern, vector<int> ctrl) {

    bool** bool_table = new bool*[num_of_pattern];
    int pattern_len = inputs.size() - 2; // constant 0, 1 do not need pattern
    long long int constant_term = get_constant(inputs, outputs, inputs_operand_bit);

    vector<int>* column_signs;
    int num_of_columns;
    int num_of_function_terms;

    vector<vector<int>> ctrl_pattern;
    for (int c=0; c<ctrl.size(); c++) {
        ctrl_pattern.push_back({});
    }
    for (int i=0; i<num_of_pattern; i++){
        vector<int> pattern = pattern_generator(inputs_operand_bit);
        for (int c=0; c<ctrl.size(); c++) {
            ctrl_pattern[c].push_back(pattern[ctrl[c]]);
        }
        auto func_tuple = compare_pattern_ctrl(pattern, inputs, outputs, inputs_operand_bit, constant_term, functions);
        bool* bool_row = get<0>(func_tuple);
        column_signs = get<1>(func_tuple);
        num_of_columns = get<2>(func_tuple);

        bool_table[i] = bool_row;
        // cout << "iteration " << i << endl;
    }

    vector<vector<tuple<int, int>>> dao;
    vector<vector<int>> ctrl_var;
    vector<vector<int>> ctrl_func;
    for (int c=0; c<ctrl.size(); c++) {
        dao.push_back({});
        ctrl_var.push_back({});
        ctrl_func.push_back({});
    }
    for (int i=0; i<functions.size(); i++) {
        for (int j=0; j<num_of_pattern; j++) {
            // cout << bool_table[j][i] << " ";
            for (int c=0; c<ctrl.size(); c++) {
                if (bool_table[j][i]) {
                    if (find(ctrl_var[c].begin(), ctrl_var[c].end(), ctrl_pattern[c][j]) == ctrl_var[c].end()) {
                        ctrl_var[c].push_back(ctrl_pattern[c][j]);
                        ctrl_func[c].push_back(i);
                        cout << "push ctrl: " << ctrl_pattern[c][j] << endl;
                        cout << "push func: " << i << endl;
                    }
                } 
            }
        }
        // cout << endl;
    }
    
    for (int c=0; c<ctrl.size(); c++) {
        for (int i=0; i<ctrl_var[c].size(); i++) {
            dao[c].push_back(make_tuple(ctrl_var[c][i], ctrl_func[c][i]));
            cout << ctrl_var[c][i] << " " << ctrl_func[c][i] << endl;
        }
    }



    return dao;

}