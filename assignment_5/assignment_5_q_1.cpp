#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string burrows_wheeler_transform(string str) {
    //add sentiniel character
    str += '$';
    int n = str.size();

    //get suffix array
    vector<string> suffix_vec(n);
    for(int i = 0; i < n; i++) {
        string curr_str = "";
        for(int j = n - 1 - i; j < 2 * n - 1 - i; j++) {
            int j_prime = j % n;
            curr_str += str[j_prime];
        }
        suffix_vec[i] = curr_str;
    }

    //sort suffix_vec
    sort(suffix_vec.begin(), suffix_vec.end());

    //contrust BWT string
    string BWT_str = "";
    for(int i = 0; i < n; i++) {
        BWT_str += suffix_vec[i][n - 1];
    }

    //finished BWT, return
    return BWT_str;
}

int main() {
    string str;
    cin >> str;

    str = burrows_wheeler_transform(str);

    cout << str << endl;

    return 0;
}