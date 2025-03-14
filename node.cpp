#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include "node.h"

using namespace std;

Node::Node(string descrip, int lat, int longit) {
    description = descrip;
    latitude = lat;
    longitude = longit;
}

bool Node::addConnection(Node* node) {
    int distance = calcDist(node);
    connectedNodes.push_back(pair(node, distance));
}

float Node::calcDist(Node* node) {
    // dist = sqrt(x^2 + y^2)
    return sqrt(pow(latitude - node->latitude, 2) + pow(longitude - node->longitude, 2));
}