//
//  Matt McGuiness(mjm6qv)
//  Homework 10
//  CS4102 - Algorithms
//  Spring 2017
//  On my honor as a student, I have neither given nor received aid on this assignment.
//
//  schedule.cpp

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <iomanip>

using namespace std;

struct Job {
    int number;
    int profit;
    int deadline;
};

void schedule(int jobs, vector<Job > jobsArray);
void printOrder(vector<Job > jobsArray);
int minimum(int x, int y);

int main() {
    
    int jobs;
    cout << "Enter the total number of jobs: ";
    cin >> jobs;

    vector<Job > jobsArray(jobs);
    //vector<int > deadlines(jobs);
    //vector<int > numbers(jobs);

    for (int i = 0; i < jobs; i++) {
        cout << "Enter the deadline and profit for job " << i+1 << ": ";
        cin >> jobsArray[i].deadline;
        cin >> jobsArray[i].profit;
        jobsArray[i].number = i + 1;
    }

    for (int pass = 0; pass < jobsArray.size() - 1; pass++) {
        for (int index = 0; index < jobsArray.size() - 1; index++) {
            if (jobsArray[index].profit > jobsArray[index + 1].profit) {
                Job temp = jobsArray[index];
                jobsArray[index] = jobsArray[index + 1];
                jobsArray[index + 1] = temp;
                
                // int temp2 = deadlines[index];
                // deadlines[index] = deadlines[index + 1];
                // deadlines[index + 1] = temp2;

                // int temp3 = numbers[index];
                // numbers[index] = numbers[index + 1];
                // numbers[index + 1] = temp3;
            }
        }
    }

    // reverse(begin(profits), end(profits));
    // reverse(begin(deadlines), end(deadlines));
    // reverse(begin(numbers), end(numbers));
    reverse(begin(jobsArray), end(jobsArray));

    schedule(jobs, jobsArray);

    return 0;
}

void schedule(int jobs, vector<Job > jobsArray) {
    int lastDeadline = 0;
	for(int i = 0; i < jobs; i++) {
		if(jobsArray[i].deadline > lastDeadline) {
			lastDeadline = jobsArray[i].deadline;
		}
	}

    int count = 0;
    int profit = 0;
    vector<bool > slot(lastDeadline, false);
    vector<Job > accepted;
    for (Job j:jobsArray) {	
        for (int i=minimum(slot.size(),j.deadline)-1; i>=0; i--) {
            if(!slot[i]){
                accepted.push_back(j);
                slot[i] = true;
                count++;
                profit += j.profit;
                cout << "S = {";
                for (int z = 0; z < accepted.size()-1; z++) cout << accepted[z].number << ", ";
                cout << accepted[accepted.size()-1].number;
                cout << "} is accepted because [";
                printOrder(accepted);
                cout << "] is a feasible sequence in the set." << endl;
                break;
            }
        }
        // if (count==slot.size()) {
        //     break;
        // }
    }
    cout << endl;
    cout << "Answer: [";
    printOrder(accepted);
    cout << "] is a feasible sequence with maximum total profit of " << profit << endl;
    
}

int minimum(int x, int y) {
    if(x < y) return x;
	return y;
}

void printOrder(vector<Job > jobsArray) {
    for (int pass = 0; pass < jobsArray.size() - 1; pass++) {
        for (int index = 0; index < jobsArray.size() - 1; index++) {
            if (jobsArray[index].deadline > jobsArray[index + 1].deadline) {
                Job temp = jobsArray[index];
                jobsArray[index] = jobsArray[index + 1];
                jobsArray[index + 1] = temp;
            }
        }
    }

    for(int i = 0 ; i < jobsArray.size() - 1; i ++) cout << jobsArray[i].number << ", ";
    cout << jobsArray[jobsArray.size()-1].number;
}