#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (char c : s) {
            if (c == '(' || c == '{' || c == '[') {
                st.push(c);
            } else {
                if (st.empty()) return false;
                char top = st.top();
                st.pop();
                if ((c == ')' && top != '(') ||
                    (c == '}' && top != '{') ||
                    (c == ']' && top != '[')) {
                    return false;
                }
            }
        }
        return st.empty();
    }
};

int main() {
    Solution sol;
    string s1 = "()";
    string s2 = "()[]{}";
    string s3 = "(]";
    
    cout << "Is \"" << s1 << "\" valid? " << (sol.isValid(s1) ? "Yes" : "No") << endl;
    cout << "Is \"" << s2 << "\" valid? " << (sol.isValid(s2) ? "Yes" : "No") << endl;
    cout << "Is \"" << s3 << "\" valid? " << (sol.isValid(s3) ? "Yes" : "No") << endl;
    
    return 0;
}
