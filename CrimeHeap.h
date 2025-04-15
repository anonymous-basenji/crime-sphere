//
// Created by andrew on 4/12/25.
//

#ifndef CRIMEHEAP_H
#define CRIMEHEAP_H

#include <iostream>
#include <queue>
#include <vector>
#include <functional>


#include "FileProcessing.h"
using namespace std;

// based on sample code at https://cplusplus.com/reference/queue/priority_queue/priority_queue/
class PairCompare
{
    bool reverse;
public:
    PairCompare(const bool& revparam=false)
    {reverse=revparam;}
    bool operator() (const pair<CrimeData, float>& lhs, const pair<CrimeData, float>& rhs) const
    {
        if (reverse) return (lhs.second > rhs.second);
        else return (lhs.second < rhs.second);
    }
};

typedef priority_queue<CrimeData, vector<pair<CrimeData, float>>, PairCompare> CustomPriorityQueue;
// Heap is implemented as a priority queue, which is implemented as a vector
class CrimeHeap {
    CustomPriorityQueue heap;
    int radius;
    float latitude;
    float longitude;
    public:
        CrimeHeap(int radParam, float latParam, float longParam); // constructor initializes heap with data from FileProcessing.data
        vector<CrimeData> getCrimes(); // returns vector of all crimes, sorted in order
        vector<CrimeData> getCrimesInRadius(); // takes in coordinates for user's current location
        float calcDist(CrimeData crime) const; // return distance between a crime and current lat/long
};



#endif //CRIMEHEAP_H
