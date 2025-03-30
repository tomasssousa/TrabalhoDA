#include <iostream>
#include "Menu.h"
#include "Batch_Mode_read.h"
#include <string>
#include <vector>
#include "../data_structures/Graph.h"
#include "readCSV.h"
#include "Driving_only.h"
#include "Menu_Input_Handler.h"


//use enums for easier control of choices
enum MainMenuChoices {
    LOAD_AND_PARSE = 1,
    DISPLAY_INFO,
    PLAN_ROUTE,
    MENU_INPUT,
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

enum MenuInputChoices {
    INPUT_READ_NORMAL = 1,
    INPUT_READ_RESTRICTED,
    INPUT_READ_RESTRICTED_MAX_WALK,
    INPUT_BATCH_BACK_TO_MAIN
};

enum BatchMenuChoices {
    READ_NORMAL = 1,
    READ_RESTRICTED,
    READ_RESTRICTED_MAX_WALK,
    BATCH_BACK_TO_MAIN
};

void displayIntroMenu() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "          Welcome to our project!     " << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "1. Load and Parse the given files " << std::endl;
    std::cout << "2. Display the information about the Urban Map" << std::endl;
    std::cout << "3. Plan a route (after choosing this option you will be sent to another menu)" << std::endl;
    std::cout << "4. Give Input in Menu" << std::endl;
    std::cout << "5. Execute Batch Mode" << std::endl;
    std::cout << "6. About" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

void displayRouteMenu() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "          Welcome to the Routes Menu!     " << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "1. Independent Route Planning" << std::endl;
    std::cout << "2. Restricted Route Planning" << std::endl;
    std::cout << "3. Environmentally-Friendly Route Planning (driving and walking)" << std::endl;
    std::cout << "4. Go back to Main Menu" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

void displayAboutMenu() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "          Welcome to the About Menu!     " << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "1. Go back to Main Menu" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

void displayMenuInput() {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "         Welcome to the Menu Input Menu!     " << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "This menu main function is to ask for user input which will write it to a input.txt file" <<
            std::endl;
    std::cout << "which can be then read using Batch Mode!" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "1. Read Normal Input File" << std::endl;
    std::cout << "2. Read Restricted Input File" << std::endl;
    std::cout << "3. Read Restricted Input File with MaxWalkTime" << std::endl;
    std::cout << "4. Go back to Main Menu" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

void displayBatchMenu() {
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "          Welcome to the Batch Mode Menu!     " << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "1. Read Normal Input File" << std::endl;
    std::cout << "2. Read Restricted Input File" << std::endl;
    std::cout << "3. Read Restricted Input File with MaxWalkTime" << std::endl;
    std::cout << "4. Go back to Main Menu" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

template<class T>
void displayUrbanInfo(Graph<T> *graph) {
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "          Welcome to the Urban Map Info Menu!     " << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "                   Vertexes                    " << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "This graph has Vertexes: ";
    for (auto v: graph->getVertexSet()) {
        std::cout << " " << v->getLocation() << ",";
    }
    std::cout << "." << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "                    Edges                    " << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "This graph has Edges:";
    for (auto v: graph->getVertexSet()) {
        for (auto e: v->getAdj()) {
            auto w = e->getDest();
            std::cout << v->getLocation() << " - " << w->getLocation() << " with weights as: " << e->getDrivingWeight()
                    << "(driving) and " << e->getWalkingWeight() << "(walking) " << std::endl;
        }
    }
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Press 6 To Exit!" << std::endl;
}

auto graph = new Graph<int>();

void handle_csv() {
    //!method to build the argument graph
    loadLocations(graph, "../CSV_Files/Locations.csv");
    loadDistances(graph, "../CSV_Files/Distances.csv");
}

void getAvoidNodes(std::vector<int> &avoid_nodes) {
    std::string input;
    std::cout << "AvoidNodes? (enter them as comma separated values)";
    std::cin.ignore(); //! ignore any leftover newline characters
    std::getline(std::cin, input);

    std::stringstream ss(input);
    std::string node;
    while (std::getline(ss, node, ',')) {
        avoid_nodes.push_back(std::stoi(node));
    }
}

void getAvoidSegments(std::vector<std::pair<int, int> > &avoid_segments) {
    std::string input;
    std::cout << "AvoidSegments? (enter them as pairs of ints separated by commas, e.g., 1,2 3,4): ";
    std::getline(std::cin, input);

    std::stringstream ss(input);
    std::string pairStr;
    while (ss >> pairStr) {
        const size_t commaPos = pairStr.find(',');
        if (commaPos != std::string::npos) {
            //!if it finds the character position
            int first = std::stoi(pairStr.substr(0, commaPos));
            int second = std::stoi(pairStr.substr(commaPos + 1));
            avoid_segments.emplace_back(first, second);
        }
    }
}


void handleMainMenuChoice(const int choice) {
    std::string mode;
    int source;
    int dest;
    std::vector<int> avoidable_nodes;
    std::vector<std::pair<int, int> > avoidable_segments;
    int included_node;
    int Max_Walk_Time;
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
                if (routeChoice == INDEPENDENT_ROUTE) {
                    //!driving only without restrictions
                    Driving_only(graph, source, dest);
                    break;
                }

                if (routeChoice == ROUTE_BACK_TO_MAIN) break;
            }
            break;
        case MENU_INPUT:
            while (true) {
                displayMenuInput();
                int inputChoice;
                std::cout << "What is your Choice? " << std::endl;
                std::cin >> inputChoice;
                if (inputChoice == INPUT_BATCH_BACK_TO_MAIN) break;
                else if (inputChoice == INPUT_READ_NORMAL) {
                    int destination;
                    int source2;
                    std::string mode2;

                    std::cout << "Mode? " << std::endl;
                    std::cin >> mode2;
                    std::cout << "Source? " << std::endl;
                    std::cin >> source2;
                    std::cout << "Destination? " << std::endl;
                    std::cin >> destination;
                    Write_Normal_Route("../Files/input.txt", mode2, source2, destination);
                } else if (inputChoice == INPUT_READ_RESTRICTED) {
                    std::string mode2;
                    int source2;
                    int destination;
                    std::vector<int> avoid_nodes2;
                    std::vector<pair<int, int> > avoid_segments2;
                    int includeNode2;
                    std::cout << "Mode? " << std::endl;
                    std::cin >> mode2;
                    std::cout << "Source? " << std::endl;
                    std::cin >> source2;
                    std::cout << "Destination? " << std::endl;
                    std::cin >> destination;
                    getAvoidNodes(avoid_nodes2);
                    std::cout << endl;
                    getAvoidSegments(avoid_segments2);
                    std::cout << endl;
                    std::cout << "IncludeNode? " << std::endl;
                    std::cin >> includeNode2;
                    Write_Avoidable_Route("../Files/input.txt", mode2, source2, destination, avoid_nodes2,
                                          avoid_segments2,
                                          includeNode2);
                } else if (inputChoice == INPUT_READ_RESTRICTED_MAX_WALK) {
                    std::string mode2;
                    int source2;
                    int destination;
                    int MaxWalkTime2;
                    std::vector<int> avoid_nodes2;
                    std::vector<pair<int, int> > avoid_segments2;
                    std::cout << "Mode? " << std::endl;
                    std::cin >> mode2;
                    std::cout << "Source? " << std::endl;
                    std::cin >> source2;
                    std::cout << "Destination? " << std::endl;
                    std::cin >> destination;
                    std::cout << "MaxWalkTime? " << std::endl;
                    std::cin >> MaxWalkTime2;
                    getAvoidNodes(avoid_nodes2);
                    std::cout << endl;
                    getAvoidSegments(avoid_segments2);
                    std::cout << endl;
                    Write_Avoidable_MaxWalk_Route("../Files/input.txt", mode2, source2, destination, MaxWalkTime2,
                                                  avoid_nodes2, avoid_segments2);
                }
            }
            break;
        case EXECUTE_BATCH_MODE:
            while (true) {
                displayBatchMenu();
                int batchChoice;
                std::cin >> batchChoice;
                if (batchChoice == BATCH_BACK_TO_MAIN) break;
                else if (batchChoice == READ_NORMAL) {
                    readBatchModeNormal("../Files/input.txt", mode, source, dest);
                    /*
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Mode: " << mode << "\n";
                    std::cout << "Source: " << source << "\n";
                    std::cout << "Destination: " << destination << "\n";
                    std::cout << "----------------------------------------" << std::endl;
                    */
                } else if (batchChoice == READ_RESTRICTED) {
                    readBatchModeComplex("../Files/input.txt", mode, source, dest, avoidable_nodes,
                                         avoidable_segments, included_node);

                    /*
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Mode: " << mode << "\n";
                    std::cout << "Source: " << source << "\n";
                    std::cout << "Destination: " << destination << "\n";

                    std::cout << "Avoidable Nodes: ";
                    for (const int &node: avoidable_nodes) {
                        std::cout << node << " ";
                    }
                    std::cout << "\n";

                    std::cout << "Avoidable Segments: ";
                    for (const auto &segment: avoidable_segments) {
                        std::cout << "(" << segment.first << "," << segment.second << ")";
                    }
                    std::cout << "\n";

                    std::cout << "Included Node: " << included_node << "\n";
                    std::cout << "----------------------------------------" << std::endl;
                    */
                } else if (batchChoice == READ_RESTRICTED_MAX_WALK) {
                    readBatchModeComplexWalkTime("../Files/input.txt", mode, source, dest, Max_Walk_Time,
                                                 avoidable_nodes, avoidable_segments, included_node);
                    /*
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Mode: " << mode << "\n";
                    std::cout << "Source: " << source << "\n";
                    std::cout << "Destination: " << destination << "\n";
                    std::cout << "MaxWalkTime: " << MaxWalkTime << "\n";

                    std::cout << "Avoidable Nodes: ";
                    for (const int &node: avoidable_nodes) {
                        std::cout << node << " ";
                    }
                    std::cout << "\n";

                    std::cout << "Avoidable Segments: ";
                    for (const auto &segment: avoidable_segments) {
                        std::cout << "(" << segment.first << "," << segment.second << ")";
                    }
                    std::cout << "\n";

                    std::cout << "Included Node: " << included_node << "\n";
                    std::cout << "----------------------------------------" << std::endl;
                    */
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
            std::cout << "Invalid Choice. Try again." << std::endl;
    }
}

