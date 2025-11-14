/**
 * @file FileManager.cpp
 * @brief Implementacja (definicje metod) klasy FileManager.
 * @details Zawiera logikę wczytywania i zapisywania drzewa BST
 * do plików tekstowych oraz binarnych.
 */

#include "FileManager.h"
#include <fstream>
#include <iostream>

/**
 * @brief Wczytuje liczby z pliku tekstowego i dodaje je do drzewa.
 * @details Otwiera plik o podanej nazwie, czyta liczby całkowite
 * (oddzielone białymi znakami) i dodaje je do istniejącego
 * obiektu drzewa za pomocą metody `drzewo.dodaj()`.
 * @param drzewo Referencja do obiektu BSTree, który ma być zmodyfikowany.
 * @param nazwaPliku Nazwa pliku .txt do wczytania.
 */
void FileManager::wczytajTekstowyDoDrzewa(BSTree& drzewo, const std::string& nazwaPliku) {
    
    std::ifstream plikWejsciowy(nazwaPliku);

    if (!plikWejsciowy.is_open()) {
        std::cout << "Blad: Nie mozna otworzyc pliku: " << nazwaPliku << std::endl;
        return;
    }

    int liczba;
    while (plikWejsciowy >> liczba) {
        drzewo.dodaj(liczba); 
    }

    plikWejsciowy.close();
    std::cout << "Wczytano liczby z pliku " << nazwaPliku << "." << std::endl;
}


/**
 * @brief Publiczna metoda zapisująca drzewo do pliku binarnego.
 * @details Otwiera plik binarny do zapisu i rozpoczyna
 * rekurencyjny proces zapisu, wywołując `zapiszBinarnieHelper`.
 * Wymaga przyjaźni z klasą BSTree, aby uzyskać dostęp do korzenia.
 * @param drzewo Referencja do drzewa, które ma być zapisane.
 * @param nazwaPliku Nazwa pliku wyjściowego (np. "drzewo.bin").
 */
void FileManager::zapiszBinarnie(BSTree& drzewo, const std::string& nazwaPliku) {
    
    std::ofstream plikWyjsciowy(nazwaPliku, std::ios::binary);

    if (!plikWyjsciowy.is_open()) {
        std::cout << "Blad: Nie mozna otworzyc pliku binarnego: " << nazwaPliku << std::endl;
        return;
    }

    zapiszBinarnieHelper(drzewo.korzen, plikWyjsciowy);   

    plikWyjsciowy.close();
    std::cout << "Zapisano drzewo binarnie do " << nazwaPliku << "." << std::endl;
}


/**
 * @brief Prywatny rekurencyjny pomocnik do zapisu binarnego.
 * @details Zapisuje drzewo do strumienia binarnego w kolejności Preorder
 * (Korzeń, Lewy, Prawy). Taka kolejność gwarantuje, że
 * drzewo można odtworzyć do identycznej struktury poprzez proste dodawanie.
 * @param wezel Aktualny węzeł w rekurencji (zaczynając od korzenia).
 * @param plik Strumień wyjściowy (std::ostream) otwarty w trybie binarnym.
 */
void FileManager::zapiszBinarnieHelper(BSTree::Wezel* wezel, std::ostream& plik) {
    
    if (wezel == nullptr) {
        return;
    }

    plik.write( (char*)&(wezel->dane), sizeof(int) );
    zapiszBinarnieHelper(wezel->lewy, plik);
    zapiszBinarnieHelper(wezel->prawy, plik);
}


/**
 * @brief Wczytuje strukturę drzewa z pliku binarnego.
 * @details Otwiera plik binarny, czyta liczby całkowite jedna po drugiej
 * i buduje *nowe* drzewo, dodając je w kolejności odczytu.
 * Działa poprawnie tylko wtedy, gdy plik był zapisany w kolejności Preorder.
 * @param nazwaPliku Nazwa pliku binarnego do wczytania.
 * @return Nowy obiekt BSTree odtworzony z pliku. Zwraca puste
 * drzewo, jeśli otwarcie pliku się nie powiodło.
 */
BSTree FileManager::wczytajBinarnie(const std::string& nazwaPliku) {
    
    BSTree noweDrzewo;

    std::ifstream plikWejsciowy(nazwaPliku, std::ios::binary);

    if (!plikWejsciowy.is_open()) {
        std::cout << "Blad: Nie mozna otworzyc pliku binarnego: " << nazwaPliku << std::endl;
        return noweDrzewo;
    }

    int liczba;
    
    while ( plikWejsciowy.read( (char*)&liczba, sizeof(int)) ) {
        noweDrzewo.dodaj(liczba);
    }

    plikWejsciowy.close();
    std::cout << "Wczytano drzewo z pliku binarnego " << nazwaPliku << "." << std::endl;
    
    return noweDrzewo;
}