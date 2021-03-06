// #include <bits/stdc++.h>
// #include "graph.h"
#include "Compare_pattern.h"


using namespace std;

long long int get_constant(vector<Gate*> inputs, vector<Gate*> outputs, vector<int> inputs_operand_bit){
    // stream in the given pattern
    int const_gate = 0;
    for (int i=0; i<inputs.size(); i++){
        if (inputs[i]->gate_name == "1'b0" || inputs[i]->gate_name == "1'b1"){
            const_gate += 1;
        }
        else{
            inputs[i]->value = 0;
        }
    }

    // calc gate value by top down DP from output
    long long int output_circuit = 0;
    // int bit = 0;
    for (int i=0; i<outputs.size(); i++){
        auto outp = outputs[i];
        string port_name = outp->gate_name;
        // cout << port_name << " ";
        // int bit = stoi(port_name.substr(port_name.find('[') + 1, port_name.find(']') - port_name.find('[') - 1));
        int gate_val = get_gate_value(outp);
        // cout << gate_val << " ";
        
        output_circuit += gate_val * pow(2, i);
        // cout << "iteration " << i << " : " <<  output_circuit << endl;
        // bit ++;
    }
    // cout << endl;
    
    cout << output_circuit << endl;

    // reset gate values
    for (auto outp: outputs){
        reset_gate_value(outp);
    }

    return output_circuit;
}


bool* compare_pattern(vector<int> pattern_vec, vector<Gate*> inputs, vector<Gate*> outputs, vector<int> inputs_operand_bit, long long int constant_term, vector<int>* column_signs, int num_of_columns){
    // ==== traversing the graph to get output ====
    // stream in the given pattern
    // int const_gate = 0;
    // for (int i=0; i<inputs.size(); i++){
    //     if (inputs[i]->gate_name == "1'b0" || inputs[i]->gate_name == "1'b1"){
    //         const_gate += 1;
    //     }
    //     else{
    //         inputs[i]->value = rand_num_cp % 2;
    //         rand_num_cp /= 2;
    //     }
    // }

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


    // vector<int> output_vals;
    // for (auto outp: outputs){
    //     int gate_val = get_gate_value(outp);
    //     output_vals.push_back(gate_val);
    // }
    // int output_circuit = 0;
    // int k = 1;
    // for (auto outp: output_vals){
    //     // cout << outp << endl;
    //     output_circuit += outp * k;
    //     k *= 2;
    // }

    // reset gate values
    for (auto outp: outputs){
        reset_gate_value(outp);
    }

    // // debug
    // for (auto val: pattern) cout << val << " ";
    // cout << endl;


    // cout << "circuit: " << output_dec << endl;

    // ==== calculate output using the formula ====
    // vector<int> words = pattern_vec;
    // long long int word = 0;
    // int tmp = 1;
    // int start_index = 0;
    // for (auto bits: inputs_operand_bit){
    //     // calc word val
    //     word = (random_number % int(pow(2, start_index+bits))) / int(pow(2, start_index));
    //     // for (int i=start_index; i<start_index+bits; i++){
    //     //     word += pattern[i] * tmp;
    //     //     tmp *= 2;
    //     // }
    //     words.push_back(word);
    //     tmp = 1;
    //     word = 0;
    //     start_index += bits;
    // }

    // // debug
    // for (auto val: words) cout << val << " ";
    // cout << endl;

    int num_of_inputs = inputs_operand_bit.size();

    auto func_tuple = simulated_function(pattern_vec, output_circuit, num_of_inputs, outputs.size(), constant_term, 4, column_signs, num_of_columns);
    // bool* bool_row = get<0>(func_tuple);
    // vector<int>* column_signs = get<1>(func_tuple);
    // int num_of_columns = get<2>(func_tuple);

    return func_tuple;


    // // now only 2 or 3 inputs are considered
    // int num_of_function_terms = (num_of_inputs == 2) ? 5 :
    //                             (num_of_inputs == 3) ? 10 : 
    //                             (num_of_inputs == 4) ? 10 : num_of_inputs;
    // int num_of_function_tested = pow(3, num_of_function_terms);

    // vector<int> term_vals;
    
    // if (num_of_inputs == 2){
    //     int a = words[0];
    //     int b = words[1];
    //     int tmp[num_of_function_terms] = {a, b, a*b, a*a, b*b};
    //     for (auto term: tmp){
    //         term_vals.push_back(term);
    //     }
    // }
    // else if (num_of_inputs == 3){
    //     int a = words[0];
    //     int b = words[1];
    //     int c = words[2];
    //     int tmp[num_of_function_terms] = {a, b, c, a*b, b*c, c*a, a*a, b*b, c*c, a*b*c};
    //     for (auto term: tmp){
    //         term_vals.push_back(term);
    //     }
    // }
    // else if (num_of_inputs == 4){
    //     int a = words[0];
    //     int b = words[1];
    //     int c = words[2];
    //     int d = words[3];
    //     int tmp[num_of_function_terms] = {a, b, c, d, a*b, a*c, a*d, b*c, b*d, c*d};
    //     for (auto term: tmp){
    //         term_vals.push_back(term);
    //     }
    // }
    // else{
    //     for (auto word: words){
    //         term_vals.push_back(word);
    //     }
    // }

    // bool* bool_row = new bool[num_of_function_tested];
    // int mod_num = pow(2, (outputs.size()));
    // // cout << mod_num << endl;
    

    // for (int i=0; i<num_of_function_tested; i++){
    //     vector<int> signs;

    //     // calc signs
    //     int index = i;
    //     for (int j=0; j<num_of_function_terms; j++){
    //         int sign = (index % 3) - 1;
    //         signs.push_back(sign);
    //         index /= 3;
    //     }

    //     // calc function values
    //     int func_val = constant_term;
    //     for (int j=0; j<num_of_function_terms; j++){
    //         func_val += term_vals[j] * signs[j];
    //     }

    //     // check equivalence
    //     bool_row[i] = (output_circuit == (func_val % mod_num));

    //     // int bias = 29524; // for num_of_inputs == 10
    //     // if (i == bias){
    //     //     cout << "==============" << i << "=============" << endl;
    //     //     cout << endl;
    //     //     cout << output_circuit << " " << (func_val % mod_num) << endl;
    //     // }
    // }


    // // for (int i=0; i<num_of_function_tested; i++) cout << bool_row[i] << " ";
    // // cout << endl;

    // return bool_row;
}

tuple<vector<int>*, int> get_column_info(int num_of_inputs, int max_nonzero_term){
    long long int MAX_NUM_OF_COLUMN = 50000;
    int num_of_function_terms = num_of_inputs;
    if (num_of_inputs == 2) num_of_function_terms = 7;
    else if (num_of_inputs == 3) num_of_function_terms = 13;
    else if (num_of_inputs == 4) num_of_function_terms = 10;
    else if (num_of_inputs == 5) num_of_function_terms = 15;


    long long int num_of_function_tested = pow(3, num_of_function_terms);
    // cout << "this much: " << num_of_function_tested << endl;
    int table_column_id = 0;
    vector<int>* column_signs = new vector<int>[MAX_NUM_OF_COLUMN];

    for (long long int i=0; i<num_of_function_tested; i++){
        // if (i % 1000000 == 0) cout << i << endl;
        vector<int> signs;
        // calc signs
        long long int index = i;
        for (int j=0; j<num_of_function_terms; j++){
            int sign = (index % 3) - 1;
            signs.push_back(sign);
            index /= 3;
        }

        int num_of_nonzero = num_of_function_terms - count(signs.begin(), signs.end(), 0);
        if (num_of_nonzero > max_nonzero_term){
            // cout << "too many terms. skip!" << endl;
            continue;
        }

        column_signs[table_column_id] = signs;
        table_column_id ++;
    }

    return make_tuple(column_signs, table_column_id);
}

bool* simulated_function(vector<int> words, long long int output_circuit, int num_of_inputs, int num_of_output_bit, long long int constant_term, int max_nonzero_term, vector<int>* column_signs, int num_of_columns){
    int MAX_NUM_OF_COLUMN = pow(3, 10);
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
    
    // long long int num_of_function_tested = pow(3, num_of_function_terms);
    // cout << "this much: " << num_of_function_tested << endl;
    // int table_column_id = 0;
    // vector<int>* column_signs = new vector<int>[MAX_NUM_OF_COLUMN];

    for (long long int i=0; i<num_of_columns; i++){
        // if (i % 1000000 == 0) cout << i << endl;
        vector<int> signs = column_signs[i];
        // // calc signs
        // long long int index = i;
        // for (int j=0; j<num_of_function_terms; j++){
        //     int sign = (index % 3) - 1;
        //     signs.push_back(sign);
        //     index /= 3;
        // }

        // int num_of_nonzero = num_of_function_terms - count(signs.begin(), signs.end(), 0);
        // if (num_of_nonzero > max_nonzero_term){
        //     // cout << "too many terms. skip!" << endl;
        //     continue;
        // }

        // calc function values
        long long int func_val = constant_term;
        for (int j=0; j<num_of_function_terms; j++){
            func_val += term_vals[j] * signs[j];
        }

        // if (i > 7000000) cout << "hi3" << endl;

        // check equivalence
        long long int func_val_mod = func_val % mod_num;
        if (func_val_mod < 0) func_val_mod += mod_num;
        // if (i > 7000000) cout << "hi5" << endl;
        bool_row[i] = (output_circuit == func_val_mod);
        // if (i > 7000000) cout << "hi6" << endl;
        // if (table_column_id == 126){
        //     cout << output_circuit << " " << func_val_mod << " ============" << endl;
        // }
        // column_signs[table_column_id] = signs;
        // if (i > 7000000) cout << "hi7" << endl;
        // table_column_id ++;
        // if (i > 7000000) cout << "hi4" << endl;

        // int bias = 29524; // for num_of_inputs == 10
        // if (i == bias){
        //     cout << "==============" << i << "=============" << endl;
        //     cout << endl;
        //     cout << output_circuit << " " << (func_val % mod_num) << endl;
        // }
    }


    // for (int i=0; i<num_of_function_tested; i++) cout << bool_row[i] << " ";
    // cout << endl;

    return bool_row;
}


int get_gate_value(Gate* gate){
    // cout << "debug  " << gate->gate_name << " " << gate->value << endl;
    if (gate->value != -1) return gate->value;
    string oper = gate->gate_name;
    // cout << oper << endl;
    if (oper == "and"){
        int val1 = get_gate_value(get<0>(gate->inputs[0]));
        int val2 = get_gate_value(get<0>(gate->inputs[1]));
        gate->value = val1 * val2;
        return gate->value;
    }
    else if (oper == "or"){
        int val1 = get_gate_value(get<0>(gate->inputs[0]));
        int val2 = get_gate_value(get<0>(gate->inputs[1]));
        gate->value = (val1 + val2 > 0) ? 1 : 0;
        return gate->value;
    }
    else if (oper == "nand"){
        int val1 = get_gate_value(get<0>(gate->inputs[0]));
        int val2 = get_gate_value(get<0>(gate->inputs[1]));
        gate->value = (val1 * val2 == 1) ? 0 : 1;
        return gate->value;
    }
    else if (oper == "nor"){
        int val1 = get_gate_value(get<0>(gate->inputs[0]));
        int val2 = get_gate_value(get<0>(gate->inputs[1]));
        gate->value = (val1 + val2 > 0) ? 0 : 1;
        return gate->value;
    }
    else if (oper == "not"){
        int val = get_gate_value(get<0>(gate->inputs[0]));
        gate->value = (val == 1) ? 0 : 1;
        return gate->value;
    }
    else if (oper == "buf"){
        int val = get_gate_value(get<0>(gate->inputs[0]));
        gate->value = val;
        return gate->value;
    }
    else if (oper == "xor"){
        int val1 = get_gate_value(get<0>(gate->inputs[0]));
        int val2 = get_gate_value(get<0>(gate->inputs[1]));
        gate->value = (val1 + val2 == 1) ? 1 : 0;
        return gate->value;
    }
    else if (oper == "xnor"){
        int val1 = get_gate_value(get<0>(gate->inputs[0]));
        int val2 = get_gate_value(get<0>(gate->inputs[1]));
        gate->value = (val1 + val2 == 1) ? 0 : 1;
        return gate->value;
    }
    else{
        int val = get_gate_value(get<0>(gate->inputs[0]));
        gate->value = val;
        return gate->value;
    }
}

void reset_gate_value(Gate* gate){
    if (gate->value == -1) return;
    if (gate->gate_name == "1'b0" || gate->gate_name == "1'b1") return;
    gate->value = -1;
    for (auto inp: gate->inputs){
        Gate* inp_gate = get<0>(inp);
        reset_gate_value(inp_gate);
    }
}