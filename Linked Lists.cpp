//============================================================================
// Author      : Jim Clark
// Course      : CS-260
// Date        : 1/15/2023
// Project     : Lab 3-2 Linked Lists & Searching
// Version     : 1.1
// Copyright   : Copyright © 2017 SNHU COCE
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // Primary Key/Index
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:
    // Task 1: Define Struct & housekeeping variables

    struct Node {
        Bid bid;
        Node* next;

        // default constructor
        Node() {
            next = nullptr;
        }
        // initialize with a bid
        Node(Bid aBid) {
            bid = aBid;
            next = nullptr;
        }
    };
    Node* head;
    Node* tail;
    int size = 0;

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
};

/**
 * Default constructor
 */
LinkedList::LinkedList() {
    // Task 2: Initialize housekeeping variables head & tail

    head = nullptr;
    tail = nullptr;
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
}

//============================================================================
// LinkedList methods
//============================================================================

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    // Task 3: Define append functionality

    Node* node = new Node(bid);

    // Check For/Address empty list
    if ((head == nullptr)) {
        head = node;
    }

    // Else, set the next pointer of the tail to be the new node
    else {
        if (tail != nullptr) {
            tail->next = node;
        }
    }

    // Increment the list and set new entry a tail
    tail = node;
    size++;
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    // Task 4 Define prepend functionality

    Node* node = new Node(bid);

    if (head != nullptr) {
        node->next = head;
    }

    // Update node list
    head = node;
    size++;
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    // Task 5 Implement print functionality
    
    // Set current node to the top of the list
    Node* current = head;

    // Iterate through the list, & print each item
    while (current != nullptr) {
        cout << current->bid.bidId << ": " << current->bid.title << " | " << current->bid.amount << " | " << current->bid.fund << endl;
        current = current->next;
    }
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // Task 6 Implement remove functionality
    
    // Compare the bidId to the head; If a match is found, create temp node.
    if (head != nullptr) {
        if (head->bid.bidId.compare(bidId) == 0) {
            Node* tempNode = head->next;

            // Update head node with the next node 
            delete head;
            head = tempNode;
        }
    }

    Node* current = head;

    // Iterate through each list and delete the bidId being searched. Update list pointers/size.
    while (current->next != nullptr) {
        if (current->next->bid.bidId.compare(bidId) == 0) {
            Node* tempNode = current->next;
            current->next = tempNode->next;
            delete tempNode;

            size--;
            return;
        }
        current = current->next;
    }
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    // Task 7 Implement search functionality

    Node* current = head;

    // Iterate to locate our bidId to each bidId in the list
    while (current != nullptr) {
        if (current->bid.bidId.compare(bidId) == 0) {
            return current->bid;
        }
        current = current->next;
    }
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}

//============================================================================
// Bid methods
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
        << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

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
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList* list) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

            // add this bid to the end
            list->Append(bid);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    clock_t ticks;

    LinkedList bidList;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter A Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);

            break;

        case 2:
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 3:
            bidList.PrintList();

            break;

        case 4:
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            }
            else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 5:
            bidList.Remove(bidKey);

            break;

        case 6:
            bid = getBid();
            bidList.Prepend(bid);
            displayBid(bid);

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}