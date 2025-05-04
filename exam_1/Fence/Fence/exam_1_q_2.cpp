// CSCI 411 - Spring 2025
// Exam 1 Question 2 - Fence
// Author: Carter Tillquist
// Feel free to use all, part, or none of this code for the fence problem on exam 1.

#include <iostream>
#include <vector>

using namespace std;

/**********************************************************************************************
 * A struct to keep track of the number of posts and required posts for each section of fence *
 * posts - int - the number of posts stored at a particular location                          *
 * required - int - the number of posts required for the next section of fence                *
 **********************************************************************************************/
struct Section {
  int posts;
  int required;
};

/***********************************************************************************************
 * Determine a suitable start location if there are enough posts                               *
 * L - std::vector<Section> - the number of posts stored at different locations along with the *
 *                            number of posts required for the next section                    *
 * return - int - -1 if there are not enough posts and a location to start building otherwise  *
 ***********************************************************************************************/
int findStart(vector<Section> L){
  //test all potential starting points for fence construction
  for(int i = 0; i < L.size(); i++) {
    //initialize values
    int candidate_start = i;
    int num_posts = 0;
    bool is_valid_start = true;

    for(int j = i; j < L.size() + i; j++) {
      //normalize iterator to ensure proper looping
      int j_prime = (j < L.size()) ? j : (j - L.size());

      num_posts += L[j_prime].posts - L[j_prime].required; //calculate new number of posts after building current segment
      if(num_posts < 0) { //more posts needed than in reserve, not a valid starting point
        is_valid_start = false;
        break;
      }
    }

    //found a valid starting point, return
    if(is_valid_start) {
      return i;
    }
  }

  //no valid starting point was found, return -1
  return -1;
}

int main(){
  int n = -1;
  cin >> n;

  vector<Section> L;
  int p = -1, r = -1;
  for (int i = 0; i < n; i++){
    cin >> p >> r;
    Section s;
    s.posts = p;
    s.required = r;
    L.push_back(s);
  }

  int location = findStart(L);
  cout << location << endl;

  return 0;
}
