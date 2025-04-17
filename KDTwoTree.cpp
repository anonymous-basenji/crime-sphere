//
// Created by joshu on 4/16/2025.
//

#include "KDTwoTree.h"

#include <algorithm>
#include <iostream>
#include <ostream>

KDTwoTree::KDTwoNode::KDTwoNode(CrimeData &crime) {
    this->crime = crime;
    this->left = nullptr;
    this->right = nullptr;
}

// Since our data is in latitude and longitude, we cannot use Euclidean distance.
// Instead, we must resort to the Haversine formula for spherical distance.
// https://en.wikipedia.org/wiki/Great-circle_distance
double KDTwoTree::haversineDistance(const KDTwoNode &first, const KDTwoNode &second)  {
    const double R = 3958.8; // Average Earth radius in miles
    const double DEG_TO_RAD = M_PI / 180.0;

    double latitudeTwo = second.crime.latitude * DEG_TO_RAD;
    double latitudeOne = first.crime.latitude * DEG_TO_RAD;
    double longitudeTwo = second.crime.longitude * DEG_TO_RAD;
    double longitudeOne = first.crime.longitude * DEG_TO_RAD;

    double dLat = latitudeTwo - latitudeOne;
    double dLon = longitudeTwo - longitudeOne;

    double a = pow(sin(dLat / 2), 2) +
            cos(latitudeOne) * cos(latitudeTwo) * pow(sin(dLon / 2), 2);

    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    return R * c;
}

bool KDTwoTree::compareByLatitude(const CrimeData &first, const CrimeData &second) {
    return first.latitude < second.latitude;
}

bool KDTwoTree::compareByLongitude(const CrimeData &first, const CrimeData &second) {
    return first.longitude < second.longitude;
}

KDTwoTree::KDTwoNode * KDTwoTree::build(std::vector<CrimeData> &points, int level, int leftIndex, int rightIndex) {
    if (leftIndex > rightIndex) return nullptr;

    int axis = level % 2;
    int middleIndex = leftIndex + (rightIndex - leftIndex) / 2; // Prevent overflow

    // Find the middle element.
    // Very efficient method found here: https://stackoverflow.com/questions/4203407/kd-tree-slow-tree-construction
    // Basically 1 iteration of Quick Sort. Helps balance the tree.
    nth_element(
        points.begin() + leftIndex,
        points.begin() + middleIndex,
        points.begin() + rightIndex + 1,
            axis == 0 ? compareByLongitude : compareByLatitude);

    KDTwoNode* node = new KDTwoNode(points[middleIndex]);

    node->left = build(points, level + 1, leftIndex, middleIndex - 1);
    node->right = build(points, level + 1, middleIndex + 1, rightIndex);

    return node;
}

// Post order traversal
void KDTwoTree::clearTree(KDTwoNode *root) {
    if (!root) return;
    clearTree(root->left);
    clearTree(root->right);
    delete root;
}

KDTwoTree::KDTwoTree(std::vector<CrimeData> &data) {
    int rightIndex = static_cast<int>(data.size() - 1);
    root = build(data, 0, 0, rightIndex);
}

KDTwoTree::~KDTwoTree() {
    clearTree(root);
}
