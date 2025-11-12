// 1. Strażnik (Header Guard)
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

// 2. Dołączenia bibliotek
#include <string> // Dla std::string

// 3. Dołączenie pełnej definicji BSTree
// MUSIMY to zrobić, ponieważ nasza funkcja pomocnicza (poniżej)
// będzie potrzebowała znać prywatny typ `BSTree::Wezel`.
// To jest jedna z kluczowych poprawek.
#include "BSTree.h" 

// 4. Deklaracja wyprzedzająca dla strumienia
// (Zamiast dołączać cały <iostream> lub <fstream>)
#include <iosfwd>

// 5. Deklaracja klasy FileManager
class FileManager {

// 6. Sekcja prywatna
// (To była druga kluczowa poprawka - dodanie tej sekcji)
private:
    /**
     * @brief Prywatny rekurencyjny pomocnik do zapisu binarnego.
     * Używa kolejności Preorder.
     * @param wezel Aktualnie przetwarzany węzeł (BSTree::Wezel)
     * @param plik Strumień pliku binarnego
     */
    void zapiszBinarnieHelper(BSTree::Wezel* wezel, std::ostream& plik);

// 7. Sekcja publiczna (API klasy)
public:
    /**
     * @brief Wczytuje liczby z pliku tekstowego i dodaje je do drzewa.
     * @param drzewo Referencja do drzewa, do którego dodajemy elementy.
     * @param nazwaPliku Nazwa pliku .txt (np. "liczby.txt").
     */
    void wczytajTekstowyDoDrzewa(BSTree& drzewo, const std::string& nazwaPliku);

    /**
     * @brief Zapisuje całą strukturę drzewa do pliku binarnego.
     * @param drzewo Referencja do drzewa, które chcemy zapisać.
     * @param nazwaPliku Nazwa pliku wyjściowego (np. "drzewo.bin").
     */
    void zapiszBinarnie(BSTree& drzewo, const std::string& nazwaPliku);

    /**
     * @brief Wczytuje strukturę drzewa z pliku binarnego.
     * @param nazwaPliku Nazwa pliku binarnego do wczytania.
     * @return Nowy obiekt BSTree odtworzony z pliku.
     */
    BSTree wczytajBinarnie(const std::string& nazwaPliku);

}; // Koniec deklaracji klasy FileManager

// 8. Koniec strażnika
#endif // FILEMANAGER_H