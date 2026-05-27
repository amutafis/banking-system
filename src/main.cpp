#include "Account.h"
#include "Admin.h"
#include "Bank.h"
#include "Card.h"
#include "Customer.h"

#include <iostream>
#include <limits>
#include <string>
using namespace std;

// ============ Помощни четения ============

void clearLine() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string readString(string label) {
    cout << label << ": ";
    string s;
    getline(cin, s);
    return s;
}

int readInt(string label) {
    cout << label << ": ";
    int x;
    while (!(cin >> x)) {
        cin.clear();
        clearLine();
        cout << "Невалиден вход. " << label << ": ";
    }
    clearLine();
    return x;
}

double readDouble(string label) {
    cout << label << ": ";
    double x;
    while (!(cin >> x)) {
        cin.clear();
        clearLine();
        cout << "Невалиден вход. " << label << ": ";
    }
    clearLine();
    return x;
}

// ============ Демо данни ============

void seed(Bank& bank) {
    bank.createCustomer("Иван", "Петров", "9001011234",
                        "ivan@example.com", "0888111222");
    bank.createCustomer("Мария", "Георгиева", "9505052345",
                        "maria@example.com", "0888333444");
    bank.createAccount("BG80BNBG12345678901234", 1, 1500.0, "EUR");
    bank.createAccount("BG80BNBG99999999999999", 2, 250.0, "EUR");
    bank.createAdmin("Админ", "Главен", "8001011111",
                     "admin@bank.com", "0888000000");
}

// ============ Демо полиморфизъм ============

void demoPolymorphism() {
    Customer c(101, "Тест", "Клиент", "0000000000", "c@x.com", "0888");
    Admin    a(202, "Тест", "Админ",  "0000000001", "a@x.com", "0877");

    Person* people[2];
    people[0] = &c;
    people[1] = &a;

    cout << "\n--- Полиморфно print() през Person* ---\n";
    for (int i = 0; i < 2; i++) {
        people[i]->print();
    }
}

// ============ Меню за администратор ============

void printAdminMenu() {
    cout << "\n=== ADMIN MENU ===\n";
    cout << " 1. Покажи всички клиенти\n";
    cout << " 2. Създай клиент\n";
    cout << " 3. Редактирай клиент\n";
    cout << " 4. Изтрий клиент\n";
    cout << " 5. Покажи всички сметки\n";
    cout << " 6. Създай сметка\n";
    cout << " 7. Изтрий сметка\n";
    cout << " 8. Промени статус на сметка (блокирай / активирай)\n";
    cout << " 9. Покажи всички карти\n";
    cout << "10. Блокирай карта\n";
    cout << "11. Деблокирай карта\n";
    cout << "12. Покажи всички транзакции\n";
    cout << "13. Извлечение на сметка\n";
    cout << "14. Демонстрация на полиморфизъм\n";
    cout << " 0. Logout\n";
}

void runAdminMenu(Bank& bank) {
    while (true) {
        printAdminMenu();
        int choice = readInt("Избор");

        if (choice == 0) {
            cout << "Logout.\n";
            return;
        }
        else if (choice == 1) {
            bank.listCustomers();
        }
        else if (choice == 2) {
            string fn   = readString("Име");
            string ln   = readString("Фамилия");
            string egn  = readString("ЕГН");
            string mail = readString("Имейл");
            string tel  = readString("Телефон");
            int newId = bank.createCustomer(fn, ln, egn, mail, tel);
            cout << "Създаден клиент с ID #" << newId << "\n";
        }
        else if (choice == 3) {
            int id = readInt("ID на клиент");
            string fn   = readString("Ново име");
            string ln   = readString("Нова фамилия");
            string mail = readString("Нов имейл");
            string tel  = readString("Нов телефон");
            if (bank.updateCustomer(id, fn, ln, mail, tel)) cout << "Обновено.\n";
            else cout << "Не е намерен.\n";
        }
        else if (choice == 4) {
            int id = readInt("ID на клиент за изтриване");
            if (bank.deleteCustomer(id)) cout << "Изтрит.\n";
            else cout << "Не е намерен.\n";
        }
        else if (choice == 5) {
            bank.listAccounts();
        }
        else if (choice == 6) {
            string iban = readString("IBAN");
            int    id  = readInt("ID на собственик");
            double bal = readDouble("Начален баланс");
            if (bank.createAccount(iban, id, bal, "EUR")) cout << "Сметката е създадена.\n";
            else cout << "Грешка.\n";
        }
        else if (choice == 7) {
            string iban = readString("IBAN за изтриване");
            if (bank.deleteAccount(iban)) cout << "Изтрита.\n";
            else cout << "Не е намерена.\n";
        }
        else if (choice == 8) {
            string iban = readString("IBAN");
            cout << "0=ACTIVE, 1=BLOCKED, 2=CLOSED\n";
            int s = readInt("Нов статус");
            if (s < 0 || s > 2) cout << "Невалиден.\n";
            else if (bank.updateAccountStatus(iban, s)) cout << "Обновен.\n";
            else cout << "Не е намерена.\n";
        }
        else if (choice == 9) {
            bank.listCards();
        }
        else if (choice == 10) {
            string num = readString("Номер на карта");
            if (bank.blockCard(num)) cout << "Блокирана.\n";
            else cout << "Не е намерена.\n";
        }
        else if (choice == 11) {
            string num = readString("Номер на карта");
            if (bank.unblockCard(num)) cout << "Деблокирана.\n";
            else cout << "Не е намерена.\n";
        }
        else if (choice == 12) {
            bank.listAllTransactions();
        }
        else if (choice == 13) {
            string iban = readString("IBAN");
            if (!bank.printStatement(iban)) cout << "Не е намерена.\n";
        }
        else if (choice == 14) {
            demoPolymorphism();
        }
        else {
            cout << "Невалиден избор.\n";
        }
    }
}

// ============ Меню за клиент ============

void printCustomerMenu(int customerId) {
    cout << "\n=== CUSTOMER MENU (клиент #" << customerId << ") ===\n";
    cout << " 1. Моите сметки\n";
    cout << " 2. Депозит\n";
    cout << " 3. Теглене\n";
    cout << " 4. Вътрешен превод\n";
    cout << " 5. Външен превод\n";
    cout << " 6. История на моя сметка\n";
    cout << " 7. Извлечение на моя сметка\n";
    cout << " 8. Издай карта към моя сметка\n";
    cout << " 9. Моите карти (по сметка)\n";
    cout << " 0. Logout\n";
}

// Проверка дали сметката с този IBAN е на текущия клиент.
bool ownsAccount(Bank& bank, int customerId, string iban) {
    int owner = bank.getAccountOwnerId(iban);
    if (owner == -1) {
        cout << "Не съществува сметка с този IBAN.\n";
        return false;
    }
    if (owner != customerId) {
        cout << "Достъп отказан: сметката не е ваша.\n";
        return false;
    }
    return true;
}

void runCustomerMenu(Bank& bank, int customerId) {
    while (true) {
        printCustomerMenu(customerId);
        int choice = readInt("Избор");

        if (choice == 0) {
            cout << "Logout.\n";
            return;
        }
        else if (choice == 1) {
            bank.listAccountsOfCustomer(customerId);
        }
        else if (choice == 2) {
            string iban = readString("IBAN на моя сметка");
            if (!ownsAccount(bank, customerId, iban)) continue;
            double amt = readDouble("Сума");
            if (bank.deposit(iban, amt)) cout << "Депозит успешен.\n";
            else cout << "Грешка.\n";
        }
        else if (choice == 3) {
            string iban = readString("IBAN на моя сметка");
            if (!ownsAccount(bank, customerId, iban)) continue;
            double amt = readDouble("Сума");
            if (bank.withdraw(iban, amt)) cout << "Тегленето е успешно.\n";
            else cout << "Грешка.\n";
        }
        else if (choice == 4) {
            string from = readString("От IBAN (моя сметка)");
            if (!ownsAccount(bank, customerId, from)) continue;
            string to  = readString("Към IBAN (вътрешна сметка)");
            double amt = readDouble("Сума");
            if (bank.transferInternal(from, to, amt)) cout << "Преводът е успешен.\n";
            else cout << "Грешка.\n";
        }
        else if (choice == 5) {
            string from = readString("От IBAN (моя сметка)");
            if (!ownsAccount(bank, customerId, from)) continue;
            string to  = readString("Външен IBAN");
            double amt = readDouble("Сума");
            if (bank.transferExternal(from, to, amt)) cout << "Външният превод е успешен.\n";
            else cout << "Грешка.\n";
        }
        else if (choice == 6) {
            string iban = readString("IBAN на моя сметка");
            if (!ownsAccount(bank, customerId, iban)) continue;
            bank.listTransactionsOfAccount(iban);
        }
        else if (choice == 7) {
            string iban = readString("IBAN на моя сметка");
            if (!ownsAccount(bank, customerId, iban)) continue;
            bank.printStatement(iban);
        }
        else if (choice == 8) {
            string iban = readString("IBAN на моя сметка");
            if (!ownsAccount(bank, customerId, iban)) continue;
            string type = readString("Тип (DEBIT / VIRTUAL)");
            string num = bank.issueCard(iban, type);
            if (num != "") cout << "Издадена карта: " << num << "\n";
            else cout << "Грешка.\n";
        }
        else if (choice == 9) {
            string iban = readString("IBAN на моя сметка");
            if (!ownsAccount(bank, customerId, iban)) continue;
            bank.listCardsOfAccount(iban);
        }
        else {
            cout << "Невалиден избор.\n";
        }
    }
}

// ============ Login екран ============

void printLoginScreen() {
    cout << "\n========================================\n";
    cout << "   Banking System — финална версия\n";
    cout << "========================================\n";
    cout << " 1. Login като клиент\n";
    cout << " 2. Login като администратор\n";
    cout << " 0. Изход от програмата\n";
}

int main() {
    Bank bank;
    seed(bank);

    cout << "Демо акаунти:\n";
    cout << "  Клиенти: ID 1 (Иван), ID 2 (Мария)\n";
    cout << "  Админ:   ID 9001\n";

    while (true) {
        printLoginScreen();
        int choice = readInt("Избор");

        if (choice == 0) {
            cout << "Чао.\n";
            return 0;
        }
        else if (choice == 1) {
            int id = readInt("Вашето клиентско ID");
            if (bank.findCustomerIndex(id) == -1) {
                cout << "Няма такъв клиент.\n";
            } else {
                runCustomerMenu(bank, id);
            }
        }
        else if (choice == 2) {
            int id = readInt("Админ ID");
            if (bank.findAdminIndex(id) == -1) {
                cout << "Няма такъв администратор.\n";
            } else {
                runAdminMenu(bank);
            }
        }
        else {
            cout << "Невалиден избор.\n";
        }
    }
}
