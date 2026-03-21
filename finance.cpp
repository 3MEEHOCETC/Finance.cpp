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

 void showHistory() {
    std::ifstream file("finances.csv");
    std::string line;

    if (!file.is_open()) {
        std::cout << "История пока пуста." << std::endl;
        return;
    }
    std::cout << "\n--- История транзакций ---" << std::endl;
    std::cout << "Дата | Сумма | Категория | Предмет" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    while (std::getline(file, line)) {
        //Здесь можно просто выводить строку или парсить её по разделителю ';'
        std::cout << line << std::endl;
    }
    file.close();
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

    int choice;
    while (true) {
        std::cout << "\n1. Добавить транзакцию\n2. Показать историю\n3. Выход\nВыбор: ";
        std::cin >> choice;

        if (choice == 1) {
            Transaction current;
            //...код вывода данных...
            saveTransaction(current);
        }else if (choice == 2) {
            showHistory();
        } else if (choice == 3) {
            break;
        }
        }
    
    return 0; }
