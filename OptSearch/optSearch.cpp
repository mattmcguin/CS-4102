//
//  Matt McGuiness(mjm6qv)
//  Homework 07
//  CS4102 - Algorithms
//  Spring 2017
//  On my honor as a student, I have neither given nor received aid on this assignment.
//
//  optSeach.cpp
//  HW07
//
//  Created by Matt McGuiness on 4/3/17.
//  Copyright © 2017 Matt McGuiness. All rights reserved.
//


#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <iomanip>

void optsearchtree(int n, std::vector<float> probs, float *minavg, std::vector<std::vector<int> > R);
void printAMatrix(std::vector<std::vector<float> > matrix);
void printRMatrix(std::vector<std::vector<int> > matrix);


int main(int argc, const char * argv[]) {

    float minavg;
    int keys;
    std::cout << "Enter the total number of keys: \n";
    std::cin >> keys;
    
    std::vector<std::string> names(keys);
    std::vector<float> probs(keys);
    std::vector<std::vector<int> > R(keys + 1, std::vector<int>(keys +1));

    // Populate the keys
    std::cout << "Enter the " << keys <<  " keys seperated by at least 1 space: " << std::endl;
    for (int i = 0; i < keys; i++) {
        std::cin >> names[i];
    }

    // Populate probabilities
    std::cout << std::setprecision(1) << std::fixed;

    std::cout << "Enter the probability for the " << keys <<  " keys seperated by at least 1 space: " << std::endl;
    for (int i = 0; i < keys; i++) {
        std::cin >> probs[i];
    }
    
    for (int pass = 0; pass < probs.size() - 1; pass++) {
        for (int index = 0; index < probs.size() - 1; index++) {
            if (probs[index] > probs[index + 1]) {
                int temp = probs[index];
                probs[index] = probs[index + 1];
                probs[index + 1] = temp;
                
                std::string temp2 = names[index];
                names[index] = names[index + 1];
                names[index + 1] = temp2;
            }
        }
    }
    
    std::reverse(std::begin(probs), std::end(probs));
    std::reverse(std::begin(names), std::end(names));
    
    for (int i = 1; i <= keys; i++) {
        std::cout << "key" << i << " = " << names[i-1] << probs[i-1] << "\n";
    }
    
    std::cout << "The following shows the A matrix and the R matrix computed, respectively.\n";
    
    optsearchtree(keys, probs, &minavg, R);
    
    
    return 0;
}

void optsearchtree(int n, std::vector<float> probs, float *minavg, std::vector<std::vector<int> > R) {
    std::vector<std::vector<float> > A(n + 1, std::vector<float>(n +1));
    int j, k;
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            A[i][j] = -1.0;
            R[i][j] = -1;
        }
    }
    
    for (int i = 0; i <= n; i++) {
        A[i][i] = 0.0;
        A[i][i+1] = probs[i];
        std::cout << probs[i];
        R[i][i] = 0;
        R[i][i+1] = i+1;
    }
    
    A[n][n] = 0;
    R[n][n] = 0;
    
    for (int diagonal = 0; diagonal < n-1 ; diagonal++) {
        for (int i = 0; i < n - diagonal; i++) {
            j = i + diagonal;
            int min = 10000;
            int temp = 0;
            for (k = i; k <= j; k++) {
                float sum = 0.0;
                int z = i;
                int y = j;
                while(z < y+1) {
                   sum+= probs[z];
                    z++;
                }
                int min1 = A[i][k-1] + A[k+1][j] + sum;
                if(min > min1) {
                    min = min1;
                    temp = k;
                }
            }
            A[i][j-1] = min;
            R[i][j-1] = temp;
        }
        *minavg = A[1][n];
    }
    
    printAMatrix(A);
    printRMatrix(R);
}

void printAMatrix(std::vector<std::vector<float> > matrix) {
    std::cout << std::setprecision(1) << std::fixed;
    for ( const std::vector<float> &v : matrix ) {
        for ( float x : v ) {
            if (x >= 0.0) {
                std::cout << x << ' ';
            } else {
                std::cout << "   " << ' ';
            }
        }
        std::cout << std::endl;
    }
}

void printRMatrix(std::vector<std::vector<int> > matrix) {
    for ( const std::vector<int> &v : matrix ) {
        for ( int x : v ) {
            if (x >= 0.0) {
                std::cout << x << ' ';
            } else {
                std::cout << " " << ' ';
            }

        }
        std::cout << std::endl;
    }
}
