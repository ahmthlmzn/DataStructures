#include <string>
#include<stack>
#include<sstream>
using namespace std;
int pre(char c)
{
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}
///----------------------------------------------------------------------------------
/// Given an expression in infix-notation, converts it to a string in post-fix notation 
/// 

string Infix2Postfix(string& s) {
    stack<char> postfix;
    stringstream ss(s);
    string result;
    char ch;
    while (ss >> ch)
    {
        if (isdigit(ch))
            result += ch;
        else if (ch == '(')
            postfix.push('(');
        else if (ch == ')')
        {
            while (!postfix.empty() && postfix.top() != '(')
            {
                result += ' ';
                result += postfix.top();
                postfix.pop();
            }
            postfix.pop();
        }
        else
        {
            result += ' ';
            while (!postfix.empty() && pre(ch) <= pre(postfix.top()))
            {
                result += postfix.top();
                result += ' ';
                postfix.pop();
            }
            postfix.push(ch);
        }
    }

    while (!postfix.empty())
    {
        result += ' ';
        result += postfix.top();
        postfix.pop();
    }
    return result;
} // end-Infix2Postfix

///----------------------------------------------------------------------------------
/// Given a string in post-fix notation, evaluates it and returns the result
/// 
int EvaluatePostfixExpression(string& s) {
    stack<int> value;
    stringstream splitedString(s);
    string str;
    while (splitedString >> str)
    {
        if (str != "-" && str != "+" && str != "*" && str != "/")
            value.push(stoi(str));
        else
        {
            int number1 = value.top();
            value.pop();
            int number2 = value.top();
            value.pop();
            if (str == "+")
                value.push(number1 + number2);
            else if (str == "-")
                value.push(number2 - number1);
            else if (str == "*")
                value.push(number2 * number1);
            else if (str == "/")
                value.push(number2 / number1);
        }
    }
    return value.top();
} // end-EvaluatePostfixExpression
