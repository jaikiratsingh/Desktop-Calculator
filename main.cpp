/*
*   This is the main file that acts as the entry point for the application : Desktop Calculator
*   Developed By : Jaikirat Singh Sandhu
*                   2016UCO1541
*                   COE - 1
*   Developed Under : Dr. Pinaki Chakraborty
                      Department of Computer Engineering
                      NSUT, New Delhi
*/

#include <iostream>
#include <string>
#include <vector>
#include <stack>

// FUNCTION DECLARATIONS
std::vector<std::string> parseExpression(std::string expression);
std::vector<std::string> infixToPostfix(std::vector<std::string> infix_tokens);
bool isOperand(std::string token);
int getPrecedence(std::string oper);
void showError();

int main() {
    // Get the expression from the user
    std::string expression;
    std::cout << "Please Enter the Expression : >>" << std::endl;
    getline(std::cin, expression);

    // Parse the tokens from the expression
    std::vector<std::string> tokens = parseExpression(expression);

    // convert to postfix
    std::vector<std::string> postfix_tokens = infixToPostfix(tokens);

    for(auto it : postfix_tokens) {
        std::cout << it << std::endl;
    }
}

// FUNCTION DEFINITIONS

// takes infix tokens as input and returns postfix tokens
std::vector<std::string> infixToPostfix(std::vector<std::string> infix_tokens) {
    std::vector<std::string>::iterator token_ptr;
    
    std::stack<std::string> s;  // stack used to convert to postfix
    std::vector<std::string> retvec;    // vector that is returned from this function

    for(token_ptr = infix_tokens.begin(); token_ptr != infix_tokens.end(); token_ptr = next(token_ptr)) {
        std::string token = *token_ptr;

        if(isOperand(token)) {
            retvec.push_back(token);
        }else if(token == "(") {
            s.push(token);
        }else if(token == ")") {
            while(!s.empty() && s.top() != "(") {
                retvec.push_back(s.top());
                s.pop();
            }

            if(!s.empty() && s.top() != "(") {
                showError();
            }else {
                s.pop();
            }
        }else {
            while(!s.empty() && getPrecedence(token) <= getPrecedence(s.top())) {
                retvec.push_back(s.top());
                s.pop();
            }
            s.push(token);
        }
    }

    while(!s.empty()) {
        retvec.push_back(s.top());
        s.pop();
    }

    return retvec;
}

// tells if the input is operand or not
bool isOperand(std::string token) {
    return (!(token == "*" || token == "+" || token == "/" || token == "-" || token == "^" || token == "(" || token == ")"));
}

// returns precedence of an operator, higher value means higher precedence
int getPrecedence(std::string oper) {
    switch(oper[0]) {
        case '+' :
        case '-' :
            return 1;
        case '*' :
        case '/' :
            return 2;
        case '^' :
            return 3;
    }

    return -1;
}

// Parses the expression, extracts all the tokens and returns it in a form of a vector
std::vector<std::string> parseExpression(std::string expression) {
    expression += ' ';  // add sentinal character at the end

    int len = (int) expression.length();
    int index = 0;

    // return vector
    std::vector<std::string> retVal;
    
    // remove initial spaces;
    while(index < len) {
        if(expression[index] == 9 || expression[index] == 32)
            index++;
        else
            break;
    }

    // extract tokens
    int firstPointer = index;
    while(index < len) {
        if(expression[index] >= '0' && expression[index] <= '9') {
            index++;
        } else if(expression[index] == '*' || expression[index] == '/' || expression[index] == '+' || expression[index] == '-' || expression[index] == '^' || expression[index] == '(' || expression[index] == ')') {
            retVal.push_back(expression.substr(firstPointer, index - firstPointer));
            retVal.push_back(expression.substr(index, 1));
            firstPointer = index+1;
            index++;
        }else {
            retVal.push_back(expression.substr(firstPointer, index - firstPointer));
            while(index < len) {
                if(expression[index] == 9 || expression[index] == 32)
                    index++;    
                else
                    break;
            }
            firstPointer = index;
            index++;
        }
    }

    // create tokens
    std::vector<std::string> finalRetVal;

    for(int i = 0; i < (int)retVal.size(); i++) {
        std::string s = "";

        for(int j = 0; j < (int)retVal[i].length(); j++) {
            if(retVal[i][j] != 9 && retVal[i][j] != 32) {
                s += retVal[i][j];
            }
        }

        if(s.length() > 0) {
            finalRetVal.push_back(s);
        }
    }

    return finalRetVal;
}

// shows the error, if it has occurred
void showError() {
    std::cout << "There is some kind of error in your given expression. Kindly review it" << std::endl;
    exit(0);
}

// ((123 + 5) * 2) / 2