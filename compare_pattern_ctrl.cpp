// #include <bits/stdc++.h>
// #include "graph.h"
#include "Compare_pattern_ctrl.h"
#include "Compare_pattern.h"


using namespace std;

tuple<bool*, vector<int>*, int> compare_pattern_ctrl(vector<int> pattern_vec, vector<Gate*> inputs, vector<Gate*> outputs, vector<int> inputs_operand_bit, long long int constant_term, vector<vector<int>> functions){

    int bit_cnt = 0;
    for (int i=0; i<pattern_vec.size(); i++){
        int rand_num = pattern_vec[i];
        int bit_num = inputs_operand_bit[i];
        for (int j=0; j<bit_num; j++){
            inputs[bit_cnt + j]->value = rand_num % 2;
            rand_num /= 2;
        }
        bit_cnt += bit_num;
    }

    // calc gate value by top down DP from output
    long long int output_circuit = 0;
    int bit = 0;
    for (auto outp: outputs){
        string port_name = outp->gate_name;
        // int bit = stoi(port_name.substr(port_name.find('[') + 1, port_name.find(']') - port_name.find('[') - 1));
        int gate_val = get_gate_value(outp);

        output_circuit += gate_val * pow(2, bit);
        bit ++;
    }


    // reset gate values
    for (auto outp: outputs){
        reset_gate_value(outp);
    }


    int num_of_inputs = inputs_operand_bit.size();

    auto func_tuple = simulated_function_ctrl(pattern_vec, output_circuit, num_of_inputs, outputs.size(), constant_term, functions, 4);

    return func_tuple;
}

tuple<bool*, vector<int>*, int> simulated_function_ctrl(vector<int> words, long long int output_circuit, int num_of_inputs, int num_of_output_bit, long long int constant_term, vector<vector<int>> functions, int max_nonzero_term=5){
    int MAX_NUM_OF_COLUMN = 100;
    vector<long long int> term_vals;
    if (num_of_inputs == 2){
        int a = words[0];
        int b = words[1];
        long long int tmp[] = {a, b, a*b, a*a, b*b, a*a*a, b*b*b};
        for (auto term: tmp){
            term_vals.push_back(term);
        }
    }
    else if (num_of_inputs == 3){
        int a = words[0];
        int b = words[1];
        int c = words[2];
        long long int tmp[] = {a, b, c, a*b, b*c, c*a, a*a, b*b, c*c, a*b*c, a*a*a, b*b*b, c*c*c};
        for (auto term: tmp){
            term_vals.push_back(term);
        }
    }
    else if (num_of_inputs == 4){
        int a = words[0];
        int b = words[1];
        int c = words[2];
        int d = words[3];
        long long int tmp[] = {a, b, c, d, a*b, a*c, a*d, b*c, b*d, c*d};
        for (auto term: tmp){
            term_vals.push_back(term);
        }
    }
    else if(num_of_inputs == 5){
        int a = words[0];
        int b = words[1];
        int c = words[2];
        int d = words[3];
        int e = words[4];
        // long long int tmp[] = {a, b, c, d, e, a*b, a*c, a*d, a*e, b*c, b*d, b*e};
        long long int tmp[] = {a, b, c, d, e, a*b, a*c, a*d, a*e, b*c, b*d, b*e, c*d, c*e, d*e};
        for (auto term: tmp){
            term_vals.push_back(term);
        }
    }
    else{
        for (auto word: words){
            term_vals.push_back(word);
        }
    }
    // cout << "hi1" << endl;
    int num_of_function_terms = term_vals.size();


    bool* bool_row = new bool[MAX_NUM_OF_COLUMN];
    long long int mod_num = pow(2, (num_of_output_bit));
    // cout << mod_num << endl;
    
    long long int num_of_function_tested = functions.size();
    // cout << "this much: " << num_of_function_tested << endl;
    int table_column_id = 0;
    vector<int>* column_signs = new vector<int>[MAX_NUM_OF_COLUMN];

    for (long long int i=0; i<num_of_function_tested; i++){
        // if (i % 1000000 == 0) cout << i << endl;
        vector<int> signs = functions[i];

        // calc function values
        long long int func_val = constant_term;
        for (int j=0; j<num_of_function_terms; j++){
            func_val += term_vals[j] * signs[j];
        }

        // check equivalence
        long long int func_val_mod = func_val % mod_num;
        if (func_val_mod < 0) func_val_mod += mod_num;
        bool_row[table_column_id] = (output_circuit == func_val_mod);
        column_signs[table_column_id] = signs;
        table_column_id ++;
    }


    // for (int i=0; i<num_of_function_tested; i++) cout << bool_row[i] << " ";
    // cout << endl;

    return make_tuple(bool_row, column_signs, table_column_id);
}

