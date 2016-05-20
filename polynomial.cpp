//
//  polynomial.cpp
//  HW #8 - using linked lists to store a polynomial and do operations 
//
//  Created by Mandy Kong on 4/18/16.
//  Copyright © 2016 Mandy Kong. All rights reserved.
//

#include "polynomial.hpp"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

//reuse of previously created Node functions
void listInsertHead(int entry, Node*& headPtr) {
    headPtr = new Node(entry, headPtr);
}

//edited to include x's and exponents
void listDisplayReverse(Node* headPtr, size_t exponent) { //call stack - n nodes, n calls
    if (headPtr == nullptr) { return; } //base case - if empty list
    listDisplayReverse(headPtr->next, exponent + 1); //starts out with degree = 0 and then adds one
    if (headPtr->data == 0) { //if the coefficient = 0, then don't return that part of the polynomial (i.e. 0x + 3 = 3)
        return;
    }
    if (exponent == 0) { //if exponent = 0, just return that value
        cout << headPtr->data;
    }
    else { //these have x's - I think there's a cleaner way to do this, but not sure yet
        if (exponent == 1) {
            cout << headPtr->data << "x"; //if exponent is 1, no need to show the exponent(^1)
        }
        else {
            cout << headPtr->data << "x^" << exponent; //otherwise show the exponent
        }
        cout << showpos;
    }
}

//output operator - needs to use recursive displayReverse function
ostream& operator<<(ostream& os, const Polynomial& poly) {
    if (poly.coefficients == nullptr) {
        os << noshowpos << 0; //if empty list, print out 0
    }
    else {
        listDisplayReverse(poly.coefficients, 0);
        os << noshowpos;
    }
    return os;
}

Polynomial::Polynomial() {} //default constructor

Polynomial::~Polynomial() { //destructor
    degree = 0;
    Node* p = coefficients;
    coefficients = nullptr;
    while (p != nullptr) {
        Node* next = p->next;
        delete p;
        p = next;
    }
}


Polynomial::Polynomial(vector<int> coefficient) { //vector from highest to lowest // 5x^2 + 4x + 3 //{5, 4, 3}
    //coefficients linked list from lowest to highest // {3, 4, 5}
    degree = coefficient.size() - 1; //set degree of polynomial
    coefficients = new Node(coefficient[0]); //create the new node with headPtr as the first value
    for (size_t i = 1; i < coefficient.size(); ++i) { //loop through the remaining nodes
        listInsertHead(coefficient[i], coefficients); //insert new node before headPtr
    }
}

Polynomial::Polynomial(const Polynomial& rhs) { //copy constructor
    //set degree as same as rhs' degree
    degree = rhs.degree;
    //create new node and set the first node's value to the rhs' first value
    coefficients = new Node((rhs.coefficients)->data);
    //temp pointers
    Node* p1 = coefficients;
    Node* p2 = rhs.coefficients->next;
    while (p2 != nullptr) { //until end of rhs' linked list
        p1->next = new Node(p2->data); //create new node with rhs' value and set it as the next value of our coefficients linked list
        p1 = p1->next;
        p2 = p2->next;
    }
}

Polynomial& Polynomial::operator=(const Polynomial& rhs) { //assignment operator
    //check for self assignment
    if (this != &rhs) {
        degree = rhs.degree;
        Node* current = coefficients;
        coefficients = nullptr;
        while (current != nullptr) { //delete old data
            Node* next = current->next;
            delete current;
            current = next;
        }
        //allocate new data
        coefficients = new Node((rhs.coefficients)->data);
        Node* p1 = coefficients;
        Node* p2 = rhs.coefficients->next;
        while (p2 != nullptr) {
            p1->next = new Node(p2->data);
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    return *this;
}
    
Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    Node* p = coefficients;
    Node* p2 = rhs.coefficients;
    while (p != nullptr) { //until end of linked list
        p->data += p2->data;
        p2 = p2->next; //go to next value in rhs' linked list
        if (p->next == nullptr) { //if the next node is null (and rhs is not done yet)
            break; //break to keep the pointer to the node that's not null
        }
        else if (p2 == nullptr) { //if rhs is null
            break; //break to keep the pointer to the node that's not null
        }
        p = p->next; //if the degree of the two polynomials, just continue adding them together
    }
    while (p2 != nullptr) { //if degree < rhs.degree, go through rest of rhs' linked list
        p->next = new Node(p2->data); //create new node with those values
        p = p->next;
        p2 = p2->next;
        degree = rhs.degree;
    }
    return *this;
}

bool Polynomial::operator==(const Polynomial& rhs) {
    if (degree != rhs.degree) { return false; } //if the degrees aren't equal, the polynomials are equal also
    else {
        Node* currPos = coefficients;
        Node* currPosRHS = rhs.coefficients;
        while (currPos != nullptr) { //until end of linked list
            if (currPos->data != currPosRHS->data) { return false; } //if the data aren't equal, false
            currPos = currPos->next;
            currPosRHS = currPosRHS->next;
        }
    }
    return true; //else true
}

int exponent(int x, int degree) { //recursive function to calculate exponent values
    int ans = x;
    if (degree == 0) { return 1; } //base case
    else {
        return ans *= exponent(x, degree - 1);
    }
}

int Polynomial::evaluate(int x) {
    int answer = coefficients->data; //set answer equal to the first data value since that has no x
    Node* currPos = coefficients->next;
    int degree = 1; //keep track of the exponents
    while (currPos != nullptr) {
        answer += ((currPos->data) * exponent(x, degree)); //add data * exponent value to answer
        currPos = currPos->next;
        degree += 1;
    }
    return answer; 
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial result(lhs);
    return result+=rhs; 
}

bool operator!=(Polynomial lhs, Polynomial rhs) {
    if (lhs == rhs) { return false; }
    return true;
}
