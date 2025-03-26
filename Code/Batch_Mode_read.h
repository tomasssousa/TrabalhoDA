#pragma once
#include <algorithm>
#include <string>
#include<iostream>
#include <sstream>
#include <fstream>
#include <vector>

//this first function is used to read normal inputs, inputs which don't avoid nodes or edges
inline void readBatchModeNormal(const std::string &filename, std::string &mode, int &source, int &destination) {
    std::ifstream file(filename); //open the file
    std::string line;

    if (!file.is_open()) {
        std::cout << "Error with opening the file!" << std::endl;
        exit(0);
    }

    while (std::getline(file,line)){ //while we are able to read each line of the file
        std::istringstream iss(line); //will receive the line as a input string
        std::string leading,value; //the leading strings before the ':' and value is what comes after

        if (std::getline(iss,leading, ':') && std::getline(iss,value)) {
            /*
             * the first getline reads characters up to the ':' symbol, extract everything before the ':' to the string leading
             * the second getline will read after the ':', will call the rest of the line, which will save it's content on value
             */
            if (leading == "Mode") {
                mode = value;
            } else if (leading == "Source") {
                source = std::stoi(value);
            } else if (leading == "Destination") {
                destination = std::stoi(value);
            }
        }
    }
    file.close();
}

inline void readBatchModeComplex(const std::string &filename, std::string &mode, int &source, int &destination,std::vector<int> &avoidable_nodes,std::vector<std::pair<int,int>> &avoidable_segments, int &included_node) {
    std::ifstream file(filename);
    std::string line;
    //same logic as the basic readBatch
    while (std::getline(file,line)) {
        std::istringstream iss(line);
        std::string leading,value;
        if (std::getline(iss,leading,':') && std::getline(iss,value)) {
            if (leading == "Mode") {
                mode = value;
            } else if (leading == "Source") {
                source = std::stoi(value);
            } else if (leading == "Destination") {
                destination = std::stoi(value);
            } else if (leading == "AvoidNodes") {
                std::istringstream nodes(value);
                std::string node;
                while (std::getline(nodes,node,',')) {
                    if (!node.empty()) {
                        avoidable_nodes.push_back(std::stoi(node));
                    }
                }
            } else if (leading == "AvoidSegments") { //this logic now will be different
                std::istringstream segments(value); //now use the value as input string
                std::string segment;
                while (std::getline(segments,segment,')')) { //we didn't reach the end of the value string
                    if (segment.empty()) continue;

                    if (segment.front() == ',')
                        segment.erase(0,1);

                    if (!segment.empty()&&segment.front() == '(')
                        segment.erase(0,1);

                    std::replace(segment.begin(),segment.end(),',',' ');
                    std::istringstream segmentStream(segment);
                    int id1;
                    int id2;
                    segmentStream >> id1 >> id2;
                    avoidable_segments.emplace_back(id1,id2);
                }
            } else if (leading == "IncludeNode") {
                included_node = std::stoi(value);
            }
        }
    }
    file.close();
}

inline void readBatchModeComplexWalkTime(const std::string &filename, std::string &mode, int &source, int &destination,int &MaxWalkTime,std::vector<int> &avoidable_nodes,std::vector<std::pair<int,int>> &avoidable_segments, int &included_node) {
    std::ifstream file(filename);
    std::string line;
    //same logic as the basic readBatch
    while (std::getline(file,line)) {
        std::istringstream iss(line);
        std::string leading,value;
        if (std::getline(iss,leading,':') && std::getline(iss,value)) {
            if (leading == "Mode") {
                mode = value;
            } else if (leading == "Source") {
                source = std::stoi(value);
            } else if (leading == "Destination") {
                destination = std::stoi(value);
            } else if (leading == "MaxWalkTime") {
                MaxWalkTime = std::stoi(value);
            } else if (leading == "AvoidNodes") {
                std::istringstream nodes(value);
                std::string node;
                while (std::getline(nodes,node,',')) {
                    if (!node.empty()) {
                        avoidable_nodes.push_back(std::stoi(node));
                    }
                }
            } else if (leading == "AvoidSegments") { //this logic now will be different
                std::istringstream segments(value); //now use the value as input string
                std::string segment;
                while (std::getline(segments,segment,')')) { //we didn't reach the end of the value string
                    if (segment.empty()) continue;

                    if (segment.front() == ',') //if it is a token like ,(4,3) we need to first remove the leading ','
                        segment.erase(0,1);

                    if (!segment.empty()&&segment.front() == '(')
                        segment.erase(0,1);

                    std::replace(segment.begin(),segment.end(),',',' ');
                    std::istringstream segmentStream(segment);
                    int id1;
                    int id2;
                    segmentStream >> id1 >> id2;
                    avoidable_segments.emplace_back(id1,id2);
                }
            } else if (leading == "IncludeNode") {
                included_node = std::stoi(value);
            }
        }
    }
    file.close();
}

#ifndef BATCH_MODE_H
#define BATCH_MODE_H

#endif //BATCH_MODE_H
