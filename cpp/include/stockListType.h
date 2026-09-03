#ifndef STOCKLISTTYPE_H
#define STOCKLISTTYPE_H

#include "listType.h"
#include "stockType.h"

#include <iosfwd>
#include <string>

// Part (b): a list of stockType objects. Derived from the template listType
// but itself not a template. Physical order is by symbol (listType::sort).
// Percent gain/loss uses a logical index array instead of rearranging list.
class stockListType : public listType<stockType> {
public:
    explicit stockListType(int size = 100);
    stockListType(const stockListType& other);
    ~stockListType();
    const stockListType& operator=(const stockListType& other);

    void loadData(std::istream& infile);
    void sortByGainLoss();
    void printBySymbol(std::ostream& os) const;
    void printByGainLoss(std::ostream& os) const;
    double closingAssets() const;

private:
    int* sortIndicesGainLoss;

    void copyIndices(const stockListType& other);
    void printReportHeader(std::ostream& os, const std::string& subtitle) const;
    void printReportFooter(std::ostream& os) const;
};

#endif