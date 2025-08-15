#include<iostream>
#include<queue>
#include<vector>
#include<stack>
#include<algorithm>

#define MAX_SIZE 7

using namespace std;

int adj[MAX_SIZE][MAX_SIZE] = {
    // s a b c d e g
    {0,3,5,0,0,0,0},
    {3,0,4,0,5,0,0},
    {5,4,0,4,0,0,0},
    {0,0,4,0,0,6,0},
    {0,5,0,0,0,0,3},
    {0,0,0,6,0,0,0},
    {0,0,0,0,3,0,0}
};

struct Node {
    int nd;
    int cost;
    vector<int> path; //all parents in the corresponding branch

    bool operator>(const Node &other) const {
        return cost > other.cost;
    }
};

void oracle(int start, int goal) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    pq.push({start, 0, {start}});
    bool found  = false;

    cout << "Traversal: ";
    //cout << start << " ";

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        cout << node.nd << " ";
        if (node.nd == goal) {
            found = true;
            cout << "\n\nPath from " << start << " to " << goal << ": ";
            for (int v : node.path) {
                cout << v << " ";
    
            }
            cout << "\nCost = " << node.cost << endl;
            cout << endl;
        }

        for (int i = 0; i < MAX_SIZE; i++) {
            if (adj[node.nd][i] > 0 && find(node.path.begin(), node.path.end(), i) == node.path.end()) {
                vector<int> newPath = node.path;
                newPath.push_back(i);
                int curCost = node.cost;
                int adjCost = adj[node.nd][i];
                int newCost = curCost + adjCost;
                pq.push({i,newCost, newPath});
                //cout << i << " ";
            }
        }
    }

    if (!found) {
        cout << "No path found from " << start << " to " << goal << endl;
    }
    
}

int main() {
    cout << "Oracle search: Start = 0 and Goal = 6\n";
    oracle(0, 6);
    cout << endl;
    return 0;
}
