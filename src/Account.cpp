#include "Account.h"
#include <iostream>
using namespace std;

string statusToString(int status) {
    if (status == ACTIVE)  return "ACTIVE";
    if (status == BLOCKED) return "BLOCKED";
    if (status == CLOSED)  return "CLOSED";
    return "UNKNOWN";
}

Account::Account(string iban,
                 int ownerId,
                 double balance,
                 string currency,
                 int status) {
    this->iban = iban;
    this->ownerId = ownerId;
    this->balance = balance;
    this->currency = currency;
    this->status = status;
}

string Account::getIban() const     { return iban; }
int    Account::getOwnerId() const  { return ownerId; }
double Account::getBalance() const  { return balance; }
string Account::getCurrency() const { return currency; }
int    Account::getStatus() const   { return status; }

void Account::setBalance(double v) { balance = v; }
void Account::setStatus(int s)     { status = s; }

void Account::print() const {
    cout << "IBAN: " << iban
         << " | owner #" << ownerId
         << " | " << balance << " " << currency
         << " | " << statusToString(status) << "\n";
}
