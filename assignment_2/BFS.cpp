#include<iostream>
#include<vector>
#include<queue>

using namespace std;

vector<bool> BFS_bool(vector<vector<int>>& adj_mx, int src) {
    queue<int> q; //BFS queue

    //mark all nodes as not viisted, make source node as visited and push to queue
    vector<bool> visited(adj_mx.size(), false);
    visited[src] = true;
    q.push(src);
    
    //attempt to visit all other nodes
    while(!q.empty()) {
        //pop off front node
        int curr = q.front();
        q.pop();

        for(int v = 0; v < adj_mx.size(); v++) {
            if(adj_mx[curr][v] != 0 && !visited[v]) {
                //found unvisited node, mark as visited and push to queue
                visited[v] = true;
                q.push(v);
            }
        }
    }

    return visited;
}