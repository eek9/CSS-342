//
// Created by Kelly Pratama on 3/3/20.
//

#include "accounttree.h"

AccountTree::AccountTree() {
    root = nullptr;
}

// Delete all nodes in BST
AccountTree::~AccountTree() {
    clear();
}

// Insert new account
bool AccountTree::insert(Account* account) {
    if (root == nullptr) {
        root = new Node(account);
    }
    insertHelper(root, account);
    return true;
}

void AccountTree::insertHelper(AccountTree::Node*& node, Account* thisAcc) {
    if (node == nullptr) {
        node = new Node(thisAcc);
        return;
    }
    // check to see if this account ID is less than other account ID
    // insert account into left node
    else if (thisAcc->getAccID() < root->account->getAccID()) {
        insertHelper(node->left, thisAcc);
    }
    else if (thisAcc->getAccID() > root->account->getAccID()) {
        insertHelper(node->right, thisAcc);
    }
}

bool AccountTree::retrieve(const int& accountNumber, Account*& account) const {
    Node* temp = root;
    while (temp != nullptr) {
        if (accountNumber == temp->account->getAccID()) {
            account = temp->account;
            return true;
        }
        else if (accountNumber < temp->account->getAccID()) {
            temp = temp->left;
        }
        else {
            temp = temp->right;
        }
    }
    account = nullptr;
    return false;
}

// Display information on all accounts
void AccountTree::display() const {
    displayHelper(root);
    //root->account->finalBalance();
}

void AccountTree::displayHelper(AccountTree::Node* node) const {
    if (node != NULL) {
        cout << node->account->getName() << " Account ID: " << node->account->getAccID() << endl;
        cout << node->account->finalBalance();
  
        displayHelper(node->left);
        displayHelper(node->right);
    }
}


// delete all information in AccountTree
void AccountTree::clear() {
    clearHelper(root);
}

// check if tree is empty
bool AccountTree::isEmpty() const {
    return root == nullptr;
}

// helper recursive function of clear function that takes in a node parameter
void AccountTree::clearHelper(Node* node) {
    if (node != nullptr) {
        clearHelper(node->left);
        clearHelper(node->right);

        delete node;
    }
}




