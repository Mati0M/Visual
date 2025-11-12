// 1. Dołączenia
#include "FileManager.h" // Plik nagłówkowy tej klasy
#include <fstream>       // Do obsługi strumieni plików (ifstream, ofstream)
#include <iostream>      // Do obsługi błędów (std::cout)

// 2. Implementacja: Wczytaj z pliku tekstowego
void FileManager::wczytajTekstowyDoDrzewa(BSTree& drzewo, const std::string& nazwaPliku) {
    
    // Otwieramy plik do odczytu
    std::ifstream plikWejsciowy(nazwaPliku);

    // Sprawdzamy, czy plik się otworzył
    if (!plikWejsciowy.is_open()) {
        std::cout << "Blad: Nie mozna otworzyc pliku: " << nazwaPliku << std::endl;
        return; // Zakończ funkcję, jeśli się nie udało
    }

    int liczba;
    // Wczytujemy liczby jedna po drugiej, dopóki plik się nie skończy
    while (plikWejsciowy >> liczba) {
        // Używamy publicznej metody drzewa, aby dodać element
        drzewo.dodaj(liczba); 
    }

    plikWejsciowy.close();
    std::cout << "Wczytano liczby z pliku " << nazwaPliku << "." << std::endl;
}


// 3. Implementacja: Zapisz binarnie (funkcja publiczna - "opakowanie")
void FileManager::zapiszBinarnie(BSTree& drzewo, const std::string& nazwaPliku) {
    
    // Otwieramy plik do zapisu w trybie binarnym
    std::ofstream plikWyjsciowy(nazwaPliku, std::ios::binary);

    if (!plikWyjsciowy.is_open()) {
        std::cout << "Blad: Nie mozna otworzyc pliku binarnego: " << nazwaPliku << std::endl;
        return;
    }

    // Wywołujemy prywatnego pomocnika, zaczynając od korzenia.
    // Mamy dostęp do 'drzewo.korzen', ponieważ BSTree
    // zadeklarowała 'friend class FileManager;'.
    zapiszBinarnieHelper(drzewo.korzen, plikWyjsciowy);   

    plikWyjsciowy.close();
    std::cout << "Zapisano drzewo binarnie do " << nazwaPliku << "." << std::endl;
}


// 4. Implementacja: Prywatny pomocnik zapisu binarnego (rekurencja)
// (Kompilator wie, że ta funkcja istnieje, bo zadeklarowaliśmy ją w .h)
void FileManager::zapiszBinarnieHelper(BSTree::Wezel* wezel, std::ostream& plik) {
    
    // Przypadek bazowy rekurencji: doszliśmy do liścia
    if (wezel == nullptr) {
        return;
    }

    // Zapisujemy w kolejności Preorder (Korzeń -> Lewy -> Prawy)
    // 1. Zapisz dane obecnego węzła (Korzeń)
    plik.write( (char*)&(wezel->dane), sizeof(int) );
    
    // 2. Rekurencyjnie zapisz lewe poddrzewo
    zapiszBinarnieHelper(wezel->lewy, plik);
    
    // 3. Rekurencyjnie zapisz prawe poddrzewo
    zapiszBinarnieHelper(wezel->prawy, plik);
}


// 5. Implementacja: Wczytaj z pliku binarnego
BSTree FileManager::wczytajBinarnie(const std::string& nazwaPliku) {
    
    // Tworzymy nowe, puste drzewo, które będziemy budować
    BSTree noweDrzewo;

    // Otwieramy plik binarny do odczytu
    std::ifstream plikWejsciowy(nazwaPliku, std::ios::binary);

    if (!plikWejsciowy.is_open()) {
        std::cout << "Blad: Nie mozna otworzyc pliku binarnego: " << nazwaPliku << std::endl;
        return noweDrzewo; // Zwróć puste drzewo, jeśli się nie udało
    }

    int liczba;
    
    // (To jest trzecia, kluczowa poprawka - literówka)
    // Czytamy z 'plikWejsciowy', a nie 'plik'
    //
    // Pętla czyta z pliku porcje o wielkości 'sizeof(int)',
    // dopóki plik się nie skończy.
    while ( plikWejsciowy.read( (char*)&liczba, sizeof(int)) ) {
        // Ponieważ plik był zapisany w Preorder, proste dodawanie
        // elementów do nowego drzewa odtworzy DOKŁADNIE
        // tę samą strukturę, jaka była zapisywana.
        noweDrzewo.dodaj(liczba);
    }

    plikWejsciowy.close();
    std::cout << "Wczytano drzewo z pliku binarnego " << nazwaPliku << "." << std::endl;
    
    // Zwracamy gotowe, odbudowane drzewo
    return noweDrzewo;
}