
#pragma once
#ifndef MENU_INPUT_HANDLER_H
#define MENU_INPUT_HANDLER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>

inline void Write_Normal_Route(const std::string &file_name, const std::string &mode, const int &source,
                               const int &destination) {
    std::ofstream file(file_name);
    if (!file.is_open() || file.fail()) {
        std::cout << "Error opening the file!" << std::endl;
        exit(0);
    }
    file << "Mode:" << mode << std::endl;
    file << "Source:" << source << std::endl;
    file << "Destination:" << destination << std::endl;

    file.close();
}

typedef std::vector<pair<int, int> > PairVector;

inline void Write_Avoidable_Route(const std::string &file_name, const std::string &mode, const int &source,
                                  const int &destination, const std::vector<int> &avoid_nodes,
                                  const PairVector &avoid_segments, const int &include_node) {
    std::ofstream file(file_name);
    if (!file.is_open() || file.fail()) {
        std::cout << "Error opening the file!" << std::endl;
        exit(0);
    }
    file << "Mode:" << mode << std::endl;
    file << "Source:" << source << std::endl;
    file << "Destination:" << destination << std::endl;

    file << "AvoidNodes:" << avoid_nodes[0];
    for (int i = 1; i < avoid_nodes.size(); i++) {
        file << "," << avoid_nodes[i];
    }
    file << std::endl;

    file << "AvoidSegments:" << "(" << avoid_segments[0].first << "," << avoid_segments[0].second << ")";
    for (int i = 1; i < avoid_segments.size(); i++) {
        file << "," << "(" << avoid_segments[i].first << "," << avoid_segments[i].second << ")";
    }
    file << std::endl;

    file << "IncludeNode:" << include_node << std::endl;


    file.close();
}

inline void Write_Avoidable_MaxWalk_Route(const std::string &file_name, const std::string &mode, const int &source,
                                          const int &destination, const int &MaxWalk,
                                          const std::vector<int> &avoid_nodes,
                                          const PairVector &avoid_segments) {
    std::ofstream file(file_name);
    if (!file.is_open() || file.fail()) {
        std::cout << "Error opening the file!" << std::endl;
        exit(0);
    }
    file << "Mode:" << mode << std::endl;
    file << "Source:" << source << std::endl;
    file << "Destination:" << destination << std::endl;
    file << "MaxWalkTime:" << MaxWalk << std::endl;

    file << "AvoidNodes:" << avoid_nodes[0];
    for (int i = 1; i < avoid_nodes.size(); i++) {
        file << "," << avoid_nodes[i];
    }
    file << std::endl;

    file << "AvoidSegments:" << "(" << avoid_segments[0].first << "," << avoid_segments[0].second << ")";
    for (int i = 1; i < avoid_segments.size(); i++) {
        file << "," << "(" << avoid_segments[i].first << "," << avoid_segments[i].second << ")";
    }
    file << std::endl;
    file.close();
}


#endif //MENU_INPUT_HANDLER_H
