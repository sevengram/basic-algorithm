#include "common.h"

bool isNumber(const string &s)
{
    return s != "+" && s != "-" && s != "*" && s != "/";
}

int evalRPN(std::vector<std::string> &tokens)
{
    stack<int> stk;
    for (string s: tokens) {
        if (isNumber(s)) {
            stk.push(atoi(s.c_str()));
        } else {
            if (stk.empty()) {
                throw -1;
            }
            int op1 = stk.top();
            stk.pop();
            if (stk.empty()) {
                throw -1;
            }
            int op2 = stk.top();
            stk.pop();
            switch (s[0]) {
                case '+':
                    stk.push(op1 + op2);
                    break;
                case '-':
                    stk.push(op1 - op2);
                    break;
                case '*':
                    stk.push(op1 * op2);
                    break;
                case '/':
                    stk.push(op1 / op2);
                default:
                    throw -1;
            }
        }
    }
    if (stk.size() == 1) {
        return stk.top();
    } else {
        throw -1;
    }
}
