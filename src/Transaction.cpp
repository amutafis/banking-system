#include "Transaction.h"
#include <iostream>

Transaction::Transaction(string iban,
                         string type,
                         double amount,
                         string description,
                         string timestamp) {
    this->iban = iban;
    this->type = type;
    this->amount = amount;
    this->description = description;
    this->timestamp = timestamp;
}

string Transaction::getIban() const        { return iban; }
string Transaction::getType() const        { return type; }
double Transaction::getAmount() const      { return amount; }
string Transaction::getDescription() const { return description; }
string Transaction::getTimestamp() const   { return timestamp; }

void Transaction::print() const {
    cout << "[" << timestamp << "] "
         << type << " "
         << amount << " EUR"
         << " | " << iban
         << " | " << description << "\n";
}
