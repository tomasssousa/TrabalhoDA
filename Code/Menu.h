
#ifndef MENU_H
#define MENU_H
#include "../data_structures/Graph.h"

void displayIntroMenu();

void displayAboutMenu();

void displayRouteMenu();

void displayMenuInput();

void displayBatchMenu();

template<class T>
void displayUrbanInfo(Graph<T> *graph);

void handleMainMenuChoice(int choice);

void getAvoidNodes(std::vector<int> &avoid_nodes);

void getAvoidSegments(std::vector<std::pair<int, int> > &avoid_segments);

#endif //MENU_H
