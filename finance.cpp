#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

struct Transaction {
    std::string date;
    double amount;
    std::string category;
    std::string item;
};

void saveTransaction(const Transaction& t) {
    //открываем в режиме ios::app (append), чтобы добавлять записи в конец
    std::ofstream file("finances.csv", std::ios::app);

    if (file.is_open()) {
        file << t.date << ","
        << t.amount << ","
        << t.category << ","
        << t.item << "\n";
        file.close();
        std::cout << "Данные успешно сохранены!" << std::endl;
    } else {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        }
}

int main() {
    Transaction current;

    std::cout << "--- Учет финансов (MVP) ---" << std::endl;

    std::cout << "Дата (ГГГГ-ММ-ДД): ";
    std::cin >> current.date;

    std::cout << "Сумма: ";
    std::cin >> current.amount;

    std::cout << "Категория: ";
    std::cin >> current.category;

    std::cout << "Предмет: ";
    std::cin.ignore(); //Очистка буфера после cin >>
    std::getline(std::cin, current.item);

    saveTransaction(current);

    return 0;
}