#include "Bank.h"
#include <iostream>
#include <ctime>
using namespace std;

Bank::Bank() {
    nextCustomerId = 1;
    nextAdminId = 9001;  // админи започват от 9001 за да се различават от клиенти
    nextCardSerial = 1000;
}

// Генерира номер на карта от вида "4000000000001000".
string Bank::generateCardNumber() {
    string prefix = "4000000000000000";
    string serial = to_string(nextCardSerial);
    nextCardSerial = nextCardSerial + 1;
    // Заменяме последните цифри със serial.
    int startPos = prefix.size() - serial.size();
    for (int i = 0; i < (int)serial.size(); i++) {
        prefix[startPos + i] = serial[i];
    }
    return prefix;
}

// Връща текущи дата/час като "Wed May  7 14:23:11 2026" (стандартен формат от ctime).
static string currentTimestamp() {
    time_t now = time(0);
    string ts = ctime(&now);
    // ctime добавя \n на края — махаме го.
    if (ts.size() > 0 && ts[ts.size() - 1] == '\n') {
        ts = ts.substr(0, ts.size() - 1);
    }
    return ts;
}

void Bank::logTransaction(string iban, string type, double amount, string description) {
    Transaction t(iban, type, amount, description, currentTimestamp());
    transactions.push_back(t);
}

// ---------- Customer CRUD ----------

int Bank::createCustomer(string firstName,
                         string lastName,
                         string egn,
                         string email,
                         string phone) {
    int newId = nextCustomerId;
    nextCustomerId = nextCustomerId + 1;

    Customer c(newId, firstName, lastName, egn, email, phone);
    customers.push_back(c);
    return newId;
}

int Bank::findCustomerIndex(int id) const {
    for (int i = 0; i < (int)customers.size(); i++) {
        if (customers[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

bool Bank::updateCustomer(int id,
                          string firstName,
                          string lastName,
                          string email,
                          string phone) {
    int idx = findCustomerIndex(id);
    if (idx == -1) return false;

    customers[idx].setFirstName(firstName);
    customers[idx].setLastName(lastName);
    customers[idx].setEmail(email);
    customers[idx].setPhone(phone);
    return true;
}

bool Bank::deleteCustomer(int id) {
    int idx = findCustomerIndex(id);
    if (idx == -1) return false;

    // Първо премахваме всички сметки на този клиент.
    for (int i = 0; i < (int)accounts.size(); ) {
        if (accounts[i].getOwnerId() == id) {
            accounts.erase(accounts.begin() + i);
        } else {
            i++;
        }
    }

    customers.erase(customers.begin() + idx);
    return true;
}

void Bank::listCustomers() const {
    if (customers.size() == 0) {
        cout << "(няма регистрирани клиенти)\n";
        return;
    }
    for (int i = 0; i < (int)customers.size(); i++) {
        customers[i].print();
    }
}

void Bank::printCustomer(int id) const {
    int idx = findCustomerIndex(id);
    if (idx == -1) {
        cout << "Не е намерен клиент с ID #" << id << "\n";
        return;
    }
    customers[idx].print();
}

// ---------- Admin ----------

int Bank::createAdmin(string firstName,
                      string lastName,
                      string egn,
                      string email,
                      string phone) {
    int newId = nextAdminId;
    nextAdminId = nextAdminId + 1;

    Admin a(newId, firstName, lastName, egn, email, phone);
    admins.push_back(a);
    return newId;
}

int Bank::findAdminIndex(int id) const {
    for (int i = 0; i < (int)admins.size(); i++) {
        if (admins[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

void Bank::listAdmins() const {
    if (admins.size() == 0) {
        cout << "(няма регистрирани администратори)\n";
        return;
    }
    for (int i = 0; i < (int)admins.size(); i++) {
        admins[i].print();
    }
}

// ---------- Помощни ----------

int Bank::getAccountOwnerId(string iban) const {
    int idx = findAccountIndex(iban);
    if (idx == -1) return -1;
    return accounts[idx].getOwnerId();
}

// ---------- Account CRUD ----------

bool Bank::createAccount(string iban,
                         int ownerId,
                         double initialBalance,
                         string currency) {
    if (findCustomerIndex(ownerId) == -1) return false;
    if (findAccountIndex(iban) != -1)     return false;

    Account a(iban, ownerId, initialBalance, currency, ACTIVE);
    accounts.push_back(a);
    return true;
}

int Bank::findAccountIndex(string iban) const {
    for (int i = 0; i < (int)accounts.size(); i++) {
        if (accounts[i].getIban() == iban) {
            return i;
        }
    }
    return -1;
}

bool Bank::updateAccountStatus(string iban, int newStatus) {
    int idx = findAccountIndex(iban);
    if (idx == -1) return false;
    accounts[idx].setStatus(newStatus);
    return true;
}

bool Bank::deleteAccount(string iban) {
    int idx = findAccountIndex(iban);
    if (idx == -1) return false;
    accounts.erase(accounts.begin() + idx);
    return true;
}

void Bank::listAccounts() const {
    if (accounts.size() == 0) {
        cout << "(няма сметки)\n";
        return;
    }
    for (int i = 0; i < (int)accounts.size(); i++) {
        accounts[i].print();
    }
}

void Bank::printAccount(string iban) const {
    int idx = findAccountIndex(iban);
    if (idx == -1) {
        cout << "Не е намерена сметка с IBAN " << iban << "\n";
        return;
    }
    accounts[idx].print();
}

void Bank::listAccountsOfCustomer(int ownerId) const {
    bool any = false;
    for (int i = 0; i < (int)accounts.size(); i++) {
        if (accounts[i].getOwnerId() == ownerId) {
            accounts[i].print();
            any = true;
        }
    }
    if (!any) {
        cout << "(клиент #" << ownerId << " няма сметки)\n";
    }
}

// ---------- Операции по сметка ----------

bool Bank::deposit(string iban, double amount) {
    if (amount <= 0) return false;

    int idx = findAccountIndex(iban);
    if (idx == -1) return false;
    if (accounts[idx].getStatus() != ACTIVE) return false;

    accounts[idx].setBalance(accounts[idx].getBalance() + amount);
    logTransaction(iban, "DEPOSIT", amount, "Депозит");
    return true;
}

bool Bank::withdraw(string iban, double amount) {
    if (amount <= 0) return false;

    int idx = findAccountIndex(iban);
    if (idx == -1) return false;
    if (accounts[idx].getStatus() != ACTIVE) return false;
    if (accounts[idx].getBalance() < amount) return false;

    accounts[idx].setBalance(accounts[idx].getBalance() - amount);
    logTransaction(iban, "WITHDRAW", amount, "Теглене");
    return true;
}

// ---------- Преводи ----------

bool Bank::transferInternal(string fromIban, string toIban, double amount) {
    if (amount <= 0) return false;
    if (fromIban == toIban) return false;

    int fromIdx = findAccountIndex(fromIban);
    int toIdx   = findAccountIndex(toIban);
    if (fromIdx == -1 || toIdx == -1) return false;
    if (accounts[fromIdx].getStatus() != ACTIVE) return false;
    if (accounts[toIdx].getStatus() != ACTIVE)   return false;
    if (accounts[fromIdx].getBalance() < amount) return false;

    accounts[fromIdx].setBalance(accounts[fromIdx].getBalance() - amount);
    accounts[toIdx].setBalance(accounts[toIdx].getBalance() + amount);

    logTransaction(fromIban, "TRANSFER_OUT", amount, "Превод към " + toIban);
    logTransaction(toIban,   "TRANSFER_IN",  amount, "Превод от " + fromIban);
    return true;
}

bool Bank::transferExternal(string fromIban, string toIban, double amount) {
    if (amount <= 0) return false;
    if (toIban.size() == 0) return false;

    int fromIdx = findAccountIndex(fromIban);
    if (fromIdx == -1) return false;
    if (accounts[fromIdx].getStatus() != ACTIVE) return false;
    if (accounts[fromIdx].getBalance() < amount) return false;

    accounts[fromIdx].setBalance(accounts[fromIdx].getBalance() - amount);
    logTransaction(fromIban, "EXTERNAL_OUT", amount, "Външен превод към " + toIban);
    return true;
}

// ---------- История на транзакции ----------

void Bank::listAllTransactions() const {
    if (transactions.size() == 0) {
        cout << "(няма транзакции)\n";
        return;
    }
    for (int i = 0; i < (int)transactions.size(); i++) {
        transactions[i].print();
    }
}

void Bank::listTransactionsOfAccount(string iban) const {
    bool any = false;
    for (int i = 0; i < (int)transactions.size(); i++) {
        if (transactions[i].getIban() == iban) {
            transactions[i].print();
            any = true;
        }
    }
    if (!any) {
        cout << "(няма транзакции за " << iban << ")\n";
    }
}

void Bank::listTransactionsOfAccountByType(string iban, string type) const {
    bool any = false;
    for (int i = 0; i < (int)transactions.size(); i++) {
        if (transactions[i].getIban() == iban && transactions[i].getType() == type) {
            transactions[i].print();
            any = true;
        }
    }
    if (!any) {
        cout << "(няма транзакции от тип " << type << " за " << iban << ")\n";
    }
}

// ---------- Извлечение ----------

bool Bank::printStatement(string iban) const {
    int idx = findAccountIndex(iban);
    if (idx == -1) return false;

    double closing = accounts[idx].getBalance();

    // Изчислява нетното движение от транзакциите за тази сметка.
    // Положителни: DEPOSIT, TRANSFER_IN.
    // Отрицателни: WITHDRAW, TRANSFER_OUT, EXTERNAL_OUT.
    double netMovement = 0;
    for (int i = 0; i < (int)transactions.size(); i++) {
        if (transactions[i].getIban() != iban) continue;
        string t = transactions[i].getType();
        double a = transactions[i].getAmount();
        if (t == "DEPOSIT" || t == "TRANSFER_IN") {
            netMovement = netMovement + a;
        } else {
            netMovement = netMovement - a;
        }
    }
    double opening = closing - netMovement;

    cout << "\n=== ИЗВЛЕЧЕНИЕ ===\n";
    cout << "Сметка: " << iban << "\n";
    cout << "Собственик #" << accounts[idx].getOwnerId() << "\n";
    cout << "Валута: " << accounts[idx].getCurrency() << "\n";
    cout << "Статус: " << statusToString(accounts[idx].getStatus()) << "\n";
    cout << "------------------\n";
    cout << "Начален баланс: " << opening << "\n";
    cout << "Движения:\n";

    bool any = false;
    for (int i = 0; i < (int)transactions.size(); i++) {
        if (transactions[i].getIban() == iban) {
            cout << "  ";
            transactions[i].print();
            any = true;
        }
    }
    if (!any) cout << "  (няма движения)\n";

    cout << "------------------\n";
    cout << "Краен баланс:   " << closing << "\n";
    cout << "==================\n";
    return true;
}

// ---------- Карти ----------

string Bank::issueCard(string iban, string type) {
    if (findAccountIndex(iban) == -1) return "";
    if (type != "DEBIT" && type != "VIRTUAL") return "";

    string number = generateCardNumber();
    Card c(number, iban, type, "12/29", "123", CARD_ACTIVE);
    cards.push_back(c);
    return number;
}

int Bank::findCardIndex(string cardNumber) const {
    for (int i = 0; i < (int)cards.size(); i++) {
        if (cards[i].getCardNumber() == cardNumber) {
            return i;
        }
    }
    return -1;
}

bool Bank::blockCard(string cardNumber) {
    int idx = findCardIndex(cardNumber);
    if (idx == -1) return false;
    cards[idx].setStatus(CARD_BLOCKED);
    return true;
}

bool Bank::unblockCard(string cardNumber) {
    int idx = findCardIndex(cardNumber);
    if (idx == -1) return false;
    cards[idx].setStatus(CARD_ACTIVE);
    return true;
}

void Bank::listCards() const {
    if (cards.size() == 0) {
        cout << "(няма издадени карти)\n";
        return;
    }
    for (int i = 0; i < (int)cards.size(); i++) {
        cards[i].print();
    }
}

void Bank::listCardsOfAccount(string iban) const {
    bool any = false;
    for (int i = 0; i < (int)cards.size(); i++) {
        if (cards[i].getAccountIban() == iban) {
            cards[i].print();
            any = true;
        }
    }
    if (!any) {
        cout << "(сметка " << iban << " няма карти)\n";
    }
}
