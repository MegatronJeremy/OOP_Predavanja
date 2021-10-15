class Tekst {
public:
    Tekst() { niska = nullptr; }    // podrazumevani konstruktor
    Tekst(const char*);         // konverzioni konstruktor
    Tekst(const Tekst&);        // kopirajuci konstruktor
    Tekst(Tekst&&);         // premestajuci konstruktor
    ~Tekst();       // destruktor
private:
    char *niska;
};
#include <cstring>      // string.h
using namespace std;
Tekst::Tekst(const char* t) {
    niska = new char[strlen(t)+1];      // pravimo na heapu niz karaktera
    strcpy(niska, t);
}
Tekst::Tekst(const Tekst &t) {
    niska = new char[strlen(t.niska)+1];
    strcpy(niska, t.niska);
}
Tekst::Tekst(Tekst &&t) {
    niska = t.niska;
    t.niska = nullptr;
}
Tekst::~Tekst() { delete[] niska; niska = nullptr; }    // moze se pozvati i eksplicitno - zato postavljamo na nullptr

// STATICKI - ZAJEDNICKI ATRIBUTI
class X {
private:
    static int i;       // samo jedan za sve objekte (svi objekti date klase dele istu memorijsku lokaciju)
    int j;          // svaki objekat ima svoj j
};
// Brojac stvorenih objekata klase - ili broj zivih objekata (ako nema eksplicitnih poziva destruktora)

int X::i = 5;   // obavezno bez static (podrazumevana vrednost je 0)

class X1 {
//    static int psa = 10;    // ! GRESKA - promenljivi stat. atr.
    static const int ick = 10;  // imenovana celobrojna konst.
//    static const double irk = 10.0; // ! GRESKA - mora celobrojno
    static const int nsa;       // nepromenljivi stat. atr.
};
const int X1::nsa = 10;

// Glava jedinstvene liste (u sustini jedan objekat)
class Element {
public:
    static Element *glava;
private:
    int vrednost;
    Element *sledeci;
};
// Vodjenje evidencije o broju kreiranih primeraka
class Objekat {
public:
    Objekat() {brojac++;}
private:
    static int brojac;
};      // Trebaju se definisati ovi staticki atributi
int Objekat::brojac;    // postaje 0

// Staticki metod nema pokazivac *this - nema tekuceg objekta - metod je za klasu - ne moze pristupati direktno atributima objekta
// staticki metod moze pristupati drugim statickim metodama, atributima
// moze se pozivati i pre stvaranja objekta klase

class X3 {
    static int x;
    int y;
public:
    static int f(X3);
    int g();
};
int X3::x=5;        // definicija statickog atributa
int X3::f(X3 x1) {  // definicija statickog metoda
    int i = x;      // pristup statickom atributu X::x
//    int j = y;      // ! GRESKA: X::y nije staticki (ne postoji pokazivac this)
    int k = x1.y;   // ovo moze;
    return x1.x;    // i ovo moze, ali nije preporucljivo, izraz "x1" se ne izracunava
}
int X3::g() {
    int i = x;      // nestaticki metod moze da koristi
    int j = y;      // i staticke i nestaticke atribute
    return j;       //      y je ovde this->y;
}
void stat() {
    X3 xx;      // lokalni automatski objekat
    int p = X3::f(xx);          // X::f moze neposredno, bez objekta
//    int q = X3::g();            // ! GRESKA: za X::g mora konkretan objekat
    xx.g();             // ovako moze;
    p = xx.f(xx);       // i ovako moze, ali nije preporucljivo - ne vrsi se prenos xx objekta
}

class X4 {
public:
    static X4 *kreiraj() { return new X4; }
private:
    X4();       // konstruktor je privatan - moze samo staticki metod da mu pristupa
};
void usluzneKlase() {
//   X4 x;         // ! GRESKA  ne moze se napraviti lokalni automatski objekat
   X4 *px = X4::kreiraj();      // samo dinamicki objekat
}

// Prijateljstvo se ne nasledjuje, nije simetricna i nije tranzitivna relacija (mora se eksplicitno definisati)
class X5 {
    friend void g(int, X5 &);
//    friend void Y::h(); // prijateljski metod druge klase
    friend int o(X5 x) {return x.i;}
//    friend int p() {return i;}  // ! GRESKA - nema this
    int i;
public:
    void f(int ip) {i = ip;}
};
void g(int k, X5 &x) { x.i = k; }   // prijatelj moze pristupati privatnoj sekciji
void prijateljska() {
    X5 x; int j;
    x.f(5);     // postavljanje preko metoda
    g(6,x);     // postavljanje preko prijateljske funkcije
    j = o(x);       // citanje preko prijateljske funkcije (ime je globalno)
}

int main() {
    Tekst a("Pozdrav!"), b = a;  // Tekst(const char*); Tekst(const Tekst&);
}