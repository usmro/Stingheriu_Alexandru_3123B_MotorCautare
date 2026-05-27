#include <iostream>
#include <filesystem>
#include <string>
#include <chrono> // Folosit pentru măsurarea vitezei de procesare

// Includem interfețele și clasele noastre
#include "Logger.h"
#include "Document.h"
#include "Index.h"

namespace fs = std::filesystem;

int main() {
    // 1. Inițializăm sistemul de logging
    Logger log("motor_cautare.log");
    log.notificare("=== START MOTOR DE CAUTARE ===");

    Index indexulMeu;
    std::string caleFolder;

    // 2. Interfața cu utilizatorul pentru folder
    std::cout << "=======================================\n";
    std::cout << "   Motor de Cautare Ultra-Rapid (OOP)  \n";
    std::cout << "=======================================\n\n";
    
    std::cout << "Introdu calea folderului pentru indexare (ex: . sau ./teste): ";
    std::getline(std::cin, caleFolder);

    // Validare robustă
    if (!fs::exists(caleFolder) || !fs::is_directory(caleFolder)) {
        log.eroare("Calea introdusa este invalida sau nu este un folder: " + caleFolder);
        std::cerr << "\n[EROARE] Calea nu exista sau nu este un folder!\n";
        return 1;
    }

    std::cout << "\nIndexez fisierele .txt... Te rog asteapta.\n";
    log.notificare("Incepem indexarea recursiva in: " + caleFolder);

    // Pornim cronometrul
    auto startTimp = std::chrono::high_resolution_clock::now();

    // 3. Parcurgerea folderelor și indexarea (Core Logic)
    try {
        for (const auto& entry : fs::recursive_directory_iterator(caleFolder)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                
                // Creăm documentul
                Document doc(entry.path().string());
                
                // Aplicăm Design Pattern-ul Observer: Logger-ul observă Documentul
                doc.adaugaObservator(&log);
                
                // Declanșăm citirea ultra-rapidă caracter cu caracter
                doc.analizeazaContinut();
                
                // Salvăm rezultatele în Inverted Index
                indexulMeu.adaugaDocument(doc, log);
            }
        }
    } catch (const std::exception& e) {
        log.eroare("Exceptie fatala la citirea folderelor: " + std::string(e.what()));
        std::cerr << "\n[EXCEPTIE] Eroare la citirea sistemului de fisiere!\n";
    }

    // Oprim cronometrul și calculăm durata
    auto stopTimp = std::chrono::high_resolution_clock::now();
    auto durata = std::chrono::duration_cast<std::chrono::milliseconds>(stopTimp - startTimp);
    
    std::cout << "---------------------------------------\n";
    std::cout << "[SUCCES] Indexare finalizata in " << durata.count() << " ms.\n";
    std::cout << "---------------------------------------\n";
    log.notificare("Indexare completata în " + std::to_string(durata.count()) + " ms.");

    // 4. Buclă interactivă pentru experiența utilizatorului
    std::cout << "\nScrie cuvantul pe care vrei sa-l cauti (sau 'exit' pentru a iesi).\n";
    
    std::string cuvantCautat;
    while (true) {
        std::cout << "\nCauta: ";
        std::getline(std::cin, cuvantCautat);

        // Condiție de ieșire
        if (cuvantCautat == "exit") {
            break;
        }

        // Evităm căutările goale (dacă utilizatorul dă doar Enter)
        if (!cuvantCautat.empty()) {
            // Convertim cuvântul căutat în litere mici pentru a se potrivi cu indexul
            for (char& c : cuvantCautat) {
                c = std::tolower(c);
            }
            indexulMeu.cautaCuvant(cuvantCautat, log);
        }
    }

    log.notificare("=== INCHIDERE MOTOR DE CAUTARE ===");
    std::cout << "La revedere!\n";

    return 0;
}