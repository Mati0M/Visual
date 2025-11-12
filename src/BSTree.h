// 1. Strażnik (Header Guard)
// To jest bardzo ważna i standardowa praktyka w C++.
// Zabezpiecza przed błędem, gdyby ten plik został dołączony
// przez pomyłkę więcej niż jeden raz w tym samym miejscu.
#ifndef BSTREE_H
#define BSTREE_H

// 2. Dołączenia bibliotek (includes)
// Staramy się tu dodawać jak najmniej.
// <string> jest potrzebny, bo funkcja zapiszDoTekstowego
// przyjmuje nazwę pliku jako obiekt std::string.
#include <string>
// <iosfwd> legalnie deklaruje w przód typy strumieni (np. std::ostream)
// bez pełnego dołączania <iostream> w nagłówku.
#include <iosfwd>

// 3. Wstępna deklaracja (Forward Declaration)
// UWAGA: Nie wolno wprowadzać własnych deklaracji w przestrzeni nazw std.
// Poprawnym sposobem jest dołączenie <iosfwd>, które deklaruje std::ostream.

class FileManager;
// 4. Deklaracja klasy
// Słowo kluczowe 'class' rozpoczyna definicję "przepisu" na
// nasz nowy typ danych, czyli drzewo BST.
class BSTree {

// 5. Sekcja prywatna (private)
// Tutaj znajdują się rzeczy "wewnętrzne", do których użytkownik
// (np. plik main.cpp) nie powinien mieć bezpośredniego dostępu.
// To jest zasada hermetyzacji (enkapsulacji).
friend class FileManager;
private:

    // 6. Wewnętrzna struktura Węzła (Node)
    // To jest "cegiełka", z której zbudowane będzie nasze drzewo.
    // Definiujemy ją w sekcji private, bo nikt spoza klasy
    // nie musi wiedzieć, jak dokładnie wygląda węzeł.
    struct Wezel {
        int dane;           // Wartość (liczba) przechowywana w węźle
        Wezel* lewy;        // Wskaźnik na lewe dziecko (mniejsze wartości)
        Wezel* prawy;       // Wskaźnik na prawe dziecko (większe wartości)

        // Konstruktor struktury Wezel
        // To jest prosta funkcja, która ułatwia tworzenie nowego węzła.
        // Ustawia od razu wartość i zeruje wskaźniki na dzieci.
        Wezel(int wartosc) {
            dane = wartosc;
            lewy = nullptr;   // Używamy 'nullptr' zamiast starego 'NULL'
            prawy = nullptr;
        }
    };

    // 7. Główny atrybut klasy (zmienna członkowska)
    // To jest JEDYNA dana, jaką przechowuje sama klasa BSTree.
    // Jest to wskaźnik na samą górę drzewa (na korzeń).
    // Jeśli drzewo jest puste, 'korzen' ma wartość 'nullptr'.
    Wezel* korzen;


    // 8. Prywatne funkcje pomocnicze (helper functions)
    // Prawdziwa "magia" (rekurencja) dzieje się tutaj.
    // Metody publiczne (niżej) są tylko "opakowaniem",
    // które wywołują te funkcje, zaczynając od 'korzen'.

    // Pomocnik do dodawania (zwraca wskaźnik na węzeł, aby zaktualizować drzewo)
    Wezel* dodajHelper(Wezel* wezel, int wartosc);

    // Pomocnik do usuwania
    Wezel* usunHelper(Wezel* wezel, int wartosc);

    // Pomocnik do znajdowania najmniejszego węzła (potrzebne do usuwania)
    Wezel* znajdzMin(Wezel* wezel);

    // Pomocnik do czyszczenia (rekurencyjnie usuwa węzły)
    void wyczyscHelper(Wezel* wezel);

    // Pomocnicy do wyświetlania (przechodzenia) drzewa
    void preorderHelper(Wezel* wezel);
    void inorderHelper(Wezel* wezel);
    void postorderHelper(Wezel* wezel);

    // Pomocnik do szukania ścieżki (zwraca true/false czy znalazł)
    // Będzie po drodze drukować ścieżkę do konsoli.
    bool znajdzSciezkeHelper(Wezel* wezel, int wartosc);
    
    // Pomocnik do zapisu do pliku (przekazujemy strumień pliku przez referencję)
    void zapiszHelper(Wezel* wezel, std::ostream& plik);

    // Pomocnik do "graficznego" wyświetlania drzewa (jako bonus)
    void wyswietlGraficznieHelper(Wezel* wezel, std::string wciecie, bool czyPrawy);


// 9. Sekcja publiczna (public)
// To jest "interfejs" naszej klasy. Te funkcje będą mogły być
// wywoływane z zewnątrz, np. z pliku main.cpp.
public:

    // 10. Konstruktor klasy
    // Specjalna funkcja, która jest automatycznie wywoływana,
    // gdy tworzymy nowy obiekt (np. `BSTree mojeDrzewo;`).
    // Ustawia 'korzen' na 'nullptr', bo drzewo jest na początku puste.
    BSTree();

    // 11. Destruktor klasy
    // Specjalna funkcja, wywoływana automatycznie, gdy obiekt jest niszczony
    // (np. na końcu programu). MUSIMY tutaj posprzątać (zwolnić pamięć),
    // inaczej będziemy mieli wyciek pamięci!
    ~BSTree();

    // --- GŁÓWNA FUNKCJONALNOŚĆ (zgodna z poleceniem) ---

    // Publiczna metoda do dodawania.
    // Użytkownik podaje tylko liczbę, resztą zajmie się funkcja.
    void dodaj(int wartosc);

    // Publiczna metoda do usuwania.
    void usun(int wartosc);

    // Publiczna metoda do czyszczenia całego drzewa.
    // (Będzie po prostu wołać destruktor lub funkcję pomocniczą)
    void wyczysc();

    // Publiczna metoda do szukania ścieżki.
    void znajdzSciezke(int wartosc);

    // Publiczna metoda do zapisu do pliku tekstowego.
    void zapiszDoTekstowego(const std::string& nazwaPliku);

    // --- WYŚWIETLANIE (zgodnie z menu z main.cpp) ---

    // Wyświetla drzewo w kolejności Preorder (Korzeń, Lewy, Prawy)
    void wyswietl_preorder();

    // Wyświetla drzewo w kolejności Inorder (Lewy, Korzeń, Prawy)
    // (Dla BST da to liczby posortowane rosnąco)
    void wyswietl_inorder();

    // Wyświetla drzewo w kolejności Postorder (Lewy, Prawy, Korzeń)
    void wyswietl_postorder();
    
    // Bonus: Prawdziwe wyświetlanie "graficzne" (2D) w konsoli
    // (Możemy to później dodać do menu w main.cpp jako opcję 3b)
    void wyswietlGraficznie();

}; // Średnik na końcu deklaracji klasy jest OBOWIĄZKOWY!

// 12. Koniec strażnika (Header Guard)
#endif // BSTREE_H