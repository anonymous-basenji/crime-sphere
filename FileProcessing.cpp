#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "FileProcessing.h"

#include "Helpers.h"

using namespace std;

/* ========= Init vectors ========= */
vector<string> FileProcessing::crimeDates;
vector<string> FileProcessing::crimeAreaNames;
vector<string> FileProcessing::crimeTypes;
vector<double> FileProcessing::crimeLongitudes;
vector<double> FileProcessing::crimeLatitudes;

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

/* ========= Getters ========= */
vector<string> FileProcessing::getCrimeDate() {
    return crimeDates;
}

vector<string> FileProcessing::getCrimeAreaName() {
    return crimeAreaNames;
}

vector<string> FileProcessing::getCrimeType() {
    return crimeTypes;
}

vector<double> FileProcessing::getCrimeLongitude() {
    return crimeLongitudes;
}

vector<double> FileProcessing::getCrimeLatitude() {
    return crimeLatitudes;
}