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

int heuristic[MAX_SIZE] = {9, 8, 6, 8, 3, 4, 0}; 

void HCHis(int start, int goal) {
    bool visited[MAX_SIZE] = {false};
    int parent[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++)
        parent[i] = -1;

    stack<int> s;
    s.push(start);

    bool found = false;
    cout << "Traversal: ";

    cout << start << " ";

    while (!s.empty()) {
        int node = s.top();
        s.pop();
        if (visited[node]) continue;
        visited[node] = true;           //makes sure that a node is visited only after it is processed, not when it is skipped due to heuristics

        if (node == goal) {
            found = true;
            break;
        }
        
        vector<pair<int, int>> children;
        for (int j = 0; j < MAX_SIZE; j++) {
            if (adj[node][j] == 1 && !visited[j]) {
                children.push_back({heuristic[j],j});
            }
        }

        sort(children.begin(), children.end(), 
            [](const pair<int, int>& a, const pair<int, int>& b) {   //reverse sort(stack) based on heuristics then lexicography
                if (a.first != b.first) {
                    return a.first > b.first; 
                }
                return a.second > b.second; 
            });

        for (const auto& ch : children) {
            int c = ch.second;
            if (!visited[c]) { 
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
    HCHis(0, 6);
    return 0;
}
