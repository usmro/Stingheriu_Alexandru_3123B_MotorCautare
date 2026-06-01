#include "Document.h"
#include <fstream>
#include <cctype>

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

void Document::analizeazaContinut() {
    std::ifstream fisier(caleAbsoluta);
    if (!fisier.is_open()) {
        notificaObservatori("EROARE CRITICA: Nu am putut deschide " + caleAbsoluta);
        return;
    }

    notificaObservatori("Am inceput analizarea (Fast-Mode) pentru: " + caleAbsoluta);

    std::string linie;
    std::string cuvantCurent;
    cuvantCurent.reserve(64); // Pre-alocăm memorie pentru a evita realocările lente

    // Citim linie cu linie - memoria RAM consumată este egală doar cu lungimea unei singure linii!
    while (std::getline(fisier, linie)) {
        for (char c : linie) {
            if (std::isalnum(c)) {
                // Construim cuvântul literă cu literă, convertit direct la litere mici
                cuvantCurent += std::tolower(c);
            } else if (!cuvantCurent.empty()) {
                // Am dat de un spațiu sau punctuație -> salvăm cuvântul în dicționar
                frecventaCuvinte[cuvantCurent]++;
                cuvantCurent.clear(); // Golim buffer-ul rapid
            }
        }
        // Verificăm ultimul cuvânt de pe linie
        if (!cuvantCurent.empty()) {
            frecventaCuvinte[cuvantCurent]++;
            cuvantCurent.clear();
        }
    }
    notificaObservatori("Analiza finalizata pentru: " + caleAbsoluta);
}