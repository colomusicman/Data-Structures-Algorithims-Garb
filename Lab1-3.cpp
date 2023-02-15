//============================================================================
// Author      : Jim Clark
// Course      : CS-260
// Date        : 1/1/2023
// Project     : Lab 1-3 Up to Speed in C++
// Version     : 1.1
// Copyright   : Copyright © 2017 SNHU COCE
//============================================================================

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

double strToDouble(string str, char ch);

// Define A Struct with appropriate Values, & init AuctionBidAmount 
struct AuctionBid {
    string AuctionItem;
    string AuctionFund;
    string AuctionVehicleId;
    double AuctionBidAmount = 0.00;
};

// Populate Correct Variable/Struct Definitions
/**
 * Display the bid information
 *
 * @param ?type? data structure containing the bid info
 */
void displayBid(AuctionBid bid) {
    cout << "Title: " << bid.AuctionItem << endl;
    cout << "Fund: " << bid.AuctionFund << endl;
    cout << "Vehicle: " << bid.AuctionVehicleId << endl;
    cout << "Bid Amount: " << bid.AuctionBidAmount << endl;

    return;
}

// Capture user input to store data in the Struct
/**
 * Prompt user for bid information
 *
 * @return data structure containing the bid info
 */
AuctionBid getBid() {
    AuctionBid ABid;

    cout << "Enter Title: ";
    cin.ignore();
    getline(cin, ABid.AuctionItem);

    cout << "Enter Fund: ";
    cin >> ABid.AuctionFund;

    cout << "Enter Vehicle: ";
    cin.ignore();
    getline(cin, ABid.AuctionVehicleId);

    cout << "Enter Amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    ABid.AuctionBidAmount = strToDouble(strAmount, '$');

    return ABid;
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
int main() {

    // Define an instance of Struct to hold bid information
    AuctionBid TheBid;

    // loop to display menu until exit chosen
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter Bid" << endl;
        cout << "  2. Display Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        // Define The Method Calls to Reference in response to input
        switch (choice) {
        case 1:
            TheBid = getBid();
            break;
        case 2:
            displayBid(TheBid);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
