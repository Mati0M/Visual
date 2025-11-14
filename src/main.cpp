/**
 * @file main.cpp
 * @brief Główny plik programu, obsługa menu i integracja klas BSTree i FileManager.
 */

#include <iostream>
#include <string>
#include <limits>

#include "BSTree.h"
#include "FileManager.h"

void wyswietlMenu();
int pobierzLiczbe(const std::string& prompt);
std::string pobierzNazwePliku(const std::string& prompt);

void op_dodaj(BSTree& drzewo);
void op_usun(BSTree& drzewo);
void op_wyswietl(BSTree& drzewo);
void op_znajdzSciezke(BSTree& drzewo);
void op_wyczysc(BSTree& drzewo);
void op_zapiszTekst(BSTree& drzewo);

void op_wczytajTekst(BSTree& drzewo, FileManager& fm);
void op_zapiszBin(BSTree& drzewo, FileManager& fm);
void op_wczytajBin(BSTree& drzewo, FileManager& fm);


/**
 * @brief Główna funkcja programu i punkt startowy.
 * * Inicjalizuje obiekty BSTree i FileManager, a następnie uruchamia 
 * główną pętlę menu, która obsługuje interakcje z użytkownikiem.
 * * @return 0 po poprawnym zakończeniu programu (wybór opcji '0').
 */
int main() {
    
    BSTree mojeDrzewo;
    FileManager managerPlikow; 

    std::cout << "--- Program Drzewo BST ---" << std::endl;
    std::cout << "Gotowy do pracy." << std::endl;

    while (true) {
        wyswietlMenu();
        int wybor = pobierzLiczbe("Wybierz opcję: ");

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
                op_wczytajTekst(mojeDrzewo, managerPlikow); 
                break;
            case 7:
                op_zapiszTekst(mojeDrzewo);
                break;
            case 8: 
                op_zapiszBin(mojeDrzewo, managerPlikow);
                break;
            case 9: 
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


/**
 * @brief Wyświetla w konsoli wszystkie dostępne opcje menu.
 */
void wyswietlMenu() {
    std::cout << "\n=== MENU ===" << std::endl;
    std::cout << "--- Drzewo ---" << std::endl;
    std::cout << "1. Dodaj element" << std::endl;
    std::cout << "2. Usuń element" << std::endl;
    std::cout << "3. Wyświetl drzewo (pre/in/post/graf)" << std::endl;
    std::cout << "4. Znajdź ścieżkę do elementu" << std::endl;
    std::cout << "5. Usuń całe drzewo" << std::endl;
    std::cout << "--- Pliki ---" << std::endl;
    std::cout << "6. Wczytaj drzewo z pliku tekstowego (liczby) [TODO]" << std::endl;
    std::cout << "7. Zapisz drzewo do pliku tekstowego" << std::endl;
    std::cout << "8. Zapisz drzewo do pliku binarnego" << std::endl;
    std::cout << "9. Wczytaj drzewo z pliku binarnego" << std::endl;
    std::cout << "--- Program ---" << std::endl;
    std::cout << "0. Wyjście" << std::endl;
}

/**
 * @brief Bezpiecznie pobiera od użytkownika liczbę całkowitą.
 * * Posiada walidację (pętlę), która wymusza podanie poprawnej liczby
 * i ignoruje błędne dane wejściowe (np. tekst).
 * * @param prompt Tekst zachęty wyświetlany użytkownikowi (np. "Podaj liczbę: ").
 * @return Poprawnie wczytana liczba całkowita.
 */
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

/**
 * @brief Pobiera od użytkownika nazwę pliku (jako pojedyncze słowo).
 * * @param prompt Tekst zachęty (np. "Podaj nazwę pliku: ").
 * @return Nazwa pliku jako std::string.
 */
std::string pobierzNazwePliku(const std::string& prompt) {
    std::string nazwa;
    std::cout << prompt;
    std::cin >> nazwa;
    return nazwa;
}

/**
 * @brief Obsługuje logikę opcji menu '1. Dodaj element'.
 * * Prosi użytkownika o wartość i wywołuje metodę `dodaj` na drzewie.
 * * @param drzewo Referencja do obiektu drzewa, do którego dodajemy.
 */
void op_dodaj(BSTree& drzewo) {
    int wartosc = pobierzLiczbe("Podaj wartość do dodania: ");
    drzewo.dodaj(wartosc); 
    std::cout << "Dodano." << std::endl;
}

/**
 * @brief Obsługuje logikę opcji menu '2. Usuń element'.
 * * Prosi użytkownika o wartość i wywołuje metodę `usun` na drzewie.
 * * @param drzewo Referencja do obiektu drzewa, z którego usuwamy.
 */
void op_usun(BSTree& drzewo) {
    int wartosc = pobierzLiczbe("Podaj wartość do usunięcia: ");
    drzewo.usun(wartosc); 
}

/**
 * @brief Obsługuje logikę opcji menu '3. Wyświetl drzewo'.
 * * Wyświetla pod-menu wyboru metody wyświetlania (Preorder, Inorder, itd.)
 * i wywołuje odpowiednią metodę na obiekcie drzewa.
 * * @param drzewo Referencja do obiektu drzewa do wyświetlenia.
 */
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

/**
 * @brief Obsługuje logikę opcji menu '4. Znajdź ścieżkę do elementu'.
 * * Prosi o wartość i wywołuje metodę `znajdzSciezke` na drzewie.
 * * @param drzewo Referencja do obiektu drzewa, w którym szukamy.
 */
void op_znajdzSciezke(BSTree& drzewo) {
    int wartosc = pobierzLiczbe("Podaj wartość do znalezienia: ");
    drzewo.znajdzSciezke(wartosc); 
}

/**
 * @brief Obsługuje logikę opcji menu '5. Usuń całe drzewo'.
 * * Wywołuje metodę `wyczysc` na drzewie.
 * * @param drzewo Referencja do drzewa, które ma być wyczyszczone.
 */
void op_wyczysc(BSTree& drzewo) {
    drzewo.wyczysc(); 
    std::cout << "Drzewo zostało wyczyszczone." << std::endl;
}

/**
 * @brief Obsługuje logikę opcji menu '7. Zapisz drzewo do pliku tekstowego'.
 * * Prosi o nazwę pliku i wywołuje metodę `zapiszDoTekstowego` na drzewie.
 * * @param drzewo Referencja do drzewa, które ma być zapisane.
 */
void op_zapiszTekst(BSTree& drzewo) {
    std::string nazwa = pobierzNazwePliku("Podaj nazwę pliku .txt do zapisu: ");
    drzewo.zapiszDoTekstowego(nazwa); 
}

/**
 * @brief Obsługuje logikę opcji menu '6. Wczytaj drzewo z pliku tekstowego'.
 * * Prosi o nazwę pliku i wywołuje metodę `wczytajTekstowyDoDrzewa` na managerze plików.
 * * @param drzewo Referencja do drzewa, do którego będą dodane elementy.
 * @param fm Referencja do obiektu FileManager.
 */
void op_wczytajTekst(BSTree& drzewo, FileManager& fm) {
    std::string nazwa = pobierzNazwePliku("Podaj nazwę pliku .txt do wczytania: ");
    fm.wczytajTekstowyDoDrzewa(drzewo, nazwa); 
}

/**
 * @brief Obsługuje logikę opcji menu '8. Zapisz drzewo do pliku binarnego'.
 * * Prosi o nazwę pliku i wywołuje metodę `zapiszBinarnie` na managerze plików.
 * * @param drzewo Referencja do drzewa, które ma być zapisane.
 * @param fm Referencja do obiektu FileManager.
 */
void op_zapiszBin(BSTree& drzewo, FileManager& fm) {
    std::string nazwa = pobierzNazwePliku("Podaj nazwę pliku .bin do zapisu: ");
    fm.zapiszBinarnie(drzewo, nazwa); 
}

/**
 * @brief Obsługuje logikę opcji menu '9. Wczytaj drzewo z pliku binarnego'.
 * * Prosi o nazwę pliku i wywołuje metodę `wczytajBinarnie`.
 * Następnie nadpisuje istniejący obiekt drzewa nowym, wczytanym drzewem.
 * * @param drzewo Referencja do drzewa, które zostanie nadpisane.
 * @param fm Referencja do obiektu FileManager.
 */
void op_wczytajBin(BSTree& drzewo, FileManager& fm) {
    std::string nazwa = pobierzNazwePliku("Podaj nazwę pliku .bin do wczytania: ");
    drzewo = fm.wczytajBinarnie(nazwa); 
}