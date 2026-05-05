#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

namespace banking {

enum AccountStatus {
    ACTIVE = 0,
    BLOCKED = 1,
    CLOSED = 2
};

std::string statusToString(int status);

class Account {
private:
    std::string iban;
    int ownerId;
    double balance;
    std::string currency;
    int status;

public:
    Account(std::string iban,
            int ownerId,
            double balance,
            std::string currency,
            int status);

    std::string getIban() const;
    int getOwnerId() const;
    double getBalance() const;
    std::string getCurrency() const;
    int getStatus() const;

    void setBalance(double v);
    void setStatus(int s);

    void print() const;
};

} // namespace banking

#endif
