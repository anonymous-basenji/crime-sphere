//
// Created by andrew on 4/12/25.
//

#include "CrimeHeap.h"

#include <iostream>
#include <math.h>
using namespace std;

CrimeHeap::CrimeHeap(int radParam, float latParam, float longParam) {
    vector<CrimeData> data = FileProcessing::getData();
    for (CrimeData crime: data) {
        pair<CrimeData, float> crimePair;
        crimePair.first = crime;
        crimePair.second = calcDist(crime);
        heap.push(crimePair);
    }
    radius = radParam;
    latitude = latParam;
    longitude = longParam;
}

vector<CrimeData> CrimeHeap::getCrimes() {
    vector<CrimeData> output;
    CustomPriorityQueue tempHeap;
    while (!heap.empty()) {
        pair<CrimeData, float> crimePair = heap.top();
        CrimeData crime = crimePair.first;
        output.push_back(crime);
        tempHeap.push(crimePair);
        heap.pop();
    }
    heap = tempHeap; // replace heap with popped elements
    return output;
}

vector<CrimeData> CrimeHeap::getCrimesInRadius() {
    vector<CrimeData> output;
    vector<pair<CrimeData, float>> tempVector;
    while (!heap.empty()) {
        pair<CrimeData, float> crimePair = heap.top();
        if (crimePair.second <= radius) {
            CrimeData crime = crimePair.first;
            output.push_back(crime);
        }
        tempVector.push_back(crimePair);
        heap.pop();
    }

    for (auto pair : tempVector) {
        heap.push(pair);
    } // bring popped elements back to the heap
    return output;
}

float CrimeHeap::calcDist(CrimeData crime) const {
    return sqrt(pow(crime.latitude - latitude, 2) + pow(crime.longitude - longitude, 2));
}

