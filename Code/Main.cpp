#include "Menu.h"
#include <iostream>
#include <string>
#include "Batch_Mode_read.h"
#include <vector>

#include "../data_structures/Graph.h"

template<class T>
extern Graph<int> graph;

int main() {
    while (true) {
        displayIntroMenu();
        int choice;
        std::cout << "What is your choice? " << std::endl;
        std::cin >> choice;
        handleMainMenuChoice(choice);
    }
    return 0;
}
