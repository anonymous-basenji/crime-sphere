#pragma once
#include <vector>
#include <string>

using namespace std;

struct CrimeData {
    double longitude;
    double latitude;
    int radius;
    string category;
    string generalCategory;
    string date;
    string time;
    string areaName;

    string getString() {
        string output;
        output += "Latitude: " + to_string(latitude) + "\n";
        output += "Longitude: " + to_string(longitude) + "\n";
        output += "Category: " + generalCategory + "\n";
        output += "Area: " + areaName + "\n";
        output += "Date: " + date + "\n";
        output += "Time: " + time + "\n";
        return output;
    }
};

class FileProcessing {
    static vector<double> crimeLongitudes;
    static vector<double> crimeLatitudes;
    static vector<int> crimeRadii;
    static vector<string> crimeAlgorithm;

    static vector<CrimeData> data;
public:
    FileProcessing();

    static void ReadFile();
    static void addSearchParameters(const double latitude, const double longitude, const int radius, const string& algorithm);

    /* ========= Getters ========= */
    static vector<string> getCrimeAlgorithm();
    static vector<CrimeData> &getData();
};