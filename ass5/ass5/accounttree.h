//
// Created by Kelly Pratama on 3/3/20.
//
#pragma once

#include "account.h"
#include <iostream>

class AccountTree {
public:
    // Create BST
    AccountTree();

    // Delete all nodes in BST
    ~AccountTree();

    // Insert new account
    bool insert(Account* account);

    // Retrieve account
    // returns true if successful AND *Account points to account
    bool retrieve(const int& accountNumber, Account*& account) const;

    // Display information on all accounts
    void display() const;

    // delete all information in AccountTree
    void clear();

    // check if tree is empty
    bool isEmpty() const;

private:
    // represents nodes in the accountTree
    class Node {
    public:
        // explicit Node constructor, prevents implicit conversion
        explicit Node(Account* account) :
            account{ account },
            right{ nullptr },
            left{ nullptr } { }

        // pointer to account
        Account* account;

        // pointer to right node
        Node* right;

        // pointer to left node
        Node* left;
    };

    // pointer to root node of accountTree
    Node* root;

    // helper method that recursively inserts an account into the current node
    void insertHelper(Node*& node, Account* thisAcc);

    // helper recursive function of clear function
    void clearHelper(Node* node);

    void displayHelper(Node* node) const;

    void travel(Node* temp) const;
};
