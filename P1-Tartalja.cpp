// Podrska za izvodjenje novih tipova iz postojecih (nasledjuje svosjstva osnovnog tipa i dodaje neka specificna svojstva)
// Stari programski kod se ne mora menjati i ponovo testirati

// Apstrakcija - prepoznavanje bitnih svojstava skupova slicnih objekata i opisivanje zajednickom klasom

// Kapsulacija implementacije - reprezentacije stanja i realizacije ponasanja

// Objavljivanje interfejsa - kroz "potpise" metoda (ime i lista argumenata)

// Izvodjenje novih tipova (klasa)
// Dinamicko povezivanje i polimorfizam

// Apstrakcija izraza: FORTRAN - registri masine postali skriveni za programera
// Apstrakcija kontrole: Algol60 - struktuiran tok kontrole programa
// Apstrakcija podataka: Pascal - razdvajanje detalja prezentacije podataka od apstraktnih
//                               operacija koje se definisu nad podacima (npr. tip nabrajanja)

// Klase su apstrakcije zajednickog atributa i zajednickog ponasanja jednog skupa srodnih objekata
// sadrze podatke clanove (atributi ili polja - definisu stanje) i funkcije clanice (metodi - definisu ponasanje)

// Implementaciju klase cine: privatni podaci clanovi i definicije (zaglavlje sa telom) funkcija

// Interfejs klase cine: javni podaci clanovi i deklaracije javnih funkcija

// Objekat je odredjen stanjem, ponasanjem i identitetom

class Publikacija {
public:
    Publikacija();                  //Podrazumevani konstruktor (suspenduje se kad napisemo drugi)
    Publikacija(int, char *n);        //Konstruktor sa dva argumenta
    virtual void unos();            //virtual metoda nadjacava metodu u osnovnoj klasi (ako su iste)
    virtual void ispis();
private:
    int id;
    char naslov[150];
};

#include <iostream>
using namespace std;
void Publikacija::unos() {
    cout << "Id? ";
    cin >> id;
    cout << "Naslov? " << endl;
    cin >> naslov;
}

void Publikacija::ispis() {
    cout << "Id: " << id << ", Naslov: "<< naslov << endl;
}

// Konstruktori - funkcije clanice koje se automatski izvrsavaju pri kreiranju objekata
// Destruktori - funkcije clanice koje se automatski izvrsavaju pri unistavanju objekata

// Polimorfizam:

// Dinamicko (kasno) vezivanje funkcija za funkciju proglasenu virtualnom (adresa se ne odredjuje u vreme prevodjenja/povezivanja)
// poziv se vezuje za funkciju u vreme izvrsenja

// Polimorfizam omogucava jedinstvenu obradu objekata osnovne i izvedenih klasa
// Ponasanje objekta na koji ukazuje pokazivac ne zavisi samo od tipa pokazivaca, vec tipa pokazanog objekta

class Casopis: public Publikacija {
public:
    Casopis();
    Casopis(int, int, int, char *);
    void unos();  //treba implementovati
    void ispis(); //redefinicija funkcije Publikacija::ispis()
private:
    int broj, god;
};

// ...implementacija

void ispisi_sve(Publikacija *p[], int n) { //neke su knjige, neke su casopisi
    for (int i = 0; i < n; i++) {
        p[i]->ispis(); //pokazivac na objekat (metod objekta -> ispis)
        cout << endl;
    }
}

// Objekti izvedenih klasa: specijalne vrste objekata osnovne klase, mogu zameniti u izrazima objekat osnovne klase
// Nasledjeni metodi se mogu redefinisati

#include <cstring>
Publikacija::Publikacija() {}
Publikacija::Publikacija(int i, char *n) {
    id = i; strcpy(naslov, n);
}

// Objektno-bazirani jezici podrzavaju: apstrakciju, kapsulaciju i modulaciju
// Ada83, Visual Basic V6
// Objektno-orijentisani jezici dodatno podrzavaju princip nasledjivanja
// Simula, Smalltalk, Eiffel, Ada95, C++, Java, Visual Basic, .NET, C#

class LosBroj {
    int broj;       //private po defaultu
public:
    LosBroj(int i) { broj = i; }
    void poruka() { cout << "Nedozvoljen broj " << broj << " !" << endl; }
};

void Casopis::unos() {
    Publikacija::unos();
    try {
        cout << "Broj? "; cin >> broj;
        if (broj < 1 || broj > 12) throw LosBroj(broj);
        cout << "Godiste? "; cin >> god;
    } catch (LosBroj izuzetak) {
        izuzetak.poruka();
        broj = 0; god = 0;
    }
}

// Mehanizam obrade izuzetaka nije svojstven samo OO jezicima (npr. Ada83)

// Preklopljeni operator definise operacije nad korisnickim (klasnim) tipom podataka

// Genericki mehanizam (mehanizam sablona) je u potpunosti staticki - zamena parametara je u vreme prevodjenja

template <class T> class SablonPublikacija {
    T id; //identifikator proizvoljnog tipa (ne samo int - vec neki string)
    //...
};

int main() {
    SablonPublikacija<int> knjiga; //generisana klasa
    Publikacija knjiga1(1, "Alhemicar"), knjiga2;
    knjiga1.ispis();
    knjiga2.unos();
    knjiga2.ispis();
    return 0;
}