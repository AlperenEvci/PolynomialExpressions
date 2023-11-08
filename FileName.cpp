#include <iostream>
#include <stack>
#include <vector>
using namespace std;

bool is_opr(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int prec_value(char c) {
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return 0;
}

string Infix2Postfix(string& s) {
    string result = "";
    stack<char> stack_oper;

    for (auto each : s) {
        if ((each >= '0' && each <= '9'))       
            result += each;
        else if (each == '(')
        {
            stack_oper.push(each);
        }
        else if (each == ')') {
            while (!stack_oper.empty() && stack_oper.top() != '(') {               
                result += " ";
                result += stack_oper.top();
                stack_oper.pop();
            }
            if (!stack_oper.empty() && stack_oper.top() == '(') {
                stack_oper.pop();
            }
        }
        else if (is_opr(each)) {
            result += " ";
            while (!stack_oper.empty() && prec_value(stack_oper.top()) >= prec_value(each)) {           
                result += stack_oper.top();
                result += " ";
                stack_oper.pop();
            }
            stack_oper.push(each);
            

        }
        
    }
    while (!stack_oper.empty()) {
        result += " ";
        result += stack_oper.top();
        stack_oper.pop();
    }

    return result;
}

int main() {
    string my_array = "3500 - ((43 * 12) + (47 / 2))";
    cout << Infix2Postfix(my_array);
    return 0;
}
