#pragma once
#include"node.hpp"


// overloading addition operator
Add operator+(Node &lhs, Node &rhs){
    return *make_shared<Add>(lhs, rhs);
}

Add operator+(Variable &lhs, ring value){
    auto rhs = make_shared<Constant>(value);
    return *make_shared<Add>(lhs, *rhs);
}

Add operator+(ring value, Variable &rhs){
    auto lhs = make_shared<Constant>(value);
    return *make_shared<Add>(*lhs, rhs);
}


// overloading subtraction operator
Subtract operator-(Node &lhs, Node &rhs){
    return *make_shared<Subtract>(lhs, rhs);
}

Subtract operator-(Variable &lhs, ring value){
    auto rhs = make_shared<Constant>(value);
    return *make_shared<Subtract>(lhs, *rhs);
}

Subtract operator-(ring value, Variable &rhs){
    auto lhs = make_shared<Constant>(value);
    return *make_shared<Subtract>(*lhs, rhs);
}

// overloading Multiplication operator
Mul operator*(Node &lhs, Node &rhs){
    return *make_shared<Mul>(lhs, rhs);
}

Mul operator*(Variable &lhs, ring value){
    auto rhs = make_shared<Constant>(value);
    return *make_shared<Mul>(lhs, *rhs);
}

Mul operator*(ring value, Variable &rhs){
    auto lhs = make_shared<Constant>(value);
    return *make_shared<Mul>(*lhs, rhs);
}

Div operator/(Node &lhs, Node &rhs){
    return *make_shared<Div>(lhs, rhs);
}

Div operator/(Variable &lhs, ring value){
    auto rhs = make_shared<Constant>(value);
    return *make_shared<Div>(lhs, *rhs);
}

Div operator/(ring value, Variable &rhs){
    auto lhs = make_shared<Constant>(value);
    return *make_shared<Div>(*lhs, rhs);
}

Pow operator^(Variable &lhs, ring value){
    return *make_shared<Pow>(lhs, value);
}
