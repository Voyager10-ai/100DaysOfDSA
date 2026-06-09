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
