#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>

#define MAX_SIZE 7

using namespace std;

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

void DFSHis(int start, int goal) {
    bool visited[MAX_SIZE] = {false};
    int parent[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++)
        parent[i] = -1;

    stack<int> s;
    s.push(start);
    visited[start] = true;

    bool found = false;
    cout << "Traversal: ";

    cout << start << " ";

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (node == goal) {
            found = true;
            break;
        }
        
        vector<int> children;
        for (int j = 0; j < MAX_SIZE; j++) {
            if (adj[node][j] == 1 && !visited[j]) {
                children.push_back(j);
            }
        }

        sort(children.rbegin(), children.rend()); //Sort children in descending order stack(lifo)

        for (int c : children) {
            if (!visited[c]) { 
                visited[c] = true;
                parent[c] = node;
                s.push(c);
                cout << c << " ";
            }
        }
    } 

    if (found) {
        stack<int> path;
        for (int v = goal; v != -1; v = parent[v]) {
            path.push(v);
        }

        cout << "\nPath from " << start << " to " << goal << ": ";
        while (!path.empty()) {
            cout << path.top() << " ";
            path.pop();
        }
        cout << endl;
    } else {
        cout << "No path found from " << start << " to " << goal << endl;
    }
}

int main() {
    cout << "DFS with history: Start = 0 and Goal = 6\n";
    DFSHis(0, 6);
    return 0;
}
