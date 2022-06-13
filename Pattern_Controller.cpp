#include "Pattern_controller.h"
#include "Compare_pattern.h"

using namespace std;

vector<int> pattern_generator(int pattern, int bit){

}

tuple<vector<Gate*>, vector<Gate*>> pattern_controller(vector<Gate*> primary_inputs, vector<Gate*> primary_outputs, vector<int> inputs_operand_bit){
    vector<Gate*> circ_inputs = primary_inputs;
    vector<Gate*> circ_outputs = primary_outputs;
    
    while (1){
        long long int pattern_num = pow(2, circ_inputs.size());
        vector<int> pattern;
        bool same_function = 1;
        for (int i=0; i<pattern_num; i++){
            pattern = pattern_generator(i, circ_inputs.size());
            bool same_value = compare_pattern(pattern, primary_inputs, primary_outputs, inputs_operand_bit);
            if (!same_value){
                same_function = 0;
                break;
            }
        }
        if (same_function){
            return make_tuple(circ_inputs, circ_outputs);
        }
        // Todo: 測試不同的output bit數
        // Todo: 更新circ_inputs 和circ_outputs
        // Todo: 如果最後都沒找到，回傳找不到(需要改一下函式的回傳形別)
    }
    

}