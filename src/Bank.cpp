#include "Bank.h"

#include <algorithm>
#include <iostream>

// ---------- Customer CRUD ----------

Customer* Bank::createCustomer(const std::string& firstName,
                               const std::string& lastName,
                               const std::string& egn,
                               const std::string& email,
                               const std::string& phone) {
    auto c = std::make_unique<Customer>(nextCustomerId++,
                                        firstName, lastName, egn, email, phone);
    Customer* raw = c.get();
    customers.push_back(std::move(c));
    return raw;
}

Customer* Bank::findCustomer(int id) {
    for (auto& c : customers) {
        if (c->getId() == id) return c.get();
    }
    return nullptr;
}

const Customer* Bank::findCustomer(int id) const {
    for (const auto& c : customers) {
        if (c->getId() == id) return c.get();
    }
    return nullptr;
}

bool Bank::updateCustomer(int id,
                          const std::string& firstName,
                          const std::string& lastName,
                          const std::string& email,
                          const std::string& phone) {
    Customer* c = findCustomer(id);
    if (!c) return false;
    c->setFirstName(firstName);
    c->setLastName(lastName);
    c->setEmail(email);
    c->setPhone(phone);
    return true;
}

bool Bank::deleteCustomer(int id) {
    auto it = std::find_if(customers.begin(), customers.end(),
                           [id](const std::unique_ptr<Customer>& c) {
                               return c->getId() == id;
                           });
    if (it == customers.end()) return false;

    // Премахни и всички сметки на този клиент.
    accounts.erase(std::remove_if(accounts.begin(), accounts.end(),
                                  [id](const Account& a) {
                                      return a.getOwnerId() == id;
                                  }),
                   accounts.end());
    customers.erase(it);
    return true;
}

void Bank::listCustomers() const {
    if (customers.empty()) {
        std::cout << "(няма регистрирани клиенти)\n";
        return;
    }
    for (const auto& c : customers) c->print();
}

// ---------- Account CRUD ----------

Account* Bank::createAccount(const std::string& iban,
                             int ownerId,
                             double initialBalance,
                             const std::string& currency) {
    if (findCustomer(ownerId) == nullptr) return nullptr;
    if (findAccount(iban) != nullptr)     return nullptr;

    accounts.emplace_back(iban, ownerId, initialBalance, currency, AccountStatus::ACTIVE);
    return &accounts.back();
}

Account* Bank::findAccount(const std::string& iban) {
    for (auto& a : accounts) {
        if (a.getIban() == iban) return &a;
    }
    return nullptr;
}

const Account* Bank::findAccount(const std::string& iban) const {
    for (const auto& a : accounts) {
        if (a.getIban() == iban) return &a;
    }
    return nullptr;
}

bool Bank::updateAccountStatus(const std::string& iban, AccountStatus newStatus) {
    Account* a = findAccount(iban);
    if (!a) return false;
    a->setStatus(newStatus);
    return true;
}

bool Bank::deleteAccount(const std::string& iban) {
    auto it = std::find_if(accounts.begin(), accounts.end(),
                           [&iban](const Account& a) {
                               return a.getIban() == iban;
                           });
    if (it == accounts.end()) return false;
    accounts.erase(it);
    return true;
}

void Bank::listAccounts() const {
    if (accounts.empty()) {
        std::cout << "(няма сметки)\n";
        return;
    }
    for (const auto& a : accounts) a.print();
}

void Bank::listAccountsOfCustomer(int ownerId) const {
    bool any = false;
    for (const auto& a : accounts) {
        if (a.getOwnerId() == ownerId) {
            a.print();
            any = true;
        }
    }
    if (!any) std::cout << "(клиент #" << ownerId << " няма сметки)\n";
}
