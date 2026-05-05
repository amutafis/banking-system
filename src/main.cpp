#include "Account.h"
#include "Bank.h"
#include "Customer.h"

#include <iostream>
#include <limits>
#include <string>

namespace {

void clearLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string prompt(const std::string& label) {
    std::cout << label << ": ";
    std::string s;
    std::getline(std::cin, s);
    return s;
}

int promptInt(const std::string& label) {
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

double promptDouble(const std::string& label) {
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
    std::cout << "\n=== Banking System (Checkpoint 2) ===\n"
              << " 1. Създай клиент\n"
              << " 2. Покажи всички клиенти\n"
              << " 3. Намери клиент по ID\n"
              << " 4. Редактирай клиент\n"
              << " 5. Изтрий клиент\n"
              << " 6. Създай сметка\n"
              << " 7. Покажи всички сметки\n"
              << " 8. Намери сметка по IBAN\n"
              << " 9. Промени статус на сметка\n"
              << "10. Изтрий сметка\n"
              << "11. Сметки на конкретен клиент\n"
              << " 0. Изход\n";
}

void seed(Bank& bank) {
    Customer* c1 = bank.createCustomer("Иван", "Петров",
                                       "9001011234", "ivan@example.com", "0888111222");
    Customer* c2 = bank.createCustomer("Мария", "Георгиева",
                                       "9505052345", "maria@example.com", "0888333444");
    bank.createAccount("BG80BNBG12345678901234", c1->getId(), 1500.0, "EUR");
    bank.createAccount("BG80BNBG99999999999999", c2->getId(), 250.0,  "EUR");
}

} // namespace

int main() {
    Bank bank;
    seed(bank);

    while (true) {
        printMenu();
        int choice = promptInt("Избор");

        switch (choice) {
            case 0:
                std::cout << "Чао.\n";
                return 0;

            case 1: {
                auto fn   = prompt("Име");
                auto ln   = prompt("Фамилия");
                auto egn  = prompt("ЕГН");
                auto mail = prompt("Имейл");
                auto tel  = prompt("Телефон");
                Customer* c = bank.createCustomer(fn, ln, egn, mail, tel);
                std::cout << "Създаден клиент с ID #" << c->getId() << "\n";
                break;
            }
            case 2:
                bank.listCustomers();
                break;
            case 3: {
                int id = promptInt("ID на клиент");
                if (Customer* c = bank.findCustomer(id)) c->print();
                else std::cout << "Не е намерен.\n";
                break;
            }
            case 4: {
                int id    = promptInt("ID на клиент");
                auto fn   = prompt("Ново име");
                auto ln   = prompt("Нова фамилия");
                auto mail = prompt("Нов имейл");
                auto tel  = prompt("Нов телефон");
                std::cout << (bank.updateCustomer(id, fn, ln, mail, tel)
                              ? "Обновено.\n" : "Не е намерен.\n");
                break;
            }
            case 5: {
                int id = promptInt("ID на клиент за изтриване");
                std::cout << (bank.deleteCustomer(id)
                              ? "Изтрит (заедно със сметките му).\n"
                              : "Не е намерен.\n");
                break;
            }
            case 6: {
                auto iban = prompt("IBAN");
                int    id = promptInt("ID на собственик");
                double bal = promptDouble("Начален баланс");
                Account* a = bank.createAccount(iban, id, bal, "EUR");
                std::cout << (a ? "Сметката е създадена.\n"
                                : "Грешка: невалиден собственик или дубликат IBAN.\n");
                break;
            }
            case 7:
                bank.listAccounts();
                break;
            case 8: {
                auto iban = prompt("IBAN");
                if (const Account* a = bank.findAccount(iban)) a->print();
                else std::cout << "Не е намерена.\n";
                break;
            }
            case 9: {
                auto iban = prompt("IBAN");
                std::cout << "Статус: 0=ACTIVE, 1=BLOCKED, 2=CLOSED\n";
                int s = promptInt("Нов статус");
                if (s < 0 || s > 2) { std::cout << "Невалиден статус.\n"; break; }
                std::cout << (bank.updateAccountStatus(iban, static_cast<AccountStatus>(s))
                              ? "Обновен статус.\n" : "Не е намерена.\n");
                break;
            }
            case 10: {
                auto iban = prompt("IBAN за изтриване");
                std::cout << (bank.deleteAccount(iban)
                              ? "Изтрита.\n" : "Не е намерена.\n");
                break;
            }
            case 11: {
                int id = promptInt("ID на клиент");
                bank.listAccountsOfCustomer(id);
                break;
            }
            default:
                std::cout << "Невалиден избор.\n";
        }
    }
}
