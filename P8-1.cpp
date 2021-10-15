//      PREKLAPANJE OPERATORA (TIP)

// Pozivanje [za funkciju X::operator T() i objekat X x;]:
//  - (T)x ili T(x) je ekvivalent izrazu x.operator T()
//  - drugi oblik je notacijski isti kao da je u pitanju konstruktor T
//  - moguc oblik je i staticki kast: static_cast<T>(x)

// Za razliku od konstruktora T(x) preklopljeni operator (T)x
//  - moze da se koristi za T koje je standardni tip
//  - operand x mora biti objekat klase (X), odnosno x ne moze biti primitivan tip
//  - primer: int(x) - konvertuje x tipa X u tip int

// int(x) - konvertuje x tipa X u tip int (ako postoji preklopljeni cast operator) <--- ne bismo mogli imati konstruktor konverzije
// tipa int, ovako mozemo

// T(x) ne moze da se koristi za tipove sa vecim brojem reci: (unsigned long) x nije isto sto i unsigned long (x) <--- konverzija u tip long

// Konverzija se primenjuje implicitno (automatski)

// Ako se zeli spreciti implicitna konverzija:
//  - modifikator explicit, kao kod konstruktora konverzije

class X {
public:
    operator int() { return 1; }
    explicit operator double() { return 2; }
};

void konv() {
    int a = X();        // eksplicitni poziv konstruktora klase X (privremeni objekat klase X) <--- implicitni poziv operator int()
    int b = (int) X();  // isto ali eksplicitni poziv i eksplicitna konverzija
    double c = (double) X(); // eksplicitna konverzija u double
    double d = X();          // konverzija u int, jer se ne moze implicitno primeniti cast u double
    // a==1, b==1, c==2.0, d==1.0
}

// T(x) <--- Konstruktor konverzije i X(t) <--- Operator cast (dvoznacno - pogresno)
// Definisane konv. T(x) i X(t) i operatori + za oba tipa X i T ---> x+t je dvoznacno

// Problem sa konverzijom tipa pri prenosu paremetara po referenci
// prenos klasnog tipa po referenci: menja se u privremeni objekat pri konverziji (objekat drugog tipa)
// u funkciju se prenosi taj privremeni objekat po adresi

//      PREKLAPANJE NEW I DELETE

// Moraju biti staticki preklopljeni -> pozivaju se za klasu ne za objekat
// Cak i ako tako nisu deklarisane, one su staticke

// Unutar tela ovih operatorskih funkcija:
//  - ne treba eksplicitno pozivati konstruktor, odnosno destruktor
//  - konstruktor se implicitno poziva posle operatorske funkcije new
//  - destruktor se implicitno poziva pre operatorske funkcije delete
//      -- prvo destruktor pa telo funkcije delete

// OPERATOR NEW

// Deklarise se kao:
//void *operator new(size_t velicina, T2 par2, ..., TN parN); <--- Mora razmak (treba vratiti pokazivac na objekat klase koji stvara)
//void *operator new[](size_t velicina, T2 par2, ..., TN parN): <--- <cstddef> <-> size_t (velicina u bajtovima)

// Poziva se kao:
//new(arg2, ..., argN) T(izraz, ..., izraz) <--- Uzima se sizeof(T) za argument velicina
//new(arg2, ..., argN) T[duzina] <-- Poziva se podrazumevani konstruktor za svaki element niza <--- Uzima se sizeof(T)*duzina

// Parametri parX, odnosno argumenti argX - opcione dodatne informacije
// Opciona lista izraza je inicijalizator - odredjuje izbor konstruktora
// Broj elemenata niza je duzina, zauzima se sizeof(T)*duzina bajtova
// Operator new treba da vrati pokazivac na alocirani prostor
// Klasa moze imati vise preklopljenih operatora new

// OPERATOR DELETE

// Deklarise se kao:
// void operator delete(void *pokazivac);
// void operator delete(void *pokazivac, size_t velicina);
// void operator delete[](void *pokazivac);
// void operator delete[](void *pokazivac, size_t velicina);

// Parametar pokazivac je pokazivac na prostor koji treba osloboditi
// Parametar velicina odredjuje prostor u bajtima koji treba osloboditi
// Ako nedostaje odgovarajuci stvarni argument za velicina
//  - funkcija mora sama da odredi velicinu, na osnovu ranije alokacije
// Funkcija delete ne vraca rezultat
// Klasa moze imati samo po jednu (za podatak i niz) delete funkciju <-- ugradjeni delete (vrv)
//  - bez obzira sto postoje po dve preklopljene operatorske funkcije delete

// Ako su u klasi T preklopljeni operatori new i delete,
// ugradjeni operator new i delete mogu da se unutar dosega T pozivaju:
//  - eksplicitno, preko unarnog operatora ::
//      za pojedinacne podatke tipa T - ::new T, odnosno ::delete pt
//      za nizove elemenata tipa T - ::new T[duz], odnosno ::delete[] pt
//  - implicitno, kada se dinamicki kreiraju/unistavaju objekti koji nisu tipa T

#include <cstddef>
using namespace std;
class XX {
public:
    void *operator new(size_t sz) { return new char[sz]; } // koristi se ugradjeni new <-- Poziva se kao new(XX) <-> prenosi se kao new(sizeof(XX))
    void operator delete(void *p) { delete []p; } // koristi se ugradjeni delete
    void operator delete(void *p, size_t velicina) {delete []p;}
    void operator delete(void *p, size_t velicina, int i) {delete []p;}
};
// Metodi new i delete ne mogu biti virtuelni, ali se nasledjuju u izvedenim klasama

//      STANDARDNI U/I TOKOVI

// iostream dve klase: istream i ostream
// cin objekat klase istream
// cout objekat klase ostream

// Za klasu istream i sve ugradjene tipove, preklopljen je operator>>
// istream &operator>>(istream &is, T &t);

// Za klasu ostream i sve ugradjene tipove, preklopjen je operator<<
// ostream &operator<<(ostream &os, const T &t);

// Razlog zbog kojeg preklopljen operator ne moze biti metod:
//  -  prvi operand je tipa istream& odnosno ostream&

#include <iostream>
using namespace std;
class Kompleksni {
    double real, imag;
    friend ostream &operator<<(ostream &, const Kompleksni &); // levi operand mora biti ostream, ne mozemo metod klase
public:
    Kompleksni(double r, double i) : real(r), imag(i) {};
};
ostream &operator<<(ostream &os, const Kompleksni &c) {
    return os << "(" << c.real << "," << c.imag << ")"; // moze biti ili cout ili drugi objekat u memoriji tog tipa
}
void out() {
    Kompleksni c(0.5, 0.1);
    cout << "c=" << c << endl; // ispis sa: c = (0.5,0.1)
}

//      OPERATORI ZA NABRAJANJA

// Nabrajanja su celobrojni tip, ali podrazumevano su dozvoljene samo:
//  - operacija dodele vrednosti istom tipu nabrajanja
//  - operacije konverzije (kast) u celobrojnu vrednost - moze i implicitno
//      osim za nabrajanja sa ogranicenim dosegom
//  - operacija konverzije iz celobrojne vrednosti - samo eksplicitno

// Prevodioc dozvoljava samo jedan tip nabrajanja u isto vreme (eksplicitno castujemo)

// Moze i implicitno (npr. sreda + 2); dan = 3 ne moze <-- mora eksplicitni cast (dan = sreda)

// Dozvoljeno preklapanje operatora koji se ne preklapaju kao metodi
// postoji operator = i (tip) <-- cast
// nije dozvoljeno za: = [] () -> (tip) new delete <-- preklapaju se kao metodi (mada i nema smisla)

enum Dani {PO, UT, SR, CE, PE, SU, NE};
inline Dani operator+(Dani d, int k) {
    k = (int(d) + k) % 7; // + vraca dvrednost (vracamo rez po vrednosti), samo d + k beskonacna rekurzija istog operatora
    if (k < 0) k+=7;
    return Dani(k);
}
inline Dani &operator+=(Dani &d, int k) { return d = d + k; }
inline Dani &operator++(Dani &d) { // prefiksni ++
    return d = Dani(d<NE?int(d)+1:PO);
}
inline Dani operator++(Dani &d, int) { // postfiksna varijanta
    Dani e(d);
    ++d;
    return e;
}

int main() {
    out();
}