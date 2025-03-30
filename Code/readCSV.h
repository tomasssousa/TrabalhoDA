#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
//#include "../data_structures/Graph.h"


using namespace std;
/**
* @brief Function to load Locations from a Locations.csv file!
* @param graph, the graph which will be used to save the vertexes
* @param filename, the file which we will fetch the data
*/

inline string trim(const string &str) {
    const auto strBegin = str.find_first_not_of(" \t\r\n,");
    if (strBegin == string::npos)
        return "";

    const auto strEnd = str.find_last_not_of(" \t\r\n,");
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

template<class T>
inline void loadLocations(Graph<T> *graph, const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream temp(line);
        std::string location, id, code, parking;
        std::getline(temp, location, ',');
        std::getline(temp, id, ',');
        std::getline(temp, code, ',');
        std::getline(temp, parking);

        location = trim(location);
        id = trim(id);
        code = trim(code);
        parking = trim(parking);

        //verify if the string is empty
        if (id.empty() || parking.empty()) {
            std::cerr << "[ERROR] Invalid line skipped (missing ID or parking): " << line << std::endl;
            continue;
        }

        //verify if id and parking are digits
        if (!std::all_of(id.begin(), id.end(), ::isdigit) ||
            !std::all_of(parking.begin(), parking.end(), ::isdigit)) {
            std::cerr << "[ERROR] Non-numeric field(s): ID='" << id << "', Parking='" << parking << "'\n";
            continue;
        }

        try {
            int parsedId = stoi(id);
            int parsedParking = stoi(parking);


            std::cout << "[INFO] Parsed: ID='" << parsedId << "', Location='" << location
                    << "', Code='" << code << "', Parking='" << parsedParking << "'\n";

            graph->addVertex(parsedId, location, code, parsedParking);
        } catch (const std::exception &e) {
            std::cerr << "[FATAL] Error converting line: " << line << " -> " << e.what() << std::endl;
        }
    }

    file.close();
}

/**
* @brief Function to load Distances from a Distances.csv file!
* @param graph, the graph which will be used to save the edges
* @param filename, the file which we will fetch the data
*/
template<class T>
inline void loadDistances(Graph<T> *graph, const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[FATAL] Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream temp(line);
        std::string loc1, loc2, driving, walking;
        std::getline(temp, loc1, ',');
        std::getline(temp, loc2, ',');
        std::getline(temp, driving, ',');
        std::getline(temp, walking);

        //trim the strings
        loc1 = trim(loc1);
        loc2 = trim(loc2);
        driving = trim(driving);
        walking = trim(walking);

        if (loc1.empty() || loc2.empty() || driving.empty() || walking.empty()) {
            std::cerr << "[ERROR] Empty field on line: " << line << std::endl;
            continue;
        }

        //verify if id and parking are digits
        if (driving != "X" && !std::all_of(driving.begin(), driving.end(), ::isdigit) ||
            !std::all_of(walking.begin(), walking.end(), ::isdigit)) {
            std::cerr << "[ERROR] Non-numeric field(s): DRIVING='" << driving << "', WALKING='" << walking << "'\n";
            continue;
        }

        try {
            int id1 = graph->getVertexIdByCode(loc1);
            int id2 = graph->getVertexIdByCode(loc2);

            double drive;
            if (driving == "X" || driving == "x") {
                drive = INF; //set the driving distance to INF
            } else if (std::all_of(driving.begin(), driving.end(), ::isdigit)) {
                drive = std::stoi(driving); //if the drive is a digit
            } else {
                std::cerr << "[ERROR] Invalid driving field: '" << driving << "'\n";
                continue;
            }

            double walk = std::stoi(walking);

            std::cout << "[INFO] Parsed: " << loc1 << " → " << loc2
                    << " | Driving: " << drive << ", Walking: " << walk << std::endl;

            graph->addEdge(id1, id2, drive, walk);
        } catch (const std::exception &e) {
            //in case the conversion fails
            std::cerr << "[ERROR] Conversion failed: " << line << " → " << e.what() << std::endl;
        }
    }

    file.close();
}

