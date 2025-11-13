#include "multiplication_algorithms.h"
#include "utils.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>

using namespace std;
using namespace std::chrono;

// Сравнительное тестирование двух алгоритмов
vector<TestResult> PerformanceTester::runComparativeTest(
    const string& num1, const string& num2) {
    
    vector<TestResult> results;
    
    // Тестирование наивного алгоритма
    cout << "Запуск наивного алгоритма..." << endl;
    auto start = high_resolution_clock::now();
    string naive_result = naiveMultiply(num1, num2);
    auto end = high_resolution_clock::now();
    double naive_time = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    results.push_back({
        "Naive O(n²)",
        (int)num1.length(),
        naive_time,
        naive_result.substr(0, 20) + "...",
        true
    });
    
    // Тестирование алгоритма Карацубы
    cout << "Запуск алгоритма Карацубы..." << endl;
    start = high_resolution_clock::now();
    string karatsuba_result = karatsubaMultiply(num1, num2);
    end = high_resolution_clock::now();
    double karatsuba_time = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    // Проверка корректности
    bool is_correct = PerformanceTester::validateResult(naive_result, karatsuba_result);
    
    results.push_back({
        "Karatsuba O(n^log₂3)",
        (int)num1.length(),
        karatsuba_time,
        karatsuba_result.substr(0, 20) + "...",
        is_correct
    });
    
    return results;
}

// Генерация полного отчета производительности
void PerformanceTester::generatePerformanceReport(int max_digits) {
    vector<TestResult> all_results;
    vector<int> test_sizes = {10, 50, 100, 200, 500, 1000, 2000};
    
    // Создаем директорию для результатов
    createDirectory("data");
    createDirectory("data/results");
    
    ofstream csv_file("data/results/performance_data.csv");
    csv_file << "Algorithm,InputSize,ExecutionTime,Correct\n";
    
    for (int size : test_sizes) {
        if (size > max_digits) break;
        
        cout << "Тестирование на числах длиной " << size << " цифр..." << endl;
        
        string num1 = TestGenerator::generateRandomNumber(size);
        string num2 = TestGenerator::generateRandomNumber(size);
        
        auto results = runComparativeTest(num1, num2);
        
        for (const auto& result : results) {
            all_results.push_back(result);
            csv_file << result.algorithm << ","
                    << result.input_size << ","
                    << result.execution_time << ","
                    << (result.correct ? "true" : "false") << "\n";
        }
    }
    
    csv_file.close();
    
    // Генерируем HTML отчет
    HTMLReporter::generateReport(all_results);
}

// Валидация результатов
bool PerformanceTester::validateResult(const string& result1, const string& result2) {
    // Удаляем ведущие нули для сравнения
    string r1 = result1;
    string r2 = result2;
    removeLeadingZeros(r1);
    removeLeadingZeros(r2);
    
    bool is_equal = (r1 == r2);
    
    if (!is_equal) {
        cout << "ОШИБКА: Результаты алгоритмов не совпадают!" << endl;
        cout << "Наивный:    " << r1.substr(0, 50) << "..." << endl;
        cout << "Карацубы: " << r2.substr(0, 50) << "..." << endl;
    }
    
    return is_equal;
}