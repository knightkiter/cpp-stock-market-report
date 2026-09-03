#ifndef STOCKTYPE_H
#define STOCKTYPE_H

#include <iostream>
#include <string>

// Part (a): a single holding. Relational operators compare by symbol so the
// natural order of a stock list is alphabetical. >> reads one file row;
// << prints one report row.
class stockType {
public:
    stockType();
    stockType(const std::string& symbol, double open, double close, double high,
              double low, double prevClose, int shares);

    void setStockInfo(const std::string& symbol, double open, double close,
                      double high, double low, double prevClose, int shares);
    void print() const;
    void showPrices() const;
    void calculateGain();
    void printGain() const;
    void showShares() const;

    std::string getSymbol() const;
    double getOpenPrice() const;
    double getClosePrice() const;
    double getHighPrice() const;
    double getLowPrice() const;
    double getPrevPrice() const;
    double getPercentGain() const;
    int getShares() const;
    double closingValue() const;

    bool operator==(const stockType& other) const;
    bool operator!=(const stockType& other) const;
    bool operator<(const stockType& other) const;
    bool operator<=(const stockType& other) const;
    bool operator>(const stockType& other) const;
    bool operator>=(const stockType& other) const;

    friend std::ostream& operator<<(std::ostream& os, const stockType& stock);
    friend std::istream& operator>>(std::istream& is, stockType& stock);

private:
    std::string symbol;
    double openingPrice;
    double closingPrice;
    double highPrice;
    double lowPrice;
    double prevClose;
    int shares;
    double percentGain;
};

#endif