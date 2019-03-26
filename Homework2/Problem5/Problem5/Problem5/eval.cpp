//
//  main.cpp
//  Problem5
//
//  Created by Samritha Nagesh on 2/3/19.
//  Copyright © 2019 Samritha Nagesh. All rights reserved.
//

#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

bool checkValid(string infix);
int checkPrec(char op);

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result){
    if(!checkValid(infix))
        return 1;
    //Infix to Postfix Conversion
    postfix = "";
    stack<char> operatorStack;
    
    for(int i=0; i<infix.size(); i++){
        switch(infix[i]){
            case '!':
            case '&':
            case '|':
                while( !operatorStack.empty() && operatorStack.top() != '('
                      && checkPrec(infix[i]) <= checkPrec(operatorStack.top()) )
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                    
                }
                operatorStack.push(infix[i]);
                break;
            case '(':
                operatorStack.push(infix[i]);
                break;
            case ')':
                while(operatorStack.top() != '('){
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.pop();
                break;
            case ' ':
                break;
            default:
                if(isalpha(infix[i]) && islower(infix[i]))
                    postfix+=infix[i];
                break;
        }
    }
    while(!operatorStack.empty()){
        postfix+=operatorStack.top();
        operatorStack.pop();
    }
    
    //Evaluationg Postfix
    stack<bool> operandStack;
    bool op1, op2;
    for(int i=0; i<postfix.size(); i++){
        if(isalpha(postfix[i])){
            if( trueValues.contains(postfix[i]) && !falseValues.contains(postfix[i]) ){
                operandStack.push(true);
            }
            else if( !trueValues.contains(postfix[i]) && falseValues.contains(postfix[i]) ){
                operandStack.push(false);
            }
            else if( trueValues.contains(postfix[i]) && falseValues.contains(postfix[i]) ){
                return 3;
            }
            else if( !trueValues.contains(postfix[i]) && !falseValues.contains(postfix[i]) ){
                return 2;
            }
        }
        else{
            if(postfix[i] == '!'){
                bool op = operandStack.top();
                operandStack.pop();
                operandStack.push(!op);
            }
            else{
                op2 = operandStack.top();
                operandStack.pop();
                op1 = operandStack.top();
                operandStack.pop();
                if(postfix[i] == '&'){
                    operandStack.push(op1 && op2);
                }
                if(postfix[i] == '|'){
                    operandStack.push(op1 || op2);
                }
            }
        }
    }
    result = operandStack.top();
    
    return 0;
}
bool checkValid(string infix)
{
    //Remove Spaces
    string removedSpaces;
    for(int i=0; i<infix.size(); i++){
        if(infix[i] != ' '){
            removedSpaces += infix[i];
        }
    }
    infix = removedSpaces;
    
    //Empty string is invalid
    if(infix.size() == 0){
        return false;
    }
    
    
    //No operators at beginning of expression
    switch(infix[0])
    {
        case '&':
        case '|':
            return 1;
            break;
        case ')':
            if(infix[infix.size()-1] != '(')
                return 1;
            break;
        default:
            break;
    }
    
    //valid characters only:
    for(int i=0; i<infix.size();i++)
    {
        switch(infix[i])
        {
            case '!':
            case '&':
            case '|':
                if(i == infix.size()-1){ //if operator is last character
                    return false;
                }
                break;
            case ')':
            case '(':
                break;
            default:
                if(!isalpha(infix[i]) && !islower(infix[i]))
                    return false;
        }
    }
    
    //Necessary operands present
    for(int i=1; i<infix.size(); i++){
        if(infix[i-1] == '&' || infix[i-1] == '|'){
            if(infix[i] == '&' || infix[i] == '|' ){ //Two operators next to each other
                return false;
            }
        }
        if(infix[i-1] == '!'){
            if(infix[i] == '&' || infix[i] == '|'){ //! next to an operator
                return false;
            }
        }
        if(isalpha(infix[i-1])){
            if (isalpha(infix[i]) || isalpha(infix[i]) || infix[i] == '('){ //two operands next to each other
                return false;
            }
        }
        if(infix[i-1] == '('){
            if(infix[i] == '|' || infix[i] == '&' || infix[i] == ')'){ //empty paren or operator at start
                return false;
                
            }
        }
        
    }
    
    //Check parentheses match
    int openParen = 0;
    int closeParen = 0;
    for(int i=0; i< infix.size(); i++){
        switch(infix[i])
        {
            case '(':
                openParen++;
                break;
            case ')':
                closeParen++;
                break;
            default:
                break;
        }
    }
    if (openParen != closeParen)
        return false;
    
    
    return true;
}
int checkPrec(char op){
    if (op == '!')
        return 3;
    if (op == '&')
        return 2;
    if (op == '|')
        return 1;
    
    return 0;
}

int main()
{
    string trueChars  = "tywz";
    string falseChars = "fnx";
    Set trues;
    Set falses;
    for (int k = 0; k < trueChars.size(); k++)
        trues.insert(trueChars[k]);
    for (int k = 0; k < falseChars.size(); k++)
        falses.insert(falseChars[k]);
    
    string pf;
    bool answer;
    
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  answer);
    assert(evaluate("y|", trues, falses, pf, answer) == 1);
    assert(evaluate("n t", trues, falses, pf, answer) == 1);
    assert(evaluate("nt", trues, falses, pf, answer) == 1);
    assert(evaluate("()", trues, falses, pf, answer) == 1);
    assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
    assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
    assert(evaluate("(n&(t|7)", trues, falses, pf, answer) == 1);
    assert(evaluate("", trues, falses, pf, answer) == 1);
    assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
           &&  pf == "ff!tn&&|"  &&  !answer);
    assert(evaluate(" x  ", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  !answer);
    trues.insert('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 3);
    falses.erase('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  answer);
    trues.erase('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 2);
    falses.insert('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  !answer);
    cout << "Passed all tests" << endl;
}

