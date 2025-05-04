#include<iostream>
#include<vector>
#include<stack>

using namespace std;

void tarjan_dfs(int u, vector<int>& disc, vector<int>& low, stack<int>& st, vector<bool>& in_stack, int& time, 
    vector<vector<int>>& adj_mx, int& num_nodes_scc, vector<int>& scc_equivalency, vector<int>& scc_sizes) {

    disc[u] = low[u] = ++time; //initialize discovery time and lowest discovery times
    st.push(u); //push u to the stack and mark as in stack
    in_stack[u] = true;

    //traverse neighbors of u
    for(int v = 0; v < adj_mx.size(); v++) {
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

vector<vector<int>> tarjan(vector<vector<int>>& adj_mx) {
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
    vector<vector<int>> scc_mx(num_nodes_scc, vector<int>(num_nodes_scc, 0));
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
}vector<vector<int>> tarjan(vector<vector<int>>& adj_mx) {
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
    vector<vector<int>> scc_mx(num_nodes_scc, vector<int>(num_nodes_scc, 0));
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