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

int main() {
    return 0;
}
