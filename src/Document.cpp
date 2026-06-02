#include "Document.h"
#include <fstream>
#include <cctype>
#include <vector>
#include <unordered_set> // Adăugat special pentru lista de Stop Words

Document::Document(const std::string& cale) : caleAbsoluta(cale) {}

void Document::adaugaObservator(IObserver* obs) {
    observatori.push_back(obs);
}

void Document::notificaObservatori(const std::string& mesaj) {
    for (auto obs : observatori) {
        obs->notificare(mesaj);
    }
}

std::string Document::getCale() const { return caleAbsoluta; }

const std::unordered_map<std::string, int>& Document::getCuvinte() const {
    return frecventaCuvinte;
}

// Secretul vitezei EXTREME: Citire binara in blocuri + Filtru Stop Words
void Document::analizeazaContinut() {
    std::ifstream fisier(caleAbsoluta, std::ios::binary);
    if (!fisier.is_open()) {
        notificaObservatori("EROARE CRITICA: Nu am putut deschide " + caleAbsoluta);
        return;
    }

    notificaObservatori("Am inceput analizarea (ULTRA-FAST + NLP) pentru: " + caleAbsoluta);

    // Dicționar de Stop Words (declarat static ca să fie creat o singură dată în memorie)
    static const std::unordered_set<std::string> stopWords = {
        "este", "sunt", "are", "sau", "dar", "iar", "daca", "pentru", 
        "din", "spre", "sub", "care", "cine", "cum", "cand",
        "nici", "deci", "insa", "totusi", "acesta", "aceasta"
    };

    const size_t DIMENSIUNE_BUFFER = 1048576; // 1 MB
    std::vector<char> buffer(DIMENSIUNE_BUFFER);
    
    std::string cuvantCurent;
    cuvantCurent.reserve(128); 

    while (fisier.read(buffer.data(), DIMENSIUNE_BUFFER) || fisier.gcount() > 0) {
        std::streamsize bytesCititi = fisier.gcount();
        
        for (std::streamsize i = 0; i < bytesCititi; ++i) {
            char c = buffer[i];
            
            if (std::isalnum(c) || c == '_') {
                cuvantCurent += std::tolower(c);
            } else if (!cuvantCurent.empty()) {
                
                // === AICI ESTE FILTRUL NOSTRU ===
                // Salvăm cuvântul DOAR dacă are minim 3 litere ȘI nu se află în lista de stopWords
                if (cuvantCurent.length() >= 3 && stopWords.find(cuvantCurent) == stopWords.end()) {
                    frecventaCuvinte[cuvantCurent]++;
                }
                
                cuvantCurent.clear();
            }
        }
    }

    // Verificăm ultimul cuvânt (în caz că fișierul se termină brusc fără un spațiu)
    if (!cuvantCurent.empty()) {
        if (cuvantCurent.length() >= 3 && stopWords.find(cuvantCurent) == stopWords.end()) {
            frecventaCuvinte[cuvantCurent]++;
        }
    }
    
    notificaObservatori("Analiza finalizata pentru: " + caleAbsoluta);
}