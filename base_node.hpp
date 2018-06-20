#pragma once
#include<iostream>

enum{NULLARY, UNARY, BINARY};
using namespace std;
using ring = long double;


class Node{
public:
    Node(){
        zero_grad();
    }

    Node(ring value): data(value){
        
    }

    virtual ring forward(){
        cache = data;
        return cache;
    }

    virtual void backward(ring gradient) {
        grad = gradient;
    }

    virtual void print(){}
    
    void set_type(int node_type){
        type = node_type;
    }
    
    virtual void zero_grad(){
        grad = 0.0;
    }

    ring data;
    ring grad;
    ring cache;

private:
    int type;
};


class Operator: public Node {
public:
    Operator(): Node(), n_operand(NULLARY){
        lhs = nullptr;
        rhs = nullptr;
    }

    Operator(Node &child): Node(), n_operand(UNARY){
        lhs = &child;
        rhs = nullptr;
    }

    Operator(Node &child1, Node &child2): Node(), n_operand(BINARY){
        lhs = &child1;
        rhs = &child2;
    }

    Node* lhs;
    Node* rhs;

    void zero_grad() override {
        grad = 0.0;
        switch (n_operand){
            case NULLARY:
                break;
            case UNARY:
                lhs->zero_grad();
                break;
            case BINARY:
                lhs->zero_grad();
                rhs->zero_grad();
                break;
            default:
                break;
        }
    }

    // ~Operator(){
    //     switch (n_operand){
    //         case NULLARY:
    //             break;
    //         case UNARY:
    //             lhs->~Node();
    //             break;
    //         case BINARY:
    //             lhs->~Node();
    //             rhs->~Node();
    //             break;
    //         default:
    //             break;
    //     }
    // }
private:
    int n_operand;
};