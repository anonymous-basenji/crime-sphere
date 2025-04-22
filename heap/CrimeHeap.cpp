//
// Created by andrew on 4/12/25.
//

#include "CrimeHeap.h"

#include <iostream>
#include <limits>
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
        insert(crimePair);
    }
}

vector<pair<CrimeData, double>> CrimeHeap::getCrimes() {
    return heap;
}

vector<pair<CrimeData, double>> CrimeHeap::getCrimesInRadius() {
    vector<pair<CrimeData, double>> output;
    vector<pair<CrimeData, double>> tempVector;
    while (!heap.empty()) {
        pair<CrimeData, double> crimePair = top();
        if (crimePair.second <= radius) {
            CrimeData crime = crimePair.first;
            output.push_back(crimePair);
        }
        tempVector.push_back(crimePair);
        pop();
    }

    for (auto pair : tempVector) {
        insert(pair);
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

void CrimeHeap::insert(pair<CrimeData, double> crime) {
    heap.push_back(crime);
    heapifyUp(heap.size() - 1);
}

// inspired by structure in Canvas lecture slides
void CrimeHeap::heapifyUp(int index) {
    int parentIndex = (index - 1) / 2;
    while (parentIndex >= 0 && heap[parentIndex].second > heap[index].second) {
        swap(heap[parentIndex], heap[index]);
        index = parentIndex;
        parentIndex = (index - 1) / 2;
    }
}

// inspired by structure in Canvas lecture slides
void CrimeHeap::heapifyDown(int index) {
    int leftChildIndex = (index * 2) + 1;
    int rightChildIndex = (index * 2) + 2;
    int smallestChildIndex = index;

    if (leftChildIndex >= heap.size()) { // leaf case
        return;
    }
    if (heap[leftChildIndex].second < heap[index].second) {
        smallestChildIndex = leftChildIndex;
        if (rightChildIndex < heap.size() && heap[rightChildIndex].second < heap[smallestChildIndex].second) {
            smallestChildIndex = rightChildIndex;
        }
    }
    if (smallestChildIndex == index) {
        return;
    }
    swap(heap[index], heap[smallestChildIndex]);
    heapifyDown(smallestChildIndex);
}

pair<CrimeData, double> CrimeHeap::top() const {
    return heap[0];
}

vector<pair<CrimeData, double>> CrimeHeap::getVector() const {
    return heap;
}

pair<CrimeData, double> CrimeHeap::pop() {
    pair<CrimeData, double> returnVal = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    heapifyDown(0);
    return returnVal;
}

