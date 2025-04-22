//
// Created by andrew on 4/12/25.
//

#ifndef CRIMEHEAP_H
#define CRIMEHEAP_H

#include <iostream>
#include <queue>
#include <vector>
#include <functional>


#include "../FileProcessing.h"
using namespace std;

// Heap is stored using a vector
class CrimeHeap {
    int radius;
    double latitude;
    double longitude;
    public:
        vector<pair<CrimeData, double>> heap;
        CrimeHeap(int radParam, double latParam, double longParam); // constructor initializes heap with data from FileProcessing.data
        vector<pair<CrimeData, double>> getCrimes(); // returns vector of all crimes, sorted in order
        vector<pair<CrimeData, double>> getCrimesInRadius(); // takes in coordinates for user's current location
        void printCrimesInRadius();
        double calcDist(CrimeData crime) const; // return distance between a crime and current lat/long
        void insert(pair<CrimeData, double> crime);
        void heapifyUp(int i);
        void heapifyDown(int i);
        pair<CrimeData, double> top() const;
        pair<CrimeData, double> pop();
};



#endif //CRIMEHEAP_H
