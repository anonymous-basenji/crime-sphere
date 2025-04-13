//
// Created by andrew on 4/12/25.
//

#include "CrimeHeap.h"

#include <iostream>
#include <math.h>
using namespace std;

CrimeHeap::CrimeHeap(int radParam, int latParam, int longParam) {
    vector<CrimeData> data = FileProcessing::getData();
    for (CrimeData crime: data) {
        pair<CrimeData, float> crimePair;
        crimePair.first = crime;
        crimePair.second = calcDist(crime);
        heap.emplace(crime);
    }
    radius = radParam;
    latitude = latParam;
    longitude = longParam;
}

vector<CrimeData> CrimeHeap::getCrimes() {
    vector<CrimeData> output;
    priority_queue<CrimeData, vector<CrimeData>, PairCompare> tempHeap;
    // while (!heap.empty()) {
    //     CrimeData crime = heap.top();
    //     output.push_back(crime);
    //     tempHeap.emplace(crime);
    //     heap.pop();
    // }
    // heap = tempHeap; // replace heap with popped elements
    return output;
}

vector<CrimeData> CrimeHeap::getCrimesInRadius() const {
    return vector<CrimeData>();
}

float CrimeHeap::calcDist(CrimeData crime) const {
    return sqrt(pow(crime.latitude - latitude, 2) + pow(crime.longitude - longitude, 2));
}

