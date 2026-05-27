#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

// Тип на картата:
//   "DEBIT"   — дебитна
//   "VIRTUAL" — виртуална

enum CardStatus {
    CARD_ACTIVE = 0,
    CARD_BLOCKED = 1
};

class Card {
private:
    string cardNumber;   // 16 цифри
    string accountIban;  // към коя сметка е
    string type;         // "DEBIT" или "VIRTUAL"
    string expiry;       // формат "MM/YY"
    string cvv;          // 3 цифри
    int status;          // CARD_ACTIVE или CARD_BLOCKED

public:
    Card(string cardNumber,
         string accountIban,
         string type,
         string expiry,
         string cvv,
         int status);

    string getCardNumber() const;
    string getAccountIban() const;
    string getType() const;
    string getExpiry() const;
    string getCvv() const;
    int    getStatus() const;

    void setStatus(int s);

    // Печата картата, но маскира CVV.
    void print() const;
};

string cardStatusToString(int status);

#endif
