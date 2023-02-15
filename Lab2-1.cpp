
//============================================================================
// Author      : Jim Clark
// Course      : CS-260
// Date        : 1/7/2023
// Project     : Lab 2-1 Up To Speed in C++
// Version     : 1.1
// Copyright   : Copyright © 2017 SNHU COCE
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

// Add the CSVParser Header/CSV Parser
#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

struct Bid {
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.title << " | " << bid.amount << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Title: ";
    cin.ignore();
    getline(cin, bid.title);

    cout << "Enter Fund: ";
    cin >> bid.fund;

    cout << "Enter Amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
 // Create the vector called "Bid"
vector<Bid> loadBids(string csvPath) {

    vector<Bid> bids;

    // initialize the CSV Parser, including the source file path.
    csv::Parser file = csv::Parser(csvPath);

    // Read the CSV Rows
    for (unsigned int i = 0; i < file.rowCount(); i++) {
        // Create the Vector values for Rows & Columns, return row count, and bid data
        Bid bid;
        bid.title = file[i][0];
        bid.fund = file[i][8];
        bid.amount = strToDouble(file[i][4], '$');
        bids.push_back(bid);
    }
    cout << bids.size() << " Bids Read " << endl;
    return bids;
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
    }

    // Create the vector to store all the bids
    vector<Bid> theBids;

    // Create a Time Variable
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Not currently implemented." << endl;

            break;
        case 2:
            // Initialize timer variable
            ticks = clock();
            // Method to call the bids
            theBids = loadBids(csvPath);
            // Determine elapsed time, and output result
            ticks = clock() - ticks;
            cout << "Time: " << ticks << " Milliseconds" << endl;
            cout << "Time: " << ticks * 1.0 / CLOCKS_PER_SEC << " Seconds" << endl;

            break;
        case 3:
            // Loop and Display The Bids
            for (unsigned int i = 0; i < theBids.size(); ++i) {
                displayBid(theBids[i]);
            }
            cout << endl;

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}