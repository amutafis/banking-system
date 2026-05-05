#ifndef BANK_H
#define BANK_H

#include "Account.h"
#include "Customer.h"

#include <string>
#include <vector>

namespace banking {

class Bank {
private:
    std::vector<Customer> customers;
    std::vector<Account> accounts;
    int nextCustomerId;

public:
    Bank();

    // ----- Customer CRUD -----
    int createCustomer(std::string firstName,
                       std::string lastName,
                       std::string egn,
                       std::string email,
                       std::string phone);

    int findCustomerIndex(int id) const;

    bool updateCustomer(int id,
                        std::string firstName,
                        std::string lastName,
                        std::string email,
                        std::string phone);

    bool deleteCustomer(int id);
    void listCustomers() const;
    void printCustomer(int id) const;

    // ----- Account CRUD -----
    bool createAccount(std::string iban,
                       int ownerId,
                       double initialBalance,
                       std::string currency);

    int findAccountIndex(std::string iban) const;

    bool updateAccountStatus(std::string iban, int newStatus);
    bool deleteAccount(std::string iban);
    void listAccounts() const;
    void printAccount(std::string iban) const;
    void listAccountsOfCustomer(int ownerId) const;
};

} // namespace banking

#endif
