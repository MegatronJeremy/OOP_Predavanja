// Primer konstruktora i destruktora

class Tekst {
public:
    Tekst() { niska = nullptr; }    // podrazumevani konstruktor
    Tekst(const char*);             // konverzioni konstruktor
    Tekst(const Tekst&);            // kopirajuci konstruktor
    Tekst(Tekst&&);                 // premestajuci konstruktor
    ~Tekst();                       // destruktor
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

//      STATICKI - ZAJEDNICKI ATRIBUTI

// Pri stvaranju objekata klase
//  - za svaki objekat - poseban komplet nestatickih atributa

// Atribut moze biti deklarisan kao staticki
//  - pomocu modifikatora static

// Postoji samo jedan primerak statickog atributa za celu klasu
//  - zajednicki podatak za sve objekte klase - objekti ga dele

class X {
private:
    static int i;       // samo jedan za sve objekte (svi objekti date klase dele istu memorijsku lokaciju)
    int j;              // svaki objekat ima svoj j
};
// Brojac stvorenih objekata klase - ili broj zivih objekata (ako nema eksplicitnih poziva destruktora)

// U klasi se staticki atribut samo deklarise
// Mora da se definise na globalnom nivou
//  - izvan definicije klasa i svih funkcija

// Cak se i privatni staticki atributi moraju definisati na taj nacin

// Dozvoljeni su svi oblici inicijalizatora

// Inicijalizacija statickog atributa se obavi
//  - pre prvog pristupa njemu i pre stvaranja objekta date klase

// Obracanje statickom atributu van klase vrsi se preko operatora ::
int X::i = 5;   // obavezno bez static (podrazumevana vrednost je 0)

// Imenovana celobrojna konstanta moze se definisati i u definiciji klase

class X1 {
//    static int psa = 10;    // ! GRESKA - promenljivi stat. atr.
    static const int ick = 10;  // imenovana celobrojna konst.
    static constexpr int icck = 10;  // imenovana celobrojna konst.
//    static const double irk = 10.0; // ! GRESKA - mora celobrojno
    static const int nsa;       // nepromenljivi stat. atr.
};
const int X1::nsa = 10;

// Slicnosti sa globalnim podacima:
//  - trajni podaci (slican zivotni vek)
//  - moraju se definisati na globalnom nivou

// Razlike od globalnih podataka:
//  - staticki atributi logicki pripadaju klasi
//  - doseg imena statickih atributa je klasa
//  - statickim atributima je moguce ograniciti pristup

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

// Staticki metodi su funkcije klase, a ne svakog posebnog objekta
// Metodi su "zajednicki" za sve objekte klase

// Primena:
//  - za opste usluge klase
//  - prvenstveno za obradu statickih atributa

// Deklarisu se dodavanjem modifikatora static ispred deklaracija

// Imaju sva svojstva globalnih funkcija osim dosega i kontrole pristupa

// Staticki metod nema pokazivac *this - nema tekuceg objekta - metod je za klasu - ne moze pristupati direktno atributima objekta
// Modifikator const i drugi iza liste parametara nemaju smisla

// Mogu pristupati nestatickim clanovima konkretnog objekta:
//  - parametra, lokalnog, globalnog

// Mogu neposredno pristupati samo statickim clanovima klase

// Pozivaju se za klasu: <klasa>::<poziv>

// Mogu se pozivati i za konkretan objekat (sto treba izbegavati)
//  - levi operand izraza se ne izracunava

// Staticki metod moze pristupati drugim statickim metodama, atributima
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
}                   // --> isto kao da je napisamo return x

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

// Primer:
//  - dohvatanje glave ili broja clanova jedinstvene liste
//  - dohvatanje broja stvorenih objekata klase koja ima njihov brojac
//  - usluzna klasa (svi staticki metodi, obrisani ugradjeni konstruktori)

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

// PRIJATELJI KLASA

// Ponekad je potrebno da klasa ima i "povlascene" korisnike koji mogu da pristupaju njenim privatnim clanovima

// Povlasceni korisnici mogu biti:
//  - funckije (globalne ili metodi drugih klasa) ili
//  - cele klase

// Prijateljstvo, kao relacija izmedju klasa:
//  - se ne nasledjuje
//  - nije simetricna relacija
//  - nije tranzitivna relacija

// Prijateljstvo je relacija koja regulise iskljucivo pravo pristupa, a ne oblast vazenja i vidljivost identifikatora

// Prijateljske funkcije su funkcije koje
//  - nisu clanice klase, ali
//  - imaju dozvoljen pristup do privatnih clanova klase

// Prijateljske funkcije mogu da budu:
//  - globalne funkcije ili
//  - metodi drugih klasa

// Funkcija je prijateljska:
//  - ako se u definiciji klase navede njena deklaracija ili definicija
//  - sa modifikatorom friend

// Potrebno je da klasa eksplicitno proglasi funkciju prijateljskom

// Ako se u definiciji klase navodi definicija prijateljske funkcije:
//  - podrazumeva se inline
//  - ime funkcije nema klasni doseg, vec doseg identifikatora klase

// Nevazno je pravo pristupa sekciji klase (privatno, zasticeno, javno) u kojoj se navodi deklaracija
// prijateljske funkcije

// Prijateljska funkcija nema pokazivac this na objekat klase kojoj je prijatelj
//  - modifikator (npr. const) nema smisla za globalnu prijateljsku funkciju

// Funkcija moze da bude prijatelj vecem broju klasa istovremeno


class X {
public:
    void h();
private:
    int x;
};

class X5 {
    friend void g(int, X5 &);   // prijateljska globalna funkcija

    friend void X::h(); // prijateljski metod druge klase

    friend int o(X5 x) {return x.i;}    // definicija globalne f-je
//    friend int p() {return i;}  // ! GRESKA - nema this
    int i;
public:
    void f(int ip) {i = ip;}    // nestaticki globalni metod klase
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