#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
    int rows, cols;
    int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

    void bfs(vector<vector<int>>& heights, vector<vector<bool>>& reachable,
             queue<pair<int,int>>& q) {
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            for (auto& d : dirs) {
                int nr = r + d[0], nc = c + d[1];
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols
                    && !reachable[nr][nc]
                    && heights[nr][nc] >= heights[r][c]) {
                    reachable[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
    }

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if (heights.empty() || heights[0].empty()) return {};

        rows = heights.size();
        cols = heights[0].size();

        vector<vector<bool>> pacific(rows, vector<bool>(cols, false));
        vector<vector<bool>> atlantic(rows, vector<bool>(cols, false));

        queue<pair<int,int>> pacQ, atlQ;

        for (int i = 0; i < rows; ++i) {
            pacific[i][0] = true;
            pacQ.push({i, 0});
            atlantic[i][cols - 1] = true;
            atlQ.push({i, cols - 1});
        }
        for (int j = 0; j < cols; ++j) {
            pacific[0][j] = true;
            pacQ.push({0, j});
            atlantic[rows - 1][j] = true;
            atlQ.push({rows - 1, j});
        }

        bfs(heights, pacific, pacQ);
        bfs(heights, atlantic, atlQ);

        vector<vector<int>> result;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if (pacific[i][j] && atlantic[i][j])
                    result.push_back({i, j});

        return result;
    }
};

// Helper to print result cells
void printResult(const string& label, const vector<vector<int>>& res) {
    cout << label << " [";
    for (int i = 0; i < (int)res.size(); ++i) {
        cout << "[" << res[i][0] << "," << res[i][1] << "]";
        if (i + 1 < (int)res.size()) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;

    // Test 1: LeetCode Example 1
    {
        vector<vector<int>> heights = {
            {1,2,2,3,5},
            {3,2,3,4,4},
            {2,4,5,3,1},
            {6,7,1,4,5},
            {5,1,1,2,4}
        };
        auto res = sol.pacificAtlantic(heights);
        printResult("Test 1:", res);
        // Expected: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
    }

    // Test 2: LeetCode Example 2 – all same height
    {
        vector<vector<int>> heights = {
            {1,1},
            {1,1}
        };
        auto res = sol.pacificAtlantic(heights);
        printResult("Test 2:", res);
        // Expected: [[0,0],[0,1],[1,0],[1,1]]
    }

    return 0;
}
