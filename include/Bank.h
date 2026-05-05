#pragma once

#include "Account.h"
#include "Customer.h"

#include <memory>
#include <string>
#include <vector>

class Bank {
private:
    std::vector<std::unique_ptr<Customer>> customers;
    std::vector<Account> accounts;
    int nextCustomerId = 1;

public:
    // ----- Customer CRUD -----
    Customer* createCustomer(const std::string& firstName,
                             const std::string& lastName,
                             const std::string& egn,
                             const std::string& email,
                             const std::string& phone);

    Customer*       findCustomer(int id);
    const Customer* findCustomer(int id) const;

    bool updateCustomer(int id,
                        const std::string& firstName,
                        const std::string& lastName,
                        const std::string& email,
                        const std::string& phone);

    bool deleteCustomer(int id);
    void listCustomers() const;

    // ----- Account CRUD -----
    Account* createAccount(const std::string& iban,
                           int ownerId,
                           double initialBalance = 0.0,
                           const std::string& currency = "EUR");

    Account*       findAccount(const std::string& iban);
    const Account* findAccount(const std::string& iban) const;

    bool updateAccountStatus(const std::string& iban, AccountStatus newStatus);

    bool deleteAccount(const std::string& iban);
    void listAccounts() const;
    void listAccountsOfCustomer(int ownerId) const;
};
