#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

enum AccountStatus {
    ACTIVE = 0,
    BLOCKED = 1,
    CLOSED = 2
};

string statusToString(int status);

class Account {
private:
    string iban;
    int ownerId;
    double balance;
    string currency;
    int status;

public:
    Account(string iban,
            int ownerId,
            double balance,
            string currency,
            int status);

    string getIban() const;
    int getOwnerId() const;
    double getBalance() const;
    string getCurrency() const;
    int getStatus() const;

    void setBalance(double v);
    void setStatus(int s);

    void print() const;
};

#endif
