#include<iostream>
#include<queue>
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

void BFSHis(int start, int goal) {
    bool visited[MAX_SIZE] = {false};
    int parent[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++)
        parent[i] = -1;

    queue<int> q;
    visited[start] = true;
    q.push(start);
    bool found = false;
    cout << "Traversal: ";

    while (!q.empty()) {
        int levelSize = q.size(); 
        vector<int> currentLevel;
        for (int i = 0; i < levelSize; i++) {
            currentLevel.push_back(q.front());
            q.pop();
        }   
    
        sort(currentLevel.begin(), currentLevel.end());  //sort lexicographically 

        for (auto &node : currentLevel){
            cout << node << " ";

            if (node == goal) {
                found = true;
                break;
            }

            for (int j = 0; j < MAX_SIZE; j++) {
                if (adj[node][j] == 1 && !visited[j]) {
                    visited[j] = true;
                    parent[j] = node;
                    q.push(j);
                }
            }

        }

        if (found) break;
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
    cout << "BFS with history: Start = 0 and Goal = 6\n";
    BFSHis(0, 6);
    return 0;
}
