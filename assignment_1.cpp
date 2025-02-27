#include<iostream>
#include<vector>
#include<stack>

using namespace std;

class kart_graph {
    private:
        int num_nodes_adj;
        int num_edges;
        vector<vector<int>> adj_matrix; //adjacency matrix

        int num_nodes_scc;
        vector<int> scc_sizes;
        vector<vector<int>> scc_matrix; //strongly connected component matrix of adj_matrix
        vector<int> scc_equivalency; //matches nodes to their equivalent node in scc_matrix

        void make_sccs(); //sccs found using Tarjan's algorithm
        void tarjan_dfs(int u, vector<int>& disc, vector<int>& low, stack<int>& st, vector<bool>& in_stack, int& time);

    public:
        kart_graph();

        void read_data();
        void print_adj_matrix();
        void print_scc_matrix();

        vector<int> player_rankings;
        void find_player_rankings();
};

kart_graph::kart_graph() : num_nodes_adj(0), num_edges(0), num_nodes_scc(0), player_rankings(3, 0) {
    adj_matrix.clear();
    scc_sizes.clear();
    scc_matrix.clear();
    scc_equivalency.clear();
}

int main() {
    kart_graph kart;
    kart.read_data();
    kart.find_player_rankings();

    return 0;
}

void kart_graph::find_player_rankings() {
    player_rankings.assign(3, 0);
    make_sccs();

    for(int i = 0; i < num_nodes_scc; i++) {
        bool source = true;
        bool sink = true;
        for(int j = 0; j < num_nodes_scc; j++) {
            if(i == j) { //ignore diagonal of scc matrix
                continue;
            }
            if(scc_matrix[i][j] == 1) { //scc node is a source
                sink = false;
            }
            if(scc_matrix[j][i] == 1) { //scc node is a sink
                source = false;
            }
        }
        if(source && !sink) { //player type A
            player_rankings[2] += scc_matrix[i][i]; //size of scc stored on diagonal
        }
        else if (!source && sink) { //player type B
            player_rankings[1] += scc_matrix[i][i];
        }
        else { //player type C
            player_rankings[0] += scc_matrix[i][i];
        }
    }

    cout << "|A| = " << player_rankings[2];
    cout << ", |B| = " << player_rankings[1];
    cout << ", |C| = " << player_rankings[0];
}

void kart_graph::make_sccs() {
    //initialize values for tarjan_dfs
    vector<int> disc(num_nodes_adj, -1);
    vector<int> low(num_nodes_adj, -1);
    vector<bool> in_stack(num_nodes_adj, false);
    stack<int> st;
    int time = 0;

    //reset scc internal values
    num_nodes_scc = 0;
    scc_equivalency.assign(num_nodes_adj, -1);

    //call DFS until all nodes are visited
    for(int u = 0; u < num_nodes_adj; u++) {
        if(disc[u] == -1) {
            tarjan_dfs(u, disc, low, st, in_stack, time);
        }
    }

    //construct scc matrix
    scc_matrix.resize(num_nodes_scc, vector<int>(num_nodes_scc, 0));
    for(int u = 0; u < num_nodes_adj; u++) {
        for(int v = 0; v < num_nodes_adj; v++) {
            if(adj_matrix[u][v] && scc_equivalency[u] != scc_equivalency[v]) { //mark 1 in scc matrix if 1 in adj matrix and u and v aren't the same scc
                scc_matrix[scc_equivalency[u]][scc_equivalency[v]] = 1;
            }
        }
        if(u < num_nodes_scc) {
            scc_matrix[u][u] = scc_sizes[u]; //save size of scc on diagonal
        }
    }
}

void kart_graph::tarjan_dfs(int u, vector<int>& disc, vector<int>& low, stack<int>& st, vector<bool>& in_stack, int& time) {
    disc[u] = low[u] = ++time; //initialize discovery time and lowest discovery times
    st.push(u); //push u to the stack and mark as in stack
    in_stack[u] = true;

    //traverse neighbors of u
    for(int v = 0; v < num_nodes_adj; v++) {
        if(adj_matrix[u][v]) { //check if an edge connects u and v
            if(disc[v] == -1) { //check if v has been discovered
                tarjan_dfs(v, disc, low, st, in_stack, time); //if v hasn't been discovered call tarjan's on v
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

void kart_graph::read_data() {
    //read # nodes and # edges
    cin >> num_nodes_adj >> num_edges;

    //resize graph to match # nodes
    adj_matrix.resize(num_nodes_adj, vector<int>(num_nodes_adj, 0)); 

    for(int i = 0; i < num_edges; i++) {
        int u, v;
        cin >> u >> v; //read node # and edge destination
        adj_matrix[u-1][v-1] = 1;
    }
}

void kart_graph::print_adj_matrix() {
    for(int i = 0; i < num_nodes_adj; i++) {
        for(int j = 0; j < num_nodes_adj; j++) {
            cout << adj_matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

void kart_graph::print_scc_matrix() {
    for(int i = 0; i < num_nodes_scc; i++) {
        for(int j = 0; j < num_nodes_scc; j++) {
            cout << scc_matrix[i][j] << " ";
        }
        cout << "\n";
    }
}