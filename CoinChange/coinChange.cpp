//
//  Matt McGuiness(mjm6qv)
//  Homework 10
//  CS4102 - Algorithms
//  Spring 2017
//  On my honor as a student, I have neither given nor received aid on this assignment.
//
//  coinChange.cpp

#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <vector>
 
using namespace std;

vector<int > greedyChange(vector<int > coins, int amount);
void dynamicCoinChange(vector<int > coins, int amount);
void print(int x, int y, vector<vector<int> > Matrix);

int main() {
    
    int amount;
    cout << "Enter the amount of money in cents: "; 
    cin >> amount;
    cout << endl;

    vector<int > coins(4);
    coins[0] = 1;
    coins[1] = 5;
    coins[2] = 10;
    coins[3] = 25;

    vector<int > coinNums(4, 0);
    coinNums = greedyChange(coins, amount);     

    cout << "Coin denominations determined: ";
    
    if (coinNums[3] != 0) {
        cout << coinNums[3] << "×25¢, ";
    }
    if (coinNums[2] != 0) {
        cout << coinNums[2] << "×10¢, ";
    }    
    if (coinNums[1] != 0) {
        cout << coinNums[1] << "×5¢, ";
    }
    if (coinNums[0] != 0) {
        cout << coinNums[0] << "×1¢" << endl;
    }

    cout << endl;
    cout << "The following shows the C[i][j] table computed." << endl << endl;
    dynamicCoinChange(coins, amount);

    return 0;
}

vector<int > greedyChange(vector<int > coins, int amount) {
    vector<int > coinNums(4, 0);

    for (int i = coins.size() - 1; i >= 0; i--) {
        while (coins[i] <= amount) {
            amount = amount - coins[i];
            coinNums[i]++;
        }
    }

    return coinNums;
}

void dynamicCoinChange(vector<int > coins, int amount) {
    int change = amount + 1;
	int numCoins = coins.size();
	int coin = coins[0]; 
	vector<vector<int> > C(numCoins, vector<int>(change));
	
	for (int y = 0; y<change; y++) {
		if (y<coin) {
			C[0][y] = 0; 
		} else {
			C[0][y] = C[0][y - coin] + 1;
		}
	}
	
	for (int x = 1; x<numCoins; x++) {
		coin = coins[x];
		for (int y = 0; y<change; y++) {
			if (y<coin) { 
				C[x][y] = C[x - 1][y];
			} else { 
				if (((C[x][y - coin]) + 1)<(C[x - 1][y])) { 
					C[x][y] = (C[x][y - coin]) + 1;
				} else {
					C[x][y] = C[x - 1][y];
				}
			}
		}
	}

    print(numCoins, change, C);
}

void print(int x, int y, vector<vector<int> > Matrix) {
    cout << setw(4) << "C[i][j] ";
    for (int i = 0; i < y; i++) cout << setw(2) << Matrix[0][i] << " ";
    cout << endl;
    for (int i = 0; i < x; i++) {
        if(i == 0) cout << "d" << i+1 << " = 1 "; 
        if(i == 1) cout << "d" << i+1 << " = 5 "; 
        if(i == 2) cout << "d" << i+1 << " = 10"; 
        if(i == 3) cout << "d" << i+1 << " = 25"; 
        for (int j = 0; j < y; j++) {
            if (Matrix[i][j] >= 0) {
                cout << setw(3) << Matrix[i][j];
            } else {
                cout << "   ";
            }
        }
        cout << endl;
    }
}