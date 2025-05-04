// CSCI 411 - Spring 2025
// Exam 1 Question 3 - Fractional Knapsack
// Author: Carter Tillquist
// Feel free to use all, part, or none of this code for the fractional knapsack problem on exam 1.

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

/*******************************************
 * A struct to hold item information       *
 * value - float - the value of the item   *
 * weight - float - the weight of the item *
 *******************************************/
struct Item {
  float value;
  float weight;

  float normalized_value; //value relative to weight = 1
};

/*****************************************************************************************
 * Determine the maximum value of items that can be held in the knapsack                 *
 * items - std::vector<Item> - the items, each with a value and a weight, to choose from *
 * capacity - float - the initial capacity of the knapsack                               *
 * return - float - the maximum value of items that can be held                          *
 *****************************************************************************************/
float maxValue(vector<Item> items, float capacity){
  //no items, return value 0
  if(items.empty())
    return 0;

  //normalize value of all candidate items
  for(int i = 0; i < items.size(); i++) {
    items[i].normalized_value = items[i].value / items[i].weight;
  }

  //sort items by their normalized values
  vector<Item> sorted_items;
  sorted_items.push_back(items[0]);
  for(int i = 1; i < items.size(); i++) {
    sorted_items.push_back(items[i]); //add additional item to back of sorted vector
    int item_index = sorted_items.size() - 1; //starting position of added item

    for(int j = 0; j < sorted_items.size() - 1; j++) { //sort added item, a maximum of n - 1 swaps can occur
      //compare added items normalized value to the normalized value of item before it
      if(sorted_items[item_index].normalized_value > sorted_items[item_index - 1].normalized_value) {
        swap(sorted_items[item_index], sorted_items[item_index - 1]); //if added item is more valueable then swap items positions
        item_index--; //update position of added item
      }
      else //no swap occured, no more comparisons required
        break;
    }
  }

  //begin filling fractional knapsack
  float knapsack_value = 0;
  for(int i = 0; i < sorted_items.size(); i++) {
    capacity -= sorted_items[i].weight; //update capacity of knapsack
    float offset = (capacity < 0) ? capacity : 0; //if knapsack were to be overfilled apply an offset to ensure knapsack is filled to capacity
    knapsack_value += (sorted_items[i].weight + offset) * sorted_items[i].normalized_value; //add value to knapsack

    if(capacity <= 0) //knapsack is full
      return knapsack_value;
  }

  //knapsack wasn't entirely filled
  return knapsack_value;
}

int main(){
  int n = -1;
  float capacity = -1;
  cin >> n >> capacity;

  vector<Item> items;
  float v = -1, w = -1;
  for (int i = 0; i < n; i++){
    cin >> v >> w;
    Item elem;
    elem.value = v;
    elem.weight = w;
    items.push_back(elem);
  }

  cout << fixed;
  cout << setprecision(3) << maxValue(items, capacity) << endl;

  return 0;
}
