//
// Created by Kelly Pratama on 3/3/20.
//

#include "bank.h"

#include <fstream>
#include <sstream> // stringstream
#include <string>

using namespace std;


Bank::Bank() : currAcc{ nullptr } {
}


Bank::~Bank() {
    delete currAcc;
};

void Bank::processTransactions(const string & fileName) {
    storeTransactions(fileName);
    processQueue(fileName);
    displayAllBankBalances();
}

//Display Error occurred while transaction and all account balance
void Bank::displayAllBankBalances() const {
    //print out the error messages that occured in the process
    for (const auto& i : error)
        cout << i << endl;
    cout << "\nProcessing Done. Final Balances." << endl;
    //calling the display function from the account to print out all
    //the final balances of each subaccount
    accounts.display();
}

void Bank::processQueue(string fileName) {
    ofstream out;
    out.open("bankTransOut.txt");

    char cmd;
    int fund;
    Transaction transaction;
    while (!queTrans.empty()) {
        transaction = queTrans.front();
        cmd = transaction.cmd;
        if (cmd != 'O') {
            // returns fund number attached to accID
            fund = transaction.thisSubAcc % 10;
        }

        switch (cmd) {
        case 'O':
            if (!accounts.retrieve(transaction.thisSubAcc, currAcc)) {
                currAcc = new Account(transaction.name,
                    transaction.thisSubAcc);
                accounts.insert(currAcc);
            }
            else {
                error.push_back("ERROR: Account " + to_string(transaction
                    .thisSubAcc) +
                    " is already open. Transaction refused.");
            }
            break;

        case 'T':
            // transfer from an account's fund into another account
            if (currAcc->fundTransfer(transaction.amt, fund, to_string(transaction.otherSubAcc))) {
                // check that fund type is different
                if (transaction.thisSubAcc / 10 != transaction.otherSubAcc / 10) {
                    // check to see if account exists/can be retrieved
                    if (!accounts.retrieve(transaction.otherSubAcc, currAcc)) {
                        error.push_back("ERROR: Could not find Account "
                            + to_string(transaction.otherSubAcc)
                            + " Transfer cancelled.");
                        accounts.retrieve(transaction.thisSubAcc, currAcc);
                    }

                }
            }
            break;

        case 'D':
            currAcc->deposit(transaction.amt, fund);
            break;

        case 'W':
            currAcc->withdraw(transaction.amt, fund);
            break;

        case 'H':
            if (queTrans.front().thisSubAcc / 1000 < 10) { //4 digit
                cout << currAcc->displayAllHistory();
            }
            else { //5 digit
                cout << currAcc->displayFundHistory(fund);
            }
            break;

        default:
            cout << "No command specified" << endl;

        }
        // while queue is not empty, pop
        queTrans.pop();
    }
} // end method process queue

Bank::Transaction Bank::transactionLine(string line) {
    stringstream sin;
    Transaction transaction;
    sin.str(line);
    //assigning the command of the line into a variable cmd
    sin >> transaction.cmd;
    //if the command is to open, it will assign the first and last
    //name of the string into a variable and add it into a full name
    //variable
    if (transaction.cmd == 'O') {
        string lName;
        string fName;
        sin >> lName;
        sin >> fName;
        transaction.name = lName + " " + fName;
        
        sin >> transaction.thisSubAcc;
    }
    //if the command is to transfer, it will remember the variables of
    //the subaccount that will transferring over to the otherSubAcc, and its
    //amount
    else if (transaction.cmd == 'T') {
        sin >> transaction.thisSubAcc;
        sin >> transaction.amt;
        sin >> transaction.otherSubAcc;

    }
    //if the commands are not either T or O, it will regularly just
    //remember the subAcc and amt for the command
    else {
        sin >> transaction.thisSubAcc;
        sin >> transaction.amt;

    }
    return transaction;
}

//open the file and push the lines into a queue
void Bank::storeTransactions(const string & fileName) {
    ifstream in;
    string str;
    //opening the file with all the transactions and if it cannot
    //opening, it will return a statement saying so
    in.open(fileName);
    if (!in.is_open()) {
        cout << "File cannot be opened: " << fileName << endl;
        return;
    }
    // while not at the end of file and the file does open
    while (!in.eof()) {
        getline(in, str);
        // push each line into the transaction queue
        queTrans.push(transactionLine(str));
    }
    in.close();
}

