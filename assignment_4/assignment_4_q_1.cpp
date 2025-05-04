#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int editDistance(string A, string B, int ins, int del, int sub) {
    int n = A.size() + 1;
    int m = B.size() + 1;

    //setup n x m vector
    vector<vector<int>> transform_vec(n, vector<int>(m));

    //initialize base cases
    for(int i = 0; i < n; i++) {
        transform_vec[i][0] = i * del;
    }
    for(int j = 0; j < m; j++) {
        transform_vec[0][j] = j * ins;
    }

    //fill in array
    for(int i = 1; i < n; i++) {
        int cost;
        for(int j = 1; j < m; j++) {
            if(A[i - 1] == B[j - 1] && sub >= 0)
                cost = 0;
            else
                cost = sub;

            //fill in vec at i, j
            transform_vec[i][j] = min(
                transform_vec[i][j - 1] + ins, 	    	//insertion
                min(
                    transform_vec[i - 1][j] + del,		//deletion
                    transform_vec[i - 1][j - 1] + cost	//substitution
                )
            );
        }
    }

    //build transformation strings for A and B
    string str_A = "";
    string str_B = "";

    int i = n - 1, j = m - 1;
    while(i > 0 || j > 0) {
        //substitution
        int cost = (i > 0 && j > 0 && A[i - 1] == B[j - 1] && sub >= 0) ? 0 : sub;
        if(i > 0 && j > 0 && transform_vec[i][j] == transform_vec[i - 1][j - 1] + cost) {
            str_A.push_back(A[i - 1]);
            str_B.push_back(B[j - 1]);
            i--;
            j--;
        }

        //deletion
        else if(i > 0 && transform_vec[i][j] == transform_vec[i - 1][j] + del) {
            str_A.push_back(A[i - 1]);
            str_B.push_back('_');
            i--;
        }

        //insertion
        else {
            str_A.push_back('_');
            str_B.push_back(B[j - 1]);
            j--;
        }
    }

    //reverse strings and cout
    reverse(str_A.begin(), str_A.end());
    reverse(str_B.begin(), str_B.end());
    cout << str_A << endl;
    cout << str_B << endl;

    return transform_vec[n - 1][m - 1];
}

int main() {
    int num_examples;
    int ins, del, sub;

    cin >> num_examples;
    cin >> ins;
    cin >> del;
    cin >> sub;

    string A, B;
    for(int i = 0; i < num_examples; i++) {
        cin >> A;
        cin >> B;
        int result = editDistance(A, B, ins, del, sub);

        cout << result << endl;
    }

    return 0;
}