#ifndef MULTIPLICATION_ALGORITHMS_H
#define MULTIPLICATION_ALGORITHMS_H

#include <string>
#include <vector>
#include <chrono>

// Вспомогательные функции
std::string addStrings(const std::string& a, const std::string& b);
std::string subtractStrings(const std::string& a, const std::string& b);

// Алгоритмы умножения
std::string naiveMultiply(const std::string& num1, const std::string& num2);
std::string karatsubaMultiply(const std::string& x, const std::string& y);

// Структура для хранения результатов тестов
struct TestResult {
    std::string algorithm;
    int input_size;
    double execution_time;
    std::string result;
    bool correct;
};

// Класс для генерации тестовых данных
class TestGenerator {
public:
    static std::string generateRandomNumber(int digits);
    static void generateTestCases();
    static std::pair<std::string, std::string> getTestPair(int size_category);
};

// Класс для тестирования производительности
class PerformanceTester {
public:
    static std::vector<TestResult> runComparativeTest(
        const std::string& num1, const std::string& num2);
    static void generatePerformanceReport(int max_digits);
    static bool validateResult(const std::string& result1, const std::string& result2);
};

// Класс для генерации HTML-отчета
class HTMLReporter {
public:
    static void generateReport(const std::vector<TestResult>& results);
    static void generatePerformanceChart(const std::vector<TestResult>& results);
};

#endif