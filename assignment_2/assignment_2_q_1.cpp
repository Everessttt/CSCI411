#include<iostream>
#include<vector>
#include<limits.h>
#include<queue>

using namespace std;

vector<int> findSetI(vector<vector<int>> G);
vector<vector<int>> parse_input();
vector<int> bellman_ford(vector<vector<int>>& adj_mx);
vector<bool> BFS_bool(vector<vector<int>>& adj_mx, vector<int> srcs);

int main() {
    vector<vector<int>> adj_mx = parse_input();

    vector<int> I = findSetI(adj_mx);

    //print out set I
    for(size_t i = 0; i < I.size(); i++) {
        if(i != 0) {
            cout << " ";
        }
        cout << I[i] + 1; //correct node values
    }
    if(I.size() != 0) {
        cout << endl;
    }

    return 0;
}

vector<int> findSetI(vector<vector<int>> G) {
    //G is an adjacency matrix
    //run bellman ford algorithm modified to detect all negative cycles
    vector<int> distances = bellman_ford(G);

    //return empty set if there is no negative cycle
    if(distances[0] != -1) {
        return {};
    }

    //negative cycle detected
    vector<bool> BFS_vec = BFS_bool(G, distances); //run BFS on a nodes in negative cycle
    vector<int> I;
    for(size_t i = 0; i < BFS_vec.size(); i++) {
        if(BFS_vec[i]) {
            I.push_back(i);
        }
    }

    return I; //return set of all nodes that achieve negative distances
}

vector<vector<int>> parse_input() {
    int num_nodes = 0;
    int num_edges = 0;

    //read first line containing # nodes and # edges from input
    cin >> num_nodes >> num_edges;

    //construct adjacency matrix
    vector<vector<int>> adj_mx(num_nodes, vector<int>(num_nodes, 0));

    int u, v, wt; //source, destination, weight
    for(int i = 0; i < num_edges; i++) {
        cin >> u >> v >> wt;
        u -= 1; //correct u and v values
        v -= 1;

        //select lighest edge for each node in the adjacency matrix
        if(adj_mx[u][v] == 0) {
            adj_mx[u][v] = wt;
        }
        else {
            adj_mx[u][v] = min(adj_mx[u][v], wt);
        }
    }

    return adj_mx; //return completed adjacency matrix
}

vector<int> bellman_ford(vector<vector<int>>& adj_mx) {
    int V = adj_mx.size();
    vector<int> dist(V, INT_MAX); //distances from current source to all other nodes

    vector<int> neg_nodes = {-1};
    bool neg_cycle = false;

    for(int i = 0; i < V; i++) {
        //search for all negative cycles in the graph
        if(dist[i] == INT_MAX) {
            dist[i] = 0;
        }
        else {
            continue;
        }

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
                    neg_cycle = true; //found negative cycle, add node to negative vector
                    neg_nodes.push_back(u);
                }
            }
        }
    }

    if(neg_cycle) {
        return neg_nodes;
    }
    else {
        return {0};
    }
}

vector<bool> BFS_bool(vector<vector<int>>& adj_mx, vector<int> srcs) {
    queue<int> q; //BFS queue

    //mark all nodes as not viisted, make source node as visited and push to queue
    vector<bool> visited(adj_mx.size(), false);

    //attempt to visit all other nodes
    for(size_t u = 1; u < srcs.size(); u++) {
        if(!visited[srcs[u]]) {
            visited[srcs[u]] = true;
            q.push(srcs[u]);
        }

        while(!q.empty()) {
            //pop off front node
            int curr = q.front();
            q.pop();

            for(size_t v = 0; v < adj_mx.size(); v++) {
                if(adj_mx[curr][v] != 0 && !visited[v]) {
                    //found unvisited node, mark as visited and push to queue
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    return visited;
}