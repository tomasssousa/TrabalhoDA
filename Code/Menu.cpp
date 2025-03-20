#include <iostream>
#include "Menu.h"


void Menu_intro() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout<<"          Welcome to our project!     "<<std::endl;
    std::cout<< "----------------------------------------" << std::endl;
    std::cout<<"1. Load and Parse the given files "<<std::endl;
    std::cout<<"2. Display the information about the Urban Map"<<std::endl;
    std::cout<<"3. Plan a route (after choosing this option you will be sent to another menu)"<<std::endl;
    std::cout<<"4. Execute Batch Mode"<<std::endl;
    std::cout<<"About"<<std::endl;
    std::cout<<"Exit"<<std::endl;
    std::cout<< "----------------------------------------" << std::endl;
}
