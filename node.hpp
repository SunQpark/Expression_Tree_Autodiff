#pragma once
#include<iostream>
#include<string>
#include<cmath>
#include<memory>
#include"base_node.hpp"

enum{
    CONSTANT, VARIABLE, 
    ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION, 
    POWER};
using namespace std;
using ring = long double;


class Constant: public Node{
public:
    Constant(ring value) : Node(value){
        set_type(CONSTANT);
    }

    ring forward() override {
        cache = data;
        return cache;
    }

    void backward(ring gradient) override {
        grad = 0.0;
    }

    void print() override {
        cout << data;
    }
    
    void zero_grad() override {
        grad = 0.0;
    }

    virtual Node operator+(Node other){
        return *this;
    }

    Node operator+(Node &other);
private:
};


class Variable: public Node{
public:
    Variable(string name): Node(), name(name){
        set_type(VARIABLE);
        assign(0.0);
    }

    Variable(ring init_value, string name): Node(), name(name){
        set_type(VARIABLE);
        assign(init_value);
    }

    void assign(ring value){
        data = value;
    }

    ring forward() override {
        cache = data;
        return cache;
    }

    void backward(ring gradient) override {
        grad += gradient;
    }

    void print(){
        cout << name;
    }

    ring get_grad(){
        return grad;
    }

    void zero_grad() override {
        grad = 0.0;
    }

private:
    string name;
};


class Add: public Operator{
public:
    Add(Node &child1, Node &child2): Operator(child1, child2){
        set_type(ADDITION);
    }
    
    // initialization given constant values
    Add(Node &child, ring value): Operator(child, *make_shared<Constant>(value)){
        set_type(ADDITION);
    }

    Add(ring value, Node &child): Operator(*make_shared<Constant>(value), child){
        set_type(ADDITION);
    }

    // Add(ring value, Node &child): Operator(make_shared<Constant>(value), child){
    //     set_type(ADDITION);
    // }

    ring forward() override {
        cache = lhs->forward() + rhs->forward();
        return cache;
    }

    void backward(ring gradient) override {
        grad += gradient;
        lhs->backward(grad);
        rhs->backward(grad);
    }

    void print() override {
        cout << "(";
        lhs->print();
        cout << "+"; 
        rhs->print();
        cout << ")";
    }
};


class Subtract: public Operator{
public:
    Subtract(Node &child1, Node &child2): Operator(child1, child2){
        set_type(SUBTRACTION);
    }

    // initialization given constant values 
    Subtract(Node &child, ring value): Operator(child, *make_shared<Constant>(value)){
        set_type(ADDITION);
    }

    Subtract(ring value, Node &child): Operator(*make_shared<Constant>(value), child){
        set_type(ADDITION);
    }

    ring forward() override {
        cache = lhs->forward() - rhs->forward();
        return cache;
    }

    void backward(ring gradient) override {
        grad += gradient;
        lhs->backward(grad);
        rhs->backward(-grad);
    }

    void print() override {
        cout << "(";
        lhs->print();
        cout << "-"; 
        rhs->print();
        cout << ")";
    }
};


class Mul: public Operator{
public:
    Mul(Node &child1, Node &child2): Operator(child1, child2){
        set_type(MULTIPLICATION);
    }

    // initialization given constant values 
    Mul(Node &child, ring value): Operator(child, *make_shared<Constant>(value)){
        set_type(ADDITION);
    }

    Mul(ring value, Node &child): Operator(*make_shared<Constant>(value), child){
        set_type(ADDITION);
    }

    ring forward() override {
        cache = lhs->forward() * rhs->forward();
        return cache;
    }

    void backward(ring gradient) override {
        grad += gradient;
        lhs->backward(grad * rhs->cache);
        rhs->backward(grad * lhs->cache);
    }

    void print() override {
        cout << "(";
        lhs->print();
        cout << "*"; 
        rhs->print();
        cout << ")";
    }
};

class Div: public Operator{
public:
    Div(Node &child1, Node &child2): Operator(child1, child2){
        set_type(DIVISION);
    }
    
    // initialization given constant values 
    Div(Node &child, ring value): Operator(child, *make_shared<Constant>(value)){
        set_type(ADDITION);
    }

    Div(ring value, Node &child): Operator(*make_shared<Constant>(value), child){
        set_type(ADDITION);
    }
    

    ring forward() override {
        // TODO: dealing with cases with ring is not double
        cache = lhs->forward() / rhs->forward();
        return cache;
    }

    void backward(ring gradient) override {
        grad += gradient;
        lhs->backward(grad / rhs->cache);
        rhs->backward(- grad * lhs->cache * pow(rhs->cache, -2));
    }

    void print() override {
        cout << "(";
        lhs->print();
        cout << "/"; 
        rhs->print();
        cout << ")";
    }
};


class Pow: public Operator{
public:
    Pow(Node &child): Operator(child){
        set_type(POWER);
        data = 1.0;
    }
    
    Pow(Node &child, ring value): Operator(child){
        set_type(POWER);
        data = value;
    }

    ring forward() override {
        // TODO: replace std::pow with more efficient thing
        cache = pow(lhs->forward(), data);
        return cache;
    }

    void print() override {
        lhs->print();
        cout << "^" << data;
    }

    void backward(ring gradient) override {
        grad += gradient;
        lhs->backward(grad * data * pow(lhs->cache, data - 1));
    }
};