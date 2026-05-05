#include "Account.h"
#include "Admin.h"
#include "Bank.h"
#include "Customer.h"

#include <iostream>
#include <limits>
#include <string>

using namespace banking;

void clearLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string readString(std::string label) {
    std::cout << label << ": ";
    std::string s;
    std::getline(std::cin, s);
    return s;
}

int readInt(std::string label) {
    std::cout << label << ": ";
    int x;
    while (!(std::cin >> x)) {
        std::cin.clear();
        clearLine();
        std::cout << "Невалиден вход. " << label << ": ";
    }
    clearLine();
    return x;
}

double readDouble(std::string label) {
    std::cout << label << ": ";
    double x;
    while (!(std::cin >> x)) {
        std::cin.clear();
        clearLine();
        std::cout << "Невалиден вход. " << label << ": ";
    }
    clearLine();
    return x;
}

void printMenu() {
    std::cout << "\n=== Banking System (Checkpoint 2) ===\n";
    std::cout << " 1. Създай клиент\n";
    std::cout << " 2. Покажи всички клиенти\n";
    std::cout << " 3. Намери клиент по ID\n";
    std::cout << " 4. Редактирай клиент\n";
    std::cout << " 5. Изтрий клиент\n";
    std::cout << " 6. Създай сметка\n";
    std::cout << " 7. Покажи всички сметки\n";
    std::cout << " 8. Намери сметка по IBAN\n";
    std::cout << " 9. Промени статус на сметка\n";
    std::cout << "10. Изтрий сметка\n";
    std::cout << "11. Сметки на конкретен клиент\n";
    std::cout << "12. Демонстрация на полиморфизъм (Customer + Admin)\n";
    std::cout << " 0. Изход\n";
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

    std::cout << "\n--- Полиморфно print() през Person* ---\n";
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
            std::cout << "Чао.\n";
            return 0;
        }
        else if (choice == 1) {
            std::string fn   = readString("Име");
            std::string ln   = readString("Фамилия");
            std::string egn  = readString("ЕГН");
            std::string mail = readString("Имейл");
            std::string tel  = readString("Телефон");
            int newId = bank.createCustomer(fn, ln, egn, mail, tel);
            std::cout << "Създаден клиент с ID #" << newId << "\n";
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
            std::string fn   = readString("Ново име");
            std::string ln   = readString("Нова фамилия");
            std::string mail = readString("Нов имейл");
            std::string tel  = readString("Нов телефон");
            if (bank.updateCustomer(id, fn, ln, mail, tel)) {
                std::cout << "Обновено.\n";
            } else {
                std::cout << "Не е намерен.\n";
            }
        }
        else if (choice == 5) {
            int id = readInt("ID на клиент за изтриване");
            if (bank.deleteCustomer(id)) {
                std::cout << "Изтрит (заедно със сметките му).\n";
            } else {
                std::cout << "Не е намерен.\n";
            }
        }
        else if (choice == 6) {
            std::string iban = readString("IBAN");
            int    id  = readInt("ID на собственик");
            double bal = readDouble("Начален баланс");
            if (bank.createAccount(iban, id, bal, "EUR")) {
                std::cout << "Сметката е създадена.\n";
            } else {
                std::cout << "Грешка: невалиден собственик или дубликат IBAN.\n";
            }
        }
        else if (choice == 7) {
            bank.listAccounts();
        }
        else if (choice == 8) {
            std::string iban = readString("IBAN");
            bank.printAccount(iban);
        }
        else if (choice == 9) {
            std::string iban = readString("IBAN");
            std::cout << "Статус: 0=ACTIVE, 1=BLOCKED, 2=CLOSED\n";
            int s = readInt("Нов статус");
            if (s < 0 || s > 2) {
                std::cout << "Невалиден статус.\n";
            } else if (bank.updateAccountStatus(iban, s)) {
                std::cout << "Обновен статус.\n";
            } else {
                std::cout << "Не е намерена.\n";
            }
        }
        else if (choice == 10) {
            std::string iban = readString("IBAN за изтриване");
            if (bank.deleteAccount(iban)) {
                std::cout << "Изтрита.\n";
            } else {
                std::cout << "Не е намерена.\n";
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
            std::cout << "Невалиден избор.\n";
        }
    }
}
