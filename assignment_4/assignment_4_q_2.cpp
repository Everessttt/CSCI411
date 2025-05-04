#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int hotelSequence(vector<int> hotel_vec, int ideal_mileage) {
    int n = hotel_vec.size() + 1;

    //create n sized vec
    hotel_vec.insert(hotel_vec.begin(), 0);
    vector<int> penalty_vec(n);

    //initialize base case
    penalty_vec[0] = 0;
    for(int i = 1; i < n; i++) {
        penalty_vec[i] = INT_MAX;
    }

    //find minimum penalties at each hotel
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            int penalty = (ideal_mileage - (hotel_vec[i] - hotel_vec[j])) * 
                (ideal_mileage - (hotel_vec[i] - hotel_vec[j]));

            penalty_vec[i] = min(penalty_vec[i], penalty_vec[j] + penalty);
        }
    }

    /*for(size_t i = 0; i < penalty_vec.size(); i++) {
        cout << penalty_vec[i] << " ";
    }
    cout << endl << endl;*/

    //trace shortest path to final hotel
    vector<int> path_vec;
    int i = n - 1;
    while(i > 0) {
        for(int j = 0; j < i; j++) {
            int penalty = (ideal_mileage - (hotel_vec[i] - hotel_vec[j])) * 
                (ideal_mileage - (hotel_vec[i] - hotel_vec[j]));

            if(penalty_vec[i] == penalty_vec[j] + penalty) {
                path_vec.push_back(i);
                i = j;
                break;
            }
        }
    }
    reverse(path_vec.begin(), path_vec.end());

    //print out path
    cout << "Enter the number of hotels and the ideal number of miles to travel per day: Enter " 
        << n - 1 << " hotel distances each on a separate line: Hotels to visit: ";
    for(size_t i = 0; i < path_vec.size(); i++) {
        cout << path_vec[i] << " ";
    }
    cout << endl;

    //return minimum penalty for final hotel
    return penalty_vec[n - 1];
}

int main() {
    int num_hotels, ideal_mileage;

    cin >> num_hotels >> ideal_mileage;


    int hotel;
    vector<int> hotel_vec(num_hotels);
    for(int i = 0; i < num_hotels; i++) {
        cin >> hotel;
        hotel_vec[i] = hotel;
    }

    /*cout << num_hotels << " " << ideal_mileage << endl;
    for(int i = 0; i < num_hotels; i++) {
        cout << hotel_vec[i] << " ";
    }
    cout << endl << endl;*/

    int total_penalty = hotelSequence(hotel_vec, ideal_mileage);
    cout << "Total penalty: " << total_penalty << endl;

    return 0;
}