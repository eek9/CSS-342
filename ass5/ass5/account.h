//
// Created by Kelly Pratama on 3/3/20.
//

#pragma once
#include <string>
#include <vector>
#include <ostream>

using namespace std;

// max array size for sub-accounts
static const int MAX_FUND = 10;

class Account {

public:
    // explicit keyword prevents compiler from making implicit conversions
    explicit Account(string name, int accID);

    // destructor
    ~Account();

    string getName();

    // returns the unique ID of an account
    int getAccID();

    bool deposit(int amt, int fund);

    bool withdraw(int amt, int fund);

    void saveHistory(string transaction, int fund, int amt, bool success,
        string other);

    bool fundTransfer(int amt, int fund, string fund2);

    string displayFundHistory(int fund);

    string displayAllHistory();

    string finalBalance();

private:
    // stores name of account owner
    string name;

    // stores account's unique ID number
    int accID;


    // string array of sub-accounts
    const string subAccs[MAX_FUND]{
            "Money Market", // idx 0
            "Prime Money Market", // idx 1
            "Long-Term Bond",
            "Short-Term Bond",
            "500 Index Fund",
            "Capital Value Fund",
            "Growth Equity Fund",
            "Growth Index Fund",
            "Value Fund",
            "Value Stock Index"
    };
    // using vector because can grow, unlike arrays
    vector<int> accBalances;

    // saves transaction history for a fund
    vector<vector<string>> History;
};
