#include<iostream>
#include<vector>
#include<queue>
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

struct Node {
    int nd;
    vector<int> path;

    bool operator>(const Node &other) const {
        if (heuristic[nd] != heuristic[other.nd])
            return heuristic[nd] > heuristic[other.nd];
        else
            return nd > other.nd;
    }
};


void BeamSearch(int start, int goal, int beam_width) {
    if (beam_width <= 0) {
        cout << "Beam width must be positive." << endl;
        return;
    }
            
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({start, {start}});
    
    bool found = false;
    cout << "Traversal:\n";

    while (!pq.empty()) {
        vector<Node> currentLevel;
        while (!pq.empty()) {
            currentLevel.push_back(pq.top());
            pq.pop();
        }

        //backtracking yet to be implemented here
        if (currentLevel.size() > beam_width) {
            currentLevel.resize(beam_width);
        }

        for (const auto& node : currentLevel) {
            //cout << node.nd << " ";

            if (node.nd == goal) {
                found = true;
                cout << "\nPath from " << start << " to " << goal << ": ";
                for (int v : node.path) {
                    cout << v << " ";
                }
                cout << endl;
                return;
            }

            for (int j = 0; j < MAX_SIZE; j++) {
                if (adj[node.nd][j] == 1 && find(node.path.begin(), node.path.end(), j) == node.path.end()) {
                    vector<int> newPath = node.path;
                    newPath.push_back(j);
                    pq.push({j, newPath});
                    cout << j << " ";
                }
            }
        }
        cout << endl;
    }

    if (!found) {
        cout << "No path found from " << start << " to " << goal << endl;
    }
}

int main() {
    cout << "Beam Search: Start = 0 and Goal = 6 (Beam Width = 2)" << endl;
    BeamSearch(0, 6, 2);
    return 0;
}