#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

// Видове транзакции, които се записват в историята.
// Държим ги като string-ове за по-ясно отпечатване.
//   "DEPOSIT"      — депозит
//   "WITHDRAW"     — теглене
//   "TRANSFER_IN"  — входящ вътрешен превод
//   "TRANSFER_OUT" — изходящ вътрешен превод
//   "EXTERNAL_OUT" — изходящ външен превод

class Transaction {
private:
    string iban;
    string type;
    double amount;
    string description;
    string timestamp;

public:
    Transaction(string iban,
                string type,
                double amount,
                string description,
                string timestamp);

    string getIban() const;
    string getType() const;
    double getAmount() const;
    string getDescription() const;
    string getTimestamp() const;

    void print() const;
};

#endif
