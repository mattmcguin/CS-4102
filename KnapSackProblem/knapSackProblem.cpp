//
//  Matt McGuiness(mjm6qv)
//  Homework 09
//  CS4102 - Algorithms
//  Spring 2017
//  On my honor as a student, I have neither given nor received aid on this assignment.
//
//  knapSackProblem.cpp

#include <iostream>
#include <stdlib.h>
#include <iomanip>
 
using namespace std;

int max(int a, int b);
int knapSack(int W, int wt[], int val[], int n);

typedef struct {
    int value;
    int added;
} Point;

int main() {
    int n;
    cout << " Enter the total number of items under consideration: "; 
    cin >> n;

    int value[n];
    int weight[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter the weight and profit for item " << i+1 << ": ";
        cin >> weight[i];
        cin >> value[i];
    }

    int  W;
    cout << "Enter the total weight the knapsack can hold: ";
    cin >> W;

    cout << "The following shows the P[i][w] table computed." << endl;

    cout << setw(10) << "P[i][w]";
    for ( int i = 0; i < W +1; i++) {
        cout << setw(10) << "w = " << i;
    }
    cout << endl;

    int maxProfit = knapSack(W, weight, value, n);
    cout << maxProfit << "." << endl;
    return 0;
}

int max(int a, int b) {
    return (a > b)? a : b;
}

int knapSack(int W, int wt[], int val[], int n) {
   int i, w;
   Point P[n+1][W+1];
 
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i==0 || w==0) {
                P[i][w].value = 0;
                P[i][w].added = 0;
            } else if (wt[i-1] <= w) {
                P[i][w].value = max(val[i-1] + P[i-1][w-wt[i-1]].value,  P[i-1][w].value);
                if (P[i][w].value > P[i-1][w].value) P[i][w].added = 1;
            } else {
                P[i][w].value = P[i-1][w].value;
                P[i][w].added = 0;
            }
        }
    }
 
    // Print out P Matrix
    for (int i = 0; i < 4; ++i) {
        cout << setw(8) << "i = " << i;
        for (int j = 0; j < 5; ++j) {
            cout << setw(8) << P[i][j].value << ", " << P[i][j].added;
        }
        cout << endl;
    }

    int array[10];
    int count = 0;
    int k = W;
    for (int i = n; i >= 1; i--) {
        if(P[i][k].added == 1) {
            array[count] = i;
            //cout << P[i][k].value << endl;
            k = k - wt[i-1];
            //cout << k << endl;
            count++;
        }
    }

    cout << "Items ";
    for (int i = count-1; i >= 1; i--) {
        cout << array[i] << ", ";
    }
    cout << "and " << array[0] << "  are included with maximum profit ";

    return P[n][W].value;
}