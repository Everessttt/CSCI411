#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include <cmath>

using namespace std;

int maxContacts(vector<vector<double>>& locs, vector<double>& S);
pair<vector<vector<double>>, vector<double>> parse_input();
void tarjan_dfs(int u, vector<int>& disc, vector<int>& low, stack<int>& st, vector<bool>& in_stack, int& time, 
    vector<vector<double>>& adj_mx, int& num_nodes_scc, vector<int>& scc_equivalency, vector<int>& scc_sizes);
vector<vector<double>> tarjan(vector<vector<double>>& adj_mx);
vector<bool> BFS_bool(vector<vector<double>>& adj_mx, int src);

int main() {
    vector<vector<double>> locs;
    vector<double> s;
    pair<vector<vector<double>>, vector<double>> locs_s;
    locs_s = parse_input();
    locs = locs_s.first;
    s = locs_s.second;

    int max_contacts = maxContacts(locs, s);

    cout << max_contacts << endl;

    return 0;
}

int maxContacts(vector<vector<double>>& locs, vector<double>& S) {
    vector<vector<double>> adj_mx(locs.size(), vector<double>(locs.size(), 0));
    for(size_t u = 0; u < locs.size(); u++) {
        for(size_t v = 0; v < locs.size(); v++) {
            double dist = sqrt(pow(locs[u][0] - locs[v][0], 2) + pow(locs[u][1] - locs[v][1], 2)); //calculate distance from distance formula
            if(S[u] >= dist) { //signal from outpost u can reach outpost v, add edge
                adj_mx[u][v] = dist;
            }
        }
    }

    //run makeSCCs function
    vector<vector<double>> scc_mx = tarjan(adj_mx);

    int max_reachable_outposts = 0;
    for(size_t u = 0; u < scc_mx.size(); u++) {
        //find if node is a source or a sink
        bool universal_source = true;
        for(size_t v = 0; v < scc_mx.size(); v++) {
            if(u == v) { //skip diagonal
                continue;
            }
            if(scc_mx[v][u] != 0) { //node is not a source
                universal_source = false;
            }
        }
        if(universal_source) { //node is a universal source, call BFS at u
            int candidate_reachable_outposts = 0;

            vector<bool> BFS_vec = BFS_bool(scc_mx, u);
            for(size_t i = 0; i < BFS_vec.size(); i++) {
                if(BFS_vec[i]) { //add all reachable outposts to count
                    candidate_reachable_outposts += scc_mx[i][i];
                }
            }

            if(candidate_reachable_outposts > max_reachable_outposts) { //update max reachable outposts if needed
                max_reachable_outposts = candidate_reachable_outposts;
            }
        }
    }

    return max_reachable_outposts; //return maximum reachable outposts in one trip
}

pair<vector<vector<double>>, vector<double>> parse_input() {
    //read # outposts from first line of input
    int num_outposts;
    cin >> num_outposts;

    //read outpost data
    double x, y, s;
    vector<vector<double>> locs(num_outposts, vector<double>(2, 0));
    vector<double> s_vec(num_outposts, 0);
    for(int i = 0; i < num_outposts; i++) {
        cin >> x >> y >> s;
        locs[i][0] = x;
        locs[i][1] = y;
        s_vec[i] = s;
    }

    return make_pair(locs, s_vec);
}

void tarjan_dfs(int u, vector<int>& disc, vector<int>& low, stack<int>& st, vector<bool>& in_stack, int& time, 
    vector<vector<double>>& adj_mx, int& num_nodes_scc, vector<int>& scc_equivalency, vector<int>& scc_sizes) {

    disc[u] = low[u] = ++time; //initialize discovery time and lowest discovery times
    st.push(u); //push u to the stack and mark as in stack
    in_stack[u] = true;

    //traverse neighbors of u
    for(size_t v = 0; v < adj_mx.size(); v++) {
        if(adj_mx[u][v]) { //check if an edge connects u and v
            if(disc[v] == -1) { //check if v has been discovered
                tarjan_dfs(v, disc, low, st, in_stack, time, adj_mx, num_nodes_scc, scc_equivalency, scc_sizes); //if v hasn't been discovered call tarjan's on v
                low[u] = min(low[u], low[v]); //update u's lowest discovery time
            }
            else if(in_stack[v]) { //check if v is in the stack
                low[u] = min(low[u], disc[v]); //update u's lowest discovery time
            }
        }
    }

    //if u is an scc root
    if(low[u] == disc[u]) {
        int scc_size = 0; //store number of nodes in current scc
        while(st.top() != u) { //look for u in the stack and remove all other nodes v
            int v = st.top();
            st.pop();
            in_stack[v] = false;
            scc_equivalency[v] = num_nodes_scc; //map v to corresponding scc
            scc_size++;
        }
        //found u, map to corresponding scc
        int v = st.top();
        st.pop();
        in_stack[v] = false;
        scc_equivalency[v] = num_nodes_scc;
        scc_size++;

        scc_sizes.push_back(scc_size); //save size of scc
        num_nodes_scc++; //increment scc count
    }
}

vector<vector<double>> tarjan(vector<vector<double>>& adj_mx) {
    int num_nodes_adj = adj_mx.size();

    //initialize values for tarjan_dfs
    vector<int> disc(num_nodes_adj, -1);
    vector<int> low(num_nodes_adj, -1);
    vector<bool> in_stack(num_nodes_adj, false);
    stack<int> st;
    int time = 0;

    //reset scc internal values
    int num_nodes_scc = 0;
    vector<int> scc_equivalency(num_nodes_adj, -1);
    vector<int> scc_sizes;

    //call DFS until all nodes are visited
    for(int u = 0; u < num_nodes_adj; u++) {
        if(disc[u] == -1) {
            tarjan_dfs(u, disc, low, st, in_stack, time, adj_mx, num_nodes_scc, scc_equivalency, scc_sizes);
        }
    }

    //construct scc matrix
    vector<vector<double>> scc_mx(num_nodes_scc, vector<double>(num_nodes_scc, 0));
    for(int u = 0; u < num_nodes_adj; u++) {
        for(int v = 0; v < num_nodes_adj; v++) {
            if(adj_mx[u][v] && scc_equivalency[u] != scc_equivalency[v]) { //mark 1 in scc matrix if 1 in adj matrix and u and v aren't the same scc
                //select lightest edge
                if(scc_mx[scc_equivalency[u]][scc_equivalency[v]] == 0) {
                    scc_mx[scc_equivalency[u]][scc_equivalency[v]] = adj_mx[u][v];
                }
                else {
                    scc_mx[scc_equivalency[u]][scc_equivalency[v]] = min(scc_mx[scc_equivalency[u]][scc_equivalency[v]], adj_mx[u][v]);
                }
            }
        }
        if(u < num_nodes_scc) {
            scc_mx[u][u] = scc_sizes[u]; //save size of scc on diagonal
        }
    }

    return scc_mx;
}

vector<bool> BFS_bool(vector<vector<double>>& adj_mx, int src) {
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

        for(size_t v = 0; v < adj_mx.size(); v++) {
            if(adj_mx[curr][v] != 0 && !visited[v]) {
                //found unvisited node, mark as visited and push to queue
                visited[v] = true;
                q.push(v);
            }
        }
    }

    return visited;
}