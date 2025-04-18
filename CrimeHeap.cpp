//
// Created by andrew on 4/12/25.
//

#include "CrimeHeap.h"

#include <iostream>
#include <math.h>
using namespace std;

CrimeHeap::CrimeHeap(int radParam, double latParam, double longParam) {
    vector<CrimeData> data = FileProcessing::getData();
    radius = radParam;
    latitude = latParam;
    longitude = longParam;
    for (CrimeData crime: data) {
        pair<CrimeData, double> crimePair;
        crimePair.first = crime;
        crimePair.second = calcDist(crime);
        heap.push(crimePair);
    }
}

vector<CrimeData> CrimeHeap::getCrimes() {
    vector<CrimeData> output;
    CustomPriorityQueue tempHeap;
    while (!heap.empty()) {
        pair<CrimeData, double> crimePair = heap.top();
        CrimeData crime = crimePair.first;
        output.push_back(crime);
        tempHeap.push(crimePair);
        heap.pop();
    }
    heap = tempHeap; // replace heap with popped elements
    return output;
}

vector<pair<CrimeData, double>> CrimeHeap::getCrimesInRadius() {
    vector<pair<CrimeData, double>> output;
    vector<pair<CrimeData, double>> tempVector;
    while (!heap.empty()) {
        pair<CrimeData, double> crimePair = heap.top();
        if (crimePair.second <= radius) {
            CrimeData crime = crimePair.first;
            output.push_back(crimePair);
        }
        tempVector.push_back(crimePair);
        heap.pop();
    }

    for (auto pair : tempVector) {
        heap.push(pair);
    } // bring popped elements back to the heap
    return output;
}

void CrimeHeap::printCrimesInRadius() {
    vector<pair<CrimeData, double>> crimes = getCrimesInRadius();
    cout << "Here are the crimes for your selected radius and location:" << endl;
    for (auto crime : crimes) {
        cout << crime.first.getString();
        cout << "Distance: " << crime.second << " miles" << endl;
        cout << endl;
    }
}


// Copied from Joshua Franco's Haversine function, with permission
double CrimeHeap::calcDist(CrimeData crime) const {
    const double R = 3958.8; // Average Earth radius in miles
    const double DEG_TO_RAD = M_PI / 180.0;

    double latitudeTwo = latitude * DEG_TO_RAD;
    double latitudeOne = crime.latitude * DEG_TO_RAD;
    double longitudeTwo = longitude * DEG_TO_RAD;
    double longitudeOne = crime.longitude * DEG_TO_RAD;

    double dLat = latitudeTwo - latitudeOne;
    double dLon = longitudeTwo - longitudeOne;

    double a = pow(sin(dLat / 2), 2) +
            cos(latitudeOne) * cos(latitudeTwo) * pow(sin(dLon / 2), 2);

    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    return R * c;
}

