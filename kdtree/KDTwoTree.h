//
// Created by joshu on 4/16/2025.
//

#ifndef KDTWOTREE_H
#define KDTWOTREE_H

#include "../FileProcessing.h"

using namespace std;

class KDTwoTree {

    struct KDTwoNode {
        CrimeData crime;

        KDTwoNode* left;
        KDTwoNode* right;

        KDTwoNode(CrimeData& crime);
    };

    static double haversineDistance(const KDTwoNode& first, const KDTwoNode& second);

    static bool compareByLatitude(const CrimeData& first, const CrimeData& second);
    static bool compareByLongitude(const CrimeData& first, const CrimeData& second);
    static double degreesToRadians(double num);

    KDTwoNode* root;

    KDTwoNode* build(vector<CrimeData>& data, int level, int leftIndex, int rightIndex);

    void clearTree(KDTwoNode* root);
    void findInRadiusHelper(KDTwoNode* node, CrimeData& target, int level, double maxMiles, vector<pair<CrimeData, double>>& results) const;


public:
    KDTwoTree(vector<CrimeData>& data);

    // Returns a pair with CrimeData and distance from input, sorted by closest crime to farthest
    vector<pair<CrimeData, double>> findInRadius(double latitude, double longitude, double maxMiles);

    ~KDTwoTree();

};

#endif //KDTWOTREE_H
