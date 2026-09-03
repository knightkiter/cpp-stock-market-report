#include "stockListType.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using std::fixed;
using std::setprecision;
using std::showpoint;

namespace {
bool isBlankOrComment(const std::string& line) {
    std::string::size_type i = 0;
    while (i < line.size() && (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')) {
        i++;
    }
    return i == line.size() || line[i] == '#';
}
}  // namespace

stockListType::stockListType(int size) : listType<stockType>(size) {
    sortIndicesGainLoss = new int[maxSize];
    for (int i = 0; i < maxSize; i++) {
        sortIndicesGainLoss[i] = i;
    }
}

stockListType::stockListType(const stockListType& other)
    : listType<stockType>(other), sortIndicesGainLoss(nullptr) {
    copyIndices(other);
}

stockListType::~stockListType() {
    delete[] sortIndicesGainLoss;
}

const stockListType& stockListType::operator=(const stockListType& other) {
    if (this != &other) {
        listType<stockType>::operator=(other);
        copyIndices(other);
    }
    return *this;
}

void stockListType::copyIndices(const stockListType& other) {
    delete[] sortIndicesGainLoss;
    sortIndicesGainLoss = new int[maxSize];
    for (int i = 0; i < maxSize; i++) {
        sortIndicesGainLoss[i] = other.sortIndicesGainLoss[i];
    }
}

void stockListType::loadData(std::istream& infile) {
    std::string line;
    while (std::getline(infile, line)) {
        if (isBlankOrComment(line)) {
            continue;
        }
        std::istringstream row(line);
        stockType stock;
        // infile >> myStock — each row is extracted into a stock object.
        if (row >> stock) {
            std::cout << "Loaded stock: " << stock.getSymbol() << '\n';
            insertEnd(stock);
        } else {
            std::cerr << "Skipping invalid row: " << line << '\n';
        }
    }
}

void stockListType::sortByGainLoss() {
    for (int i = 0; i < length; i++) {
        sortIndicesGainLoss[i] = i;
    }

    // Selection sort of the index array only — list itself is not moved.
    for (int i = 0; i < length - 1; i++) {
        int best = i;
        for (int j = i + 1; j < length; j++) {
            double gainJ = list[sortIndicesGainLoss[j]].getPercentGain();
            double gainBest = list[sortIndicesGainLoss[best]].getPercentGain();
            if (gainJ > gainBest) {
                best = j;
            } else if (gainJ == gainBest) {
                if (list[sortIndicesGainLoss[j]] < list[sortIndicesGainLoss[best]]) {
                    best = j;
                }
            }
        }
        int temp = sortIndicesGainLoss[i];
        sortIndicesGainLoss[i] = sortIndicesGainLoss[best];
        sortIndicesGainLoss[best] = temp;
    }
}

double stockListType::closingAssets() const {
    double total = 0;
    for (int i = 0; i < length; i++) {
        total += list[i].closingValue();
    }
    return total;
}

void stockListType::printReportHeader(std::ostream& os,
                                      const std::string& subtitle) const {
    os << "*********  First Investor's Heaven  **********\n";
    os << "*********    " << subtitle << "    **********\n";
    os << "Stock          Today                         Previous Percent\n";
    os << "Symbol     Open     Close     High      Low     Close    Gain      Volume\n";
    os << "------  -------  --------  -------  -------  -------- -------    --------\n";
}

void stockListType::printReportFooter(std::ostream& os) const {
    os << "Closing Assets: $" << fixed << showpoint << setprecision(2)
       << closingAssets() << '\n';
    os << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
}

void stockListType::printBySymbol(std::ostream& os) const {
    printReportHeader(os, "Financial Report");
    for (int i = 0; i < length; i++) {
        os << list[i] << '\n';
    }
    printReportFooter(os);
}

void stockListType::printByGainLoss(std::ostream& os) const {
    printReportHeader(os, "Gain/Loss Report");
    for (int i = 0; i < length; i++) {
        os << list[sortIndicesGainLoss[i]] << '\n';
    }
    printReportFooter(os);
}