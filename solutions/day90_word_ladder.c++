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

// Helper to run a test case
void runTest(int id, string beginWord, string endWord, vector<string> wordList, int expected) {
    Solution sol;
    int result = sol.ladderLength(beginWord, endWord, wordList);
    cout << "Test " << id << ": " << (result == expected ? "PASS" : "FAIL")
         << " (got " << result << ", expected " << expected << ")" << endl;
}

int main() {
    // Test 1: LeetCode Example 1 – "hit" → "cog" via hot→dot→dog→cog = 5
    runTest(1, "hit", "cog",
            {"hot","dot","dog","lot","log","cog"}, 5);

    // Test 2: LeetCode Example 2 – "hit" → "cog", but "cog" not in list → 0
    runTest(2, "hit", "cog",
            {"hot","dot","dog","lot","log"}, 0);

    // Test 3: beginWord equals endWord concept – but endWord must be in list
    //   "a" → "c" via a→b→c = 3
    runTest(3, "a", "c", {"a","b","c"}, 2);

    // Test 4: Single-letter words, no path – "a" → "z", only "b" available
    runTest(4, "a", "z", {"b"}, 0);

    // Test 5: Direct one-hop transformation – "ab" → "ac"
    runTest(5, "ab", "ac", {"ac"}, 2);

    // Test 6: No transformation possible – completely disjoint words
    runTest(6, "aaa", "zzz", {"bbb","ccc"}, 0);

    // Test 7: Longer chain – "aaaa" → "cccc"
    //   aaaa→aaac→aacc→accc→cccc = 5
    runTest(7, "aaaa", "cccc",
            {"aaac","aacc","accc","cccc"}, 5);

    // Test 8: Multiple shortest paths exist – should still return correct length
    //   hit → hot → {dot, lot} → {dog, log} → cog = 5
    runTest(8, "hit", "cog",
            {"hot","dot","dog","lot","log","cog","hog"}, 5);

    return 0;
}
