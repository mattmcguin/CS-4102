//
//  Matt McGuiness (mjm6qv)
//  Homework 5
//  CS4102 - Algorithms
//  Spring 2017
//  On my honor as a student, I have neither given nor recieved aid on this assignment.
//  arithmetic.cpp
//  NumberArithmetic
//
//  Created by Matt McGuiness on 3/22/17.
//  Copyright © 2017 Matt McGuiness. All rights reserved.
//

#include <iostream>
#include <math.h>

long long prod(long long u, long long v);

int main(int argc, const char * argv[]) {
    
    long long first;
    long long second;
    
    std::cout << "Please input an integer?\n";
    std::cin >> first;
    std::cout << "Please input another integer?\n";
    std::cin >> second;
    
    std::cout << "The first number times the second number using standard multiplication is:" << first * second << "\n";
    
    std::cout << "The first number times the second number using large integer arithmetic is:" << prod(first, second) << "\n";

    return 0;
}

long long prod(long long u, long long v) {
    long long w, x, y, z, m, n;
    long long temp1 = u, temp2 = v;
    if (u >= v) {
        n = 0; do { temp1 /= 10; n++; } while (temp1 != 0);
    } else {
        n = 0; do { temp2 /= 10; n++; } while (temp2 != 0);
    }
    
    
    if(u == 0 || v == 0) {
        return 0;
    } else if (n <= 2) {
        return u * v;
    } else {
        m = floor(n/2);
        long long power = pow(10, m);
        
        x = u / power;
        y = u % power;
        w = v / power;
        z = v % power;
        return prod(x, w) * pow(10, 2*m) + (prod(x, z) + prod(w, y)) * power + prod(y, z);
    }
}
