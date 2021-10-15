//              PREKLAPANJE OPERATORA (TIP)

//int(x) - konvertuje x tipa X u tip int (ako postoji preklopljeni cast operator) <--- ne bismo mogli imati konstruktor konverzije
// tipa int, ovako mozemo

// T(x) ne moze da se koristi za tipove sa veim brojem reci: (unsigned long) x nije isto sto i unsigned long (x) <--- konverzija u tip long
// Konverzija se primenjuje implicitno (automatski)

class X {
public:
    operator int() { return 1; }
    explicit operator double() { return 2; }
};

void konv() {
    int a = X(); // eksplicitni poziv konstruktora klase X (privremeni objekat klase X) <--- implicitni poziv operator int()
    int b = (int) X();  // isto ali eksplicitni poziv i eksplicitna konverzija
    double c = (double) X(); // eksplicitna konverzija u double
    double d = X();   // konverzija u int, jer se ne moze implicitno primeniti cast u double
    // a==1, b==1, c==2.0, d==1.0
}

// T(x) <--- Konstruktor konverzije i X(t) <--- Operator cast (dvoznacno - pogresno)
// T(x) i X(t) i operatori + za X i T i operator + za oba tipa X i T x+t je dvoznacno

// Prenos klasnog tipa po referenci: menja se u privremeni objekat pri konverziji (objekat drugog tipa)

//              PREKLAPANJE NEW I DELETE

// moraju biti staticki preklopljeni -> pozivaju se za klasu ne za objekat
// delete <-- prvo destruktor pa telo funkcije delete

// OPERATOR NEW
//void *operator new(size_t velicina, T2 par2, ..., TN parN); <--- Mora razmak (treba vratiti pokazivac na objekat klase koji stvara)
//void *operator new[](size_t velicina, T2 par2, ..., TN parN): <--- <cstddef> <-> size_t (velicina u bajtovima)

//new(arg2, ..., argN) T(izraz, ..., izraz) <--- Uzima se sizeof(T)
//new(arg2, ..., argN) T[duzina] <-- Poziva se podrazumevani konstruktor za svaki element niza <--- Uzima se sizeof(T)*duzina

// OPERATOR DELETE
// void operator delete(void *pokazivac);
// void operator delete(void *pokazivac, size_t velicina);
// void operator delete[](void *pokazivac);
// void operator delete[](void *pokazivac, size_t velicina);

#include <cstddef>
using namespace std;
class XX {
public:
    void *operator new(size_t sz) { return new char[sz]; } // koristi se ugradjeni new <-- Poziva se kao new(XX) <-> prenosi se kao new(sizeof(XX))
    void operator delete(void *p) { delete []p; } // koristi se ugradjeni delete
};
// new i delete ne mogu biti virtuelni, ali se nasledjuju u izvedenim klasama

//          STANDARDNI U/I TOKOVI

// iostream dve klase: istream i ostream
// cin objekat klase istream
// cout objekat klase ostream

// Za klasu istream i sve ugradjene tipove, preklopljen je operator>>
// istream &operator>>(istream &is, T &t);

// Za klasu ostream i sve ugradjene tipove, preklopjen je operator<<
// ostream &operator<<(ostream &os, const T &t);

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

//          OPERATORI ZA NABRAJANJA

// prevodioc dozvoljava samo jedan tip nabrajanja u isto vreme (eksplicitno castujemo)
// moze i implicitno (npr. sreda + 2), dan = 3 ne moze (dan = sreda)

// dozvoljeno preklapanje operatora koji se ne preklapaju kao metodi
// postoji operator = i (tip) <-- cast
// nije dozvoljeno za: = [] () -> (tip) new delete <-- preklapaju se kao metodi (mada i nema smisla)

enum Dani {PO, UT, SR, CE, PE, SU, NE};
inline Dani operator+(Dani d, int k) {
    k = (int(d) + k) % 7; // + vraca dvrednost (vracamo rez po vrednosti), samo d + k beskonacna rekurzija istog operatora
    if (k < 0) k+=7;
    return Dani(k);
}
inline Dani &operator+=(Dani &d, int k) { return d = d + k; }
inline Dani &operator++(Dani &d) { // prefiskni ++
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