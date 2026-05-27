#include "Index.h"
#include <iostream>

using namespace std;

void Index::adaugaDocument(const Document& doc, Logger& log) {
    const auto& cuvinteDocument = doc.getCuvinte();
    string caleDoc = doc.getCale();

    // Iterăm prin cuvintele unice găsite în acest document specific
    for (const auto& pereche : cuvinteDocument) {
        const string& cuvant = pereche.first;
        int frecventa = pereche.second;
        
        // Populăm indexul global
        dictionar[cuvant][caleDoc] = frecventa;
    }
    
    // Înregistrăm acțiunea folosind metoda 'notificare' cerută de IObserver
    log.notificare("Document integrat in indexul global: " + caleDoc);
}

void Index::cautaCuvant(const string& cuvantCautat, Logger& log) {
    log.notificare("Utilizatorul a cautat cuvantul: " + cuvantCautat);
    
    // Căutare ultra-rapidă folosind tabela de dispersie (hash table)
    auto it = dictionar.find(cuvantCautat);
    
    if (it != dictionar.end()) {
        cout << "\n>>> Cuvantul '" << cuvantCautat << "' a fost gasit in " << it->second.size() << " document(e):\n";
        
        // Afișăm fiecare document în care apare și frecvența
        for (const auto& doc_info : it->second) {
            cout << "    -> " << doc_info.first << " (de " << doc_info.second << " ori)\n";
        }
    } else {
        cout << "\n>>> Cuvantul '" << cuvantCautat << "' NU a fost gasit in niciun document indexat.\n";
    }
    cout << "---------------------------------------\n";
}