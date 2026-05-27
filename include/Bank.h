#ifndef BANK_H
#define BANK_H

#include "Account.h"
#include "Admin.h"
#include "Card.h"
#include "Customer.h"
#include "Transaction.h"

#include <string>
#include <vector>
using namespace std;

class Bank {
private:
    vector<Customer> customers;
    vector<Admin> admins;
    vector<Account> accounts;
    vector<Transaction> transactions;
    vector<Card> cards;
    int nextCustomerId;
    int nextAdminId;
    int nextCardSerial;  // за уникален номер на карта

    // Помощни — записва транзакция с текущ timestamp.
    void logTransaction(string iban, string type, double amount, string description);

    // Генерира 16-цифрен номер на карта (детерминистично за демо).
    string generateCardNumber();

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

    // ----- Admin -----
    int createAdmin(string firstName,
                    string lastName,
                    string egn,
                    string email,
                    string phone);
    int findAdminIndex(int id) const;
    void listAdmins() const;

    // ----- Помощни -----
    // Връща ownerId на сметка по IBAN, или -1 ако сметката не съществува.
    int getAccountOwnerId(string iban) const;

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

    // ----- Преводи -----
    // Вътрешен превод между две сметки в системата.
    bool transferInternal(string fromIban, string toIban, double amount);
    // Външен превод към IBAN извън системата.
    bool transferExternal(string fromIban, string toIban, double amount);

    // ----- История на транзакции -----
    void listAllTransactions() const;
    void listTransactionsOfAccount(string iban) const;
    void listTransactionsOfAccountByType(string iban, string type) const;

    // ----- Извлечение (statement) -----
    // Печата извлечение за дадена сметка: начален баланс, всички движения, краен баланс.
    bool printStatement(string iban) const;

    // ----- Карти -----
    string issueCard(string iban, string type);  // връща новия номер или "" при грешка
    bool blockCard(string cardNumber);
    bool unblockCard(string cardNumber);
    void listCards() const;
    void listCardsOfAccount(string iban) const;
    int  findCardIndex(string cardNumber) const;
};

#endif
