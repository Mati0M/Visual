#include <iostream>     // Do obsługi wejścia/wyjścia (cin, cout)
#include <string>       // Do obsługi std::string
#include <limits>       // Do walidacji strumieni (cin.ignore)

// -----------------------------------------------------------
// 1. PLIKI NAGŁÓWKOWE KLAS (NA RAZIE WYKOMENTOWANE)
// Zostaną odkomentowane, gdy utworzymy te pliki.
// #include "BSTree.h"
// #include "FileManager.h"
// -----------------------------------------------------------


// --- Prototypy funkcji pomocniczych (Interfejs użytkownika) ---

/**
 * @brief Wyświetla główne menu programu.
 */
void wyswietlMenu();

/**
 * @brief Pobiera od użytkownika liczbę całkowitą z walidacją.
 * @param prompt Tekst zachęty wyświetlany użytkownikowi.
 * @return Poprawnie wczytana liczba całkowita.
 */
int pobierzLiczbe(const std::string& prompt);


// -----------------------------------------------------------
// 2. PROTOTYPY FUNKCJI "PLACEHOLDER" (NA RAZIE PUSTE)
// Te funkcje będą później wywoływać metody z naszych klas.
// -----------------------------------------------------------
void op_dodaj();
void op_usun();
void op_wyswietl();
void op_znajdzSciezke();
void op_wyczysc();
void op_zapiszTekst();
void op_wczytajTekst();
void op_zapiszBin();
void op_wczytajBin();


// === GŁÓWNA FUNKCJA PROGRAMU ===
int main() {
    // 3. TWORZENIE OBIEKTÓW (NA RAZIE POMINIĘTE)
    // W tym miejscu później znajdą się:
    // BSTree mojeDrzewo;
    // FileManager managerPlikow;

    std::cout << "--- Program Drzewo BST (Wersja: SZKIELET) ---" << std::endl;

    // 4. Główna pętla programu (menu)
    while (true) {
        wyswietlMenu();
        int wybor = pobierzLiczbe("Wybierz opcję: ");

        // 5. Obsługa wyboru użytkownika (woła puste funkcje)
        switch (wybor) {
            case 1:
                op_dodaj();
                break;
            case 2:
                op_usun();
                break;
            case 3:
                op_wyswietl();
                break;
            case 4:
                op_znajdzSciezke();
                break;
            case 5:
                op_wyczysc();
                break;
            case 6:
                op_wczytajTekst();
                break;
            case 7:
                op_zapiszTekst();
                break;
            case 8:
                op_zapiszBin();
                break;
            case 9:
                op_wczytajBin();
                break;
            case 0:
                std::cout << "Do widzenia!" << std::endl;
                // 6. Zakończenie programu
                return 0;
            default:
                std::cout << "Niepoprawna opcja. Spróbuj ponownie." << std::endl;
                break;
        }

        std::cout << "\nNaciśnij Enter, aby kontynuować...";
        // Czeka na dowolny klawisz, aby użytkownik zdążył przeczytać wynik
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
    std::cout << "3. Wyświetl drzewo (pre/in/post)" << std::endl;
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
    // Pętla walidacji: działa dopóki użytkownik nie poda poprawnej liczby
    while (!(std::cin >> wartosc)) {
        std::cout << "Błąd. To nie jest liczba. Podaj poprawną liczbę: ";
        // Czyszczenie flag błędu strumienia cin
        std::cin.clear();
        // Ignorowanie błędnych danych w buforze (aż do znaku nowej linii)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return wartosc;
}

// -----------------------------------------------------------
// 7. IMPLEMENTACJE FUNKCJI "PLACEHOLDER"
// Na razie tylko wyświetlają komunikat, że opcja została wybrana.
// -----------------------------------------------------------

void op_dodaj() {
    std::cout << "-> Wybrano: Dodaj element (jeszcze nie zaimplementowano)" << std::endl;
}

void op_usun() {
    std::cout << "-> Wybrano: Usuń element (jeszcze nie zaimplementowano)" << std::endl;
}

void op_wyswietl() {
    std::cout << "-> Wybrano: Wyświetl drzewo (jeszcze nie zaimplementowano)" << std::endl;
}

void op_znajdzSciezke() {
    std::cout << "-> Wybrano: Znajdź ścieżkę (jeszcze nie zaimplementowano)" << std::endl;
}

void op_wyczysc() {
    std::cout << "-> Wybrano: Usuń całe drzewo (jeszcze nie zaimplementowano)" << std::endl;
}

void op_wczytajTekst() {
    std::cout << "-> Wybrano: Wczytaj z pliku tekstowego (jeszcze nie zaimplementowano)" << std::endl;
}

void op_zapiszTekst() {
    std::cout << "-> Wybrano: Zapisz do pliku tekstowego (jeszcze nie zaimplementowano)" << std::endl;
}

void op_zapiszBin() {
    std::cout << "-> Wybrano: Zapisz do pliku binarnego (jeszcze nie zaimplementowano)" << std::endl;
}

void op_wczytajBin() {
    std::cout << "-> Wybrano: Wczytaj z pliku binarnego (jeszcze nie zaimplementowano)" << std::endl;
}