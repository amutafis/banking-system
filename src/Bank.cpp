#include "Bank.h"
#include <iostream>
using namespace std;

Bank::Bank() {
    nextCustomerId = 1;
}

// ---------- Customer CRUD ----------

int Bank::createCustomer(string firstName,
                         string lastName,
                         string egn,
                         string email,
                         string phone) {
    int newId = nextCustomerId;
    nextCustomerId = nextCustomerId + 1;

    Customer c(newId, firstName, lastName, egn, email, phone);
    customers.push_back(c);
    return newId;
}

int Bank::findCustomerIndex(int id) const {
    for (int i = 0; i < (int)customers.size(); i++) {
        if (customers[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

bool Bank::updateCustomer(int id,
                          string firstName,
                          string lastName,
                          string email,
                          string phone) {
    int idx = findCustomerIndex(id);
    if (idx == -1) return false;

    customers[idx].setFirstName(firstName);
    customers[idx].setLastName(lastName);
    customers[idx].setEmail(email);
    customers[idx].setPhone(phone);
    return true;
}

bool Bank::deleteCustomer(int id) {
    int idx = findCustomerIndex(id);
    if (idx == -1) return false;

    // Първо премахваме всички сметки на този клиент.
    for (int i = 0; i < (int)accounts.size(); ) {
        if (accounts[i].getOwnerId() == id) {
            accounts.erase(accounts.begin() + i);
        } else {
            i++;
        }
    }

    customers.erase(customers.begin() + idx);
    return true;
}

void Bank::listCustomers() const {
    if (customers.size() == 0) {
        cout << "(няма регистрирани клиенти)\n";
        return;
    }
    for (int i = 0; i < (int)customers.size(); i++) {
        // Полиморфно викане: print() от Person ползва role() от Customer.
        customers[i].print();
    }
}

void Bank::printCustomer(int id) const {
    int idx = findCustomerIndex(id);
    if (idx == -1) {
        cout << "Не е намерен клиент с ID #" << id << "\n";
        return;
    }
    customers[idx].print();
}

// ---------- Account CRUD ----------

bool Bank::createAccount(string iban,
                         int ownerId,
                         double initialBalance,
                         string currency) {
    if (findCustomerIndex(ownerId) == -1) return false;
    if (findAccountIndex(iban) != -1)     return false;

    Account a(iban, ownerId, initialBalance, currency, ACTIVE);
    accounts.push_back(a);
    return true;
}

int Bank::findAccountIndex(string iban) const {
    for (int i = 0; i < (int)accounts.size(); i++) {
        if (accounts[i].getIban() == iban) {
            return i;
        }
    }
    return -1;
}

bool Bank::updateAccountStatus(string iban, int newStatus) {
    int idx = findAccountIndex(iban);
    if (idx == -1) return false;
    accounts[idx].setStatus(newStatus);
    return true;
}

bool Bank::deleteAccount(string iban) {
    int idx = findAccountIndex(iban);
    if (idx == -1) return false;
    accounts.erase(accounts.begin() + idx);
    return true;
}

void Bank::listAccounts() const {
    if (accounts.size() == 0) {
        cout << "(няма сметки)\n";
        return;
    }
    for (int i = 0; i < (int)accounts.size(); i++) {
        accounts[i].print();
    }
}

void Bank::printAccount(string iban) const {
    int idx = findAccountIndex(iban);
    if (idx == -1) {
        cout << "Не е намерена сметка с IBAN " << iban << "\n";
        return;
    }
    accounts[idx].print();
}

void Bank::listAccountsOfCustomer(int ownerId) const {
    bool any = false;
    for (int i = 0; i < (int)accounts.size(); i++) {
        if (accounts[i].getOwnerId() == ownerId) {
            accounts[i].print();
            any = true;
        }
    }
    if (!any) {
        cout << "(клиент #" << ownerId << " няма сметки)\n";
    }
}
