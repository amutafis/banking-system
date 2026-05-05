#ifndef BANK_H
#define BANK_H

#include "Account.h"
#include "Customer.h"

#include <string>
#include <vector>
using namespace std;

class Bank {
private:
    vector<Customer> customers;
    vector<Account> accounts;
    int nextCustomerId;

public:
    Bank();

    // ----- Customer CRUD -----
    int createCustomer(string firstName,
                       string lastName,
                       string egn,
                       string email,
                       string phone);

    int findCustomerIndex(int id) const;

    bool updateCustomer(int id,
                        string firstName,
                        string lastName,
                        string email,
                        string phone);

    bool deleteCustomer(int id);
    void listCustomers() const;
    void printCustomer(int id) const;

    // ----- Account CRUD -----
    bool createAccount(string iban,
                       int ownerId,
                       double initialBalance,
                       string currency);

    int findAccountIndex(string iban) const;

    bool updateAccountStatus(string iban, int newStatus);
    bool deleteAccount(string iban);
    void listAccounts() const;
    void printAccount(string iban) const;
    void listAccountsOfCustomer(int ownerId) const;
};

#endif
