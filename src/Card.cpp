#include "Card.h"
#include <iostream>
using namespace std;

string cardStatusToString(int status) {
    if (status == CARD_ACTIVE)  return "ACTIVE";
    if (status == CARD_BLOCKED) return "BLOCKED";
    return "UNKNOWN";
}

Card::Card(string cardNumber,
           string accountIban,
           string type,
           string expiry,
           string cvv,
           int status) {
    this->cardNumber = cardNumber;
    this->accountIban = accountIban;
    this->type = type;
    this->expiry = expiry;
    this->cvv = cvv;
    this->status = status;
}

string Card::getCardNumber() const  { return cardNumber; }
string Card::getAccountIban() const { return accountIban; }
string Card::getType() const        { return type; }
string Card::getExpiry() const      { return expiry; }
string Card::getCvv() const         { return cvv; }
int    Card::getStatus() const      { return status; }

void Card::setStatus(int s) { status = s; }

void Card::print() const {
    cout << "Card " << cardNumber
         << " (" << type << ")"
         << " | сметка " << accountIban
         << " | exp " << expiry
         << " | CVV ***"
         << " | " << cardStatusToString(status) << "\n";
}
