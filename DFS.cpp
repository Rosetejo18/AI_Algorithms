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

struct Node {
    int nd;
    vector<int> path; //all parents in the corresponding branch
};

void DFS(int start, int goal) {
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

        vector<int> children;
        for (int j = 0; j < MAX_SIZE; j++) {
            if (adj[node.nd][j] == 1 && find(node.path.begin(), node.path.end(), j) == node.path.end()) {
                children.push_back(j);
                cout << j << " ";
            }
        }

        sort(children.rbegin(), children.rend()); //Sort children in descending order stack(lifo)

        for (int c : children) {
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
    cout << "DFS without history: Start = 0 and Goal = 4\n";
    DFS(0, 6);
    return 0;
}










