#include<iostream>
#include<queue>
#include<vector>
#include<stack>
#include<algorithm>

#define MAX_SIZE 7

using namespace std;

int adj[MAX_SIZE][MAX_SIZE] = {
    // s a b c d e g
    {0,1,1,0,0,0,0},
    {1,0,1,0,1,0,0},
    {1,1,0,1,0,0,0},
    {0,0,1,0,0,1,0},
    {0,1,0,0,0,0,1},
    {0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0}
};

struct Node {
    int nd;
    vector<int> path; //all parents in the corresponding branch

    bool operator>(const Node &other) const {
        return nd > other.nd;
    }
};

void BMS(int start, int goal) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    pq.push({start,{start}});
    bool found  = false;

    cout << "Traversal: ";
    cout << start << " ";

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        if (node.nd == goal) {
            found = true;
            cout << "\nPath from " << start << " to " << goal << ": ";
            for (int v : node.path) {
                cout << v << " ";
            }
        }

        for (int i = 0; i < MAX_SIZE; i++) {
            if (adj[node.nd][i] == 1 && find(node.path.begin(), node.path.end(), i) == node.path.end()) {
                vector<int> newPath = node.path;
                newPath.push_back(i);
                pq.push({i, newPath});
                cout << i << " ";
            }
        }
    }

    if (!found) {
        cout << "No path found from " << start << " to " << goal << endl;
    }
    
}

int main() {
    cout << "British museum search: Start = 0 and Goal = 6\n";
    BMS(0, 6);
    cout << endl;
    return 0;
}
