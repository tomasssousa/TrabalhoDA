#ifndef PALLET_H
#define PALLET_H

#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"
#include<iostream>


// Structure to store the pallets
struct Pallet{
    // the Pallets weight
    int weight;
    // the Pallets value
    int value;
};


// Map to identify each Pallet by its id
// it's here just to help with understanding the way the function is currently receiving the pallets
Map<int, struct Pallet> palletmap;

#endif //PALLET_H