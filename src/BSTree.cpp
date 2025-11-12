// 1. Dołączenia niezbędnych bibliotek
#include "BSTree.h"     // Nasz plik nagłówkowy - "spis treści" klasy
#include <iostream>     // Dla operacji wejścia/wyjścia (cout)
#include <fstream>      // Dla operacji na plikach (ofstream)
#include <string>       // Dla std::string

// === KONSTRUKTOR I DESTRUKTOR ===

// 2. Konstruktor klasy
// Wywoływany, gdy tworzymy obiekt: BSTree mojeDrzewo;
// Ustawia korzeń na 'nullptr', bo drzewo jest puste.
BSTree::BSTree() {
    korzen = nullptr;
    // std::cout << "Drzewo utworzone (puste)." << std::endl; // Można odkomentować do testów
}

// 3. Destruktor klasy
// Wywoływany automatycznie, gdy obiekt jest niszczony (np. koniec programu)
// Musi posprzątać (zwolnić pamięć), inaczej mamy wyciek pamięci!
BSTree::~BSTree() {
    // std::cout << "Niszczenie drzewa..." << std::endl; // Można odkomentować do testów
    wyczysc(); // Używamy naszej publicznej funkcji do czyszczenia
}

// === METODY PUBLICZNE (INTERFEJS) ===
// To są "opakowania" dla metod prywatnych.
// Są proste i tylko wywołują funkcje pomocnicze,
// zaczynając od 'korzen'.

void BSTree::dodaj(int wartosc) {
    // Musimy zaktualizować 'korzen', na wypadek gdyby był 'nullptr'
    korzen = dodajHelper(korzen, wartosc);
}

void BSTree::usun(int wartosc) {
    korzen = usunHelper(korzen, wartosc);
}

void BSTree::wyczysc() {
    wyczyscHelper(korzen); // Wywołaj rekurencyjne czyszczenie
    korzen = nullptr;      // WAŻNE: Ustaw korzeń na nullptr po wyczyszczeniu
}

void BSTree::znajdzSciezke(int wartosc) {
    std::cout << "Sciezka do " << wartosc << ": ";
    // Wywołujemy pomocnika i sprawdzamy, czy coś znalazł
    if (znajdzSciezkeHelper(korzen, wartosc) == false) {
        std::cout << "Nie znaleziono elementu.";
    }
    std::cout << std::endl;
}

void BSTree::zapiszDoTekstowego(const std::string& nazwaPliku) {
    // 4. Otwieranie strumienia pliku
    std::ofstream plikWyjsciowy(nazwaPliku);

    // Sprawdzenie, czy plik otworzył się poprawnie
    if (!plikWyjsciowy.is_open()) {
        std::cout << "Blad: Nie mozna otworzyc pliku do zapisu!" << std::endl;
        return; // Zakończ funkcję, jeśli się nie udało
    }

    // Wywołaj pomocnika, przekazując mu strumień pliku
    zapiszHelper(korzen, plikWyjsciowy);

    // Zamknij plik po zakończeniu zapisu
    plikWyjsciowy.close();
    std::cout << "Zapisano drzewo do pliku: " << nazwaPliku << std::endl;
}


// --- Metody publiczne do wyświetlania ---

void BSTree::wyswietl_preorder() {
    std::cout << "Preorder: [ ";
    preorderHelper(korzen);
    std::cout << "]" << std::endl;
}

void BSTree::wyswietl_inorder() {
    std::cout << "Inorder: [ ";
    inorderHelper(korzen);
    std::cout << "]" << std::endl;
}

void BSTree::wyswietl_postorder() {
    std::cout << "Postorder: [ ";
    postorderHelper(korzen);
    std::cout << "]" << std::endl;
}

void BSTree::wyswietlGraficznie() {
    std::cout << "--- Struktura drzewa (obrocone o 90 stopni) ---" << std::endl;
    wyswietlGraficznieHelper(korzen, "", false);
    std::cout << "-----------------------------------------------" << std::endl;
}


// === METODY PRYWATNE (LOGIKA REKURENCYJNA) ===
// Tu dzieje się cała "magia".

// 5. Prywatny pomocnik: dodaj
// Używa rekurencji, by znaleźć odpowiednie miejsce (nullptr)
BSTree::Wezel* BSTree::dodajHelper(Wezel* wezel, int wartosc) {
    // 1. Przypadek bazowy: Znaleźliśmy puste miejsce.
    // Tworzymy nowy węzeł i zwracamy go, aby podłączyć go do rodzica.
    if (wezel == nullptr) {
        return new Wezel(wartosc); // new Wezel() wywołuje konstruktor struktury Wezel
    }

    // 2. Krok rekurencyjny: Idziemy w dół drzewa
    if (wartosc < wezel->dane) {
        // Idź w lewo i zaktualizuj wskaźnik lewego dziecka
        wezel->lewy = dodajHelper(wezel->lewy, wartosc);
    } else if (wartosc > wezel->dane) {
        // Idź w prawo i zaktualizuj wskaźnik prawego dziecka
        wezel->prawy = dodajHelper(wezel->prawy, wartosc);
    }
    // else (wartosc == wezel->dane) -> Duplikat, nic nie robimy

    // 3. Zwróć (niezmieniony) wskaźnik na węzeł
    return wezel;
}

// 6. Prywatny pomocnik: usuń
// Najbardziej skomplikowana funkcja
BSTree::Wezel* BSTree::usunHelper(Wezel* wezel, int wartosc) {
    // 1. Przypadek bazowy: Nie znaleziono węzła
    if (wezel == nullptr) {
        std::cout << "Nie znaleziono elementu " << wartosc << " do usuniecia." << std::endl;
        return nullptr;
    }

    // 2. Krok rekurencyjny: Szukanie węzła do usunięcia
    if (wartosc < wezel->dane) {
        wezel->lewy = usunHelper(wezel->lewy, wartosc);
    } else if (wartosc > wezel->dane) {
        wezel->prawy = usunHelper(wezel->prawy, wartosc);
    } 
    // 3. ZNALEZIONO WĘZEŁ (wezel->dane == wartosc)
    else {
        // PRZYPADEK 1: Węzeł jest liściem (nie ma dzieci)
        if (wezel->lewy == nullptr && wezel->prawy == nullptr) {
            delete wezel;    // Zwolnij pamięć
            return nullptr;   // Zwróć nullptr, aby rodzic wiedział, że dziecko zniknęło
        }
        // PRZYPADEK 2: Węzeł ma JEDNO dziecko (prawe LUB lewe)
        else if (wezel->lewy == nullptr) { // Ma tylko prawe dziecko
            Wezel* temp = wezel->prawy; // Zapisz wskaźnik na dziecko
            delete wezel;              // Usuń węzeł
            return temp;               // Zwróć dziecko, aby rodzic je "adoptował"
        }
        else if (wezel->prawy == nullptr) { // Ma tylko lewe dziecko
            Wezel* temp = wezel->lewy;
            delete wezel;
            return temp;
        }
        // PRZYPADEK 3: Węzeł ma DWOJE dzieci (najtrudniejszy)
        else {
            // Znajdź "następnika" - czyli najmniejszą wartość
            // w PRAWYM poddrzewie (tzw. następnik inorder)
            Wezel* nastepnik = znajdzMin(wezel->prawy);

            // Skopiuj dane następnika do obecnego węzła
            wezel->dane = nastepnik->dane;

            // Teraz usuń następnika z prawego poddrzewa
            // (Następnik na pewno będzie miał co najwyżej jedno prawe dziecko,
            // więc trafimy w PRZYPADEK 1 lub 2)
            wezel->prawy = usunHelper(wezel->prawy, nastepnik->dane);
        }
    }
    return wezel; // Zwróć wskaźnik na węzeł (po modyfikacjach)
}

// 7. Prywatny pomocnik: znajdź minimum
// Potrzebny do usuwania (Przypadek 3)
BSTree::Wezel* BSTree::znajdzMin(Wezel* wezel) {
    // W drzewie BST najmniejsza wartość jest zawsze
    // idąc maksymalnie w lewo.
    Wezel* obecny = wezel;
    while (obecny != nullptr && obecny->lewy != nullptr) {
        obecny = obecny->lewy;
    }
    return obecny;
}

// 8. Prywatny pomocnik: wyczysc
// Używa rekurencji (Postorder), aby bezpiecznie usunąć węzły
void BSTree::wyczyscHelper(Wezel* wezel) {
    // Przypadek bazowy
    if (wezel == nullptr) {
        return;
    }

    // Krok rekurencyjny:
    // 1. Najpierw usuń dzieci
    wyczyscHelper(wezel->lewy);
    wyczyscHelper(wezel->prawy);

    // 2. Na końcu usuń samego siebie
    // (Gdybyśmy usunęli siebie najpierw, stracilibyśmy wskaźniki do dzieci!)
    delete wezel;
}


// --- Pomocnicy do wyświetlania (rekurencja) ---

void BSTree::preorderHelper(Wezel* wezel) {
    if (wezel == nullptr) return;
    std::cout << wezel->dane << " "; // Korzeń
    preorderHelper(wezel->lewy);     // Lewy
    preorderHelper(wezel->prawy);    // Prawy
}

void BSTree::inorderHelper(Wezel* wezel) {
    if (wezel == nullptr) return;
    inorderHelper(wezel->lewy);      // Lewy
    std::cout << wezel->dane << " "; // Korzeń
    inorderHelper(wezel->prawy);     // Prawy
}

void BSTree::postorderHelper(Wezel* wezel) {
    if (wezel == nullptr) return;
    postorderHelper(wezel->lewy);    // Lewy
    postorderHelper(wezel->prawy);   // Prawy
    std::cout << wezel->dane << " "; // Korzeń
}

// 9. Prywatny pomocnik: szukanie ścieżki
bool BSTree::znajdzSciezkeHelper(Wezel* wezel, int wartosc) {
    // Przypadek bazowy 1: Nie ma takiego węzła
    if (wezel == nullptr) {
        return false;
    }

    // Drukujemy obecny węzeł na ścieżce
    std::cout << wezel->dane;

    // Przypadek bazowy 2: Znaleziono!
    if (wezel->dane == wartosc) {
        std::cout << " (Znaleziono)";
        return true;
    }

    // Krok rekurencyjny: Idziemy w dół
    std::cout << " -> "; // Strzałka do następnego węzła
    if (wartosc < wezel->dane) {
        return znajdzSciezkeHelper(wezel->lewy, wartosc);
    } else {
        return znajdzSciezkeHelper(wezel->prawy, wartosc);
    }
}

// 10. Prywatny pomocnik: zapis do pliku
// Użyjemy Inorder, aby plik był posortowany (jak w liczby.txt)
void BSTree::zapiszHelper(Wezel* wezel, std::ostream& plik) {
    if (wezel == nullptr) {
        return;
    }
    
    zapiszHelper(wezel->lewy, plik);    // Idź w lewo
    plik << wezel->dane << "\n";      // Zapisz węzeł (każdy w nowej linii)
    zapiszHelper(wezel->prawy, plik);   // Idź w prawo
}

// 11. Prywatny pomocnik: wyświetlanie graficzne
// To jest rekurencja "Reverse Inorder" (Prawo, Korzeń, Lewo)
void BSTree::wyswietlGraficznieHelper(Wezel* wezel, std::string wciecie, bool czyPrawy) {
    if (wezel == nullptr) {
        return;
    }

    // 1. Idź maksymalnie w prawo
    wyswietlGraficznieHelper(wezel->prawy, wciecie + "    ", true);

    // 2. Wydrukuj obecny węzeł
    std::cout << wciecie;
    if (czyPrawy) {
        std::cout << "/---"; // Gałąź idąca w górę (prawe dziecko)
    } else {
        std::cout << "\\---"; // Gałąź idąca w dół (lewe dziecko lub korzeń)
    }
    std::cout << wezel->dane << std::endl;

    // 3. Idź w lewo
    wyswietlGraficznieHelper(wezel->lewy, wciecie + "    ", false);
}