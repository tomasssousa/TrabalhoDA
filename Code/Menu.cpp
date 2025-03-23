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
    std::cout<<"5. About"<<std::endl;
    std::cout<<"6. Exit"<<std::endl;
    std::cout<< "----------------------------------------" << std::endl;

    int choice;
    std::cout<<"What is your choice (choose a number between 1-6)? ";
    std::cin >> choice;
    if (choice == 3) {
        Menu_routes();
    } else if (choice == 6) {
        exit(0);
    }
}

void Menu_routes() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout<<"          Welcome to the Routes Menu!     "<<std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "1. Independent Route Planning" <<std::endl;
    std::cout << "2. Restricted Route Planning" <<std::endl;
    std::cout << "3. Environmentally-Friendly Route Planning (driving and walking)" <<std::endl;
    std::cout << "4. Go back to Main Menu" <<std::endl;
    std::cout<< "----------------------------------------" << std::endl;
    int choice;
    std::cout<<"What is your choice (choose a number between 1-4)? ";
    std::cin >> choice;
    if (choice == 4) {
        Menu_intro();
    }

}

void Menu_about() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout<<"          Welcome to the About Menu!     "<<std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "1. Go back to Main Menu"<<std::endl;
    int choice;
    std::cout<<"What is your choice? ";
    std::cin>>choice;
    if (choice == 1) {
        Menu_intro();
    }

}

