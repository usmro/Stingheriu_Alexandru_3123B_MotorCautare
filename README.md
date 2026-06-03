# Motor de Căutare

Acesta este un proiect de motor de căutare ultra-rapid în C++, care indexează fișiere text dintr-un director și permite utilizatorului să caute cuvinte în acele fișiere. Proiectul este dezvoltat sub forma unei aplicații de tip consolă (CLI) interactive și folosește structuri de date avansate (Inverted Index) pentru performanță maximă.

## Caracteristici

* **Indexare ultra-rapidă:** Citirea fișierelor se face binar, în blocuri de memorie (Buffered I/O), minimizând timpul de acces la hard disk.
* **Structuri de date eficiente:** Căutarea se realizează în timp constant O(1) folosind tabele de dispersie (`std::unordered_map`).
* **Filtru NLP (Stop Words):** Sistemul ignoră automat cuvintele sub 3 litere și cuvintele de legătură (ex: "este", "pentru", "daca") pentru a optimiza masiv consumul de memorie RAM.
* **Meniu Interactiv:** Utilizatorul poate naviga ușor prin opțiunile aplicației (indexare, căutare, afișare statistici performanță, ieșire).
* **Comenzi speciale de ieșire:** Folosirea comenzii `!meniu` în modul de căutare pentru o ieșire sigură și intuitivă.
* **Logging:** Înregistrarea acțiunilor și erorilor într-un fișier `motor_cautare.log`, implementat folosind modelul de proiectare Observer (Polimorfism).

## Dependințe

Pentru a compila și rula acest proiect, veți avea nevoie de următoarele:

* **Git**
* **GNU Make** (pentru automatizarea compilării)
* **Un compilator C++17** (de ex., GCC, G++)

Spre deosebire de alte implementări, acest proiect este complet "vanilla" și nu necesită librării externe complicate (precum OpenGL sau GLFW), fiind optimizat pentru a rula nativ în orice mediu Linux/WSL.

### Instalarea Dependințelor 

Dacă folosiți o distribuție bazată pe Debian/Ubuntu (sau WSL), puteți instala dependințele de bază folosind:

```bash
sudo apt-get update
sudo apt-get install build-essential git

