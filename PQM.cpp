#include "PQM.h"

using namespace std;

bool complete_cover(vector<bool> cover) {
    return (all_of(cover.begin(), cover.end(), [](bool b) {return b;}));
}

vector<int> get_ctrl(vector<int> cover, vector<tuple<string, int>> module_inputs, vector<int>* column_signs){
    vector<int> ctrl;
    // for (auto inp: module_inputs){
    //     ctrl.push_back(get<0>(inp));
    // }
    int num_of_inputs = module_inputs.size();
    for (int i=0; i<num_of_inputs; i++){
        ctrl.push_back(i);
    }
    vector<vector<int>> used_input;

    if (num_of_inputs == 2){
        // long long int tmp[] = {a, b, a*b, a*a, b*b, a*a*a, b*b*b};
        used_input = {{0}, {1}, {0, 1}, {0}, {1}, {0}, {1}};

    }
    else if (num_of_inputs == 3){
        // long long int tmp[] = {a, b, c, a*b, b*c, c*a, a*a, b*b, c*c, a*b*c, a*a*a, b*b*b, c*c*c};
        used_input = {{0}, {1}, {2}, {0, 1}, {1, 2}, {2, 0}, {0}, {1}, {2}, {0, 1, 2}, {0}, {1}, {2}};
    }
    else if (num_of_inputs == 4){
        // long long int tmp[] = {a, b, c, d, a*b, a*c, a*d, b*c, b*d, c*d};
        used_input = {{0}, {1}, {2}, {3}, {0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}};
    }
    else if(num_of_inputs == 5){
        // long long int tmp[] = {a, b, c, d, e, a*b, a*c, a*d, a*e, b*c, b*d, b*e};
        // long long int tmp[] = {a, b, c, d, e, a*b, a*c, a*d, a*e, b*c, b*d, b*e, c*d, c*e, d*e};
        used_input = {{0}, {1}, {2}, {3}, {4}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}};
    }
    else{
        // for (auto word: words){
        //     term_vals.push_back(word);
        // }
        for (int i=0; i<num_of_inputs; i++){
            used_input.push_back({i});
        }
    }
    
    for (auto cov: cover){
        vector<int> signs = column_signs[cov];
        for (int i=0; i<signs.size(); i++){
            if (signs[i] == 0) continue;
            for (auto val: used_input[i]){
                auto it = find(ctrl.begin(), ctrl.end(), val);
                if (it != ctrl.end()){
                    ctrl.erase(it);
                }
            }
        }
    }

    for (auto val: ctrl) cout << val << " ";
    cout << endl;

    return ctrl;
}


vector<int> PQM(bool** table, int num_of_minterm, int num_of_pattern, vector<int>* column_signs) {
    // find dominance minterm
    int num_of_1;
    vector<int> dominance; // list of index of dominance minterms
    vector<pair<int, int>> minterm_size; // <index of minterm, number of 1 of that minterm>
    int tmp_dominance;
    vector<int> minterm_distance;
    for (int j=0; j<num_of_minterm; j++) {
        // sign
        vector<int> signs;
        // int index = j;
        // // cout << index << endl;
        // for (int k=0; k<round(log(num_of_minterm)/log(3)); k++){
        //     int sign = (index % 3) - 1;
        //     signs.push_back(sign);
        //     index /= 3;
        // }
        signs = column_signs[j];
        int distance = count(signs.begin(), signs.end(), 0);
        minterm_distance.push_back(distance);
        // debug
        // for (int sign: signs){
        //     cout << sign << " ";
        // }
        // cout << endl;
    }

    for (int i=0; i<num_of_pattern; i++) {
        num_of_1 = 0;
        for (int j=0; j<num_of_minterm; j++) {
            if (table[i][j]) {
                num_of_1 ++;
                tmp_dominance = j;
            }
            if (num_of_1 > 1) break;
            if (j == num_of_minterm-1 && num_of_1 == 1) {
                // find dominance minterm
                if (find(dominance.begin(), dominance.end(), tmp_dominance) == dominance.end()) {
                    dominance.push_back(tmp_dominance);
                }
            }
        }
    }
    
    for (int i=0; i<num_of_minterm; i++) {
        num_of_1 = 0;
        for (int j=0; j<num_of_pattern; j++) {
            if (table[j][i]) {
                num_of_1 ++;
            }
        }
        if (find(dominance.begin(), dominance.end(), i) == dominance.end()){
            minterm_size.push_back(make_pair(i, num_of_1));
        }
    }

    cout << "dominance minterm: ";
    for (auto minterm : dominance) {
        cout << minterm << " ";
    }
    cout << "\n";

    // initialize
    vector<bool> cover(num_of_pattern, false);
    for (auto domi : dominance) {
        for (int i=0; i<num_of_pattern; i++) {
            if (table[i][domi]) cover[i] = true;
        }
    }

    // sort minterm_size from the biggest to the smallest
    sort(minterm_size.begin(), minterm_size.end(), [&minterm_distance](auto &left, auto &right) {
        if (left.second == right.second) return minterm_distance[left.first] > minterm_distance[right.first];
        else return left.second > right.second;
    });

    // Select the maximum minterm, if it cover some new patterns
    // until cover all patterns
    vector<int> empty;
    while (!complete_cover(cover)) {
        int largest_minterm = minterm_size[0].first;
        // cout << largest_minterm << " size: " << minterm_size[0].second << endl;
        minterm_size.erase(minterm_size.begin());
        for (int i=0; i<num_of_pattern; i++) {
            if (table[i][largest_minterm]) cover[i] = true;
        }
        dominance.push_back(largest_minterm);
        if (minterm_size.size() == 0) {
            cout << "I give up." << endl;
            return empty;
            break;
        }
        // cout << minterm_size.size() << endl;
        minterm_size.clear();
        for (int i=0; i<num_of_minterm; i++) {
            num_of_1 = 0;
            for (int j=0; j<num_of_pattern; j++) {
                if (table[j][i] && !cover[j]) {
                    num_of_1 ++;
                }
            }
            if (find(dominance.begin(), dominance.end(), i) == dominance.end()){
                minterm_size.push_back(make_pair(i, num_of_1));
            }
        }
        sort(minterm_size.begin(), minterm_size.end(), [&minterm_distance](auto &left, auto &right) {
            if (left.second == right.second) return minterm_distance[left.first] > minterm_distance[right.first];
            else return left.second > right.second;
        });
    }


    return dominance;
}

// int main() {
//     int num_of_pattern = 5;
//     int num_of_minterm = 4;
//     bool** table = new bool*[num_of_pattern];
//     for (int i=0; i<num_of_pattern; i++) {
//         table[i] = new bool[num_of_minterm];
//         for (int j=0; j<num_of_minterm; j++) {
//             table[i][j] = false;
//         }
//     }
//     table[0][0] = true;
//     table[1][0] = true;
//     table[1][1] = true;
//     table[2][1] = true;
//     table[3][1] = true;
//     table[4][1] = true;
//     table[3][2] = true;
//     table[4][2] = true;
//     table[0][3] = true;
//     table[1][3] = true;
//     table[2][3] = true;

//     vector<int> dominance;
//     dominance = PQM(table, num_of_minterm, num_of_pattern);
//     for (int i=0; i<dominance.size(); i++) {
//         cout << dominance[i] << " ";
//     }

//     return 0;
// }