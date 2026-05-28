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

int main() {
    return 0;
}
