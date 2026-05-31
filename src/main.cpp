#include <iostream>
#include <filesystem>
#include <string>
#include <chrono>

#include "Logger.h"
#include "Document.h"
#include "Index.h"

namespace fs = std::filesystem;

int main() {
    Logger log("motor_cautare.log");
    log.notificare("=== APLICATIE PORNITA ===");

    Index indexulMeu;
    bool indexareEfectuata = false; // Ne asigurăm că nu caută înainte să indexeze
    long long ultimaDurataMs = 0;   // Pentru statistici
    int fisiereIndexate = 0;        // Pentru statistici

    while (true) {
        std::cout << "\n===================================================\n";
        std::cout << "       MOTOR DE CAUTARE - MENIU PRINCIPAL\n";
        std::cout << "===================================================\n";
        std::cout << "  [1] Indexeaza un director\n";
        std::cout << "  [2] Cauta un cuvant\n";
        std::cout << "  [3] Afiseaza statistici index\n";
        std::cout << "  [4] Iesire din aplicatie\n";
        std::cout << "===================================================\n";
        std::cout << "Alege o optiune (1-4): ";

        std::string optiune;
        std::getline(std::cin, optiune);

        if (optiune == "1") {
            // --- OPTIUNEA 1: INDEXARE ---
            std::cout << "\nIntrodu calea folderului (ex: . sau ./test_extrem): ";
            std::string caleFolder;
            std::getline(std::cin, caleFolder);

            if (!fs::exists(caleFolder) || !fs::is_directory(caleFolder)) {
                std::cerr << "[EROARE] Calea nu exista sau nu este un folder!\n";
                log.eroare("Cale invalida introdusa in meniu: " + caleFolder);
                continue; // Ne întoarcem la meniu
            }

            std::cout << "\nIndexez fisierele .txt... Te rog asteapta.\n";
            log.notificare("Incepem indexarea in: " + caleFolder);
            fisiereIndexate = 0;

            auto startTimp = std::chrono::high_resolution_clock::now();

            try {
                for (const auto& entry : fs::recursive_directory_iterator(caleFolder)) {
                    if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                        Document doc(entry.path().string());
                        doc.adaugaObservator(&log);
                        doc.analizeazaContinut();
                        indexulMeu.adaugaDocument(doc, log);
                        fisiereIndexate++;
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "\n[EXCEPTIE] " << e.what() << "\n";
            }

            auto stopTimp = std::chrono::high_resolution_clock::now();
            ultimaDurataMs = std::chrono::duration_cast<std::chrono::milliseconds>(stopTimp - startTimp).count();
            indexareEfectuata = true;

            std::cout << "[SUCCES] Indexare finalizata in " << ultimaDurataMs << " ms.\n";

        } 
        else if (optiune == "2") {
            // --- OPTIUNEA 2: CAUTARE ---
            if (!indexareEfectuata) {
                std::cout << "\n[!] Te rog sa indexezi un director (Optiunea 1) inainte de a cauta!\n";
                continue;
            }

            std::cout << "\n--- Mod Cautare (scrie 'inapoi' pentru a reveni la meniu) ---\n";
            while (true) {
                std::cout << "Cauta: ";
                std::string cuvantCautat;
                std::getline(std::cin, cuvantCautat);

                if (cuvantCautat == "inapoi" || cuvantCautat == "exit") {
                    break; // Iesim din bucla de căutare, ne întoarcem la meniu
                }

                if (!cuvantCautat.empty()) {
                    for (char& c : cuvantCautat) {
                        c = std::tolower(c);
                    }
                    indexulMeu.cautaCuvant(cuvantCautat, log);
                }
            }
        } 
        else if (optiune == "3") {
            // --- OPTIUNEA 3: STATISTICI ---
            std::cout << "\n--- Statistici Motor de Cautare ---\n";
            if (!indexareEfectuata) {
                std::cout << "Stare: Niciun folder nu a fost indexat inca.\n";
            } else {
                std::cout << "Fisiere scanate la ultima rulare: " << fisiereIndexate << "\n";
                std::cout << "Timp de procesare: " << ultimaDurataMs << " milisecunde\n";
                std::cout << "Cuvinte unice in memorie (RAM): " << indexulMeu.getNumarCuvinteUnice() << " cuvinte\n";
            }
            std::cout << "-----------------------------------\n";
            
            // Așteptăm un Enter ca să nu treacă direct la meniu
            std::cout << "Apasa Enter pentru a continua...";
            std::string dummy;
            std::getline(std::cin, dummy);
        } 
        else if (optiune == "4") {
            // --- OPTIUNEA 4: IESIRE ---
            std::cout << "\nInchidere aplicatie... La revedere!\n";
            log.notificare("=== APLICATIE INCHISA NORMAL ===");
            break; // Oprește bucla infinită, programul se termină
        } 
        else {
            std::cout << "\n[!] Optiune invalida. Te rog alege o cifra intre 1 si 4.\n";
        }
    }

    return 0;
}