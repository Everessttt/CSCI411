#include <iostream>
#include <vector>
#include <string>

using namespace std;

string construct_string(int x, int y, int z) {
    //to prevent 000, 111, 222 as substrings the following must be true
    //  max(x, y, z) / 2 - 1 <= min(x, y, z) + (x + y + z - max + min)
    
    int largest = max(x, max(y, z));
    int first_min = min(x, min(y, z));
    int second_min = x + y + z - largest - first_min;

    //string can't be constructed
    if(((largest + 1) / 2) - 1 > first_min + second_min) {
        return "";
    }

    //contruct string
    string str = "";
    while(x > 0 || y > 0 || z > 0) {
        int curr_max = max(x, max(y, z));

        //find next character to add to string
        char next_char;
        if(x == curr_max) {
            next_char = '0';
        }
        else if(y == curr_max) {
            next_char = '1';
        }
        else {
            next_char = '2';
        }

        //ensure three of the same character don't appear in a row
        if(str.size() >= 2 && str[str.size() - 1] == next_char && str[str.size() - 2] == next_char) {
            if(next_char == '0') {
                if(y >= z) next_char = '1';
                else next_char = '2';
            }
            else if(next_char == '1') {
                if(x >= z) next_char = '0';
                else next_char = '2';
            }
            else {
                if(x >= y) next_char = '0';
                else next_char = '1';
            }
        }

        //add character to string
        str += next_char;

        //decrement trackers x, y, or z
        if(next_char == '0') x--;
        else if(next_char == '1') y--;
        else z--;
    }

    return str;
}

int main() {
    int num_tests;
    cin >> num_tests;

    int x, y, z;
    for(int i = 0; i < num_tests; i++) {
        cin >> x >> y >> z;

        //print out results
        string str = construct_string(x, y, z);
        if(str == "") {
            cout << "No such string" << endl;
        }
        else {
            cout << str << endl;
        }
    }

    return 0;
}