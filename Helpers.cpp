#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "FileProcessing.h"
#include "Helpers.h"

Helpers::Helpers() = default;

/* ========= Print data ========= */
void Helpers::PrintDate(FileProcessing& fileProcessing) {
    const vector<string> dates = fileProcessing.getCrimeDate();

    // Print each date
    for (const string& date : dates) {
        cout << date << endl;
    }
}

void Helpers::PrintAreaName(FileProcessing& fileProcessing) {
    const vector<string> areas = fileProcessing.getCrimeAreaName();

    // Print each area
    for (const string& area : areas) {
        cout << area << endl;
    }
}
