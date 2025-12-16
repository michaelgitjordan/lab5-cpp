#include "files.h"
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <limits>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstring>

using namespace std;

std::string getStringInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);
    return input;
}

template<typename T>
T getNumericInput(const std::string& prompt, T minValue, T maxValue) {
    T value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите число.\n";
        }
        else if (value < minValue || value > maxValue) {
            std::cout << "Ошибка! Значение должно быть от " << minValue 
                      << " до " << maxValue << ".\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    return value;
}

int LabFile::generateRandom(int min, int max) {
    static mt19937 generator(static_cast<unsigned>(time(nullptr)));
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

void LabFile::fillWithRandom(const string& filename, int count, int min, int max){
    ofstream file(filename, ios::binary);

    if (!file.is_open()) {
        cerr << "Невозможно открыть файл " << filename << " для записи." << endl;
        return;
    }

    for (int i; i < count; i++) {
        int num = generateRandom(min, max);
        file.write(reinterpret_cast<const char*>(&num), sizeof(int));
    }

    file.close();
    cout << "Файл " << filename << " успешно заполнен" << count << " числами от " << min << " до " << max << endl;

}

int LabFile::findDiff(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    
    if (!file) {
        std::cerr << "Файл не открыт: " << filename << std::endl;
        return 0;
    }
    
    int first, current, maxVal;
    
    // Читаем первый элемент
    file.read((char*)&first, sizeof(int));
    if (!file) {
        std::cerr << "Ошибка чтения" << std::endl;
        return 0;
    }
    
    maxVal = first;
    
    // Читаем остальное
    while (file.read((char*)&current, sizeof(int))) {
        if (current > maxVal) {
            maxVal = current;
        }
    }
    
    std::cout << "Первый: " << first << ", Макс: " << maxVal 
              << ", Разность: " << (first - maxVal) << std::endl;
    
    return first - maxVal;
}

Toy LabFile::createToy() {
    cout << " Ввод данных об игрушке: " << endl;

    std::string name;
    while (true) {
        name = getStringInput("Введите название игрушки: ");
        if (name.empty()) {
            std::cout << "Ошибка! Название не может быть пустым.\n";
        }
        else if (name.length() > 49) {
            std::cout << "Внимание! Название будет обрезано до 49 символов.\n";
            break;
        }
        else {
            break;
        }
    }
    
    // 2. Ввод цены
    double price = getNumericInput<double>("Введите стоимость игрушки (руб.): ", 0.0, 1000000.0);
    
    // 3. Ввод возрастных границ
    cout << "\nВведите возрастные границы:" << endl;
    int minAge = getNumericInput<int>("Минимальный возраст (0-18): ", 0, 18);
    
    int maxAge;
    while (true) {
        maxAge = getNumericInput<int>("Максимальный возраст (0-18): ", 0, 18);
        
        if (maxAge < minAge) {
            cout << "Ошибка! Максимальный возраст не может быть меньше минимального.\n";
            cout << "Минимальный возраст: " << minAge << endl;
        }
        else {
            break;
        }
    }
    
    // 4. Определение типа игрушки
    cout << "Это кукла?" << endl;
    cout << "1. Да, это кукла" << endl;
    cout << "2. Нет, это другая игрушка" << endl;
    
    int choice;
    bool isDoll = false;
    
    while (true) {
        choice = getNumericInput<int>("Выберите (1-2): ", 1, 2);
        if (choice == 1) {
            isDoll = true;
            break;
        }
        else if (choice == 2) {
            isDoll = false;
            break;
        }
    }
    
    // Создание объекта Toy
    Toy toy(name, price, static_cast<uint8_t>(minAge), static_cast<uint8_t>(maxAge), isDoll);
    
    // Подтверждение введенных данных
    cout << "Игрушка успешно создана!" << endl;
    cout << "Проверьте введенные данные:" << endl;
    cout << string(40, '-') << endl;
    
    return toy;
}

void LabFile::printToy(const Toy& toy) {
    cout << "Название: " << toy.name << endl;
    cout << "Стоимость: " << fixed << setprecision(2) << toy.price << " руб." << endl;
    cout << "Возраст: от " << static_cast<int>(toy.minAge) 
              << " до " << static_cast<int>(toy.maxAge) << " лет" << endl;
    cout << "Тип: " << (toy.isDoll ? "Кукла" : "Другая игрушка") << endl;
    cout << string(40, '-') << endl;
}

void LabFile::createToyFile(const std::string& filename) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла " << filename << endl;
        return;
    }
    
    int count = getNumericInput<int>("Сколько игрушек добавить? ", 1, 100);
    
    for (int i = 0; i < count; i++) {
        cout << "\nИгрушка #" << (i + 1) << ":" << endl;
        Toy toy = createToy();
        
        cout << "Сохранить эту игрушку в файл? (y/n): ";
        char confirm;
        cin >> confirm;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (confirm == 'y' || confirm == 'Y') {
            file.write(reinterpret_cast<const char*>(&toy), sizeof(Toy));
            cout << "Игрушка сохранена." << endl;
        } else {
            cout << "Игрушка не сохранена." << endl;
            i--; // Повторяем ввод для этой позиции
        }
    }
    
    file.close();
    cout << "\nФайл " << filename << " создан." << endl;
}

void LabFile::addToyToFile(const std::string& filename) {
    // Открываем файл в режиме добавления
    ofstream file(filename, ios::binary | ios::app);
    
    if (!file.is_open()) {
        // Если файл не существует, создаем новый
        file.open(filename, ios::binary);
        if (!file.is_open()) {
            cerr << "Ошибка: не удалось создать/открыть файл " << filename << endl;
            return;
        }
        cout << "Создан новый файл." << endl;
    } else {
        cout << "Файл открыт для добавления." << endl;
    }
    
    // Вводим данные об игрушке
    Toy toy = createToy();
    
    // Подтверждение
    cout << "Добавить эту игрушку в файл? (y/n): ";
    char confirm;
    cin >> confirm;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (confirm == 'y' || confirm == 'Y') {
        // Записываем в файл
        file.write(reinterpret_cast<const char*>(&toy), sizeof(Toy));
        file.close();
        cout << "Игрушка добавлена в файл " << filename << endl;
    } else {
        file.close();
        cout << "Добавление отменено." << endl;
    }
}

double LabFile::calculateDoll(const std::string& filename, int targetAge) {
    ifstream file(filename, ios::binary);
    
    if (!file.is_open()) {
        cerr << "Ошибка: невозможно открыть файл " << filename << endl;
        return 0.0;
    }
    
    Toy toy;
    double totalCost = 0.0;
    int suitableDolls = 0;
    int totalToys = 0;
    int totalDolls = 0;
    
    cout << "\nПоиск кукол для возраста " << targetAge << " лет..." << endl;
    
    while (file.read(reinterpret_cast<char*>(&toy), sizeof(Toy))) {
        totalToys++;
        
        if (toy.isDoll) {
            totalDolls++;
            
            if (targetAge >= static_cast<int>(toy.minAge) && 
                targetAge <= static_cast<int>(toy.maxAge)) {
                
                suitableDolls++;
                totalCost += toy.price;
                
                cout << "\nНайдена кукла: " << endl;
                printToy(toy);
            }
        }
    }
    
    file.close();

    cout << "Всего игрушек в файле: " << totalToys << endl;
    cout << "Всего кукол в файле: " << totalDolls << endl;
    cout << "Кукол для возраста " << targetAge << " лет: " << suitableDolls << endl;

    return totalCost;
   
}