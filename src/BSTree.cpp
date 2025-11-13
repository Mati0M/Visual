/**
 * @file BSTree.cpp
 * @brief Implementacja (definicje metod) klasy BSTree.
 */

#include "BSTree.h"
#include <iostream>
#include <fstream>
#include <string>


/**
 * @brief Konstruktor domyślny klasy BSTree.
 * Inicjalizuje drzewo jako puste (korzeń wskazuje na nullptr).
 */
BSTree::BSTree() {
    korzen = nullptr;
}

/**
 * @brief Destruktor klasy BSTree.
 * Automatycznie zwalnia całą pamięć zajmowaną przez węzły drzewa,
 * wywołując metodę wyczysc().
 */
BSTree::~BSTree() {
    wyczysc();
}


/**
 * @brief Publiczna metoda dodająca nową wartość do drzewa.
 * Jest "opakowaniem" dla rekurencyjnej funkcji dodajHelper.
 * @param wartosc Liczba całkowita do wstawienia.
 */
void BSTree::dodaj(int wartosc) {
    korzen = dodajHelper(korzen, wartosc);
}

/**
 * @brief Publiczna metoda usuwająca węzeł o podanej wartości z drzewa.
 * Jest "opakowaniem" dla rekurencyjnej funkcji usunHelper.
 * @param wartosc Liczba całkowita do usunięcia.
 */
void BSTree::usun(int wartosc) {
    korzen = usunHelper(korzen, wartosc);
}

/**
 * @brief Publiczna metoda usuwająca wszystkie węzły z drzewa.
 * Drzewo staje się puste, a korzeń jest ustawiany na nullptr.
 */
void BSTree::wyczysc() {
    wyczyscHelper(korzen);
    korzen = nullptr;
}

/**
 * @brief Publiczna metoda szukająca ścieżki od korzenia do węzła.
 * Wyświetla ścieżkę w konsoli.
 * @param wartosc Wartość węzła, do którego szukamy ścieżki.
 */
void BSTree::znajdzSciezke(int wartosc) {
    std::cout << "Sciezka do " << wartosc << ": ";
    if (znajdzSciezkeHelper(korzen, wartosc) == false) {
        std::cout << "Nie znaleziono elementu.";
    }
    std::cout << std::endl;
}

/**
 * @brief Publiczna metoda zapisująca drzewo do pliku tekstowego.
 * Używa metody inorder (posortowanej) do zapisu.
 * @param nazwaPliku Nazwa pliku wyjściowego (np. "drzewo.txt").
 */
void BSTree::zapiszDoTekstowego(const std::string& nazwaPliku) {
    std::ofstream plikWyjsciowy(nazwaPliku);

    if (!plikWyjsciowy.is_open()) {
        std::cout << "Blad: Nie mozna otworzyc pliku do zapisu!" << std::endl;
        return;
    }

    zapiszHelper(korzen, plikWyjsciowy);

    plikWyjsciowy.close();
    std::cout << "Zapisano drzewo do pliku: " << nazwaPliku << std::endl;
}


/**
 * @brief Wyświetla drzewo w kolejności Preorder.
 */
void BSTree::wyswietl_preorder() {
    std::cout << "Preorder: [ ";
    preorderHelper(korzen);
    std::cout << "]" << std::endl;
}

/**
 * @brief Wyświetla drzewo w kolejności Inorder (posortowane).
 */
void BSTree::wyswietl_inorder() {
    std::cout << "Inorder: [ ";
    inorderHelper(korzen);
    std::cout << "]" << std::endl;
}

/**
 * @brief Wyświetla drzewo w kolejności Postorder.
 */
void BSTree::wyswietl_postorder() {
    std::cout << "Postorder: [ ";
    postorderHelper(korzen);
    std::cout << "]" << std::endl;
}

/**
 * @brief Wyświetla strukturę drzewa "graficznie" w konsoli (obrócone).
 */
void BSTree::wyswietlGraficznie() {
    std::cout << "--- Struktura drzewa (obrocone o 90 stopni) ---" << std::endl;
    wyswietlGraficznieHelper(korzen, "", false);
    std::cout << "-----------------------------------------------" << std::endl;
}


/**
 * @brief Prywatna, rekurencyjna funkcja pomocnicza do dodawania węzłów.
 * @param wezel Aktualny węzeł w rekurencji (zaczyna od korzenia).
 * @param wartosc Wartość do wstawienia.
 * @return Wskaźnik na węzeł (zaktualizowany, jeśli był nullptr).
 */
BSTree::Wezel* BSTree::dodajHelper(Wezel* wezel, int wartosc) {
    if (wezel == nullptr) {
        return new Wezel(wartosc);
    }

    if (wartosc < wezel->dane) {
        wezel->lewy = dodajHelper(wezel->lewy, wartosc);
    } else if (wartosc > wezel->dane) {
        wezel->prawy = dodajHelper(wezel->prawy, wartosc);
    }

    return wezel;
}

/**
 * @brief Prywatna, rekurencyjna funkcja pomocnicza do usuwania węzłów.
 * Obsługuje 3 przypadki: liść, węzeł z 1 dzieckiem, węzeł z 2 dzieci.
 * @param wezel Aktualny węzeł w rekurencji.
 * @param wartosc Wartość do usunięcia.
 * @return Wskaźnik na węzeł, który powinien zastąpić 'wezel' (lub sam 'wezel').
 */
BSTree::Wezel* BSTree::usunHelper(Wezel* wezel, int wartosc) {
    if (wezel == nullptr) {
        std::cout << "Nie znaleziono elementu " << wartosc << " do usuniecia." << std::endl;
        return nullptr;
    }

    if (wartosc < wezel->dane) {
        wezel->lewy = usunHelper(wezel->lewy, wartosc);
    } else if (wartosc > wezel->dane) {
        wezel->prawy = usunHelper(wezel->prawy, wartosc);
    } 
    else {
        if (wezel->lewy == nullptr && wezel->prawy == nullptr) {
            delete wezel;
            return nullptr;
        }
        else if (wezel->lewy == nullptr) {
            Wezel* temp = wezel->prawy;
            delete wezel;
            return temp;
        }
        else if (wezel->prawy == nullptr) {
            Wezel* temp = wezel->lewy;
            delete wezel;
            return temp;
        }
        else {
            Wezel* nastepnik = znajdzMin(wezel->prawy);
            wezel->dane = nastepnik->dane;
            wezel->prawy = usunHelper(wezel->prawy, nastepnik->dane);
        }
    }
    return wezel;
}

/**
 * @brief Prywatna funkcja pomocnicza znajdująca węzeł o najmniejszej wartości.
 * Potrzebna do usuwania węzła z dwójką dzieci.
 * @param wezel Węzeł, od którego zaczynamy szukanie (zazwyczaj korzeń prawego poddrzewa).
 * @return Wskaźnik na węzeł z najmniejszą wartością.
 */
BSTree::Wezel* BSTree::znajdzMin(Wezel* wezel) {
    Wezel* obecny = wezel;
    while (obecny != nullptr && obecny->lewy != nullptr) {
        obecny = obecny->lewy;
    }
    return obecny;
}

/**
 * @brief Prywatna, rekurencyjna funkcja pomocnicza do czyszczenia drzewa.
 * Używa kolejności Postorder, aby bezpiecznie zwolnić pamięć.
 * @param wezel Aktualny węzeł w rekurencji.
 */
void BSTree::wyczyscHelper(Wezel* wezel) {
    if (wezel == nullptr) {
        return;
    }
    wyczyscHelper(wezel->lewy);
    wyczyscHelper(wezel->prawy);
    delete wezel;
}


/**
 * @brief Prywatny pomocnik do wyświetlania Preorder (Korzeń, Lewy, Prawy).
 * @param wezel Aktualny węzeł w rekurencji.
 */
void BSTree::preorderHelper(Wezel* wezel) {
    if (wezel == nullptr) return;
    std::cout << wezel->dane << " ";
    preorderHelper(wezel->lewy);
    preorderHelper(wezel->prawy);
}

/**
 * @brief Prywatny pomocnik do wyświetlania Inorder (Lewy, Korzeń, Prawy).
 * @param wezel Aktualny węzeł w rekurencji.
 */
void BSTree::inorderHelper(Wezel* wezel) {
    if (wezel == nullptr) return;
    inorderHelper(wezel->lewy);
    std::cout << wezel->dane << " ";
    inorderHelper(wezel->prawy);
}

/**
 * @brief Prywatny pomocnik do wyświetlania Postorder (Lewy, Prawy, Korzeń).
 * @param wezel Aktualny węzeł w rekurencji.
 */
void BSTree::postorderHelper(Wezel* wezel) {
    if (wezel == nullptr) return;
    postorderHelper(wezel->lewy);
    postorderHelper(wezel->prawy);
    std::cout << wezel->dane << " ";
}

/**
 * @brief Prywatny pomocnik do znajdowania i wyświetlania ścieżki.
 * @param wezel Aktualny węzeł w rekurencji.
 * @param wartosc Szukana wartość.
 * @return true jeśli znaleziono, false jeśli nie.
 */
bool BSTree::znajdzSciezkeHelper(Wezel* wezel, int wartosc) {
    if (wezel == nullptr) {
        return false;
    }

    std::cout << wezel->dane;

    if (wezel->dane == wartosc) {
        std::cout << " (Znaleziono)";
        return true;
    }

    std::cout << " -> ";
    if (wartosc < wezel->dane) {
        return znajdzSciezkeHelper(wezel->lewy, wartosc);
    } else {
        return znajdzSciezkeHelper(wezel->prawy, wartosc);
    }
}

/**
 * @brief Prywatny pomocnik do zapisu drzewa do strumienia (pliku).
 * Używa kolejności Inorder.
 * @param wezel Aktualny węzeł w rekurencji.
 * @param plik Strumień wyjściowy (std::ostream), do którego zapisujemy dane.
 */
void BSTree::zapiszHelper(Wezel* wezel, std::ostream& plik) {
    if (wezel == nullptr) {
        return;
    }
    zapiszHelper(wezel->lewy, plik);
    plik << wezel->dane << "\n";
    zapiszHelper(wezel->prawy, plik);
}

/**
 * @brief Prywatny pomocnik do "graficznego" wyświetlania struktury.
 * Używa "odwróconego Inorder" (Reverse Inorder).
 * @param wezel Aktualny węzeł w rekurencji.
 * @param wciecie Ciąg znaków (spacje) reprezentujący poziom wcięcia.
 * @param czyPrawy Flaga informująca, czy węzeł jest prawym dzieckiem.
 */
void BSTree::wyswietlGraficznieHelper(Wezel* wezel, std::string wciecie, bool czyPrawy) {
    if (wezel == nullptr) {
        return;
    }

    wyswietlGraficznieHelper(wezel->prawy, wciecie + "    ", true);

    std::cout << wciecie;
    if (czyPrawy) {
        std::cout << "/---";
    } else {
        std::cout << "\\---";
    }
    std::cout << wezel->dane << std::endl;

    wyswietlGraficznieHelper(wezel->lewy, wciecie + "    ", false);
}