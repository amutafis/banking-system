#ifndef BANK_H
#define BANK_H

#include "Account.h"
#include "Customer.h"
#include "Transaction.h"

#include <string>
#include <vector>
using namespace std;

class Bank {
private:
    vector<Customer> customers;
    vector<Account> accounts;
    vector<Transaction> transactions;
    int nextCustomerId;

    // Помощни — записва транзакция с текущ timestamp.
    void logTransaction(string iban, string type, double amount, string description);

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

    // ----- Операции по сметка -----
    bool deposit(string iban, double amount);
    bool withdraw(string iban, double amount);

    // ----- История на транзакции -----
    void listAllTransactions() const;
    void listTransactionsOfAccount(string iban) const;
    void listTransactionsOfAccountByType(string iban, string type) const;
};

#endif
