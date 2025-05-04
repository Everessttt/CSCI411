// CSCI 411 - Spring 2025
// Exam 1 Question 2 - Cut Vertices
// Author: Carter Tillquist
// Feel free to use all, part, or none of this code for the cut vertex problem on exam 1.

#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/***********************************************************************************
 * Find the cut vertices of the graph with the given adjacency list                *
 * A - std::vector<std::vector<int>> - an adjacency matrix for an undirected graph *
 * return - std::vector<int> - a vector containing cut vertex names                *
 ***********************************************************************************/
vector<int> findCutVertices(vector<vector<int>> A){
  vector<int> cut_vertices;
  if(A.empty() || A.size() == 1)
    return cut_vertices;

  for(int i = 0; i < A.size(); i++) {
    int cut_node = i; //suppose node i was removed...
    //node i is a cut vertex if a connected graph cannot be made without it

    //use BFS to attempt to reach all nodes without the cut node
    queue<int> q;
    int starting_node = (cut_node == 0) ? 1 : 0; //set starting node as first non cut node, either 0 or 1
    q.push(starting_node);
    
    vector<bool> is_node_visited(A.size(), false); //initialize visited vector
    is_node_visited[i] = true; //set cut node and starting node as visited
    is_node_visited[starting_node] = true;

    //begin calling BFS
    while(!q.empty()) {
      int curr_node = q.front();
      q.pop();

      for(int j = 0; j < A.size(); j++) {
        if(A[curr_node][j] == 1 && !is_node_visited[j]) { //add neighbor to queue
          q.push(j);
          is_node_visited[j] = true;
        }
      }
    }

    //i is a cut vertex if a false exists in BFS visited vector
    for(int j = 0; j < A.size(); j++) {
      if(!is_node_visited[j]) { //i is a cut vertex, add to vector
        cut_vertices.push_back(i);
        break;
      }
    }
  }

  //found all cut vertices, return
  return cut_vertices;
}

int main(){
  int num_vertices = -1;
  int num_edges = -1;
  cin >> num_vertices >> num_edges;

  vector<vector<int>> A(num_vertices, vector<int>(num_vertices, 0));

  int src = -1;
  int dst = -1;
  for(int i = 0; i < num_edges; i++){
    cin >> src >> dst;
    A[src][dst] = 1;
    A[dst][src] = 1;
  }

  vector<int> cutVertices = findCutVertices(A);
  sort(cutVertices.begin(), cutVertices.end());

  for(int i = 0; i < cutVertices.size(); i++) {
    cout << cutVertices[i] << " ";
  }
  if(cutVertices.size() > 0){ cout << endl; }

  return 0;
}