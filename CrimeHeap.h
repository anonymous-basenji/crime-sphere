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
    bool operator() (const pair<CrimeData, double>& lhs, const pair<CrimeData, double>& rhs) const
    {
        if (reverse) return (lhs.second < rhs.second);
        else return (lhs.second > rhs.second);
    }
};

typedef priority_queue<pair<CrimeData, double>, vector<pair<CrimeData, double>>, PairCompare> CustomPriorityQueue;
// Heap is implemented as a priority queue, which is implemented as a vector
class CrimeHeap {
    CustomPriorityQueue heap;
    int radius;
    double latitude;
    double longitude;
    public:
        CrimeHeap(int radParam, double latParam, double longParam); // constructor initializes heap with data from FileProcessing.data
        vector<CrimeData> getCrimes(); // returns vector of all crimes, sorted in order
        vector<pair<CrimeData, double>> getCrimesInRadius(); // takes in coordinates for user's current location
        void printCrimesInRadius();
        double calcDist(CrimeData crime) const; // return distance between a crime and current lat/long
};



#endif //CRIMEHEAP_H
