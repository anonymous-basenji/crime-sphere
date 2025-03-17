#pragma once
#include <vector>

using namespace std;

struct CrimeData {
    string date;
    string areaName;
    string type;
    double longitude;
    double latitude;
};

class FileProcessing {
    static vector<string> crimeDates;
    static vector<string> crimeAreaNames;
    static vector<string> crimeTypes;
    static vector<double> crimeLongitudes;
    static vector<double> crimeLatitudes;
public:
    FileProcessing();

    static void ReadFile();

    /* ========= Getters ========= */
    static vector<string> getCrimeDate();
    static vector<string> getCrimeAreaName();
    static vector<string> getCrimeType();
    static vector<double> getCrimeLongitude();
    static vector<double> getCrimeLatitude();
};