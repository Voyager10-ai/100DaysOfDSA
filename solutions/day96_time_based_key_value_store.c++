#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// LeetCode 981 – Time Based Key-Value Store
// Design a data structure that stores multiple values for the same key at
// different timestamps and retrieves the value at a certain timestamp.
//
// Operations:
//   set(key, value, timestamp) – Stores key with value at the given timestamp.
//   get(key, timestamp) – Returns the value set for key at the largest
//                          timestamp <= the given timestamp, or "" if none.
//
// Guarantee: All timestamps in set() calls are strictly increasing.
//
// Algorithm:
//   - Use an unordered_map where each key maps to a vector of {timestamp, value}
//     pairs. Since set() is called with strictly increasing timestamps, each
//     vector is already sorted by timestamp.
//   - For get(), binary search the vector to find the largest timestamp <= query.
//
// Time Complexity:
//   set(): O(1) amortized — just append to the vector
//   get(): O(log n) — binary search over stored timestamps
// Space Complexity: O(total set calls)

class TimeMap {
    // Each key maps to a sorted list of (timestamp, value) pairs
    unordered_map<string, vector<pair<int, string>>> store;

public:
    TimeMap() {}

    void set(string key, string value, int timestamp) {
        store[key].push_back({timestamp, value});
    }

    string get(string key, int timestamp) {
        if (store.find(key) == store.end()) return "";

        const auto& entries = store[key];
        int lo = 0, hi = (int)entries.size() - 1;
        string result = "";

        // Binary search for the largest timestamp <= given timestamp
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (entries[mid].first <= timestamp) {
                result = entries[mid].second;  // candidate answer
                lo = mid + 1;                  // try to find a later one
            } else {
                hi = mid - 1;
            }
        }

        return result;
    }
};

// Helper to check a get() result
int testNum = 0;
void check(const string& result, const string& expected, const string& desc) {
    ++testNum;
    bool pass = (result == expected);
    cout << "Test " << testNum << ": " << (pass ? "PASS" : "FAIL")
         << " — " << desc
         << " (got \"" << result << "\", expected \"" << expected << "\")" << endl;
}

int main() {
    // ---- LeetCode Example 1 ----
    {
        TimeMap tm;
        tm.set("foo", "bar", 1);

        check(tm.get("foo", 1), "bar",
              "get foo at exact timestamp 1");

        check(tm.get("foo", 3), "bar",
              "get foo at timestamp 3 (returns latest <= 3)");

        tm.set("foo", "bar2", 4);

        check(tm.get("foo", 4), "bar2",
              "get foo at exact timestamp 4");

        check(tm.get("foo", 5), "bar2",
              "get foo at timestamp 5 (returns latest <= 5)");
    }

    // ---- LeetCode Example 2: query before any set ----
    {
        TimeMap tm;
        tm.set("love", "high", 10);
        tm.set("love", "low", 20);

        check(tm.get("love", 5), "",
              "get before any timestamp returns empty");

        check(tm.get("love", 10), "high",
              "get at exact first timestamp");

        check(tm.get("love", 15), "high",
              "get between two timestamps");

        check(tm.get("love", 20), "low",
              "get at exact second timestamp");

        check(tm.get("love", 25), "low",
              "get after all timestamps");
    }

    return 0;
}
