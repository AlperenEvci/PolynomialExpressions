#include <string>
#include <stack>
#include <vector>
#include <sstream>
using namespace std;

///----------------------------------------------------------------------------------
/// Given an expression in infix-notation, converts it to a string in post-fix notation 
/// 
 
bool is_opr(char c) {
    //Bool Function for whether the element is operator or not.
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int prec_value(char c) {
    //assigning the precendence value to our operators.
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return 0;
}

string Infix2Postfix(string &s) {
   
    //defining a string array for our result.
    string result = "";
    stack<char> stack_oper;

    for (auto each : s) {
        //controlling each chars in input whether its a digit or not.
        if ((each >= '0' && each <= '9'))
            //if its a digit add to the result.
            result += each;
        else if (each == '(')
            //if there is a '(' character push towards to the stack.
            stack_oper.push(each);
        
        else if (each == ')') {
            //controlling whether the next element of input is ')'.
            while (!stack_oper.empty() && stack_oper.top() != '(') {
                //if its not a '(' character add the result to the stack.
                result += " ";
                result += stack_oper.top();
                stack_oper.pop();
                //after the adding we must pop it from our stack.
            }
            //if there is a '(' stop and pop the llast element of stack.
            if (!stack_oper.empty() && stack_oper.top() == '(') {
                stack_oper.pop();
            }
        }
        //controlling whether the next element of input is an operator or not.
        else if (is_opr(each)) {
            result += " ";
            
            // until the stack is empty or the priority of the current operator is lower than the priority of the operator at the top of the stack
            while (!stack_oper.empty() && prec_value(stack_oper.top()) >= prec_value(each)) {
                
                result += stack_oper.top(); // the operator at the top of the stack is added to the result
                result += " ";
                stack_oper.pop();// and removed from the stack
            }
            stack_oper.push(each);// current operator is added to the stack


        }

    }
    while (!stack_oper.empty()) {// if the stack is still not empty
        result += " ";
        result += stack_oper.top();// operator at the top of the stack is added to the result
        stack_oper.pop();// and removed from the stack
    }

    return result;
} // end-Infix2Postfix

///----------------------------------------------------------------------------------
/// Given a string in post-fix notation, evaluates it and returns the result
/// 
int EvaluatePostfixExpression(string& s) {
    
    stack<int> operand_stack;
    //Use sstream library for erase the spaces between numbers in our string input.
    stringstream ss(s);
    string element;

    
    while (ss >> element) {
        //controlling each numbers in input whether its a digit or not.
        if ((element[0] >= '0' && (element[0] <= '9'))) {
            //If its a digit we push the number to our stack.
            operand_stack.push(stoi(element));
        }
        else {
            //if there is not enough elements in our stack we must throw an error.
            if (operand_stack.size() < 2)
                throw runtime_error("Invalid postfix expression");

            //Because of the FILO rules the last element of stack is must be our second element.
            int second_element = operand_stack.top();
            operand_stack.pop();
            //Because of the FILO rules the second element of stack is must be our first element.
            int first_element = operand_stack.top();
            operand_stack.pop();

            //check algorithm of operators.
            if (element == "+")
                operand_stack.push(first_element + second_element);
            else if (element == "-")
                operand_stack.push(first_element - second_element);
            else if (element == "/")
                operand_stack.push(first_element / second_element);
            else if (element == "*")
                operand_stack.push(first_element * second_element);
        }
    }
    //If there is a mistake with our input thats throws an error.
    if(operand_stack.size() != 1)
        throw runtime_error("Invalid postfix expression");
    return operand_stack.top();
} // end-EvaluatePostfixExpression
