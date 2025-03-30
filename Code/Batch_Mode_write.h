#pragma once
#ifndef BATCH_MODE_WRITE_H
#define BATCH_MODE_WRITE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//Some forms of output
/*
*
*
--For Driving Only
Source:<id>
Destination:<id>
BestDrivingRoute:<id>,<id>,<id>(<int>)
AlternativeDrivingRoute:<id>,<id>,<id>(<int>)
------------------------------------------------------
Source:<id>
Destination:<id>
RestrictedDrivingRoute:<id>,<id>,<id>(<int>)
------------------------------------------------------

---For driving and walking---
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

/**
 *driving only
 * @brief This function will write the output from the Driving_only file to the output.txt, in this case only the source, destination, best driving route and alternative route
 * @param filename the file which we want to write into
 * @param source the source node
 * @param dest the destination node
 * @param BestDrivingRoute the best driving route
 * @param AlternativeDrivingRoute the alternative route
 * This code can also handle the cases when the AlternativeDrivingRoute is empty, or non-existent
 * @param best_time the time of the best driving route
 * @param alternative_time the time of alternative route
 */

inline void writeBatchModeNormal(const std::string &filename, const int source, const int dest,
                                 const std::vector<int> &BestDrivingRoute,
                                 const std::vector<int> &AlternativeDrivingRoute, const int best_time,
                                 const int alternative_time) {
    std::ofstream file(filename); //declare file as a output file
    if (!file.is_open() || file.fail()) {
        std::cout << "Error opening the file!" << std::endl;
        exit(0);
    }

    file << "Source:" << source << std::endl;
    file << "Destination:" << dest << std::endl;
    file << "BestDrivingRoute:";
    if (BestDrivingRoute.empty()) {
        //no path obtained
        file << "none" << std::endl;
    } else {
        for (const int i: BestDrivingRoute) {
            file << i << ",";
        }
    }
    file << "(" << best_time << ")";
    file << std::endl;

    file << "AlternativeDrivingRoute:";
    if (AlternativeDrivingRoute.empty()) {
        file << "none" << std::endl;
    } else {
        for (const int i: AlternativeDrivingRoute) {
            file << i << ",";
        }
        file << "(" << alternative_time << ")";
    }
    file << std::endl;

    file.close();
}

/**
 *driving only
 * @brief This function will write the output from the Driving_only file to the output.txt, in this case we will have a restricted path
 * @param filename the file which we want to write into
 * @param source the source node
 * @param dest the destination node
 * @param RestrictedDrivingRoute the best driving route
 * This code can also handle the cases when the AlternativeDrivingRoute is empty, or non-existent
 * @param restricted_time
 */

inline void writeBatchModeNormalRestricted(const std::string &filename, const int source, const int dest,
                                           const std::vector<int> &RestrictedDrivingRoute, const int restricted_time) {
    std::ofstream file(filename); //declare file as a output file
    if (!file.is_open() || file.fail()) {
        std::cout << "Error opening the file!" << std::endl;
        exit(0);
    }

    file << "Source:" << source << std::endl;
    file << "Destination:" << dest << std::endl;
    file << "RestrictedDrivingRoute:";
    if (RestrictedDrivingRoute.empty()) {
        //no path obtained
        file << "none" << std::endl;
    } else {
        for (const int i: RestrictedDrivingRoute) {
            file << i << ",";
        }
        file << "(" << restricted_time << ")";
    }
    file << std::endl;
    file.close();
}

/**
 *driving-walking mode
 * @brief This function will write the output from the Driving_And_Walking file to the output.txt
 * @param filename the file which we want to write into
 * @param source the source node
 * @param dest the destination node
 * @param DrivingRoute the driving route path
 * @param driving_time the driving route time
 * @param ParkingNode the parking node where we stopped
 * @param WalkingRoute the walking route path
 * @param walking_time the walking route time
 * @param TotalTime the total time spent
 */

inline void writeBatchModeDrivingWalking(const std::string &filename, const int source, const int dest,
                                         const std::vector<int> &DrivingRoute, const int driving_time,
                                         const int ParkingNode,
                                         const std::vector<int> &WalkingRoute, const int walking_time,
                                         const int TotalTime) {
    std::ofstream file(filename); //declare file as a output file
    if (!file.is_open() || file.fail()) {
        std::cout << "Error opening the file!" << std::endl;
        exit(0);
    }

    file << "Source:" << source << std::endl;
    file << "Destination:" << dest << std::endl;
    file << "DrivingRoute:";
    if (DrivingRoute.empty()) {
        //no path obtained
        file << "none" << std::endl;
    } else {
        for (const int i: DrivingRoute) {
            file << i << ",";
        }
        file << "(" << driving_time << ")";
    }
    file << std::endl;

    file << "ParkingNode:" << ParkingNode << std::endl;
    file << "WalkingRoute:";

    if (WalkingRoute.empty()) {
        file << "none" << std::endl;
    } else {
        for (const int i: WalkingRoute) {
            file << i << ",";
        }
        file << "(" << walking_time << ")";
    }
    file << std::endl;

    file << "TotalTime:" << TotalTime << std::endl;
    file.close();
}

/**
 *driving-walking mode, when the path is impossible
 * @brief This function will write the output from the Driving_And_Walking file to the output.txt
 * @param filename the file which we want to write into
 * @param source the source node
 * @param dest the destination node
 * @param message the error message

 */
inline void writeBatchModeDrivingWalkingImpossible(const std::string &filename, const int source, const int dest,
                                                   const std::string &message) {
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
    file << "Message:" << message << std::endl;

    file.close();
}

/**
 *driving-walking mode
 *alternatives routes case
 * @brief This function will write the output from the Driving_And_Walking file to the output.txt
 * @param filename the file which we want to write into
 * @param source the source node
 * @param dest the destination node
 * @param DrivingRoute1 the driving route 1
 * @param driving_time1 the driving time 1
 * @param ParkingNode1 the parking node 1
 * @param WalkingRoute1 the walking route 1
 * @param walking_time_1 the walking time 1
 * @param TotalTime1 the total time 1
 * @param DrivingRoute2 the driving route 2
 * @param driving_time2 the driving time 2
 * @param ParkingNode2 the parking node 2
 * @param WalkingRoute2 the walking route 2
 * @param walking_time_2 the walking time 2
 * @param TotalTime2 the total time 2
 *
 */

inline void writeBatchModeDrivingWalkingApproximate(const std::string &filename, const int source, const int dest,
                                                    const std::vector<int> &DrivingRoute1, const int driving_time1,
                                                    const int ParkingNode1,
                                                    const std::vector<int> &WalkingRoute1, const int walking_time_1,
                                                    int TotalTime1,
                                                    const std::vector<int> &DrivingRoute2, const int driving_time2,
                                                    const int ParkingNode2,
                                                    const std::vector<int> &WalkingRoute2, const int walking_time_2,
                                                    const int TotalTime2) {
    std::ofstream file(filename); //declare file as a output file
    if (!file.is_open() || file.fail()) {
        std::cout << "Error opening the file!" << std::endl;
        exit(0);
    }

    file << "Source:" << source << std::endl;
    file << "Destination:" << dest << std::endl;
    file << "DrivingRoute1:";
    if (DrivingRoute1.empty()) {
        //no path obtained
        file << "none" << std::endl;
    } else {
        for (const int i: DrivingRoute1) {
            file << i << ",";
        }
        file << "(" << driving_time1 << ")";
    }
    file << std::endl;

    file << "ParkingNode1:" << ParkingNode1 << std::endl;
    file << "WalkingRoute1:";

    if (WalkingRoute1.empty()) {
        file << "none" << std::endl;
    } else {
        for (const int i: WalkingRoute1) {
            file << i << ",";
        }
        file << "(" << walking_time_1 << ")";
    }
    file << std::endl;

    file << "TotalTime1:" << TotalTime1 << std::endl;

    file << "DrivingRoute2:";
    if (DrivingRoute2.empty()) {
        //no path obtained
        file << "none" << std::endl;
    } else {
        for (const int i: DrivingRoute2) {
            file << i << ",";
        }
        file << "(" << driving_time2 << ")";
    }
    file << std::endl;

    file << "ParkingNode2:" << ParkingNode2 << std::endl;
    file << "WalkingRoute2:";

    if (WalkingRoute2.empty()) {
        file << "none" << std::endl;
    } else {
        for (const int i: WalkingRoute2) {
            file << i << ",";
        }
        file << "(" << walking_time_2 << ")";
    }
    file << std::endl;

    file << "TotalTime2:" << TotalTime2 << std::endl;

    file.close();
}


#endif //BATCH_MODE_WRITE_H
