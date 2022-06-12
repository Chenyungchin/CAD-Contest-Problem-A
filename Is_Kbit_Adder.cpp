// #include <bits/stdc++.h>
// #include "graph.h"
// #include "netlist2graph.h"

// // 1. find FA with no Ci (or HA)
// // 2. search along the way of Co until it reaches output or it stops

// // find from output might be better 

// // bool Is_Kbit_adder(int k){
// //     // find a FA(HA) that is not pointed by any other FA (if there are more than one such FA, CSA structure need to be considered)
// //     Gate start = ??;

    
// // }

// int main(){
//     // init input
//     vector<Gate*> primary_inputs;
//     for (int i=0; i<3; i++){
//         for (int j=0; j<2; j++){
//             Gate *newGate = new Gate("in" + to_string(i+1)+"["+ to_string(j) +"]");
//             primary_inputs.push_back(newGate);
//         }
//     }
//     // debug
//     for (auto gate: primary_inputs){
//         cout << gate->gate_name << " ";
//     }
//     cout << endl;
//     // FA
//     vector<Gate*> FAs;
//     for (int i=0; i<4; i++){
//         Gate* FA = new Gate("FA");
//         FAs.push_back(FA);
//     }
//     // FA0 connection
//     FAs[0]->inputs.push_back(make_tuple(primary_inputs[0], 0)); // in1[0] <- FA[0]
//     FAs[0]->inputs.push_back(make_tuple(primary_inputs[2], 0)); // in2[0] <- FA[0]
//     FAs[0]->inputs.push_back(make_tuple(primary_inputs[4], 0)); // in3[0] <- FA[0]
//     primary_inputs[0]->outputs.push_back({make_tuple(FAs[0], 0)}); // in1[0] -> FA[0]
//     primary_inputs[2]->outputs.push_back({make_tuple(FAs[0], 1)}); // in2[0] -> FA[0]
//     primary_inputs[4]->outputs.push_back({make_tuple(FAs[0], 2)}); // in3[0] -> FA[0]

//     // FA1 connection
//     FAs[1]->inputs.push_back(make_tuple(primary_inputs[1], 0)); // in1[1] <- FA[1]
//     FAs[1]->inputs.push_back(make_tuple(primary_inputs[3], 0)); // in2[1] <- FA[1]
//     FAs[1]->inputs.push_back(make_tuple(primary_inputs[5], 0)); // in3[1] <- FA[1]
//     primary_inputs[1]->outputs.push_back({make_tuple(FAs[1], 0)}); // in1[1] -> FA[1]
//     primary_inputs[3]->outputs.push_back({make_tuple(FAs[1], 1)}); // in2[1] -> FA[1]
//     primary_inputs[5]->outputs.push_back({make_tuple(FAs[1], 2)}); // in3[1] -> FA[1]

//     // 
    
//     return 0;
// }