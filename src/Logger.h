#pragma once
#include "Observer.h"
#include <fstream>
#include <mutex>

class Logger : public IObserver {
private:
    std::ofstream fisierLog;
    // Mutex pentru a preveni erorile dacă adaugi multithreading ulterior
    std::mutex logMutex; 

public:
    Logger(const std::string& caleFisier);
    ~Logger() override;
    
    // Suprascrierea metodei din interfață
    void notificare(const std::string& mesaj) override;
    
    // Funcții specifice
    void eroare(const std::string& mesaj);
};