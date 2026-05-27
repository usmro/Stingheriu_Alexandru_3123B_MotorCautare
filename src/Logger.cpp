#include "Logger.h"
#include <iostream>

Logger::Logger(const std::string& caleFisier) {
    fisierLog.open(caleFisier, std::ios::app);
}

Logger::~Logger() {
    if (fisierLog.is_open()) fisierLog.close();
}

void Logger::notificare(const std::string& mesaj) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::cout << "[INFO] " << mesaj << '\n';
    if (fisierLog.is_open()) fisierLog << "[INFO] " << mesaj << '\n';
}

void Logger::eroare(const std::string& mesaj) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::cerr << "[EROARE] " << mesaj << '\n';
    if (fisierLog.is_open()) fisierLog << "[EROARE] " << mesaj << '\n';
}