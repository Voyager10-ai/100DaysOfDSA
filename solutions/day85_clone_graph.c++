#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() : val(0), neighbors(vector<Node*>()) {}
    Node(int _val) : val(_val), neighbors(vector<Node*>()) {}
    Node(int _val, vector<Node*> _neighbors) : val(_val), neighbors(_neighbors) {}
};

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;

        unordered_map<Node*, Node*> visited;
        queue<Node*> q;

        visited[node] = new Node(node->val);
        q.push(node);

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            for (Node* neighbor : curr->neighbors) {
                if (visited.find(neighbor) == visited.end()) {
                    visited[neighbor] = new Node(neighbor->val);
                    q.push(neighbor);
                }
                visited[curr]->neighbors.push_back(visited[neighbor]);
            }
        }

        return visited[node];
    }
};

// Helper: build an adjacency-list graph from a list of neighbor lists
Node* buildGraph(const vector<vector<int>>& adjList) {
    if (adjList.empty()) return nullptr;

    int n = adjList.size();
    vector<Node*> nodes(n + 1);
    for (int i = 1; i <= n; ++i)
        nodes[i] = new Node(i);

    for (int i = 1; i <= n; ++i)
        for (int nb : adjList[i - 1])
            nodes[i]->neighbors.push_back(nodes[nb]);

    return nodes[1];
}

// Helper: verify the clone is a deep copy with identical structure
bool verifyClone(Node* original, Node* clone) {
    if (!original && !clone) return true;
    if (!original || !clone) return false;

    unordered_map<Node*, Node*> mapping;
    queue<Node*> q;
    q.push(original);
    mapping[original] = clone;

    while (!q.empty()) {
        Node* orig = q.front();
        q.pop();
        Node* copy = mapping[orig];

        if (orig->val != copy->val) return false;
        if (orig == copy) return false;  // must be different objects
        if (orig->neighbors.size() != copy->neighbors.size()) return false;

        for (int i = 0; i < (int)orig->neighbors.size(); ++i) {
            Node* origNb = orig->neighbors[i];
            Node* copyNb = copy->neighbors[i];

            if (origNb->val != copyNb->val) return false;
            if (origNb == copyNb) return false;

            if (mapping.find(origNb) == mapping.end()) {
                mapping[origNb] = copyNb;
                q.push(origNb);
            }
        }
    }
    return true;
}

// Helper: free all nodes reachable from a root
void freeGraph(Node* node) {
    if (!node) return;
    unordered_map<int, bool> freed;
    queue<Node*> q;
    q.push(node);
    freed[node->val] = true;
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        for (Node* nb : curr->neighbors) {
            if (!freed[nb->val]) {
                freed[nb->val] = true;
                q.push(nb);
            }
        }
        delete curr;
    }
}

int main() {
    Solution sol;

    // Test 1: LeetCode Example – 4-node cycle  [[2,4],[1,3],[2,4],[1,3]]
    {
        Node* orig = buildGraph({{2,4},{1,3},{2,4},{1,3}});
        Node* clone = sol.cloneGraph(orig);
        cout << "Test 1: " << (verifyClone(orig, clone) ? "PASS" : "FAIL")
             << " (4-node cycle)" << endl;
        freeGraph(orig);
        freeGraph(clone);
    }

    // Test 2: Single node, no neighbors  [[]]
    {
        Node* orig = new Node(1);
        Node* clone = sol.cloneGraph(orig);
        cout << "Test 2: " << (verifyClone(orig, clone) ? "PASS" : "FAIL")
             << " (single node)" << endl;
        delete orig;
        delete clone;
    }

    // Test 3: Empty graph
    {
        Node* clone = sol.cloneGraph(nullptr);
        cout << "Test 3: " << (clone == nullptr ? "PASS" : "FAIL")
             << " (empty graph)" << endl;
    }

    // Test 4: Two connected nodes  [[2],[1]]
    {
        Node* orig = buildGraph({{2},{1}});
        Node* clone = sol.cloneGraph(orig);
        cout << "Test 4: " << (verifyClone(orig, clone) ? "PASS" : "FAIL")
             << " (two connected nodes)" << endl;
        freeGraph(orig);
        freeGraph(clone);
    }

    // Test 5: Star graph – node 1 connected to all others
    {
        Node* orig = buildGraph({{2,3,4,5},{1},{1},{1},{1}});
        Node* clone = sol.cloneGraph(orig);
        cout << "Test 5: " << (verifyClone(orig, clone) ? "PASS" : "FAIL")
             << " (star graph)" << endl;
        freeGraph(orig);
        freeGraph(clone);
    }

    // Test 6: Fully connected 3-node graph  [[2,3],[1,3],[1,2]]
    {
        Node* orig = buildGraph({{2,3},{1,3},{1,2}});
        Node* clone = sol.cloneGraph(orig);
        cout << "Test 6: " << (verifyClone(orig, clone) ? "PASS" : "FAIL")
             << " (fully connected 3 nodes)" << endl;
        freeGraph(orig);
        freeGraph(clone);
    }

    // Test 7: Linear chain  1-2-3-4-5
    {
        Node* orig = buildGraph({{2},{1,3},{2,4},{3,5},{4}});
        Node* clone = sol.cloneGraph(orig);
        cout << "Test 7: " << (verifyClone(orig, clone) ? "PASS" : "FAIL")
             << " (linear chain)" << endl;
        freeGraph(orig);
        freeGraph(clone);
    }

    return 0;
}
