#pragma once
#include <string>
#include <unordered_map>
#include "Document.h"
#include "Logger.h"

class Index {
private:
    // Structura optimizată pentru index inversat:
    // Cuvânt -> {Cale_Document -> Număr_Apariții}
    std::unordered_map<std::string, std::unordered_map<std::string, int>> dictionar;

public:
    // Preia datele dintr-un document analizat și le integrează în dicționarul general
    void adaugaDocument(const Document& doc, Logger& log);
    
    // Caută cuvântul instantaneu (O(1)) și afișează rezultatele
    void cautaCuvant(const std::string& cuvantCautat, Logger& log);
    size_t getNumarCuvinteUnice() const;
};