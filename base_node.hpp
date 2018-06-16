#pragma once
#include<iostream>

enum{NULLARY, UNARY, BINARY};
enum{CONSTANT, VARIABLE, ADDITION, SUBSTRACTION, MULTIPLICATION};
using ring = double;


class Node{
public:
    Node(){
    }

    Node(ring value): data(value){
        grad = 0.0;
        requires_grad = false;
    }

    int type;
    ring data;
    ring grad;
    bool requires_grad;

    virtual ring forward(){
        return data;
    }

    virtual void backward(ring gradient) {
        grad = gradient;
    }

    virtual void print(){}
    virtual ~Node(){}
};


class Operator: public Node {
public:
    Operator(): n_operand(NULLARY), data(0){
        lhs = NULL;
        rhs = NULL;
        grad = 0.0;
    }

    Operator(ring value): n_operand(NULLARY), data(value){
        lhs = NULL;
        rhs = NULL;
        grad = 0.0;
    }

    Operator(Node &child): n_operand(UNARY){
        lhs = &child;
        rhs = NULL;
        grad = 0.0;
    }

    Operator(Node &child1, Node &child2): n_operand(BINARY){
        lhs = &child1;
        rhs = &child2;
        grad = 0.0;
    }
    
private:
    int n_operand;
    int type;
    ring data;
    Node* lhs;
    Node* rhs;
};