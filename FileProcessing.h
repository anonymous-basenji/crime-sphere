#pragma once
#include <vector>
#include <string>

using namespace std;

struct CrimeData {
    double longitude;
    double latitude;
    string category;
    string generalCategory;
    string date;
    string time;
    string areaName;
    string algorithm;
};

class FileProcessing {
    static vector<double> crimeLongitudes;
    static vector<double> crimeLatitudes;
    static vector<int> crimeRadii;
    static vector<string> crimeTypes;
    static vector<string> crimeDates;
    static vector<string> crimeAreaNames;
    static vector<string> crimeAlgorithm;

    static vector<CrimeData> data;
public:
    FileProcessing();

    static void ReadFile();
    static void addSearchParameters(const double latitude, const double longitude, const int radius, const string& algorithm);
    static void addCrimeData(const CrimeData& crimeData);

    /* ========= Getters ========= */
    static vector<double> getCrimeLongitude();
    static vector<double> getCrimeLatitude();
    static vector<int> getCrimeRadii();
    static vector<string> getCrimeType();
    static vector<string> getCrimeDate();
    static vector<string> getCrimeAreaName();
    static vector<string> getCrimeAlgorithm();
    static vector<CrimeData> &getData();
};