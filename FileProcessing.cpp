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

vector<CrimeData> FileProcessing::data;

FileProcessing::FileProcessing() = default;

void FileProcessing::ReadFile() {
    // Open CSV file
    ifstream stream("crime_stats_2024.csv", ios_base::in);
    string line;

    // Fail checks
    if (!stream) {
        cerr << "Error opening file: crime_stats_2024.csv" << endl;
        return;
    }

    // Skip header
    getline(stream, line);

    // Read file line by line - 10 lines for debugging
    while (getline(stream, line)) {
        CrimeData crime;
        std::stringstream lineStream(line);

        // Extract the date, time, area, latitude/longitude, and general category

        getline(lineStream, crime.date,',');
        getline(lineStream, crime.time,',');

        getline(lineStream, crime.areaName,',');
        getline(lineStream, crime.category,',');

        string latitude, longitude;
        getline(lineStream, latitude,',');
        getline(lineStream, longitude,',');

        crime.latitude = stod(latitude);
        crime.longitude = stod(longitude);

        getline(lineStream, crime.generalCategory, ',');

        // Store data
        data.push_back(crime);
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

vector<CrimeData> FileProcessing::getData() {
    return data;
}
