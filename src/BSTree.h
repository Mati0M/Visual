/**
 * @file BSTree.h
 * @brief Deklaracja (interfejs) klasy binarnego drzewa poszukiwań (BSTree).
 */

#ifndef BSTREE_H
#define BSTREE_H

#include <string>
#include <iosfwd>

class FileManager;

/**
 * @class BSTree
 * @brief Klasa implementująca strukturę binarnego drzewa poszukiwań (BST).
 * * Zarządza węzłami przechowującymi liczby całkowite, umożliwiając
 * operacje takie jak dodawanie, usuwanie, przeszukiwanie i wyświetlanie.
 */
class BSTree {

/**
 * @brief Deklaracja przyjaźni z klasą FileManager.
 * Umożliwia klasie FileManager dostęp do prywatnych pól (korzen)
 * i typów (Wezel) tej klasy w celu zapisu binarnego.
 */
friend class FileManager;

private:

    /**
     * @struct Wezel
     * @brief Prywatna struktura reprezentująca pojedynczy węzeł w drzewie.
     * * Przechowuje wartość (dane) oraz wskaźniki na lewe i prawe dziecko.
     */
    struct Wezel {
        /** @brief Wartość (liczba) przechowywana w węźle. */
        int dane;
        /** @brief Wskaźnik na lewe dziecko (mniejsze wartości). */
        Wezel* lewy;
        /** @brief Wskaźnik na prawe dziecko (większe wartości). */
        Wezel* prawy;

        /**
         * @brief Konstruktor węzła.
         * Ustawia podaną wartość i inicjalizuje wskaźniki na dzieci jako nullptr.
         * @param wartosc Liczba całkowita do przechowania w węźle.
         */
        Wezel(int wartosc) {
            dane = wartosc;
            lewy = nullptr
        }
    };

    /** @brief Wskaźnik na korzeń (główny węzeł) drzewa. Nullptr, jeśli drzewo jest puste. */
    Wezel* korzen;


    /** @brief Prywatny pomocnik rekurencyjny do dodawania węzłów. */
    Wezel* dodajHelper(Wezel* wezel, int wartosc);

    /** @brief Prywatny pomocnik rekurencyjny do usuwania węzłów. */
    Wezel* usunHelper(Wezel* wezel, int wartosc);

    /** @brief Prywatny pomocnik do znajdowania węzła o minimalnej wartości w poddrzewie. */
    Wezel* znajdzMin(Wezel* wezel);

    /** @brief Prywatny pomocnik rekurencyjny do zwalniania pamięci całego drzewa. */
    void wyczyscHelper(Wezel* wezel);

    /** @brief Prywatny pomocnik rekurencyjny do wyświetlania Preorder. */
    void preorderHelper(Wezel* wezel);
    
    /** @brief Prywatny pomocnik rekurencyjny do wyświetlania Inorder. */
    void inorderHelper(Wezel* wezel);
    
    /** @brief Prywatny pomocnik rekurencyjny do wyświetlania Postorder. */
    void postorderHelper(Wezel* wezel);

    /** @brief Prywatny pomocnik rekurencyjny do znajdowania i wyświetlania ścieżki. */
    bool znajdzSciezkeHelper(Wezel* wezel, int wartosc);
    
    /** @brief Prywatny pomocnik rekurencyjny do zapisu drzewa do strumienia (pliku). */
    void zapiszHelper(Wezel* wezel, std::ostream& plik);

    /** @brief Prywatny pomocnik rekurencyjny do "graficznego" wyświetlania struktury. */
    void wyswietlGraficznieHelper(Wezel* wezel, std::string wciecie, bool czyPrawy);


public:
    /**
     * @brief Konstruktor domyślny klasy BSTree.
     * Tworzy puste drzewo (korzen = nullptr).
     */
    BSTree();

    /**
     * @brief Destruktor klasy BSTree.
     * Automatycznie wywołuje metodę wyczysc() w celu zwolnienia pamięci.
     */
    ~BSTree();


    /**
     * @brief Dodaje nową wartość do drzewa BST.
     * @param wartosc Liczba całkowita do wstawienia.
     */
    void dodaj(int wartosc);

    /**
     * @brief Usuwa węzeł o podanej wartości z drzewa BST.
     * @param wartosc Liczba całkowita do usunięcia.
     */
    void usun(int wartosc);

    /**
     * @brief Usuwa wszystkie węzły z drzewa, zwalniając pamięć.
     */
    void wyczysc();

    /**
     * @brief Wyszukuje ścieżkę od korzenia do węzła o podanej wartości.
     * Ścieżka jest drukowana bezpośrednio do konsoli.
     * @param wartosc Wartość, do której szukana jest ścieżka.
     */
    void znajdzSciezke(int wartosc);

    /**
     * @brief Zapisuje zawartość drzewa do pliku tekstowego.
     * Wartości są zapisywane w kolejności Inorder (posortowane).
     * @param nazwaPliku Nazwa pliku wyjściowego.
     */
    void zapiszDoTekstowego(const std::string& nazwaPliku);


    /**
     * @brief Wyświetla zawartość drzewa w konsoli w kolejności Preorder.
     */
    void wyswietl_preorder();

    /**
     * @brief Wyświetla zawartość drzewa w konsoli w kolejności Inorder.
     * (Wynik będzie posortowany rosnąco).
     */
    void wyswietl_inorder();

    /**
     * @brief Wyświetla zawartość drzewa w konsoli w kolejności Postorder.
     */
    void wyswietl_postorder();
    
    /**
     * @brief Wyświetla strukturę drzewa w konsoli w formie "graficznej".
     * (Drzewo jest obrócone o 90 stopni).
     */
    void wyswietlGraficznie();

}; 

#endif // BSTREE_H