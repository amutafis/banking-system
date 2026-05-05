#include "Account.h"
#include "Admin.h"
#include "Bank.h"
#include "Customer.h"

#include <iostream>
#include <limits>
#include <string>
using namespace std;

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

void printMenu() {
    cout << "\n=== Banking System (Checkpoint 2) ===\n";
    cout << " 1. Създай клиент\n";
    cout << " 2. Покажи всички клиенти\n";
    cout << " 3. Намери клиент по ID\n";
    cout << " 4. Редактирай клиент\n";
    cout << " 5. Изтрий клиент\n";
    cout << " 6. Създай сметка\n";
    cout << " 7. Покажи всички сметки\n";
    cout << " 8. Намери сметка по IBAN\n";
    cout << " 9. Промени статус на сметка\n";
    cout << "10. Изтрий сметка\n";
    cout << "11. Сметки на конкретен клиент\n";
    cout << "12. Демонстрация на полиморфизъм (Customer + Admin)\n";
    cout << " 0. Изход\n";
}

void seed(Bank& bank) {
    bank.createCustomer("Иван", "Петров", "9001011234",
                        "ivan@example.com", "0888111222");
    bank.createCustomer("Мария", "Георгиева", "9505052345",
                        "maria@example.com", "0888333444");
    bank.createAccount("BG80BNBG12345678901234", 1, 1500.0, "EUR");
    bank.createAccount("BG80BNBG99999999999999", 2, 250.0, "EUR");
}

// Демонстрация на полиморфизъм: масив от Person*, който съдържа
// и Customer, и Admin, а print() избира правилния role() автоматично.
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

int main() {
    Bank bank;
    seed(bank);

    while (true) {
        printMenu();
        int choice = readInt("Избор");

        if (choice == 0) {
            cout << "Чао.\n";
            return 0;
        }
        else if (choice == 1) {
            string fn   = readString("Име");
            string ln   = readString("Фамилия");
            string egn  = readString("ЕГН");
            string mail = readString("Имейл");
            string tel  = readString("Телефон");
            int newId = bank.createCustomer(fn, ln, egn, mail, tel);
            cout << "Създаден клиент с ID #" << newId << "\n";
        }
        else if (choice == 2) {
            bank.listCustomers();
        }
        else if (choice == 3) {
            int id = readInt("ID на клиент");
            bank.printCustomer(id);
        }
        else if (choice == 4) {
            int id = readInt("ID на клиент");
            string fn   = readString("Ново име");
            string ln   = readString("Нова фамилия");
            string mail = readString("Нов имейл");
            string tel  = readString("Нов телефон");
            if (bank.updateCustomer(id, fn, ln, mail, tel)) {
                cout << "Обновено.\n";
            } else {
                cout << "Не е намерен.\n";
            }
        }
        else if (choice == 5) {
            int id = readInt("ID на клиент за изтриване");
            if (bank.deleteCustomer(id)) {
                cout << "Изтрит (заедно със сметките му).\n";
            } else {
                cout << "Не е намерен.\n";
            }
        }
        else if (choice == 6) {
            string iban = readString("IBAN");
            int    id  = readInt("ID на собственик");
            double bal = readDouble("Начален баланс");
            if (bank.createAccount(iban, id, bal, "EUR")) {
                cout << "Сметката е създадена.\n";
            } else {
                cout << "Грешка: невалиден собственик или дубликат IBAN.\n";
            }
        }
        else if (choice == 7) {
            bank.listAccounts();
        }
        else if (choice == 8) {
            string iban = readString("IBAN");
            bank.printAccount(iban);
        }
        else if (choice == 9) {
            string iban = readString("IBAN");
            cout << "Статус: 0=ACTIVE, 1=BLOCKED, 2=CLOSED\n";
            int s = readInt("Нов статус");
            if (s < 0 || s > 2) {
                cout << "Невалиден статус.\n";
            } else if (bank.updateAccountStatus(iban, s)) {
                cout << "Обновен статус.\n";
            } else {
                cout << "Не е намерена.\n";
            }
        }
        else if (choice == 10) {
            string iban = readString("IBAN за изтриване");
            if (bank.deleteAccount(iban)) {
                cout << "Изтрита.\n";
            } else {
                cout << "Не е намерена.\n";
            }
        }
        else if (choice == 11) {
            int id = readInt("ID на клиент");
            bank.listAccountsOfCustomer(id);
        }
        else if (choice == 12) {
            demoPolymorphism();
        }
        else {
            cout << "Невалиден избор.\n";
        }
    }
}
