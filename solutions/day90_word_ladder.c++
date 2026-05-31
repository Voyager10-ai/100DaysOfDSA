#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// Check if two words differ by exactly one character
bool isAdjacent(const string& a, const string& b) {
    if (a.size() != b.size()) return false;
    int diff = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        if (a[i] != b[i]) ++diff;
        if (diff > 1) return false;
    }
    return diff == 1;
}

class Solution {
public:
    // BFS – shortest transformation sequence from beginWord to endWord
    // Returns the number of words in the sequence (including begin & end), or 0 if unreachable
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());

        // endWord must be in the dictionary
        if (wordSet.find(endWord) == wordSet.end())
            return 0;

        // Build adjacency via wildcard patterns: "hot" → {"*ot", "h*t", "ho*"}
        unordered_map<string, vector<string>> patternMap;
        wordSet.insert(beginWord); // include beginWord for pattern building
        for (auto& w : wordSet) {
            for (int i = 0; i < (int)w.size(); ++i) {
                string pattern = w;
                pattern[i] = '*';
                patternMap[pattern].push_back(w);
            }
        }

        // BFS from beginWord
        queue<string> q;
        unordered_set<string> visited;
        q.push(beginWord);
        visited.insert(beginWord);
        int depth = 1;

        while (!q.empty()) {
            int levelSize = q.size();
            for (int l = 0; l < levelSize; ++l) {
                string curr = q.front();
                q.pop();

                if (curr == endWord)
                    return depth;

                // Explore all neighbors via wildcard patterns
                for (int i = 0; i < (int)curr.size(); ++i) {
                    string pattern = curr;
                    pattern[i] = '*';
                    for (auto& neighbor : patternMap[pattern]) {
                        if (visited.find(neighbor) == visited.end()) {
                            visited.insert(neighbor);
                            q.push(neighbor);
                        }
                    }
                }
            }
            ++depth;
        }

        return 0; // no path found
    }
};
