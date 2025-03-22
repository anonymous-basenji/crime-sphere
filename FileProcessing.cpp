#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "FileProcessing.h"

#include "Helpers.h"

using namespace std;

/* ========= Init vectors ========= */
vector<double> FileProcessing::crimeLongitudes;
vector<double> FileProcessing::crimeLatitudes;
vector<int> FileProcessing::crimeRadii;
vector<string> FileProcessing::crimeTypes;
vector<string> FileProcessing::crimeDates;
vector<string> FileProcessing::crimeAreaNames;

FileProcessing::FileProcessing() = default;

void FileProcessing::ReadFile() {
    // Open CSV file
    ifstream stream("Crime_Data_from_2020_to_Present.csv", ios_base::in);
    string line;

    // Fail checks
    if (!stream) {
        cerr << "Error opening file: Crime_Data_from_2020_to_Present.csv" << endl;
        return;
    }

    // Skip header
    getline(stream, line);
    // cout << "Header: " << line << endl; // debug
    int count = 0;

    // Read file line by line - 10 lines for debugging
    // while (getline(stream, line)) {
    while (count < 10 && getline(stream, line)) {
        cout << line << endl; // debug
        CrimeData crime;

        // Extract report ID, date reported, time of occurrence without using them
        string reportID, dateReported, timeOCC, area;

        getline(stream, reportID,',');
        getline(stream, dateReported,',');

        // Extract Date
        getline(stream, crime.date,',');

        getline(stream, timeOCC,',');
        getline(stream, area,',');

        // Extract Area Name
        getline(stream, crime.areaName,',');

        // Store data
        crimeDates.push_back(crime.date);
        crimeDates.push_back(crime.areaName);

        count++;
    }
}

void FileProcessing::addSearchParameters(const double latitude, const double longitude, const int radius) {
    crimeLatitudes.push_back(latitude);
    crimeLongitudes.push_back(longitude);
    crimeRadii.push_back(radius);
}

void FileProcessing::addCrimeTypeParameters(const string& type, const int radius) {
    crimeTypes.push_back(type);
    crimeRadii.push_back(radius);
}

/* ========= Getters ========= */
vector<double> FileProcessing::getCrimeLongitude() {
    return crimeLongitudes;
}

vector<double> FileProcessing::getCrimeLatitude() {
    return crimeLatitudes;
}

vector<int> FileProcessing::getCrimeRadii() {
    return crimeRadii;
}

vector<string> FileProcessing::getCrimeDate() {
    return crimeDates;
}

vector<string> FileProcessing::getCrimeAreaName() {
    return crimeAreaNames;
}

vector<string> FileProcessing::getCrimeType() {
    return crimeTypes;
}

