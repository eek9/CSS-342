//
// Created by Kelly Pratama on 3/3/20.
//

#pragma once

#include "accounttree.h"
#include <fstream> // for reading inline
#include <string>
#include <queue>

using namespace std;

class Bank {
public:
    Bank();
    ~Bank();

    void processTransactions(const string& fileName);

    void displayAllBankBalances() const;

private:
    struct Transaction {
        string name = "";
        int thisSubAcc = 0;
        int otherSubAcc = 0;
        char cmd;
        int amt = 0;
    };

    // binary search tree of accounts
    AccountTree accounts;

    // pointer to current account
    Account* currAcc;

    // Transaction queue that stores transactions
    queue<Transaction> queTrans;

    // processes each line of transactions
    void processQueue(string fileName);

    //Store Error occurred during processing queue
    vector<string> error;

    // accepts as input a filename and stores data into a queue of Transactions
    void storeTransactions(const string& fileName);

    // convert a line from the input file into a transaction struct
    Transaction transactionLine(string line);

};
