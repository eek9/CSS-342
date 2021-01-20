//
// Created by Kelly Pratama on 3/3/20.
//

#include "account.h"
#include <iostream>

Account::Account(string name, int accID) : name{ name }, accID{ accID } {
    vector<int> accB(10, 0);
    accBalances = accB;
    vector<vector<string>> hist(36);
    History = hist;
}

Account::~Account() {

}

string Account::getName() {
    return name;
}

int Account::getAccID() {
    return accID;
}

bool Account::deposit(int amt, int fund) {
    accBalances[fund] += amt;
    saveHistory("D", fund, amt, true, "");
    return true;
}

bool Account::withdraw(int amt, int fund) {
    int total = accBalances[fund] - amt; // minimum amount of money needed
    if (total >= 0) {
        accBalances[fund] -= amt;
        saveHistory("W", fund, amt, true, "");
        return true;
    }
    // if withdrawing from Money Market and balance of Prime Money Market
    // exceeds money needed to complete withdrawal, deposit amount needed to
    // complete withdrawal into Money Market
    /*if (fund == 0 && accBalances[1] > minAmt) {

    }*/
    else {
        saveHistory("W", fund, amt, false, "");
        return false;
    }
}

void Account::saveHistory(string transaction, int fund, int amt, bool success,
    string other) {
    string history = transaction + " " + to_string(accID) + to_string
    (fund) +" " + to_string(amt);
    if (other != "") {
        history += " " + other;
    }
    if (!success) {
        history += " (Failed)";
    }
    History[fund].push_back(history);
}

bool Account::fundTransfer(int amt, int fund, string fund2) {
    int minAmt = accBalances[fund] - amt;
    if (minAmt >= 0) {
        accBalances[fund] -= amt;
        saveHistory("T", fund, amt, true, fund2);
        return true;
    }
    saveHistory("T", fund, amt, false, fund2);
    return false;
}

string Account::displayFundHistory(int fund) {
    string fundHistory = "Displaying Transaction History for " + name + "'s "
        + subAccs[fund] + ": $" + to_string
        (accBalances[fund]) + "\n";
    for (int i = 0; i < History[fund].size(); i++)
        fundHistory += "	" + History[fund][i] + "\n";

    return fundHistory;
}

string Account::displayAllHistory() {
    string allHistory = "Displaying Transaction History for " + name + " by fund.\n";
    for (int i = 0; i < MAX_FUND; i++) {
        allHistory += subAccs[i] + ": $" + to_string(accBalances[i]) + "\n";
        for (int j = 0; j < History[i].size(); j++)
            allHistory += "	" + History[i][j] + "\n";
    }
    return allHistory;
}

string Account::finalBalance() {
    /*string finalBal = name + " Account ID: " + to_string(accID) + "\n";*/
    string finalBal = "";
    for (int i = 0; i < MAX_FUND; i++) {
        finalBal += "	" + subAccs[i] + ": $" + to_string(accBalances[i]) +
            "\n";
    }
    return finalBal;
}
