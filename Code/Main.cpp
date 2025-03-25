#include "Menu.h"
#include <iostream>
#include <string>
#include "Batch_Mode_read.h"
#include <vector>

int main() {

    //Menu_intro();
    std::string mode;
    int source;
    int destination;
    std::vector<int> avoidable_nodes;
    std::vector<std::pair<int,int>> avoidable_segments;
    int included_node;
    //readBatchModeNormal("../Files/input.txt",mode,source,destination);
    //std::cout << mode << " " << source << " " << destination << std::endl;
    readBatchModeComplex("../Files/input.txt",mode,source,destination,avoidable_nodes,avoidable_segments,included_node);
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
    return 0;
}
