#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int countShortestPaths(vector<vector<int>> G, int s, int u) {
    int n = G.size();

    vector<int> dist_from_s(n, -1);
    vector<int> num_shortest_paths(n, 0);

    //fill in dist_from_s
    queue<int> q;
    q.push(s);
    dist_from_s[s] = 0;
    num_shortest_paths[s] = 1;

    while(!q.empty()) {
        int src = q.front();
        q.pop();

        for(int dst = 0; dst < n; dst++) {
            //no edge from src to dst
            if(G[src][dst] == 0) {
                continue;
            }
            
            //visiting an unvisited neighbor 
            if(dist_from_s[dst] == -1) {
                dist_from_s[dst] = dist_from_s[src] + 1;
                num_shortest_paths[dst] = num_shortest_paths[src];
                q.push(dst);
            }

            //visiting an already visited neighbor but an additional shortest path has been found
            else if(dist_from_s[dst] == dist_from_s[src] + 1) {
                num_shortest_paths[dst] += num_shortest_paths[src];
            }
        }
    }

    return num_shortest_paths[u];
}

int main() {
    //read inputs
    //  n: num vertrices, m: num edges, s: start vertex, u: destination.
    int n, m, s, u;
    cin >> n >> m >> s >> u;

    //cout << n << " " << m << " " << s << " " << u << endl;

    //create n x n matrix
    vector<vector<int>> path_mx(n, vector<int>(n, 0));

    //read next m lines
    //  v, w: vertices
    int v, w;
    for(int i = 0; i < m; i++) {
        cin >> v >> w;
        path_mx[v][w] = 1;
        path_mx[w][v] = 1;

        //cout << v << " " << w << endl;
    }
    
    //call countShortestPaths
    int num_shortest_paths = countShortestPaths(path_mx, s, u);
    cout << num_shortest_paths << endl;
    //cout << "NUM SHORTEST PATHS: >>" << num_shortest_paths << "<<\n";

    return 0;
}