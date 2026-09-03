#include "stockType.h"

#include <iomanip>
#include <iostream>

using std::fixed;
using std::left;
using std::right;
using std::setprecision;
using std::showpoint;
using std::setw;

stockType::stockType()
    : symbol(""),
      openingPrice(0),
      closingPrice(0),
      highPrice(0),
      lowPrice(0),
      prevClose(0),
      shares(0),
      percentGain(0) {}

stockType::stockType(const std::string& symbol, double open, double close,
                     double high, double low, double prevClose, int shares) {
    setStockInfo(symbol, open, close, high, low, prevClose, shares);
}

void stockType::setStockInfo(const std::string& newSymbol, double open,
                             double close, double high, double low,
                             double previous, int shareCount) {
    symbol = newSymbol;
    openingPrice = open;
    closingPrice = close;
    highPrice = high;
    lowPrice = low;
    prevClose = previous;
    shares = shareCount;
    calculateGain();
}

void stockType::calculateGain() {
    if (prevClose == 0) {
        percentGain = 0;
        return;
    }
    percentGain = ((closingPrice - prevClose) / prevClose) * 100.0;
}

void stockType::print() const {
    std::cout << *this << '\n';
}

void stockType::showPrices() const {
    std::cout << fixed << showpoint << setprecision(2);
    std::cout << "Open: " << openingPrice
              << "  Close: " << closingPrice
              << "  High: " << highPrice
              << "  Low: " << lowPrice
              << "  Previous close: " << prevClose << '\n';
}

void stockType::printGain() const {
    std::cout << fixed << showpoint << setprecision(2);
    std::cout << "Percent gain/loss: " << percentGain << "%\n";
}

void stockType::showShares() const {
    std::cout << "Shares held: " << shares << '\n';
}

std::string stockType::getSymbol() const { return symbol; }
double stockType::getOpenPrice() const { return openingPrice; }
double stockType::getClosePrice() const { return closingPrice; }
double stockType::getHighPrice() const { return highPrice; }
double stockType::getLowPrice() const { return lowPrice; }
double stockType::getPrevPrice() const { return prevClose; }
double stockType::getPercentGain() const { return percentGain; }
int stockType::getShares() const { return shares; }

double stockType::closingValue() const {
    return closingPrice * static_cast<double>(shares);
}

bool stockType::operator==(const stockType& other) const {
    return symbol == other.symbol;
}

bool stockType::operator!=(const stockType& other) const {
    return symbol != other.symbol;
}

bool stockType::operator<(const stockType& other) const {
    return symbol < other.symbol;
}

bool stockType::operator<=(const stockType& other) const {
    return symbol <= other.symbol;
}

bool stockType::operator>(const stockType& other) const {
    return symbol > other.symbol;
}

bool stockType::operator>=(const stockType& other) const {
    return symbol >= other.symbol;
}

std::ostream& operator<<(std::ostream& os, const stockType& stock) {
    os << left << setw(6) << stock.symbol
       << right << fixed << showpoint << setprecision(2)
       << setw(10) << stock.openingPrice
       << setw(10) << stock.closingPrice
       << setw(10) << stock.highPrice
       << setw(10) << stock.lowPrice
       << setw(10) << stock.prevClose
       << setw(8) << stock.percentGain << '%'
       << setw(12) << stock.shares;
    return os;
}

std::istream& operator>>(std::istream& is, stockType& stock) {
    is >> stock.symbol >> stock.openingPrice >> stock.closingPrice
       >> stock.highPrice >> stock.lowPrice >> stock.prevClose >> stock.shares;
    if (is) {
        stock.calculateGain();
    }
    return is;
}