
#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"
#include "Pallet.h"
#include <iostream>
#include <map>

using namespace std;
/**
* @brief This function is responsible for calculating the optimal setup, using the brute force method.
* @param Pallets A map with the pallets to be used in the problem, identifiable by their id.
* @param n Number of Pallets.
* @param maxWeight Max possible weight.
* @param usedItems[] An array with items used marked in true or false             Could be changed to store the id of the used ones
* @return The integer with the optimal value.
*/
unsigned int knapsackBF(Map<int, struct Pallet> Pallets, unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    //total number of possibilities for arranging the truck, not counting weight limitations.
    unsigned int Iteration = pow(2,n);
    unsigned int MaxPossibleValue =0;
    for(unsigned int i = 0; i < Iteration; i++) {
        //binary representaion of the truck layout.
        std::bitset<Iteration> binarySub(i);
        int IterationV=0;
        int IterationW=0;
        for (int j=0; j<n;j++) {
            IterationV+=Pallets[j].value*binarySub[j];
            IterationW+=Pallets[j].weight*binarySub[j];
        }
        if (IterationW<=maxWeight && IterationV>MaxPossibleValue) {
            MaxPossibleValue=IterationV;
            for (int j=0; j<n;j++) {
                if (binarySub[j]==1) {usedItems[j]=true;}
                else {usedItems[j]=false;}
            }
        }
        // making sure that, if the solution is the empty truck, a most rare case, the array displays all false.
        if (MaxPossibleValue==0){
            for (int j=0; j<n;j++) {
                usedItems[j]=false;
            }
        }
    }
    return MaxPossibleValue;
}

#endif //BRUTE_FORCE_H