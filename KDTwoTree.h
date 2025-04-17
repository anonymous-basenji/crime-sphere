//
// Created by joshu on 4/16/2025.
//

#ifndef KDTWOTREE_H
#define KDTWOTREE_H

#include "FileProcessing.h"

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

    KDTwoNode* root;

    KDTwoNode* build(std::vector<CrimeData>& data, int level, int leftIndex, int rightIndex);

    void clearTree(KDTwoNode* root);

public:
    KDTwoTree(std::vector<CrimeData>& data);

    ~KDTwoTree();

};



#endif //KDTWOTREE_H
