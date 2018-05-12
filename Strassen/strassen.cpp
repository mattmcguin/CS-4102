//
//  Matt McGuiness (mjm6qv)
//  Homework 5
//  CS4102 - Algorithms
//  Spring 2017
//  On my honor as a student, I have neither given nor recieved aid on this assignment.
//
//  strassen.cpp
//  HW5
//
//  Created by Matt McGuiness on 3/1/17.
//  Copyright © 2017 Matt McGuiness. All rights reserved.


#include <iostream>
#include <vector>

std::vector<std::vector<int> > strassen(std::vector<std::vector<int> > A, std::vector<std::vector<int> > B);
std::vector<std::vector<int> > multiply(std::vector<std::vector<int> > A, std::vector<std::vector<int> > B);
std::vector<std::vector<int> > add(std::vector<std::vector<int> > A, std::vector<std::vector<int> > B);
std::vector<std::vector<int> > subtract(std::vector<std::vector<int> > A, std::vector<std::vector<int> > B);
void printMatrix(std::vector<std::vector<int> > matrix);
std::vector<std::vector<int> > partition(std::vector<std::vector<int> > parentMatrix, std::vector<std::vector<int> > childMatrix, int x, int y);
std::vector<std::vector<int> > combine(int n, std::vector<std::vector<int> > childMatrix1, std::vector<std::vector<int> > childMatrix2, std::vector<std::vector<int> > childMatrix3, std::vector<std::vector<int> > childMatrix4);

int main(int argc, const char * argv[]) {
    
    int n;
    
    std::cout << "How big would you like the matrices to be?\n";
    std::cin >> n;
    // insert code here...
    std::vector<std::vector<int> > A(n, std::vector<int>(n));
    std::vector<std::vector<int> > B(n, std::vector<int>(n));
    std::vector<std::vector<int> > C(n, std::vector<int>(n));
    std::vector<std::vector<int> > D(n, std::vector<int>(n));
    
    // Random numbers into matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = arc4random() % 10;
            B[i][j] = arc4random() % 10;
        }
    }
    
    // Print out original matrices
    std::cout << "Matrix A is: \n";
    printMatrix(A);
    
    std::cout << "Matrix B is: \n";
    printMatrix(B);
    
    C = strassen(A, B);
    
    std::cout << "Using Strassen Matrix C is: \n";
    printMatrix(C);
    
    D = multiply(A, B);
    std::cout << "Using standard multiply Matrix D is: \n";
    printMatrix(D);
    
    return 0;
}

std::vector<std::vector<int> > strassen(std::vector<std::vector<int> > A, std::vector<std::vector<int> > B){
    
    int n = A[0].size();
    std::vector<std::vector<int> > C(n, std::vector<int>(n));
    
    if( n <= 4) {
        C = multiply(A, B);
    } else {
        std::vector<std::vector<int> >  A11(n/2, std::vector<int>(n/2));
        std::vector<std::vector<int> >  A12(n/2, std::vector<int>(n/2));
        std::vector<std::vector<int> >  A21(n/2, std::vector<int>(n/2));
        std::vector<std::vector<int> >  A22(n/2, std::vector<int>(n/2));
        std::vector<std::vector<int> >  B11(n/2, std::vector<int>(n/2));
        std::vector<std::vector<int> >  B12(n/2, std::vector<int>(n/2));
        std::vector<std::vector<int> >  B21(n/2, std::vector<int>(n/2));
        std::vector<std::vector<int> >  B22(n/2, std::vector<int>(n/2));
        
        A11 = partition(A, A11, 0 , 0);
        A12 = partition(A, A12, 0 , n/2);
        A21 = partition(A, A21, n/2, 0);
        A22 = partition(A, A22, n/2, n/2);
        B11 = partition(B, B11, 0 , 0);
        B12 = partition(B, B12, 0 , n/2);
        B21 = partition(B, B21, n/2, 0);
        B22 = partition(B, B22, n/2, n/2);
        
        std::vector<std::vector<int> > M1 = strassen(add(A11, A22), add(B11, B22));
        std::vector<std::vector<int> > M2 = strassen(add(A21, A22), B11);
        std::vector<std::vector<int> > M3 = strassen(A11, subtract(B12, B22));
        std::vector<std::vector<int> > M4 = strassen(A22, subtract(B21, B11));
        std::vector<std::vector<int> > M5 = strassen(add(A11, A12), B22);
        std::vector<std::vector<int> > M6 = strassen(subtract(A21, A11), add(B11, B12));
        std::vector<std::vector<int> > M7 = strassen(subtract(A12, A22), add(B21, B22));
        
        std::vector<std::vector<int> > C11 = add(subtract(add(M1, M4), M5), M7);
        std::vector<std::vector<int> > C12 = add(M3, M5);
        std::vector<std::vector<int> > C21 = add(M2, M4);
        std::vector<std::vector<int> > C22 = add(subtract(add(M1, M3), M2), M6);
        
        
        C = combine(n, C11, C12, C21, C22);
        
    }
    
    return C;
}

std::vector<std::vector<int> > multiply(std::vector<std::vector<int> > A, std::vector<std::vector<int> > B) {
    
    int size = A[0].size();
    std::vector<std::vector<int> > C(size, std::vector<int>(size));
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
    
    return C;
}

std::vector<std::vector<int>> add(std::vector<std::vector<int> > A, std::vector<std::vector<int> > B) {
    
    int size = A[0].size();
    std::vector<std::vector<int> > C(size, std::vector<int>(size));
    
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    
    return C;
}

std::vector<std::vector<int>> subtract(std::vector<std::vector<int> > A, std::vector<std::vector<int> > B) {
    
    int size = A[0].size();
    std::vector<std::vector<int> > C(size, std::vector<int>(size));
    
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    
    return C;
}

void printMatrix(std::vector<std::vector<int> > matrix) {
     for ( const std::vector<int> &v : matrix ) {
         for ( int x : v ) std::cout << x << ' ';
         std::cout << std::endl;
     }
}

std::vector<std::vector<int> > partition(std::vector<std::vector<int> > parentMatrix, std::vector<std::vector<int> > childMatrix, int x, int y) {
    
    int size = childMatrix[0].size();
    std::vector<std::vector<int> > C(size, std::vector<int>(size));
    
    for(int i1 = 0, i2 = x; i1 < size; i1++, i2++) {
        for(int j1 = 0, j2 = y; j1 < size; j1++, j2++) {
            C[i1][j1] = parentMatrix[i2][j2];
        }
    }
    
    return C;
}

std::vector<std::vector<int> > combine(int n, std::vector<std::vector<int> > childMatrix1, std::vector<std::vector<int> > childMatrix2, std::vector<std::vector<int> > childMatrix3, std::vector<std::vector<int> > childMatrix4) {
    
    std::vector<std::vector<int> > C(n, std::vector<int>(n));
    
    for(int i = 0; i < n/2; i++) {
        for(int j = 0; j < n/2; j++) {
            C[i][j] = childMatrix1[i][j];
        }
    }
    
    for(int i = 0; i < n/2; i++) {
        for(int j = n/2, j2 = 0; j < n; j++, j2++) {
            C[i][j] = childMatrix2[i][j2];
        }
    }
    
    for(int i = n/2, i2 = 0; i < n; i++, i2++) {
        for(int j = 0; j < n/2; j++) {
            C[i][j] = childMatrix3[i2][j];
        }
    }
    
    for(int i = n/2, i2 = 0; i < n; i++, i2++) {
        for(int j = n/2, j2 = 0; j < n; j++, j2++) {
            C[i][j] = childMatrix4[i2][j2];
        }
    }
    
    return C;
}

