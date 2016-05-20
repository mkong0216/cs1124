//
//  polynomial.hpp
//  HW #8
//
//  Created by Mandy Kong on 4/18/16.
//  Copyright © 2016 Mandy Kong. All rights reserved.
//

#ifndef polynomial_hpp
#define polynomial_hpp
#include <vector>
#include <string>
#include <iostream>

struct Node {
    Node(int data = 0, Node* next = nullptr): data(data), next(next) {}
    int data;
    Node* next;
};

Node* listDuplicate(Node* headPtr);

void listInsertHead(int entry, Node*& headPtr);

int exponent(int x, int degree);

class Polynomial {
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
public:
    Polynomial();
    Polynomial(std::vector<int> coefficient);
    ~Polynomial(); 
    Polynomial(const Polynomial& rhs);
    Polynomial& operator=(const Polynomial& rhs); 
    Polynomial& operator+=(const Polynomial& rhs);
    bool operator==(const Polynomial& rhs);
    int evaluate(int x); 
private:
    size_t degree = 0;
    Node* coefficients = nullptr;
};

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);

bool operator!=(Polynomial lhs, Polynomial rhs);

#endif /* polynomial_hpp */
