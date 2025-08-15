#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

#define MAX_SIZE 5

using namespace std;

int adj[MAX_SIZE][MAX_SIZE] = {
    //s a b c d e g
    /*{0,1,1,0,0,0,0},
    {1,0,1,0,1,0,0},
    {1,1,0,1,0,0,0},
    {0,0,1,0,0,1,0},
    {0,1,0,0,0,0,1},
    {0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0}*/
    {0,1,1,0,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {0,1,1,0,1},
    {0,0,0,1,0}

};

struct Node {
    int node;
    vector<int> path; //all parents in the corresponding branch
};

void BFS(int start, int goal) {
    queue<Node> q;
    q.push({start, {start}});
    bool found = false;

    cout << "Traversal:";

    while (!q.empty()) {
        int levelSize = q.size();
        vector<Node> currentLevel;

        for (int i = 0; i < levelSize; i++) {
            currentLevel.push_back(q.front());
            q.pop();
        }


        sort(currentLevel.begin(), currentLevel.end(), 
        [](const Node &a, const Node &b) {return a.node < b.node;});  

        for (auto &cur : currentLevel) {
            cout << cur.node << " ";

            if (cur.node == goal) {
                found = true;

                cout << "\nPath from " << start << " to " << goal << ": ";
                for (int v : cur.path) {
                    cout << v << " ";
                }
                cout << endl;

                break;
            }

            vector<int> children;
            for (int j = 0; j < MAX_SIZE; j++) {
                if (adj[cur.node][j] == 1 && find(cur.path.begin(), cur.path.end(), j) == cur.path.end()) {
                    vector<int> newPath = cur.path;
                    newPath.push_back(j);
                    q.push({j, newPath});
                }
            }

        }

        if (found) break;
    }

    if (!found) {
        cout << "No path found from " << start << " to " << goal << endl;
    }
}

int main() {
    cout << "BFS without history: Start = 0 and Goal = 4\n";
    BFS(0, 4);
    return 0;
}
