#include "FileProcessing.h"
#include "Helpers.h"

int main() {

    FileProcessing fileProcessing;
    fileProcessing.ReadFile();

    /* ========= Print data for debugging ========= */
    Helpers helpers;
    // Helpers::PrintDate(fileProcessing);
    // helpers.PrintAreaName(fileProcessing);

    return 0;
}
