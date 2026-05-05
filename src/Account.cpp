#include "Account.h"

#include <iostream>
#include <utility>

std::string toString(AccountStatus s) {
    switch (s) {
        case AccountStatus::ACTIVE:  return "ACTIVE";
        case AccountStatus::BLOCKED: return "BLOCKED";
        case AccountStatus::CLOSED:  return "CLOSED";
    }
    return "UNKNOWN";
}

Account::Account(std::string iban,
                 int ownerId,
                 double balance,
                 std::string currency,
                 AccountStatus status)
    : iban(std::move(iban)),
      ownerId(ownerId),
      balance(balance),
      currency(std::move(currency)),
      status(status) {}

const std::string& Account::getIban() const     { return iban; }
int                Account::getOwnerId() const  { return ownerId; }
double             Account::getBalance() const  { return balance; }
const std::string& Account::getCurrency() const { return currency; }
AccountStatus      Account::getStatus() const   { return status; }

void Account::setBalance(double v)         { balance = v; }
void Account::setStatus(AccountStatus s)   { status = s; }

void Account::print() const {
    std::cout << "IBAN: " << iban
              << " | owner #" << ownerId
              << " | " << balance << " " << currency
              << " | " << toString(status) << "\n";
}
