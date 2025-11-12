#include <iostream>
#include <string>
#include <limits>

// 1. AKTUALIZACJA: Dołączamy plik nagłówkowy klasy drzewa
#include "BSTree.h"

// Plik FileManagera wciąż jest wykomentowany, bo go nie mamy
// #include "FileManager.h"


// --- Prototypy funkcji pomocniczych (Interfejs użytkownika) ---
void wyswietlMenu();
int pobierzLiczbe(const std::string& prompt);
std::string pobierzNazwePliku(const std::string& prompt);


// 2. AKTUALIZACJA: Zmieniamy prototypy, by przyjmowały obiekt drzewa
// Funkcje "placeholder" dla FileManagera zostają bez zmian
void op_dodaj(BSTree& drzewo);
void op_usun(BSTree& drzewo);
void op_wyswietl(BSTree& drzewo);
void op_znajdzSciezke(BSTree& drzewo);
void op_wyczysc(BSTree& drzewo);
void op_zapiszTekst(BSTree& drzewo);

void op_wczytajTekst(); // Placeholder
void op_zapiszBin();   // Placeholder
void op_wczytajBin();  // Placeholder


// === GŁÓWNA FUNKCJA PROGRAMU ===
int main() {
    
    // 3. AKTUALIZACJA: Tworzymy obiekt klasy BSTree!
    BSTree mojeDrzewo;

    // Obiekt FileManager wciąż jest wykomentowany
    // FileManager managerPlikow;

    std::cout << "--- Program Drzewo BST ---" << std::endl;
    std::cout << "Zintegrowano klase BSTree." << std::endl;

    while (true) {
        wyswietlMenu();
        int wybor = pobierzLiczbe("Wybierz opcję: ");

        // 4. AKTUALIZACJA: Przekazujemy 'mojeDrzewo' do funkcji
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
            case 6:
                // Ta opcja będzie wymagać FileManagera
                op_wczytajTekst(); 
                break;
            case 7:
                // Ta opcja jest zaimplementowana w BSTree
                op_zapiszTekst(mojeDrzewo);
                break;
            case 8:
                // Ta opcja będzie wymagać FileManagera
                op_zapiszBin();
                break;
            case 9:
                // Ta opcja będzie wymagać FileManagera
                op_wczytajBin();
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
    std::cout << "3. Wyświetl drzewo (pre/in/post)" << std::endl;
    std::cout << "4. Znajdź ścieżkę do elementu" << std::endl;
    std::cout << "5. Usuń całe drzewo" << std::endl;
    std::cout << "--- Pliki ---" << std::endl;
    std::cout << "6. Wczytaj drzewo z pliku tekstowego (liczby) [TODO]" << std::endl;
    std::cout << "7. Zapisz drzewo do pliku tekstowego" << std::endl;
    std::cout << "8. Zapisz drzewo do pliku binarnego [TODO]" << std::endl;
    std::cout << "9. Wczytaj drzewo z pliku binarnego [TODO]" << std::endl;
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

// Ta funkcja będzie potrzebna dla opcji 7
std::string pobierzNazwePliku(const std::string& prompt) {
    std::string nazwa;
    std::cout << prompt;
    std::cin >> nazwa;
    return nazwa;
}


// 5. AKTUALIZACJA: Implementacje funkcji wołają metody na obiekcie 'drzewo'

void op_dodaj(BSTree& drzewo) {
    int wartosc = pobierzLiczbe("Podaj wartość do dodania: ");
    drzewo.dodaj(wartosc); // WYWOŁANIE METODY KLASY
    std::cout << "Dodano." << std::endl;
}

void op_usun(BSTree& drzewo) {
    int wartosc = pobierzLiczbe("Podaj wartość do usunięcia: ");
    drzewo.usun(wartosc); // WYWOŁANIE METODY KLASY
}

void op_wyswietl(BSTree& drzewo) {
    std::cout << "Wybierz metodę wyświetlania:" << std::endl;
    std::cout << "1. Preorder (Korzeń, Lewy, Prawy)" << std::endl;
    std::cout << "2. Inorder (Lewy, Korzeń, Prawy - posortowane)" << std::endl;
    std::cout << "3. Postorder (Lewy, Prawy, Korzeń)" << std::endl;
    std::cout << "4. Graficznie (struktura)" << std::endl;
    
    int wybor = pobierzLiczbe("Wybór: ");
    switch (wybor) {
        case 1:
            drzewo.wyswietl_preorder(); // WYWOŁANIE METODY KLASY
            break;
        case 2:
            drzewo.wyswietl_inorder(); // WYWOŁANIE METODY KLASY
            break;
        case 3:
            drzewo.wyswietl_postorder(); // WYWOŁANIE METODY KLASY
            break;
        case 4:
            drzewo.wyswietlGraficznie(); // WYWOŁANIE METODY KLASY
            break;
        default:
            std::cout << "Nieznana opcja." << std::endl;
            break;
    }
}

void op_znajdzSciezke(BSTree& drzewo) {
    int wartosc = pobierzLiczbe("Podaj wartość do znalezienia: ");
    drzewo.znajdzSciezke(wartosc); // WYWOŁANIE METODY KLASY
}

void op_wyczysc(BSTree& drzewo) {
    drzewo.wyczysc(); // WYWOŁANIE METODY KLASY
    std::cout << "Drzewo zostało wyczyszczone." << std::endl;
}

void op_zapiszTekst(BSTree& drzewo) {
    std::string nazwa = pobierzNazwePliku("Podaj nazwę pliku (np. drzewo.txt): ");
    drzewo.zapiszDoTekstowego(nazwa); // WYWOŁANIE METODY KLASY
}

// 6. AKTUALIZACJA: Placeholdery dla FileManagera zostają
void op_wczytajTekst() {
    std::cout << "-> Wybrano: Wczytaj z pliku tekstowego (Wymaga FileManager)" << std::endl;
}

void op_zapiszBin() {
    std::cout << "-> Wybrano: Zapisz do pliku binarnego (Wymaga FileManager)" << std::endl;
}

void op_wczytajBin() {
    std::cout << "-> Wybrano: Wczytaj z pliku binarnego (Wymaga FileManager)" << std::endl;
}