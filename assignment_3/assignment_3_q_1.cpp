#include <iostream>
#include <vector>

using namespace std;

float maxArea(vector<float> B) {
    int pointerL = 0;
    int pointerR = B.size() - 1;

    float max_area = 0;
    while(pointerL < pointerR) {
        int width = pointerR - pointerL;
        float height = min(B[pointerL], B[pointerR]);
        max_area = max(max_area, width * height);

        //update the pointer for the lower bar
        if(B[pointerL] < B[pointerR]) {
            pointerL++;
        }
        else {
            pointerR--;
        }
    }

    //found max area, return
    return max_area;
}

int main() {
    int num_bars;
    cin >> num_bars;

    //create bar height vector
    vector<float> bar_vec(num_bars);

    //fill in vector
    float bar_height;
    for(int i = 0; i < num_bars; i++) {
        cin >> bar_height;
        bar_vec[i] = bar_height;
    }

    //find maxArea
    float max_area = maxArea(bar_vec);
    cout << max_area << endl;

    return 0;
}