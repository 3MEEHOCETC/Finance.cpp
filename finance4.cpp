#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>

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
double total = 0; 

    if (!file.is_open()) {
        std::cout << "История пока пуста." << std::endl;
        return;
    }

    std::cout << "\n--- История транзакций ---" << std::endl;
    std::cout << "Дата | Сумма | Категория | Предмет" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    while (std::getline(file, line)) {
      std::cout << line << std::endl;

      //парсинг суммы для подсчета итого
      std::stringstream ss(line);
      std::string segment;
      int column = 0;

      while (std::getline(ss, segment, ',')) {
        column++;
        if (column ==2) { // вторая колонка это сумма
        try {
            total += std::stod(segment);
        }    catch (...) {
            //пропускаем если в сумме мусор
        }
        }
      }
    }
std::cout << "------------------------------------" << std::endl;
std::cout << "Итого потрачено: " << total << " тенге" << std::endl;
    file.close();
 }
std::string getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    std::ostringstream oss;
    oss << (now->tm_year + 1900) << "-"
    << std::setfill('0') << std::setw(2) << (now->tm_mon + 1) << "-"
    << std::setfill('0') << std::setw(2) << now->tm_mday;
    return oss.str();
}


int main() {

    Transaction current;

    std::cout << "--- Учет финансов (MVP) ---" << std::endl;

   //Автоматическая дата
   current.date = getCurrentDate();
   std::cout << "Дата (авто): " << current.date << std::endl;

    std::cout << "Сумма: ";
    if (!(std::cin >> current.amount)) {
        std::cout << "Ошибка: введите число!" << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return 0;
    };

    std::cout << "Категория: ";
    std::cin.ignore(10000, '\n'); //критично: чистим буфер после ввода суммы
    std::getline(std::cin, current.category);

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