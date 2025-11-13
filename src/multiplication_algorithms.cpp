#include "multiplication_algorithms.h"
#include "utils.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

// Сложение двух больших чисел в строковом формате
string addStrings(const string& a, const string& b) {
    string result;
    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;
    
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    
    reverse(result.begin(), result.end());
    removeLeadingZeros(result);
    return result;
}

// Вычитание двух больших чисел (a >= b)
string subtractStrings(const string& a, const string& b) {
    if (a == b) return "0";
    
    string result;
    int borrow = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;
    
    while (i >= 0) {
        int digitA = a[i--] - '0' - borrow;
        int digitB = j >= 0 ? b[j--] - '0' : 0;
        
        if (digitA < digitB) {
            digitA += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.push_back((digitA - digitB) + '0');
    }
    
    // Удаляем ведущие нули
    removeLeadingZeros(result);
    return result;
}

// 1. Наивный алгоритм (школьный метод) - O(n²)
string naiveMultiply(const string& num1, const string& num2) {
    int n1 = num1.size();
    int n2 = num2.size();
    if (n1 == 0 || n2 == 0) return "0";
    if (num1 == "0" || num2 == "0") return "0";
    
    vector<int> result(n1 + n2, 0);
    
    for (int i = n1 - 1; i >= 0; i--) {
        for (int j = n2 - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + result[i + j + 1];
            
            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }
    
    string strResult;
    for (int num : result) {
        if (!(strResult.empty() && num == 0)) {
            strResult.push_back(num + '0');
        }
    }
    
    return strResult.empty() ? "0" : strResult;
}

// 2. Алгоритм Карацубы - O(n^log₂3)
string karatsubaMultiply(const string& x, const string& y) {
    // Приводим числа к одинаковой длине
    int n = max(x.length(), y.length());
    
    // Базовый случай - используем наивное умножение для маленьких чисел
    if (n <= 4) {
        return naiveMultiply(x, y);
    }
    
    // Дополняем числа нулями слева до одинаковой длины
    string a = x;
    string b = y;
    while (a.length() < n) a = "0" + a;
    while (b.length() < n) b = "0" + b;
    
    // Разбиваем числа на две части
    int mid = n / 2;
    int remain = n - mid;
    
    string a1 = a.substr(0, mid);
    string a0 = a.substr(mid, remain);
    string b1 = b.substr(0, mid);
    string b0 = b.substr(mid, remain);
    
    // Удаляем ведущие нули
    removeLeadingZeros(a1);
    removeLeadingZeros(a0);
    removeLeadingZeros(b1);
    removeLeadingZeros(b0);
    
    // Рекурсивно вычисляем три произведения
    string z2 = karatsubaMultiply(a1, b1);           // a1 * b1
    string z0 = karatsubaMultiply(a0, b0);           // a0 * b0
    
    // (a1 + a0) * (b1 + b0)
    string a1_plus_a0 = addStrings(a1, a0);
    string b1_plus_b0 = addStrings(b1, b0);
    string z1 = karatsubaMultiply(a1_plus_a0, b1_plus_b0);
    
    // z1 = (a1 + a0)(b1 + b0) - z2 - z0
    z1 = subtractStrings(z1, z2);
    z1 = subtractStrings(z1, z0);
    
    // Собираем результат: z2 * 10^(2*remain) + z1 * 10^remain + z0
    for (int i = 0; i < 2 * remain; i++) {
        z2 += "0";
    }
    for (int i = 0; i < remain; i++) {
        z1 += "0";
    }
    
    string result = addStrings(z2, z1);
    result = addStrings(result, z0);
    
    return result;
}