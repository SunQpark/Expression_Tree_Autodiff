#pragma once
#include<iostream>
#include<string>
#include"base_node.hpp"

using namespace std;
using ring = double;


class Constant: public Node{
public:
    Constant(ring value) : type(CONSTANT), data(value){
        requires_grad = false;
        grad = 0;
    }

    ring forward() override {
        return data;
    }

    void backward(ring grad) override {
        
    }

    void print() override {
        cout << data;
    }

private:
    int type;
    ring data;
    ring grad;
    bool requires_grad;
};


class Variable: public Node{
public:
    Variable(string name): type(VARIABLE), name(name){
        assign(0.0);
        grad = 0.0;
    }

    Variable(ring init_value, string name): type(VARIABLE), name(name){
        assign(init_value);
        grad = 0.0;
    }

    void assign(ring value){
        data = value;
    }

    ring forward() override {
        return data;
    }

    void backward(ring gradient) override {
        grad += gradient;
        // return gradient;
    }

    void print(){
        std::cout << name;
    }

    ring get_grad(){
        return grad;
    }

private:
    string name;
    int type;
    ring data;
    ring grad;
    bool requires_grad;
};


class Add: public Operator{
public:
    Add(Node &child1, Node &child2): type(ADDITION), n_operand(BINARY){
        lhs = &child1;
        rhs = &child2;
        
    }

    ring forward() override {
        return lhs->forward() + rhs->forward();
    }

    void backward(ring gradient) override {
        grad = gradient;
        lhs->backward(grad);
        rhs->backward(grad);
    }

    void print(){
        cout << "(";
        lhs->print();
        cout << "+"; 
        rhs->print();
        cout << ")";
    }
private:
    int n_operand;
    int type;
    ring data;
    ring grad;
    Node* lhs;
    Node* rhs;
};


class Pow: public Operator{
public:
    Pow(Node &child) {
        lhs = &child;
        data = 1.0;
    }

    ring forward() override {
        return lhs->forward();
    }

    void print() override {
        
        lhs->print();
        cout << "^" << data;

    }

private:
    int n_operand;
    int type;
    ring data;
    ring grad;
    Node* lhs;
    Node* rhs;
};