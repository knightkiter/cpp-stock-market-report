#include "stockListType.h"

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::string filename = "data/daily-listings.txt";
    if (argc > 1) {
        filename = argv[1];
    }

    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << filename
                  << " was not found. Pass a path to the daily holdings file.\n";
        return 1;
    }

    stockListType stocks(50);
    stocks.loadData(infile);
    infile.close();

    if (stocks.isEmpty()) {
        std::cerr << "No holdings were read from " << filename << ".\n";
        return 1;
    }

    // Natural (physical) order: by stock symbol, using overloaded operator<.
    stocks.sort();
    stocks.printBySymbol(std::cout);

    std::cout << '\n';

    // Logical order only: sortIndicesGainLoss, list is not rearranged.
    stocks.sortByGainLoss();
    stocks.printByGainLoss(std::cout);

    return 0;
}