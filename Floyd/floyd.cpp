//  Matt McGuiness(mjm6qv)
//  Homework 06
//  CS4102 - Algorithms
//  Spring 2017
//  On my honor as a student, I have neither given nor received aid on this assignment.
//
//  floyd.cpp
//  HW06
//
//  Created by Matt McGuiness on 3/30/17.
//  Copyright © 2017 Matt McGuiness. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

std::vector<std::vector<int>> floyd(std::vector<std::vector<int>> W);
std::vector<std::vector<int>> floyd2(std::vector<std::vector<int>> W, std::vector<std::vector<int>> D);
void path(int q, int r, std::vector<std::vector<int>> P);
void printMatrix(std::vector<std::vector<int>> matrix);


int main(int argc, const char * argv[]) {
    // insert code here...
    int n;
    std::cout << "Enter the total number of vertices:";
    std::cin >> n;
    // insert code here...
    std::vector<std::vector<int>> W(n, std::vector<int>(n));
    std::vector<std::vector<int>> D(n, std::vector<int>(n));
    std::vector<std::vector<int>> P(n, std::vector<int>(n));
    
    
    for (int i = 0; i < n; i++) {
        std::cout << "Enter row " << i + 1 << " of the adjacency matrix:";
        for (int j = 0; j < n; j++) {
            std::cin >> W[i][j];
            
        }
    }
    
    D = floyd(W);
    std::cout << "The following shows the D and P matrices\n";
    printMatrix(D);
    std::cout << "\n";
    P = floyd2(W, D);
    printMatrix(P);
    char findPaths;
    std::vector<int> A(2);
    
    do {
        std::cout << "\nEnter a source vertex and a destination vertex:";
        for (int j = 0; j < 2; j++) {
            std::cin >> A[j];
        }
        A[0]--;
        A[1]--;

        std::cout << "The shortest path between the source and the destination is " << A[0] + 1 << " --> ";
        path(A[0], A[1], P);
        std::cout << A[1] + 1 << " with weight " << D[A[0]][A[1]] << "\n";
        std::cout << "More paths?";
        std::cin >> findPaths;
    }while(findPaths == 'y');
    
    return 0;
}

std::vector<std::vector<int>> floyd(std::vector<std::vector<int>> W) {
    
    long n = W[0].size();
    std::vector<std::vector<int>> D(n, std::vector<int>(n));
    
    int i, j, k;
    
    D = W;
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                D[i][j] = std::min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }
    
    return D;

}

std::vector<std::vector<int>> floyd2(std::vector<std::vector<int>> W, std::vector<std::vector<int>> D) {
    
    long n = W[0].size();
    std::vector<std::vector<int>> P(n, std::vector<int>(n));
    
    int i, j, k;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            P[i][j] = 0;
        }
    }
    
    D = W;
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if(D[i][j] >  D[i][k] + D[k][j]) {
                    P[i][j] = k + 1;
                    D[i][j] =  D[i][k] + D[k][j];
                }
            }
        }
    }

    return P;
}

void path(int q, int r, std::vector<std::vector<int>> P) {
    if (P[q][r] != 0) {
        path(q, P[q][r] - 1, P);
        std::cout << P[q][r] << " --> ";
        path(P[q][r] - 1, r, P);
    }
}

void printMatrix(std::vector<std::vector<int>> matrix) {
    for ( const std::vector<int> &v : matrix ) {
        for ( int x : v ) std::cout << x << ' ';
        std::cout << std::endl;
    }
}

//0 1 9999 1 5
//9 0 3 2 9999
//9999 9999 0 4 9999
//9999 9999 2 0 3
//3 9999 9999 9999 0
