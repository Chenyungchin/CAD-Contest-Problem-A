#include "PQM.h"

using namespace std;

bool complete_cover(vector<bool> cover) {
    return (all_of(cover.begin(), cover.end(), [](bool b) {return b;}));
}


vector<int> PQM(bool** table, int num_of_minterm, int num_of_pattern) {
    // find dominance minterm
    int num_of_1;
    vector<int> dominance; // list of index of dominance minterms
    vector<pair<int, int>> minterm_size; // <index of minterm, number of 1 of that minterm>
    int tmp_dominance;
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
            if (table[j][i] == true) {
                num_of_1 ++;
            }
        }
        if (find(dominance.begin(), dominance.end(), i) == dominance.end()){
            minterm_size.push_back(make_pair(i, num_of_1));
        }
    }

    // initialize
    vector<bool> cover(num_of_pattern, false);
    for (auto domi : dominance) {
        for (int i=0; i<num_of_pattern; i++) {
            if (table[i][domi]) cover[i] = true;
        }
    }

    // sort minterm_size from the biggest to the smallest
    sort(minterm_size.begin(), minterm_size.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    });

    // Select the maximum minterm, if it cover some new patterns
    // until cover all patterns
    while (!complete_cover(cover)) {
        int largest_minterm = minterm_size[0].first;
        for (int i=0; i<num_of_pattern; i++) {
            if (table[i][largest_minterm]) cover[i] = true;
        }
        dominance.push_back(largest_minterm);
        minterm_size.erase(minterm_size.begin());
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