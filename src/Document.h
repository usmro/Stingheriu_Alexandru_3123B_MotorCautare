#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "Observer.h"

class Document {
private:
    std::string caleAbsoluta;
    std::unordered_map<std::string, int> frecventaCuvinte;
    std::vector<IObserver*> observatori; // Lista de observatori

    // Funcție privată pentru a curăța și transforma în litere mici
    inline void proceseazaCuvant(std::string& cuvant);

public:
    Document(const std::string& cale);
    
    void adaugaObservator(IObserver* obs);
    void notificaObservatori(const std::string& mesaj);

    std::string getCale() const;
    const std::unordered_map<std::string, int>& getCuvinte() const;
    
    // Aceasta este funcția ultra-optimizată
    void analizeazaContinut();
};