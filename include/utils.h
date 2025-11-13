#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sys/stat.h>

// Вспомогательная функция для создания директорий
inline void createDirectory(const std::string& path) {
    #ifdef _WIN32
        _mkdir(path.c_str());
    #else
        mkdir(path.c_str(), 0777);
    #endif
}

// Вспомогательная функция для удаления ведущих нулей
inline void removeLeadingZeros(std::string& str) {
    size_t pos = str.find_first_not_of('0');
    if (pos != std::string::npos) {
        str = str.substr(pos);
    } else {
        str = "0";
    }
}

#endif