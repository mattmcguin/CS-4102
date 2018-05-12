//
//  Matt McGuiness(mjm6qv)
//  Homework 08
//  CS4102 - Algorithms
//  Spring 2017
//  On my honor as a student, I have neither given nor received aid on this assignment.
//
//  matrixMultiplication.cpp

#include <iostream>
#include <vector>

using namespace std;

int minmult(int n, vector<int> d, vector<vector<int> > &P);
void order(int i, int j, vector<vector<int> > &P);
void print(int size, vector<vector<int> > Matrix);

int main(int argc, const char * argv[]) {
    int numberMatrices;

    cout << " Enter the total number of matrices to be multiplied: "; 
    cin >> numberMatrices;

    vector<int> matrices(numberMatrices * 2 + 1);
    vector<int> actualMatrices(numberMatrices * 2 + 1);
    vector<vector<int> > P(numberMatrices + 1, vector<int>(numberMatrices + 1));

    for(int i = 1; i <= numberMatrices; i++){
        for(int j = 1; j <= numberMatrices; j++){
            P[i][j] = -1;
        }
    }

    for (int i = 0; i < numberMatrices*2; i+=2) {
        cout << " Enter the dimension for matrix " << i/2 << ": ";
        for (int j = 0; j < 2; j++) {
            cin >> matrices[i + j] ;
        }
    }

    actualMatrices[0] = matrices[0];
    int j = 1;
    for (int i = 1; i < numberMatrices * 2; i+=2) {
        actualMatrices[j] = matrices[i];
        j++;
    }

    cout << "The following shows the M matrix and the P matrix computed, respectively.\n";

    int mults = minmult(numberMatrices, actualMatrices, P);

    print(numberMatrices + 1, P);

    order(1, numberMatrices, P);
    cout <<endl;
    return 0;
}

int minmult(int n, vector<int> d, vector<vector<int> > &P) {
    int i, j, k, diagonal;
    vector<vector<int> > M(n+1, vector<int> (n+1));

    for(i = 1; i <= n; i++){
        for(j = 1; j <= n; j++){
            M[i][j] = -1;
        }
    }

    for(i = 1; i <= n; i++){
        M[i][i] = 0;
    }

    for(int length = 1; length < n; length++)
    {
        for(int i = 1; i<n-length + 1; i++)
        {

            int j = i+ length;
        int tempCost;
        int k = i;
        int minCost = M[i][k] + M[k+1][j] + d[i-1]*d[k]*d[j];
        int kay = i;
        for(; k<j; k++)
        {
        tempCost = M[i][k] + M[k+1][j] + d[i-1]*d[k]*d[j];
        if(tempCost<minCost)
        {
            minCost = tempCost;
            kay = k;
        }
        }

        M[i][j] = minCost;
        P[i][j] = kay;
        }
    }
    print(M.size(), M);
    return M[1][n];
}

void print(int size, vector<vector<int> > Matrix) {
    for (int i = 1; i < size; i++) {
        for (int j = 1; j < size; j++) {
            if (Matrix[i][j] >= 0) {
                cout << Matrix[i][j] << "  ";
            } else {
                cout << "   ";
            }
        }
        cout << endl;
    }
}

void order(int i, int j, vector<vector<int> > &P) {
    int k;
    if(i == j){
        cout << "M" << i;
    } else {
        k = P[i][j];
        cout << "(";
        order(i, k, P);
        order(k+1, j, P);
        cout << ")";
    }
}