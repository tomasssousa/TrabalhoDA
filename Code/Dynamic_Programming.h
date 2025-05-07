
#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H


#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"
#include "Pallet.h"

/**
* @brief This function is responsible for calculating the optimal setup, using Dynalic Programming.
* @param Pallets A map with the pallets to be used in the problem, identifiable by their id.
* @param n Number of Pallets.
* @param maxWeight Max possible weight.
* @param usedItems[] An array with items used marked in true or false             Could be changed to store the id of the used ones
* @return The integer with the optimal value.
*/
unsigned int knapsackDP(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    unsigned int maxValue[n][maxWeight+1];

    // Step 1: Initialize the DP matrix with the values for the base cases
    for(unsigned int k = 0; k <= maxWeight; k++) {
        maxValue[0][k] = (k >= weights[0]) ? values[0] : 0; // base case considers using the first item
    }
    for(unsigned int i = 1; i <= n; i++) {
        maxValue[i][0] = 0; // value of 0 for knapsacks of capacity = 0
    }

    // Step 2: Compute values of the DP matrix for the recursive cases
    for(unsigned int i = 1; i < n; i++) {
        for(unsigned int k = 1; k <= maxWeight; k++) {
            if(k < weights[i]) {
                maxValue[i][k] = maxValue[i - 1][k]; // item is too big for the knapsack, so the optimal solution is the same as not considering it
            }
            else {
                unsigned int valueUsingItemI = maxValue[i - 1][k - weights[i]] + values[i];
                if(valueUsingItemI > maxValue[i - 1][k]) {
                    maxValue[i][k] = valueUsingItemI; // using item i improves the solution
                }
                else {
                    maxValue[i][k] = maxValue[i - 1][k]; // using item i does not improve the solution
                }
            }
        }
    }

    // Step 3: Build the solution
    for(unsigned int i = 0; i < n; i++) {
        usedItems[i] = false;
    }
    unsigned int remainingWeight = maxWeight;
    unsigned int curItem = n - 1;
    for(unsigned int i = n - 1; i > 0; i--) {
        // Stop earlier of the all the items have already been added to the solution
        if(remainingWeight == 0) break;

        // An item is used if not including reduces the total value for a knapsack of the same size
        if(maxValue[i][remainingWeight] != maxValue[i-1][remainingWeight]) {
            usedItems[i] = true;
            remainingWeight -= weights[i];
            curItem--;
        }
    }
    // If remainingWeight > 0, then the first item is used
    if(remainingWeight > 0) {
        usedItems[0] = true;
    }

    return maxValue[n-1][maxWeight];
}

#endif //DYNAMIC_PROGRAMMING_H
