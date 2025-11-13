#include <iostream>     // Do obsługi wejścia/wyjścia (cin, cout)
#include <string>       // Do obsługi std::string
#include <limits>       // Do walidacji strumieni (cin.ignore)

// 1. Dołączamy OBUDWA pliki nagłówkowe
#include "BSTree.h"
#include "FileManager.h"

// --- Prototypy funkcji pomocniczych (Interfejs użytkownika) ---
void wyswietlMenu();
int pobierzLiczbe(const std::string& prompt);
std::string pobierzNazwePliku(const std::string& prompt);

// --- Prototypy funkcji-łączników (Wszystkie zaimplementowane) ---
void op_dodaj(BSTree& drzewo);
void op_usun(BSTree& drzewo);
void op_wyswietl(BSTree& drzewo);
void op_znajdzSciezke(BSTree& drzewo);
void op_wyczysc(BSTree& drzewo);
void op_zapiszTekst(BSTree& drzewo);

// Funkcje FileManagera
void op_wczytajTekst(BSTree& drzewo, FileManager& fm);
void op_zapiszBin(BSTree& drzewo, FileManager& fm);
void op_wczytajBin(BSTree& drzewo, FileManager& fm);


// === GŁÓWNA FUNKCJA PROGRAMU ===
int main() {
    
    // 2. Tworzymy obiekty OBU klas
    BSTree mojeDrzewo;
    FileManager managerPlikow; // Obiekt do zarządzania plikami

    std::cout << "--- Program Drzewo BST ---" << std::endl;
    std::cout << "Gotowy do pracy." << std::endl;

    while (true) {
        wyswietlMenu();
        int wybor = pobierzLiczbe("Wybierz opcję: ");

        // 3. Wszystkie opcje menu są w pełni funkcjonalne
        switch (wybor) {
            case 1:
                op_dodaj(mojeDrzewo);
                break;
            case 2:
                op_usun(mojeDrzewo);
                break;
            case 3:
                op_wyswietl(mojeDrzewo);
                break;
            case 4:
                op_znajdzSciezke(mojeDrzewo);
                break;
            case 5:
                op_wyczysc(mojeDrzewo);
                break;
            case 6: // Już nie jest [TODO]
                op_wczytajTekst(mojeDrzewo, managerPlikow); 
                break;
            case 7:
                op_zapiszTekst(mojeDrzewo);
                break;
            case 8: // Już nie jest [TODO]
                op_zapiszBin(mojeDrzewo, managerPlikow);
                break;
            case 9: // Już nie jest [TODO]
                op_wczytajBin(mojeDrzewo, managerPlikow);
                break;
            case 0:
                std::cout << "Do widzenia!" << std::endl;
                return 0;
            default:
                std::cout << "Niepoprawna opcja. Spróbuj ponownie." << std::endl;
                break;
        }

        std::cout << "\nNaciśnij Enter, aby kontynuować...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
}

// === Implementacje funkcji pomocniczych ===

void wyswietlMenu() {
    std::cout << "\n=== MENU ===" << std::endl;
    std::cout << "--- Drzewo ---" << std::endl;
    std::cout << "1. Dodaj element" << std::endl;
    std::cout << "2. Usuń element" << std::endl;
    std::cout << "3. Wyświetl drzewo (pre/in/post/graf)" << std::endl;
    std::cout << "4. Znajdź ścieżkę do elementu" << std::endl;
    std::cout << "5. Usuń całe drzewo" << std::endl;
    std::cout << "--- Pliki ---" << std::endl;
    std::cout << "6. Wczytaj drzewo z pliku tekstowego (liczby)" << std::endl;
    std::cout << "7. Zapisz drzewo do pliku tekstowego" << std::endl;
    std::cout << "8. Zapisz drzewo do pliku binarnego" << std::endl;
    std::cout << "9. Wczytaj drzewo z pliku binarnego" << std::endl;
    std::cout << "--- Program ---" << std::endl;
    std::cout << "0. Wyjście" << std::endl;
}

int pobierzLiczbe(const std::string& prompt) {
    int wartosc;
    std::cout << prompt;
    while (!(std::cin >> wartosc)) {
        std::cout << "Błąd. To nie jest liczba. Podaj poprawną liczbę: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return wartosc;
}

std::string pobierzNazwePliku(const std::string& prompt) {
    std::string nazwa;
    std::cout << prompt;
    std::cin >> nazwa;
    return nazwa;
}

// --- Funkcje operacji (bez zmian) ---
void op_dodaj(BSTree& drzewo) {
    int wartosc = pobierzLiczbe("Podaj wartość do dodania: ");
    drzewo.dodaj(wartosc); 
    std::cout << "Dodano." << std::endl;
}

void op_usun(BSTree& drzewo) {
    int wartosc = pobierzLiczbe("Podaj wartość do usunięcia: ");
    drzewo.usun(wartosc); 
}

void op_wyswietl(BSTree& drzewo) {
    std::cout << "Wybierz metodę wyświetlania:" << std::endl;
    std::cout << "1. Preorder" << std::endl;
    std::cout << "2. Inorder (posortowane)" << std::endl;
    std::cout << "3. Postorder" << std::endl;
    std::cout << "4. Graficznie (struktura)" << std::endl;
    
    int wybor = pobierzLiczbe("Wybór: ");
    switch (wybor) {
        case 1: drzewo.wyswietl_preorder(); break;
        case 2: drzewo.wyswietl_inorder(); break;
        case 3: drzewo.wyswietl_postorder(); break;
        case 4: drzewo.wyswietlGraficznie(); break;
        default: std::cout << "Nieznana opcja." << std::endl; break;
    }
}

void op_znajdzSciezke(BSTree& drzewo) {
    int wartosc = pobierzLiczbe("Podaj wartość do znalezienia: ");
    drzewo.znajdzSciezke(wartosc); 
}

void op_wyczysc(BSTree& drzewo) {
    drzewo.wyczysc(); 
    std::cout << "Drzewo zostało wyczyszczone." << std::endl;
}

void op_zapiszTekst(BSTree& drzewo) {
    std::string nazwa = pobierzNazwePliku("Podaj nazwę pliku .txt do zapisu: ");
    drzewo.zapiszDoTekstowego(nazwa); 
}


// 4. IMPLEMENTACJA FUNKCJI, KTÓRE BYŁY [TODO]
// Te funkcje zastąpiły stare "placeholdery"

void op_wczytajTekst(BSTree& drzewo, FileManager& fm) {
    std::string nazwa = pobierzNazwePliku("Podaj nazwę pliku .txt do wczytania: ");
    // Wywołanie metody z klasy FileManager
    fm.wczytajTekstowyDoDrzewa(drzewo, nazwa); 
}

void op_zapiszBin(BSTree& drzewo, FileManager& fm) {
    std::string nazwa = pobierzNazwePliku("Podaj nazwę pliku .bin do zapisu: ");
    // Wywołanie metody z klasy FileManager
    fm.zapiszBinarnie(drzewo, nazwa); 
}

void op_wczytajBin(BSTree& drzewo, FileManager& fm) {
    std::string nazwa = pobierzNazwePliku("Podaj nazwę pliku .bin do wczytania: ");
    
    // Metoda wczytajBinarnie() ZWRACA nowe drzewo.
    // Nadpisujemy nasze obecne drzewo tym nowym.
    drzewo = fm.wczytajBinarnie(nazwa); // Wywołanie metody z klasy FileManager
}