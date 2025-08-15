#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>

#define MAX_SIZE 7

using namespace std;

// Adjacency matrix for the graph
int adj[MAX_SIZE][MAX_SIZE] = {
    //s a b c d e g
    {0,1,1,0,0,0,0},
    {1,0,1,0,1,0,0},
    {1,1,0,1,0,0,0},
    {0,0,1,0,0,1,0},
    {0,1,0,0,0,0,1},
    {0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0}
};

bool DLS(int node, int goal, int limit, int parent[], bool visited[]) {
    visited[node] = true;
    cout << node << " ";

    if (node == goal) {
        return true;
    }

    if (limit <= 0) {
        return false;
    }

    vector<int> children;
    for (int j = 0; j < MAX_SIZE; j++) {
        if (adj[node][j] == 1) {
            children.push_back(j);
        }
    }
    sort(children.begin(), children.end());

    for (int c : children) {
        if (!visited[c]) { 
            parent[c] = node;
            if (DLS(c, goal, limit - 1, parent, visited)) {
                return true;
            }
        }
    }
    return false;
}

void BFSDFS(int start, int goal) {
    cout << "BFSDFS Traversal:";
    int parent[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) {
        parent[i] = -1;
    }

    for (int limit = 0; limit < MAX_SIZE; limit++) {
        cout << "\nDepth Limit " << limit << ": ";
        bool visited[MAX_SIZE] = {false};
        parent[start] = -1; 
        
        if (DLS(start, goal, limit, parent, visited)) {
            cout << "\nGoal found at depth " << limit << ".\n";
            stack<int> path;
            for (int v = goal; v != -1; v = parent[v]) {
                path.push(v);
            }
            cout << "Path from " << start << " to " << goal << ": ";
            while (!path.empty()) {
                cout << path.top() << " ";
                path.pop();
            }
            cout << endl;
            return;
        }
    }
    cout << "\nNo path found from " << start << " to " << goal << " within max depth." << endl;
}

int main() {
    cout << "Running BFSDFS: Start = 0 and Goal = 6\n";
    BFSDFS(0, 6);
    return 0;
}