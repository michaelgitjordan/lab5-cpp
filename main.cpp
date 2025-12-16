#include "files.h"
#include <iostream>
#include <limits>
#include <string>
#include <fstream>

using namespace std;

void createTestFile() {
    cout << "Создание тестового файла" << endl;
    
    cout << "Выберите тип тестового файла:" << endl;
    cout << "1. Маленький (5 чисел, 1-10)" << endl;
    cout << "2. Средний (10 чисел, 1-100)" << endl;
    cout << "3. Большой (20 чисел, -50-50)" << endl;
    cout << "Выбор (1-3): ";
    
    int choice;
    cin >> choice;
    
    switch (choice) {
        case 1:
            LabFile::fillWithRandom("test_small.bin", 5, 1, 10);
            break;
        case 2:
            LabFile::fillWithRandom("test_medium.bin", 10, 1, 100);
            break;
        case 3:
            LabFile::fillWithRandom("test_large.bin", 20, -50, 50);
            break;
        default:
            cout << "Неверный выбор." << endl;
    }
}

void executeTask1() {
    cout << "Выполнение задания 1: " << endl;
    cout << "Введите имя файла: ";
    
    string filename;
    cin >> filename;
    
    cout << "\nАнализ файла: " << filename << endl;
    int result = LabFile::findDiff(filename);
    
    if (result != 0 || cin) {
        cout << "Задание 1 выполнено успешно!" << endl;
    }
}

void workWithToyFile() {
    cout << "Работа с файлом игрушек" << endl;
    cout << "1. Создать новый файл" << endl;
    cout << "2. Добавить игрушку в файл" << endl;
    cout << "Выбор (1-2): ";
    
    int choice;
    cin >> choice;
    
    string filename;
    cout << "Введите имя файла: ";
    cin >> filename;
    
    if (choice == 1) {
        LabFile::createToyFile(filename);
    } else if (choice == 2) {
        LabFile::addToyToFile(filename);
    } else {
        cout << "Неверный выбор." << endl;
    }
}

void executeTask3() {
    cout << "Выполнение задания 3" << endl;
    cout << "Введите имя файла с игрушками: ";
    
    string filename;
    cin >> filename;
    
    int targetAge = 6;
    cout << "Введите возраст для поиска (по умолчанию 6): ";
    
    // Проверяем, ввел ли пользователь возраст
    string input;
    cin >> input;
    
    try {
        targetAge = stoi(input);
    } catch (...) {
        // Если не число, используем значение по умолчанию
        targetAge = 6;
    }
    
    cout << "\nПоиск кукол для возраста " << targetAge << " лет..." << endl;
    LabFile::calculateDoll(filename, targetAge);
}


// Главная функция
int main() {
    cout << "Лабораторная 5: " << endl;
    
    int choice = -1;
    
    while(choice != 0) {
        cout << "\nГЛАВНОЕ МЕНЮ:" << endl;
        cout << "1. Создать тестовый числовой файл" << endl;
        cout << "2. Выполнить задание 1 (разность)" << endl;
        cout << "3. Работа с файлом игрушек" << endl;
        cout << "4. Выполнить задание 3 (стоимость кукол)" << endl;
        cout << "0. Выход" << endl;
        cout << "Выбор (0-5): ";
        
        cin >> choice;
        
        // Очистка буфера ввода
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                createTestFile();
                break;
            case 2:
                executeTask1();
                break;
            case 3:
                workWithToyFile();
                break;
            case 4:
                executeTask3();
                break;
            case 0:
                cout << "Выход из программы..." << endl;
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    }
    
    cout << "\nПрограмма завершена." << endl;
    return 0;
}