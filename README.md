# C++ Stock Market Report

A C++ console program that reads daily stock information from a text file and produces two financial reports:

1. Stocks sorted alphabetically by symbol
2. Stocks sorted from highest to lowest percentage gain or loss

## C++ concepts demonstrated

- Class templates
- Inheritance
- Operator overloading
- Dynamic arrays
- File input
- Sorting objects
- Logical sorting with an index array
- Header and implementation files

## Project structure

- `cpp/include` — class header files
- `cpp/src` — C++ implementation files
- `data/daily-listings.txt` — sample stock information

## Compile

From the project’s root folder in VS Code:

```powershell
g++ -std=c++17 -I cpp/include cpp/src/main.cpp cpp/src/stockType.cpp cpp/src/stockListType.cpp -o cpp/stock-report.exe