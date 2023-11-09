#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
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

int EvaluatePostfixExpression(string& s) {
    stack<int> stk;
    stringstream ss(s);
    string element;
    while (ss >> element){
        if (isdigit(element[0])) {
            stk.push(stoi(element));
        }

        else{
            if (stk.size() < 2)
                throw runtime_error("Invalid postfix expression");
            
            int second_element = stk.top();
            stk.pop();
            int first_element = stk.top();
            stk.pop();

            if (element == "+")
            {
                stk.push(first_element + second_element);
            }
            else if (element == "-")
            {
                stk.push(first_element - second_element);
            }
            else if (element == "/")
            {
                stk.push(first_element / second_element);
            }
            else if (element == "*")
            {
                stk.push(first_element * second_element);
            }
        }
            
    }
    if (stk.size() != 1)
        throw runtime_error("Invalid postfix expression");

    return stk.top();
}
int main() {
    string my_array = "3500 - ((43 * 12) + (47 / 2))";
    cout << Infix2Postfix(my_array) << endl;
    string postfix = Infix2Postfix(my_array);
    cout << EvaluatePostfixExpression(postfix);

    return 0;
}
