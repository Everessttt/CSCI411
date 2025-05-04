#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void makeChange(vector<int> target_vec, vector<int> coin_vec) {
    //find fewest number of coins needed for value i
    for(size_t i = 0; i < target_vec.size(); i++) {
        int target = target_vec[i];

        //create trial vector for current iteration
        vector<int> trial_vec(target + 1, INT_MAX);
        trial_vec[0] = 0; //base case

        //create output matrix for current iteration
        vector<vector<int>> output_mx(target + 1, vector<int>(coin_vec.size(), 0));
        
        //fill in trial vector for current target
        for(int j = 1; j < target + 1; j++) {
            int coin_index = -1;
            for(size_t k = 0; k < coin_vec.size(); k++) {
                int coin = coin_vec[k];
                if(j - coin >= 0 && trial_vec[j - coin] + 1 < trial_vec[j] && trial_vec[j - coin] != INT_MAX) {
                    trial_vec[j] = trial_vec[j - coin] + 1;
                    coin_index = k;
                }
            }

            //update output matrix
            if(coin_index != -1) {
                output_mx[j] = output_mx[j - coin_vec[coin_index]];
                output_mx[j][coin_index] += 1;
            }
        }

        //print output matrix for target
        for(size_t j = 0; j < coin_vec.size(); j++) {
            cout << output_mx[target_vec[i]][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int num_coin_denominations, target_amounts;
    cin >> num_coin_denominations >> target_amounts;

    int coin;
    vector<int> coin_vec(num_coin_denominations);
    for(int i = 0; i < num_coin_denominations; i++) {
        cin >> coin;
        coin_vec[i] = coin;
    }
    
    int target;
    vector<int> target_vec(target_amounts);
    for(int i = 0; i < target_amounts; i++) {
        cin >> target;
        target_vec[i] = target;
    }

    /*cout << num_coin_denominations << " " << target_amounts << endl;
    for(int i = 0; i < num_coin_denominations; i++) {
        cout << coin_vec[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < target_amounts; i++) {
        cout << target_vec[i] << " ";
    }
    cout << endl << endl;*/

    makeChange(target_vec, coin_vec);

    return 0;
}