#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    // Kahn's Algorithm – BFS topological sort
    // Returns a valid course ordering, or empty vector if a cycle exists
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> inDegree(numCourses, 0);

        // Build adjacency list and compute in-degrees
        for (auto& p : prerequisites) {
            adj[p[1]].push_back(p[0]);
            inDegree[p[0]]++;
        }

        // Seed the queue with all courses having no prerequisites
        queue<int> q;
        for (int i = 0; i < numCourses; ++i)
            if (inDegree[i] == 0)
                q.push(i);

        vector<int> order;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            order.push_back(course);

            for (int next : adj[course]) {
                if (--inDegree[next] == 0)
                    q.push(next);
            }
        }

        // If we couldn't schedule every course, a cycle exists
        if ((int)order.size() != numCourses)
            return {};

        return order;
    }
};

// Helper: verify that 'order' is a valid topological ordering
bool isValidOrder(int numCourses, vector<vector<int>>& prereqs, vector<int>& order) {
    if ((int)order.size() != numCourses) return false;

    // Map each course to its position in the ordering
    vector<int> pos(numCourses, -1);
    for (int i = 0; i < (int)order.size(); ++i)
        pos[order[i]] = i;

    // Every prerequisite must appear before the course it unlocks
    for (auto& p : prereqs) {
        if (pos[p[1]] >= pos[p[0]])
            return false;
    }
    return true;
}

void runTest(int id, int numCourses, vector<vector<int>> prereqs, bool canFinish) {
    Solution sol;
    vector<int> result = sol.findOrder(numCourses, prereqs);

    if (!canFinish) {
        // Expect empty result when a cycle exists
        bool pass = result.empty();
        cout << "Test " << id << ": " << (pass ? "PASS" : "FAIL")
             << " (expected empty, got size " << result.size() << ")" << endl;
    } else {
        bool pass = isValidOrder(numCourses, prereqs, result);
        cout << "Test " << id << ": " << (pass ? "PASS" : "FAIL")
             << " (order: [";
        for (int i = 0; i < (int)result.size(); ++i)
            cout << result[i] << (i + 1 < (int)result.size() ? "," : "");
        cout << "])" << endl;
    }
}

int main() {
    // Test 1: LeetCode Example 1 – 2 courses, one prerequisite
    runTest(1, 2, {{1,0}}, true);

    // Test 2: LeetCode Example 2 – 4 courses, multiple prerequisites
    runTest(2, 4, {{1,0},{2,0},{3,1},{3,2}}, true);

    // Test 3: Single course, no prerequisites
    runTest(3, 1, {}, true);

    // Test 4: Cycle – impossible to finish
    runTest(4, 2, {{1,0},{0,1}}, false);

    // Test 5: No prerequisites at all – any permutation is valid
    runTest(5, 4, {}, true);

    // Test 6: Linear chain 0→1→2→3
    runTest(6, 4, {{1,0},{2,1},{3,2}}, true);

    // Test 7: Diamond DAG
    //   0 → 1 → 3
    //   0 → 2 → 3
    runTest(7, 4, {{1,0},{2,0},{3,1},{3,2}}, true);

    // Test 8: 3-node cycle embedded in a larger graph
    runTest(8, 5, {{1,0},{2,1},{0,2},{4,3}}, false);

    // Test 9: Self-loop
    runTest(9, 3, {{0,0}}, false);

    // Test 10: Large chain – stress-lite (1000 courses)
    {
        int n = 1000;
        vector<vector<int>> prereqs;
        for (int i = 1; i < n; ++i)
            prereqs.push_back({i, i - 1});
        runTest(10, n, prereqs, true);
    }

    // Test 11: Disconnected components – one with a cycle
    runTest(11, 6, {{1,0},{2,1},{4,3},{5,4},{3,5}}, false);

    // Test 12: Disconnected components – both acyclic
    runTest(12, 6, {{1,0},{2,1},{4,3},{5,4}}, true);

    return 0;
}
