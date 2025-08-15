#include<iostream>
#include<vector>
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

struct Node {
    int nd;
    vector<int> path;
};

void HC(int start, int goal) {
    stack<Node> s;
    s.push({start, {start}});
    bool found = false;

    cout << "Traversal: ";

    while (!s.empty()) {
        Node node = s.top();
        s.pop();

        if (node.nd == goal) {
            found = true;
            cout << "\nPath from " << start << " to " << goal << ": ";
            for (int v : node.path) {
                cout << v << " ";
            }
            cout << endl;
            break;
        }

        vector<pair<int,int>> children;
        for (int j = 0; j < MAX_SIZE; j++) {
            if (adj[node.nd][j] == 1 && find(node.path.begin(), node.path.end(), j) == node.path.end()) {
                children.push_back({heuristic[j],j});
                cout << j << " ";
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
            vector<int> newPath = node.path;
            newPath.push_back(c);
            s.push({c, newPath});
        }

    }

    if (!found) {
        cout << "No path found from " << start << " to " << goal << endl;
    }
}

int main() {
    cout << "Hill Climbing: Start = 0 and Goal = 6" << endl;
    HC(0, 6);
    return 0;
}