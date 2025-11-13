#include "multiplication_algorithms.h"
#include "utils.h"
#include <random>
#include <fstream>
#include <iostream>

using namespace std;

// Генерация случайного числа заданной длины
string TestGenerator::generateRandomNumber(int digits) {
    if (digits <= 0) return "0";
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> first_digit_dist(1, 9);  // Первая цифра не может быть 0
    uniform_int_distribution<int> digit_dist(0, 9);        // Остальные цифры
    
    string number;
    number.push_back(first_digit_dist(gen) + '0');
    
    for (int i = 1; i < digits; i++) {
        number.push_back(digit_dist(gen) + '0');
    }
    
    return number;
}

// Создание тестовых пар чисел
void TestGenerator::generateTestCases() {
    // Создаем директории для тестовых данных
    createDirectory("data");
    createDirectory("data/test_cases");
    createDirectory("data/test_cases/small");
    createDirectory("data/test_cases/medium");
    createDirectory("data/test_cases/large");
    
    // Малые числа (10-100 цифр)
    vector<int> small_sizes = {10, 20, 50, 100};
    for (int size : small_sizes) {
        ofstream file("data/test_cases/small/test_" + to_string(size) + ".txt");
        string num1 = generateRandomNumber(size);
        string num2 = generateRandomNumber(size);
        file << num1 << endl << num2;
        file.close();
    }
    
    // Средние числа (100-1000 цифр)
    vector<int> medium_sizes = {200, 500, 1000};
    for (int size : medium_sizes) {
        ofstream file("data/test_cases/medium/test_" + to_string(size) + ".txt");
        string num1 = generateRandomNumber(size);
        string num2 = generateRandomNumber(size);
        file << num1 << endl << num2;
        file.close();
    }
    
    // Большие числа (1000-10000 цифр)
    vector<int> large_sizes = {2000, 5000, 10000};
    for (int size : large_sizes) {
        ofstream file("data/test_cases/large/test_" + to_string(size) + ".txt");
        string num1 = generateRandomNumber(size);
        string num2 = generateRandomNumber(size);
        file << num1 << endl << num2;
        file.close();
    }
    
    cout << "Тестовые данные сгенерированы в папке data/test_cases/" << endl;
}

// Получение тестовой пары чисел по категории размера
std::pair<std::string, std::string> TestGenerator::getTestPair(int size_category) {
    int size;
    
    switch (size_category) {
        case 0: // small
            size = 100;
            break;
        case 1: // medium
            size = 1000;
            break;
        case 2: // large
            size = 10000;
            break;
        default:
            size = 100;
    }
    
    // Генерируем числа нужного размера
    return {generateRandomNumber(size), generateRandomNumber(size)};
}