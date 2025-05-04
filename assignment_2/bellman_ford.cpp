#include<iostream>
#include<vector>
#include<limits.h>

using namespace std;

vector<int> bellman_ford(vector<vector<int>>& adj_mx, int src = 0) {
    int V = adj_mx.size();
    vector<int> dist(V, INT_MAX); //distances from src to all other nodes
    dist[src] = 0;

    //relax all edges V-1 times
    for(int k = 0; k < V - 1; k++) {
        for(int u = 0; u < V; u++) {
            for(int v = 0; v < V; v++) {
                if(adj_mx[u][v] != 0 && dist[u] != INT_MAX) { 
                    dist[v] = min(dist[v], dist[u] + adj_mx[u][v]);
                }
            }
        }
    }

    //check for negative cycle
    for(int u = 0; u < V; u++) {
        for(int v = 0; v < V; v++) {
            if(adj_mx[u][v] != 0 && dist[u] != INT_MAX && dist[u] + adj_mx[u][v] < dist[v]) {
                return {-1, u}; //found negative cycle, return -1 at first index and a node in the negative cycle
            }
        }
    }

    return dist;
}