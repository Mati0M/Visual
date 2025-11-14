/**
 * @file FileManager.h
 * @brief Deklaracja (interfejs) klasy FileManager.
 * @details Klasa ta odpowiada za operacje wejścia/wyjścia,
 * w tym wczytywanie i zapisywanie drzewa BST do plików.
 */

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include "BSTree.h" 
#include <iosfwd>

/**
 * @class FileManager
 * @brief Klasa narzędziowa do obsługi operacji plikowych dla drzewa BST.
 * * Zapewnia metody do serializacji (zapisu) i deserializacji (odczytu)
 * drzewa do/z formatu tekstowego i binarnego.
 */
class FileManager {

private:
    /**
     * @brief Prywatny rekurencyjny pomocnik do zapisu binarnego.
     * * Zapisuje drzewo do strumienia w kolejności Preorder, co
     * gwarantuje odtworzenie tej samej struktury drzewa.
     * @param wezel Aktualny węzeł w rekurencji (zaczynając od korzenia).
     * @param plik Strumień wyjściowy (std::ostream) otwarty w trybie binarnym.
     */
    void zapiszBinarnieHelper(BSTree::Wezel* wezel, std::ostream& plik);

public:
    /**
     * @brief Wczytuje liczby z pliku tekstowego i dodaje je do drzewa.
     * * Otwiera plik tekstowy i dodaje każdą znalezioną liczbę
     * do istniejącego obiektu drzewa.
     * @param drzewo Referencja do obiektu BSTree, który ma być zmodyfikowany.
     * @param nazwaPliku Nazwa pliku .txt do wczytania.
     */
    void wczytajTekstowyDoDrzewa(BSTree& drzewo, const std::string& nazwaPliku);

    /**
     * @brief Zapisuje całą strukturę drzewa do pliku binarnego.
     * * Wykorzystuje prywatną funkcję pomocniczą do rekurencyjnego
     * zapisu w kolejności Preorder.
     * @param drzewo Referencja do drzewa, które ma być zapisane.
     * @param nazwaPliku Nazwa pliku wyjściowego (np. "drzewo.bin").
     */
    void zapiszBinarnie(BSTree& drzewo, const std::string& nazwaPliku);

    /**
     * @brief Wczytuje strukturę drzewa z pliku binarnego.
     * * Tworzy i zwraca *nowy* obiekt BSTree, odtworzony z pliku binarnego.
     * * Zakłada, że plik został zapisany w kolejności Preorder.
     * @param nazwaPliku Nazwa pliku binarnego do wczytania.
     * @return Nowy obiekt BSTree odtworzony z pliku.
     */
    BSTree wczytajBinarnie(const std::string& nazwaPliku);

};

#endif // FILEMANAGER_H