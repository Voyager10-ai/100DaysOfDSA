#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    // Kahn's Algorithm – BFS-based topological sort
    // If we can process all courses (no cycle), return true
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
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

        int processed = 0;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            ++processed;

            for (int next : adj[course]) {
                if (--inDegree[next] == 0)
                    q.push(next);
            }
        }

        return processed == numCourses;
    }
};

// Helper to run a test case
void runTest(int id, int numCourses, vector<vector<int>> prereqs, bool expected) {
    Solution sol;
    bool result = sol.canFinish(numCourses, prereqs);
    cout << "Test " << id << ": " << (result == expected ? "PASS" : "FAIL")
         << " (got " << (result ? "true" : "false")
         << ", expected " << (expected ? "true" : "false") << ")" << endl;
}

int main() {
    // Test 1: LeetCode Example 1 – 2 courses, one prerequisite, no cycle
    runTest(1, 2, {{1,0}}, true);

    // Test 2: LeetCode Example 2 – 2 courses, mutual prerequisite (cycle)
    runTest(2, 2, {{1,0},{0,1}}, false);

    // Test 3: No prerequisites at all
    runTest(3, 5, {}, true);

    // Test 4: Single course
    runTest(4, 1, {}, true);

    // Test 5: Linear chain – 0→1→2→3→4
    runTest(5, 5, {{1,0},{2,1},{3,2},{4,3}}, true);

    // Test 6: Diamond shape – no cycle
    //   0 → 1 → 3
    //   0 → 2 → 3
    runTest(6, 4, {{1,0},{2,0},{3,1},{3,2}}, true);

    // Test 7: 3-node cycle embedded in a larger graph
    //   0→1→2→0, plus 3→4
    runTest(7, 5, {{1,0},{2,1},{0,2},{4,3}}, false);

    // Test 8: Self-loop
    runTest(8, 2, {{0,0}}, false);

    // Test 9: Large chain – stress-lite
    {
        int n = 1000;
        vector<vector<int>> prereqs;
        for (int i = 1; i < n; ++i)
            prereqs.push_back({i, i - 1});
        runTest(9, n, prereqs, true);
    }

    // Test 10: Disconnected components, one has a cycle
    //   Component A: 0→1→2  (no cycle)
    //   Component B: 3→4→5→3 (cycle)
    runTest(10, 6, {{1,0},{2,1},{4,3},{5,4},{3,5}}, false);

    return 0;
}
