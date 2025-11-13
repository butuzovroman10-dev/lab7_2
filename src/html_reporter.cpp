#include "multiplication_algorithms.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <filesystem>

using namespace std;

void HTMLReporter::generateReport(const vector<TestResult>& results) {
    ofstream html_file("docs/report.html");
    
    html_file << R"(<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Отчет: Умножение больших чисел</title>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <style>
        body { 
            font-family: Arial, sans-serif; 
            margin: 0; 
            padding: 20px; 
            background-color: #f5f5f5; 
        }
        .container { 
            max-width: 1200px; 
            margin: 0 auto; 
            background: white; 
            padding: 20px; 
            border-radius: 10px; 
            box-shadow: 0 2px 10px rgba(0,0,0,0.1); 
        }
        h1, h2, h3 { 
            color: #333; 
            border-bottom: 2px solid #eee; 
            padding-bottom: 10px; 
        }
        .summary { 
            background: #e8f4fd; 
            padding: 15px; 
            border-radius: 5px; 
            margin: 20px 0; 
        }
        table { 
            width: 100%; 
            border-collapse: collapse; 
            margin: 20px 0; 
        }
        th, td { 
            border: 1px solid #ddd; 
            padding: 12px; 
            text-align: left; 
        }
        th { 
            background-color: #4CAF50; 
            color: white; 
        }
        tr:nth-child(even) { 
            background-color: #f2f2f2; 
        }
        .correct { color: green; font-weight: bold; }
        .incorrect { color: red; font-weight: bold; }
        .chart-container { 
            margin: 30px 0; 
            height: 400px; 
        }
        .conclusion { 
            background: #fff3cd; 
            padding: 15px; 
            border-radius: 5px; 
            margin: 20px 0; 
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>📊 Отчет по умножению больших чисел</h1>
        
        <div class="summary">
            <h2>🎯 Цель исследования</h2>
            <p>Сравнение производительности алгоритмов умножения больших чисел: наивного O(n²) и алгоритма Карацубы O(n^log₂3)</p>
        </div>
        
        <h2>📈 Результаты тестирования</h2>
        <table>
            <thead>
                <tr>
                    <th>Алгоритм</th>
                    <th>Размер входных данных</th>
                    <th>Время выполнения (мс)</th>
                    <th>Результат (первые 20 цифр)</th>
                    <th>Корректность</th>
                </tr>
            </thead>
            <tbody>
)";

    // Заполняем таблицу результатами
    for (const auto& result : results) {
        html_file << "<tr>\n";
        html_file << "<td>" << result.algorithm << "</td>\n";
        html_file << "<td>" << result.input_size << " цифр</td>\n";
        html_file << "<td>" << result.execution_time << " мс</td>\n";
        html_file << "<td>" << result.result << "</td>\n";
        html_file << "<td class='" << (result.correct ? "correct" : "incorrect") << "'>"
                 << (result.correct ? "✓ Корректно" : "✗ Ошибка") << "</td>\n";
        html_file << "</tr>\n";
    }

    html_file << R"(
            </tbody>
        </table>

        <div class="chart-container">
            <canvas id="performanceChart"></canvas>
        </div>

        <div class="conclusion">
            <h2>💡 Выводы и анализ</h2>
            <h3>Теоретическая сложность:</h3>
            <ul>
                <li><strong>Наивный алгоритм:</strong> O(n²) - квадратичная сложность</li>
                <li><strong>Алгоритм Карацубы:</strong> O(n^log₂3) ≈ O(n¹.⁵⁸) - субквадратичная сложность</li>
            </ul>
            
            <h3>Практические наблюдения:</h3>
            <ul>
                <li>Для малых чисел (до 100 цифр) наивный алгоритм может быть быстрее из-за накладных расходов рекурсии</li>
                <li>Для средних и больших чисел алгоритм Карацубы демонстрирует значительное превосходство</li>
                <li>При размерах 5000+ цифр разница в производительности становится особенно заметной</li>
            </ul>
            
            <h3>Рекомендации по выбору алгоритма:</h3>
            <ul>
                <li><strong>Малые числа (< 100 цифр):</strong> Наивный алгоритм</li>
                <li><strong>Средние числа (100-1000 цифр):</strong> Алгоритм Карацубы</li>
                <li><strong>Большие числа (> 1000 цифр):</strong> Алгоритм Карацубы или более продвинутые методы</li>
            </ul>
        </div>

        <h2>🔧 Методология тестирования</h2>
        <p>Тестирование проводилось на числах различной длины, генерируемых случайным образом. Для каждого теста:</p>
        <ul>
            <li>Измерялось время выполнения в миллисекундах</li>
            <li>Проверялась корректность результатов</li>
            <li>Сравнивалась производительность алгоритмов</li>
        </ul>
    </div>

    <script>
        // Данные для графика
        const results = )";

    // Генерируем JavaScript данные для графика
    html_file << "[";
    map<string, vector<pair<int, double>>> algorithm_data;
    for (const auto& result : results) {
        algorithm_data[result.algorithm].push_back({result.input_size, result.execution_time});
    }
    
    bool first_algorithm = true;
    for (const auto& [algorithm, data_points] : algorithm_data) {
        if (!first_algorithm) html_file << ",";
        first_algorithm = false;
        
        html_file << "{\n";
        html_file << "  label: '" << algorithm << "',\n";
        html_file << "  data: [";
        
        bool first_point = true;
        for (const auto& point : data_points) {
            if (!first_point) html_file << ",";
            first_point = false;
            html_file << "{x: " << point.first << ", y: " << point.second << "}";
        }
        
        html_file << "],\n";
        html_file << "  borderColor: '" << (algorithm.find("Naive") != string::npos ? "#ff6384" : "#36a2eb") << "',\n";
        html_file << "  backgroundColor: '" << (algorithm.find("Naive") != string::npos ? "#ff6384" : "#36a2eb") << "20',\n";
        html_file << "  fill: false\n";
        html_file << "}";
    }
    html_file << "];\n";

    html_file << R"(
        // Создание графика
        const ctx = document.getElementById('performanceChart').getContext('2d');
        new Chart(ctx, {
            type: 'line',
            data: {
                datasets: results
            },
            options: {
                responsive: true,
                maintainAspectRatio: false,
                scales: {
                    x: {
                        type: 'linear',
                        position: 'bottom',
                        title: {
                            display: true,
                            text: 'Размер входных данных (количество цифр)'
                        }
                    },
                    y: {
                        type: 'logarithmic',
                        title: {
                            display: true,
                            text: 'Время выполнения (мс)'
                        }
                    }
                },
                plugins: {
                    title: {
                        display: true,
                        text: 'Сравнение производительности алгоритмов умножения'
                    },
                    tooltip: {
                        callbacks: {
                            label: function(context) {
                                return context.dataset.label + ': ' + context.parsed.y.toFixed(2) + ' мс';
                            }
                        }
                    }
                }
            }
        });
    </script>
</body>
</html>)";

    html_file.close();
    cout << "HTML отчет сгенерирован: docs/report.html" << endl;
}

void HTMLReporter::generatePerformanceChart(const vector<TestResult>& results) {
    // Реализация уже включена в generateReport
}