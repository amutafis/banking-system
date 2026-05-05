#pragma once

#include <string>

enum class AccountStatus {
    ACTIVE,
    BLOCKED,
    CLOSED
};

std::string toString(AccountStatus s);

class Account {
private:
    std::string iban;
    int ownerId;
    double balance;
    std::string currency;
    AccountStatus status;

public:
    Account(std::string iban,
            int ownerId,
            double balance = 0.0,
            std::string currency = "EUR",
            AccountStatus status = AccountStatus::ACTIVE);

    const std::string& getIban() const;
    int getOwnerId() const;
    double getBalance() const;
    const std::string& getCurrency() const;
    AccountStatus getStatus() const;

    void setBalance(double v);
    void setStatus(AccountStatus s);

    void print() const;
};
