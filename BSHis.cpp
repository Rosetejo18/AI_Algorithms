#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<limits>

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

struct compHeuristics {
    bool operator()(const int& a, const int& b) const {
        if (heuristic[a] != heuristic[b])
            return heuristic[a] > heuristic[b];
        else
            return a > b;
    }
};

void BeamSearch(int start, int goal, int beam_width) {
    if (beam_width <= 0) {
        cout << "Beam width must be positive." << endl;
        return;
    }
    
    bool visited[MAX_SIZE] = {false};
    int parent[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++)
        parent[i] = -1;

    priority_queue<int, vector<int>, compHeuristics> pq;
    pq.push(start);
    visited[start] = true;
    
    bool found = false;
    cout << "Traversal:\n";

    while (!pq.empty()) {
        vector<int> currentLevel;
        while (!pq.empty()) {
            currentLevel.push_back(pq.top());
            pq.pop();
        }

        if (currentLevel.size() > beam_width) {
            currentLevel.resize(beam_width);
        }

        for (const auto& node : currentLevel) {
            cout << node << " ";
            if (node == goal) {
                found = true;
                break;
            }

            for (int j = 0; j < MAX_SIZE; j++) {
                if (adj[node][j] == 1 && !visited[j]) {
                    parent[j] = node;
                    pq.push(j);
                    visited[j] = true;
                    //cout << j << " ";
                }
            }
        }
        cout << endl;
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
    cout << "Beam Search: Start = 0 and Goal = 6 (Beam Width = 2)" << endl;
    BeamSearch(0, 6, 2);
    return 0;
}