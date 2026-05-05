#include "Account.h"
#include <iostream>

namespace banking {

std::string statusToString(int status) {
    if (status == ACTIVE)  return "ACTIVE";
    if (status == BLOCKED) return "BLOCKED";
    if (status == CLOSED)  return "CLOSED";
    return "UNKNOWN";
}

Account::Account(std::string iban,
                 int ownerId,
                 double balance,
                 std::string currency,
                 int status) {
    this->iban = iban;
    this->ownerId = ownerId;
    this->balance = balance;
    this->currency = currency;
    this->status = status;
}

std::string Account::getIban() const     { return iban; }
int         Account::getOwnerId() const  { return ownerId; }
double      Account::getBalance() const  { return balance; }
std::string Account::getCurrency() const { return currency; }
int         Account::getStatus() const   { return status; }

void Account::setBalance(double v) { balance = v; }
void Account::setStatus(int s)     { status = s; }

void Account::print() const {
    std::cout << "IBAN: " << iban
              << " | owner #" << ownerId
              << " | " << balance << " " << currency
              << " | " << statusToString(status) << "\n";
}

} // namespace banking
