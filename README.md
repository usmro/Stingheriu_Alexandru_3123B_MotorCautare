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
```

## Compilare și Rulare

1. Clonați repository-ul

Descărcați proiectul local folosind Git:
```bash
git clone <url-repository>
cd POO_MotorCautare
```

2. Compilați proiectul

Proiectul se compilează automat folosind Makefile-ul inclus, care aplică flag-uri de optimizare extremă (-O3)
```bash
make
```

3. Rulați aplicația

Executabilul va fi creat în rădăcina proiectului. Porniți aplicația cu comanda:
```bash
./motor_cautare
```


## Organizarea și Conceptele POO

Arhitectura proiectului respectă principiile fundamentale ale Programării Orientate pe Obiecte (POO):

* Încapsulare: Datele interne ale claselor (Index, Document) sunt protejate și accesibile doar prin metode publice.
* Polimorfism și Moștenire: Implementate prin Design Pattern-ul Observer. Interfața IObserver este moștenită de clasa Logger, permițând decuplarea logicii de parsare de cea de jurnalizare.
* Gestionarea Excepțiilor: Folosirea blocurilor try-catch previne blocajele în cazul citirii unor fișiere cu permisiuni restricționate.
