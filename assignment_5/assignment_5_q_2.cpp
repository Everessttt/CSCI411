#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string inverse_burrows_wheeler_transform(string str) {
    int n = str.size();

    //create sorted string to begin inverse BWT
    string sorted_str = str;
    sort(sorted_str.begin(), sorted_str.end());

    //map sorted input string to sorted string
    vector<int> map(n, -1);
    vector<bool> is_char_used(n, false);
    for(int i = 0; i < n; i++) {
        char input_char = str[i];
        for(int j = 0; j < n; j++) {
            char sorted_char = sorted_str[j];

            //found corresponding char, add to map
            if(input_char == sorted_char && !is_char_used[j]) {
                is_char_used[j] = true;
                map[i] = j;
                break;
            }
        }
    }

    //find sentinel character index
    int curr_index;
    for(int i = 0; i < n; i++) {
        if(str[i] == '$') {
            curr_index = i;
            break;
        }
    }

    //contruct original string from map
    string inverse_BWT = "";
    while(inverse_BWT.size() != static_cast<size_t>(n)) {
        inverse_BWT += str[curr_index];
        curr_index = map[curr_index];
    }

    //reverse string to put into correct order
    reverse(inverse_BWT.begin(), inverse_BWT.end());

    //inverse BWT string found, return
    return inverse_BWT;
}

int main() {
    string str;
    cin >> str;

    str = inverse_burrows_wheeler_transform(str);

    cout << str << endl;

    return 0;
}