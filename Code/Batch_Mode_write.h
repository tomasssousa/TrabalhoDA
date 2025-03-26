#pragma once
#ifndef BATCH_MODE_WRITE_H
#define BATCH_MODE_WRITE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

//Some forms of output
/*
*
Source:<id>
Destination:<id>
BestDrivingRoute:<id>,<id>,<id>(<int>)
AlternativeDrivingRoute:<id>,<id>,<id>(<int>)
------------------------------------------------------
Source:<id>
Destination:<id>
RestrictedDrivingRoute:<id>,<id>,<id>(<int>)
------------------------------------------------------
Source:<id>
Destination:<id>
DrivingRoute:<id>,<id>,<id>(<int>)
ParkingNode:<id>
WalkingRoute:<id>,<id>,<id>(<int>)
TotalTime:<int>
----------------------------------------------------------
Source<id>
Destination:<id>
DrivingRoute1:<id>,<id>,<id>(<int>)
ParkingNode1:<id>
WalkingRoute1:<id>,<id>,<id>(<int>)
TotalTime1:<int>
DrivingRoute2:<id>,<id>,<id>(<int>)
ParkingNode2:<id>
WalkingRoute2:<id>,<id>,<id>(<int>)
TotalTime2:<int>
 */


//Similar logic to reading from the input.txt

inline void writeBatchModeNormal(const std::string &filename,const int source,const int dest, const std::vector<int>& BestDrivingRoute, const std::vector<int>& AlternativeDrivingRoute) {
    std::ofstream file(filename); //declare file as a output file
    if (!file.is_open() || file.fail()) {
   std::cout << "Error opening the file!" << std::endl;
      exit(0);
    }

    file << "Source:" << source << std::endl;
    file << "Destination:" << dest << std::endl;
    file << "BestDrivingRoute:";
    if (BestDrivingRoute.empty()) { //no path obtained
        file << "none" << std::endl;
    } else {
        for (const int i : BestDrivingRoute) {
            file << i << ",";
        }
    }
    file << std::endl;

    file << "AlternativeDrivingRoute:";
    if (AlternativeDrivingRoute.empty()) {
        file << "none" << std::endl;
    } else {
        for (const int i : AlternativeDrivingRoute) {
            file << i << ",";
        }
    }
    file << std::endl;

    file.close();
}

inline void writeBatchModeNormalRestricted(const std::string &filename,const int source,const int dest, const std::vector<int>& RestrictedDrivingRoyte) {
    std::ofstream file(filename); //declare file as a output file
    if (!file.is_open() || file.fail()) {
        std::cout << "Error opening the file!" << std::endl;
        exit(0);
    }

    file << "Source:" << source << std::endl;
    file << "Destination:" << dest << std::endl;
    file << "RestrictedDrivingRoute:";
    if (RestrictedDrivingRoyte.empty()) { //no path obtained
        file << "none" << std::endl;
    } else {
        for (const int i : RestrictedDrivingRoyte) {
            file << i << ",";
        }
    }
    file << std::endl;
    file.close();
}

inline void writeBatchModeDrivingWalking(const std::string &filename,const int source,const int dest, const std::vector<int>& DrivingRoute, const int ParkingNode, const std::vector<int>& WalkingRoute,int TotalTime) {
    std::ofstream file(filename); //declare file as a output file
    if (!file.is_open() || file.fail()) {
        std::cout << "Error opening the file!" << std::endl;
        exit(0);
    }

    file << "Source:" << source << std::endl;
    file << "Destination:" << dest << std::endl;
    file << "DrivingRoute:";
    if (DrivingRoute.empty()) { //no path obtained
        file << "none" << std::endl;
    } else {
        for (const int i : DrivingRoute) {
            file << i << ",";
        }
    }
    file << std::endl;

    file << "ParkingNode:" << ParkingNode << std::endl;
    file << "WalkingRoute:";

    if (WalkingRoute.empty()) {
        file << "none" << std::endl;
    } else {
        for (const int i : WalkingRoute) {
            file << i << ",";
        }
    }
    file << std::endl;

    file << "TotalTime:" << TotalTime << std::endl;
    file.close();
}

inline void writeBatchModeDrivingWalkingImpossible(const std::string &filename,const int source, const int dest, std::string message) {
    std::ofstream file(filename); //declare file as a output file
    if (!file.is_open() || file.fail()) {
        std::cout << "Error opening the file!" << std::endl;
        exit(0);
    }

    file << "Source:" << source << std::endl;
    file << "Destination:" << dest << std::endl;
    file << "DrivingRoute:none" << std::endl;
    file << "ParkingNode:none" << std::endl;
    file << "WalkingRoute:none" << std::endl;
    file << "TotalTime:none" << std::endl;
    file << message << std::endl;

    file.close();
}

inline void writeBatchModeDrivingWalkingApproximate(const std::string &filename,const int source,const int dest, const std::vector<int>& DrivingRoute1, const int ParkingNode1, const std::vector<int>& WalkingRoute1,int TotalTime1,const std::vector<int>& DrivingRoute2,const int ParkingNode2,const std::vector<int>& WalkingRoute2,const int TotalTime2){
    std::ofstream file(filename); //declare file as a output file
    if (!file.is_open() || file.fail()) {
        std::cout << "Error opening the file!" << std::endl;
        exit(0);
    }

    file << "Source:" << source << std::endl;
    file << "Destination:" << dest << std::endl;
    file << "DrivingRoute1:";
    if (DrivingRoute1.empty()) { //no path obtained
        file << "none" << std::endl;
    } else {
        for (const int i : DrivingRoute1) {
            file << i << ",";
        }
    }
    file << std::endl;

    file << "ParkingNode1:" << ParkingNode1 << std::endl;
    file << "WalkingRoute1:";

    if (WalkingRoute1.empty()) {
        file << "none" << std::endl;
    } else {
        for (const int i : WalkingRoute1) {
            file << i << ",";
        }
    }
    file << std::endl;

    file << "TotalTime1:" << TotalTime1 << std::endl;

    file << "DrivingRoute2:";
    if (DrivingRoute2.empty()) { //no path obtained
        file << "none" << std::endl;
    } else {
        for (const int i : DrivingRoute2) {
            file << i << ",";
        }
    }
    file << std::endl;

    file << "ParkingNode2:" << ParkingNode2 << std::endl;
    file << "WalkingRoute2:";

    if (WalkingRoute2.empty()) {
        file << "none" << std::endl;
    } else {
        for (const int i : WalkingRoute2) {
            file << i << ",";
        }
    }
    file << std::endl;

    file << "TotalTime2:" << TotalTime2 << std::endl;

    file.close();
}





#endif //BATCH_MODE_WRITE_H
