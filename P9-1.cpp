//      SAKRIVANJE CLANOVA
// Redefinisanje identifikatora clana osnovne klase u izvedenoj klasi
//  - sakriva identifikator iz osnovne

// Pristup sakrivenom clanu iz osnovne klase:
//  ime_osnovne_klase::clan

// Ako se u izvedenoj klase napise neki metod koji ima isto ime kao metod iz osnovne klase
//  - takav metod sakriva sve nasledjene metode sa istim imenom (ne vazi preklapanje implicitno)
//  - iz metoda izvedene klase se ne moze pristupiti sakrivenim metodima
//  - samo preko ime_osnovne_klase::ime_metode_osnovne_klase
//  - nasledjeni sakriveni metodi se ne mogu pozivati ni za objekat izvedene klase
//      osim preko pokazivaca na osnovnu klasu koji pokazuje na objekat izvedene klase

//      UVOZ CLANOVA
// Izrazi postaju manje elegantni sa prethodnom sintaksom

// Da bismo prevazisli problem mozemo uvesti clanove osnovne klase deklaracijom USING

// using osnovna_klasa::ime_metoda uvezli smo u izvedenu klasu sve istoimene metode iz osnovne klase
// mozemo pristupati prostim imenovanjem

// Ne mozemo restaurirati vidljivost samo jednog metoda osnovne klase
// Restauriramo sve metode sa istim imenom

class O {
public:
    int a = 1;      // celobrojni atribut
    void m1();      // po dva metoda sa istim imenom
    void m1(int);
    void m2();
    void m2(int);
};

class I : public O { // javno izvedena klasa (pravo izvodjenje)
public:
    using O::m2;     // navodimo deklaraciju
    int a =2;        // definisan (specifican) atribut izvedene klase
    void m1(int);    // izvedena klasa ima dva atributa sa imenom a <-- u osnovnoj klasi sakriven
    void m2(int);
    void m() {
        int x = a;    // x=I::a
        int y = O::a; // x=O::a
//        m1();         // ! GRESKA <-- sakrili su sve metode iz osnovne klase
        m1(x);        // I::m1(int)
        O::m1();      // O::m1()
        O::m1(y);     // O::m1(int)
        m2();         // m2 je direktno vidljiv O::m2() <-- restaurirali smo vidljivost
        m2(x);        // I::m2(int) <-- redefinisan metod u izvedenoj klasi
        O::m2(y);     // O::m2(int)
    }
};

void f() {
    I i;            // Objekat izvedene klase
    O *po = &i;          // pokazivac na osnovnu klase koji pokazuje na objekat izvedene klase
    int p = i.a;    // I::a <-- postoji a u izvedenoj klasi
    int q = i.O::a; // O::a <-- pristup nasledjenom atributu a eksplicitno
//    i.m1();         // ! GRESKA <-- sakriven
    i.O::m1();      // O::m1()
    i.m1(p);        // I::m1(int) <--- redefinisan u izvedenoj
    i.O::m1(q);     // O::m1(int)
    i.m2();         // O::m2(int) <-- restauriran
    i.m2(p);        // I::m2(int)
    i.O::m2(q);     // O::m2(int)

    po->m1();       // Mozemo pristupati bilo kom clanu (staticko vezivanje)
    po->m1(2);
    po->m2();
    po->m2(1);
    po->a;          // Podrazumevano iz osnovne klase (tako definisan pokazivac)
}

//      UVOZ KONSTRUKTORA

// Konstruktori osnovne klase se ne nasledjuju
// Implicitno se pozivaju (skriveni su)

// using ime_klase::ime_klase
// Cinimo konstruktore osnovne klase vidljivim u izvedenoj

// Generisu se konstruktori izvedene sa istim potpisima
// Imaju prazno telo, implicitno pozivaju konstruktore osnovne

class A {
public: A(int i) {}
};

class B: public A {public: using A::A;};

B b(1); // Poziva se implicitno A::A(1)
//  Pravi se objekat b klase B

//      IZVODJENJE STRUKTURA

// Mogu se izvoditi iz osnovnih struktura ili klasa

// Podrazumeva se javno izvodjenje kod struktura (kod klasa privatno)

struct OS{};
class OK{};
class IKS: OS{}; // privatno izvodjenje
class IKK: OK{}; // privatno izvodjenje
struct ISK: OK{};   // javno izvodjenje
struct ISS: OS{};   // javno izvodjenje

// Unije se ne mogu izvoditi, niti se iz unije moze izvoditi

//      KONSTRUKTORI I DESTRUKTORI

// Kad se kreira objekat izvedene klase, poziva se najpre konstruktor osnovne klase

// Pri destrukciji objekta izvedene klase, poziva se destruktor izvedene, pa destruktor osnovne klase

// Ako ne zelimo podrazumevani konstruktor osnovne klase:
//  - u listi inicijalizatora ( (param...) : atributi(inic) )
//  - mozemo napisati ime osnovne klase sa listom argumenata za zeljeni konstruktor osnovne klase
//  - u izvedenoj klasi NE MOZEMO da inicijalizujemo atribute osnovne klase
//  - bice inicijalizovani implicitno podrazumevanim konstruktorom ili eksplicitno preko konstruktora u listi inicijalizatora

class Osnovna {
    int bi;
public:
    Osnovna(int);   // Konstruktor osnovne klase
};                  // Suspendovali smo Osnovna()

Osnovna::Osnovna(int i) : bi(i) // Inicijalizujemo bi
{}

class Izvedena : public Osnovna {
    int di;        // Nasledili smo i bi
public:
    Izvedena(int);
};
Izvedena::Izvedena(int i) : Osnovna(i), di(i+1)   // Ne mozemo navesti bi ovde
{}  // Parametar izvedene klase i koristimo za konstruktor osnovne klase
// Da nemamo Osnovna(i) program se ne bi preveo! Nema podrazumevanog konstruktor osnovne klase!

// Izvedeni objekat ima nasledjeni podobjekat

//      REDOSLED KONSTRUKCIJE

// Pre izvrsavanja tela konstruktora izvedene klase, poziva se konstruktor osnovne klase

// Pri visestrukom izvodjenju, vrsimo poziv konstruktora osnovnih po redosledu izvodjenja osnovnih klasa
// (ne u listi inicijalizatora - bitan redosled u deklaraciji izvodjenja)
// class I : public O1 : public O2 : public O3 --> O1(), O2() pa O3()

// Incijalizacija atributa - po redosledu navodjenja atributa u izvedenoj klasi
// Redosled liste inicijalizatora nebitan
// Prioritet vrednosti dodele atributu dobija se iz liste inicijalizatora
// Ako su neki atributi klasnog tipa, sa njega se poziva konstruktor te klase (odredjujemo kroz listu inicijalizatora
// uz odgovorajuci atribut lista argumenata za incijalizaciju)
// Ukoliko je atribut nizovski, pozivaju se konstruktori elemenata niza po redosledu rastuceg indeksa
// Na kraju telo konstruktora izvedene klase

// Konstrukcija nasledjenih podobjekta -> incijalizacija atributa -> izvrsavanje tela
// Destrukcija uvek obrnutim redosledom od redosleda konstrukcije
// Destruktori osnovnih klasa, pa destruktori atributa

#include <iostream>
using namespace std;

class C {
public:
    C() {cout << "Konstruktor A." << endl;}
    ~C() {cout << "Destruktor A." << endl;}
};

class O1 {
public:
    O1() {cout << "Konstruktor O." << endl;}
    ~O1() {cout << "Destruktor O." << endl;}
};

class T : public O {
    C a;
public:
    T() {cout << "Konstruktor I." << endl;}
    ~T() {cout << "Destruktor I." << endl;}
};

int main () {T d;}

//  Izlaz: OAIIAO

//      KONVERZIJA

// Objekat JAVNO izvedene klase je i objekat osnovne klase
// Javno izvedena - zadrzava se ugovor objekta osnovne klase

// Posledice:
//  - pokazivac na objekat izvedene klase moze se implicitno konvertovati na objekat osnovne klase
//  - obrnuto ne vazi (nebezbedna konverzija)
//  - isto vazi i za reference
//  - objekat osnovne klase moze se inicijalizovati objektom izvedene klase (ima sve sto i osnovna klasa + nesto dodatno)
//  - objektu osnovne klase moze da se dodeli (=) objekat izvedene klase

// Objekat privatno/zasticeno izvedene klase nije i objekat osnovne klase
//  - implicitne konverzije moguce samo UNUTAR izvedene klase (ne izvan)

//      POJAM POLIMORFIZMA
//  Imamo klasu figura - apstrakcija geometrijskih figura
//  Znamo da ih treba crtati
//  Iz osnovne klase figura (prazan metod) izvodimo klase krug, kvadrat, pravougaonik itd.
//  U tim klasama znamo kako da nacrtamo odgovarajucu figuru
//  Realizujemo crtanje na svojstven nacin

class Figura {
public: void crtaj();
};
void crtanje (int br_figura, Figura **niz_figura) { // Bitno! U nizu pokazivaci na figure
    for (int i = 0; i < br_figura; i++)
        niz_figura[i]->crtaj();
}   // Razlicitim figurama se pristupa preko niza pokazivaca na figura
//  Indirektnim pristupom aktivira se mehanizam koji obezbedjuje polimorfno ponasanje

// Svaka figura je figura odredjene klase u kojoj je definisano kako se ta figura crta

// Svaki objekat "prepoznaje" kojoj izvedenoj klasi figure pripada, iako se obracamo njemo
// kao objektu osnovne klase - bitna je klasa pokazanog objekta

// Prevodilac ne zna unapred koju metodu "crtaj" ce pozivati - vrsi se DINAMICKO povezivanje
// U vreme izvrsenja se pristupa odgovarajucem metodu

// Polimorfizam: Poly (vise) + Morph (oblik)
// Metod pokazuje viseoblicje (objekat kome pristupamo pokazuje viseoblicje)

//      VIRTUELNI (POLIMORFNI) METODI

// Moze se dobiti polimorfno ponasanje koristenjem virtuelnih metoda:

// virtual ispred metode u osnovnoj klasi - pokazuje polimorfno ponasanje
// virtual ispred deklaracije metode

// virtual metod nadjacavama (polimorfno redefinisemo) u izvedenoj klasi
// eng. override

// Podrazumeva se da je metod virtualan ako je nadjacan (nije potrebno u izvedenoj klasi navoditi)

// U izvedenoj klasi potreban metod istog potpisa i skoro istog tipa rezultata
// Mora se slagati ime, tipovi parametra, broj parametra (potpis potpuno isti)

// Dozvoljeno je ako metod u osnovnoj klasi vraca pokazivac ili referencu na osnovnu klasa,
// da izvedena klasa vraca referencu ili pokazivac na NEKU izvedenu klasu (od tipa rezultata u osnovnoj klasi)

// Ako se u izvedenoj klasi ne slaze potpis metode sa osnovnom klasom
// to je sakrivanje metoda iz osnovne klase - ne nadjacanje

// Ako je razlika samo u TIPU REZULTATA (nedozvoljena razlika) - GRESKA

// Ne moramo virtuelni metod redefinisati u izvedenoj klasi (samo se nasledjuje)
// Moze se redefinisati u sledecem koraku izvodjenja

class ClanBiblioteke {
protected:
    Racun r;                    // zasticeni racun
public:
    virtual Racun platiClanarinu()  // virtuelni metod osnovne klase
    { return r-=Clanarina}
};

clas PocasniClan : public ClanBiblioteke {  // javno izvedena klasa (ispunjava ugovor clana biblioteke)
public:                         // nasledio je racun kao atribut
    Racun platiClanarinu()      // virtuelni metod izvedene klase
    { return r; }               // pocasni clan ne placa clanarinu
};

int g() {
    ClanBiblioteke *clanovi[100];   // neki od clanova ce biti pocasni clan
    for (int i = 0; i < brojClanova; i++) cout << clanovi[i]->platiClanarinu();
}

