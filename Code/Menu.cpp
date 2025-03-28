#include <iostream>
#include "Menu.h"
#include "Batch_Mode_read.h"
#include <string>
#include <vector>
#include "../data_structures/Graph.h"
#include "readCSV.h"
#include "Driving_only.h"


//use enums for easier control of choices
enum MainMenuChoices {
    LOAD_AND_PARSE = 1,
    DISPLAY_INFO,
    PLAN_ROUTE,
    EXECUTE_BATCH_MODE,
    ABOUT,
    EXIT
};

enum RouteMenuChoices {
    INDEPENDENT_ROUTE = 1,
    RESTRICTED_ROUTE,
    ENVIRONMENTALLY_FRIENDLY_ROUTE,
    ROUTE_BACK_TO_MAIN
};

enum AboutMenuChoices {
    ABOUT_BACK_TO_MAIN = 1
};

enum BatchMenuChoices {
    READ_NORMAL = 1,
    READ_RESTRICTED,
    READ_RESTRICTED_MAX_WALK,
    BATCH_BACK_TO_MAIN
};

void displayIntroMenu() {
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
}

void displayRouteMenu() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout<<"          Welcome to the Routes Menu!     "<<std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "1. Independent Route Planning" <<std::endl;
    std::cout << "2. Restricted Route Planning" <<std::endl;
    std::cout << "3. Environmentally-Friendly Route Planning (driving and walking)" <<std::endl;
    std::cout << "4. Go back to Main Menu" <<std::endl;
    std::cout<< "----------------------------------------" << std::endl;
}

void displayAboutMenu() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout<<"          Welcome to the About Menu!     "<<std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "1. Go back to Main Menu"<<std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

void displayBatchMenu() {
    std::cout << "---------------------------------------------" << std::endl;
    std::cout<<"          Welcome to the Batch Mode Menu!     "<<std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "1. Read Normal Input File"<<std::endl;
    std::cout << "2. Read Restricted Input File"<<std::endl;
    std::cout << "3. Read Restricted Input File with MaxWalkTime"<<std::endl;
    std::cout << "4. Go back to Main Menu" <<std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

template <class T>
void displayUrbanInfo(Graph<T> *graph){
    std::cout << "---------------------------------------------" << std::endl;
    std::cout<<"          Welcome to the Urban Map Info Menu!     "<<std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "                   Vertexes                    "<<std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "This graph has Vertexes: ";
    for (auto v : graph->getVertexSet()) {
        std::cout << " " << v->getLocation() << ",";
    }
    std::cout << "." << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "                    Edges                    " << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "This graph has Edges:";
    for (auto v : graph->getVertexSet()) {
        for (auto e : v->adj) {
            auto w = e->dest;
            std::cout << v->getLocation() << " - " << w->getLocation() << " with weights as: " << e->getDrivingWeight() << "(driving) and " << e->getWalkingWeight() << "(walking) " << std::endl;
        }
    }
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Press 6 To Exit!" << std::endl;
}

auto graph = new Graph<int>();

void handle_csv() { //!method to build the argument graph
    loadLocations(graph,"../CSV_Files/Location.csv");
    loadDistances(graph,"../CSV_Files/Distances.csv");
}


void handleMainMenuChoice(const int choice) {
    switch (choice) {
        case LOAD_AND_PARSE: //will build the graph
            handle_csv();
            break;
        case DISPLAY_INFO: //display
            while (true) {
                displayUrbanInfo(graph);
                int infoChoice;
                std::cin >> infoChoice;
                if (infoChoice == 6) {
                    break;
                }
            }
            break;
        case PLAN_ROUTE:
            while (true) {
                displayRouteMenu();
                int routeChoice;
                std::cin >> routeChoice;
                if (routeChoice == ROUTE_BACK_TO_MAIN) break;
            }
            break;
        case EXECUTE_BATCH_MODE:
            while (true) {
                displayBatchMenu();
                int batchChoice;
                std::cin >> batchChoice;
                if (batchChoice == BATCH_BACK_TO_MAIN) break;
                else if (batchChoice == READ_NORMAL) {
                    std::string mode;
                    int source;
                    int destination;
                    readBatchModeNormal("../File/input.txt",mode,source,destination);
                    /*
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Mode: " << mode << "\n";
                    std::cout << "Source: " << source << "\n";
                    std::cout << "Destination: " << destination << "\n";
                    std::cout << "----------------------------------------" << std::endl;
                    */
                }
                else if (batchChoice == READ_RESTRICTED) {
                    std::string mode;
                    int source;
                    int destination;
                    std::vector<int> avoidable_nodes;
                    std::vector<std::pair<int,int>> avoidable_segments;
                    int included_node;
                    readBatchModeComplex("../Files/input.txt",mode,source,destination,avoidable_nodes,avoidable_segments,included_node);
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Mode: " << mode << "\n";
                    std::cout << "Source: " << source << "\n";
                    std::cout << "Destination: " << destination << "\n";

                    std::cout << "Avoidable Nodes: ";
                    for (const int &node : avoidable_nodes) {
                        std::cout << node << " ";
                    }
                    std::cout << "\n";

                    std::cout << "Avoidable Segments: ";
                    for (const auto &segment : avoidable_segments) {
                        std::cout << "(" << segment.first << "," << segment.second << ")";
                    }
                    std::cout << "\n";

                    std::cout << "Included Node: " << included_node << "\n";
                    std::cout << "----------------------------------------" << std::endl;
                }
                else if (batchChoice == READ_RESTRICTED_MAX_WALK) {
                    std::string mode;
                    int source;
                    int destination;
                    int MaxWalkTime;
                    std::vector<int> avoidable_nodes;
                    std::vector<std::pair<int,int>> avoidable_segments;
                    int included_node;
                    readBatchModeComplexWalkTime("../Files/input.txt",mode,source,destination,MaxWalkTime,avoidable_nodes,avoidable_segments,included_node);
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Mode: " << mode << "\n";
                    std::cout << "Source: " << source << "\n";
                    std::cout << "Destination: " << destination << "\n";
                    std::cout << "MaxWalkTime: " << MaxWalkTime << "\n";

                    std::cout << "Avoidable Nodes: ";
                    for (const int &node : avoidable_nodes) {
                        std::cout << node << " ";
                    }
                    std::cout << "\n";

                    std::cout << "Avoidable Segments: ";
                    for (const auto &segment : avoidable_segments) {
                        std::cout << "(" << segment.first << "," << segment.second << ")";
                    }
                    std::cout << "\n";

                    std::cout << "Included Node: " << included_node << "\n";
                    std::cout << "----------------------------------------" << std::endl;
                }
            }
            break;
        case ABOUT:
            displayAboutMenu();
            int aboutChoice;
            std::cin >> aboutChoice;
            if (aboutChoice == 1) break;
            break;
        case EXIT:
            graph->clear();
            std::exit(0);
        default:
            std::cout << "Invalid Choice. Try again."<<std::endl;
    }
}

