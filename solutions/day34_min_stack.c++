#include <iostream>
#include <stack>

using namespace std;

class MinStack {
private:
    stack<int> s;
    stack<int> minStack;

public:
    MinStack() {
        
    }
    
    void push(int val) {
        s.push(val);
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }
    
    void pop() {
        if (!s.empty()) {
            if (s.top() == minStack.top()) {
                minStack.pop();
            }
            s.pop();
        }
    }
    
    int top() {
        if (!s.empty()) {
            return s.top();
        }
        return -1;
    }
    
    int getMin() {
        if (!minStack.empty()) {
            return minStack.top();
        }
        return -1;
    }
};

int main() {
    MinStack* obj = new MinStack();
    obj->push(-2);
    obj->push(0);
    obj->push(-3);
    cout << "Min: " << obj->getMin() << endl; // returns -3
    
    obj->pop();
    cout << "Top: " << obj->top() << endl;    // returns 0
    cout << "Min: " << obj->getMin() << endl; // returns -2
    
    delete obj;
    return 0;
}
