//      SPECIJALIZACIJA GENERICKIH FUNKCIJA

// Specijalizacija sablonskih funkcija mora biti POTPUNA
// Ne moze nijedan parametar biti u listi parametara sablona specijalizovane genericke/sablonske funkcije

// Deklaracija:
// template<>tip GSFunkcija<argumenti> (...);
// Definicija:
// template<>tip GSFunkcija<argumenti> (...) {/*...*/}

// Mora isto postojati opsti sablon funkcije - ali se moraju svi parametri specijalizovati

// Treba na nekom mestu stvoriti konkretnu funkciju iz takve specijalizovane genericke funkcije
// Automatski pozivom

// Moguce navesti argumente kojima se specijalizuje koja funkcija ce se pozvati - ali nije obavezno
// Eksplicitno navodjenje argumenata sablona - ili implicitno zakljucivanje na osnovu tipova argumenata poziva funkcija

template<typename T> T maximum(T a, T b) {
    return a>b?a:b;
}

//template<>char *maximum<char *> (char *a, char *b) {return "a";}; //ili:
template<>char *maximum(char *a, char *b) {return "a";};  // specijalizacija za stringove

// Mozemo a ne moramo pisati argument specijalizacije (zakljucuje se na osnovu tipova parametara
// argument za specijalizaciju sablona)

void f() {
    char *m = maximum<char*>("alfa", "beta");   // ili:
    const char *n = maximum("alfa", "beta");      // Poziva definisanu (negenericku funkciju maximum ako takva postoji)
}

// Obicna funkcija uvek prioritet na osnovu bilo kakvo generisanje iz sablona

//      GENERICKI METODI

// U jednoj generickoj klasi mogu svi konstruktori i metodi biti negericki
// a MOGU BITI i genericki metodi i konstruktori
// Kao i genericka globalna funkcija

// Vazi isto i za genericku i negenericku klasu

// Genericki metodi NE MOGU biti VIRTUELNI
// Moze postojati virtuelni metod u generickoj klasi ali NE MOZE biti genericki

// Konstruktor moze biti genericka funkcija
// Jedino destruktor ne moze biti genericki

// Genericki metod moze biti i staticki
// Ako je nestaticki metod, poziva se preko objekta

// Moguce je pisati ispred imena metoda kljucnu rec template - ali neki prevodioci to ne traze

// ime metoda<argumenti> - ispred imena metoda template
// ime klase:: template ime_metoda<argumenti sablona metoda>(argumenti funkcije metoda)

class A {
    double x;
public:
    // Genericki Konstruktor:
    template<typename T> A(const T &t) : x(t) {}    // inicijalizujemo double na osnovu T
    // Definisali smo

    template<typename T> void m(const T &t);        // Genericki metod
    // Samo deklaracija
};
template<typename T>  void A::m(const T &t) { x = t; }
// A je obicna klasa (samo je metod genericki)

void f1() {
    // Generisu se konkretni konstruktori tipa:
    A a1(5);        // A::A(const int &)
    A a2(1.2);      // A::A(const double &)
    A a3('q');      // A::A(const char &)

    // Neki prevodioci traze kada se navode eksplicitno argumenti sablona <int>
    a1.template m<int>(1.2);       // A::m(const int &)
    a1.template m<char>(3.4);      // A::m(const char &)
    // Radi se konverzija (eksplicitno smo naveli tip parametra sablona)

    a1.m(3.4);                     // A::m(const double &)
}

// Genericki metod genericke klase
template <typename T> class B {     // Sablonska klasa
        T t;                // t zavisi od tipa T
    public:
        template<typename U> void m(const U&);  // m zavisi od tipa U
        // samo definicija
    };

template <typename T> template<typename U> void B<T>::m(const U &u) { t = u; }
// Potrebno navesti i jedan i drugi naziv sablona
// Samo ime B ne znaci nista - sablonska klasa

void f2() {
    B<int> b1;          // Konkrektna klasa za tip int
    B<float> b2;        // Klasa za tip float
    b1.m(55);        // Automatski se zakljucuje po parametru sablona u da je U tip int
    b2.m(55);

    b2.template m<char>(55); // Eksplicitno smo naveli sta je U
    // Generisali smo metod m za karaktere (vrsi se konverzija - implicitna)
}

//      UNUTRASNJE GENERICKE KLASE

// Unutrasnje klase mogu biti genericke
// Koncept ugnjezdenja klasa - u obicnoj klasi mogla biti ugnjezdena klasa

// Bilo koja kombinacija koja je sablonska koja nesablonska

template<typename T> class C{
    public:
        template<typename U> class D;       // Ugnjezdena klasa D (zavisi od drugog tipa)
        // Samo deklaracija klase D unutar tela
    };

// Definicija klase
template <typename T> template <typename U> class C<T>::D{
public:
    // metod je negenericki (ali moze biti i on genericki)
    void m(const U&);
};

// definicija metoda m
template <typename T> template <typename U> void C<T>::D<U>::m(const U &u) {
    /***/
}

void f3() {
    C<int> c;
    C<double>::D<char> d; // generise se spoljasnja klasa za tip double i njena ugnj. klasa za char
    d.m(true);         // pozivamo obicni metod - true se konvertuje u tip char
}

//          NIJE ZA ISPIT - PROSTORI IMENA

//  PROBLEM KONFLIKTA IMENA

// Dodeljivanje istog imena vise u vise promenljivih
// Linker se buni - dve definicije podatka sa istim imenom
// Proizvoljno mnogo deklaracija - ali jedna definicija

class A;
class A;
// Moze

// Fundamentalna razlika izmedju prostora imena i klasa:
// Prostori imena NEMAJU OBJEKTE
// Ista imena su mogu pojaviti i u drugom prostoru imena (nece praviti konflikt)
// Puno ime je ime_prostora::ime_iz_prostora

// Prostor imena ne menja ni nacin povezivanja, ni zivotni vek objekata
// Cisto nacin imenovanja

//  OSOBINE PROSTORA IMENA

// Otvoreni su - mogu se nadovezivati
// npr. prostor imena namespace A{ nemaspace B {}} pa opet namespace A{... - nadovezujemo se na prethodni PI}
// Mozemo koristiti barem ono sto je pre deklarisano - ne mora biti definisano

// dat1.h
namespace N {
    int a = 100;            // definicija
    double f() {return 0.0;} // definicija funkcije
    extern char b;      // globalni podatak (deklaracija zbog extern-a)
    float g(float);     // deklaracija funkcije g(float)
}
// Definicije i deklaracije na globalnom nivou - ali su imena u okviru prostora imena A

namespace M {
    double a = 1.0;         // potpuno razlicita memorijska lokacija
    // drugo puno ime
}

namespace N {       // formira se unija (nastavljamo prostor imena N)
    extern float x;
    char b = 'b';   // definicija podatka b (kojeg smo prethodno deklarisali)
    char h();       // deklaracija f-ja
}

// dat1.cpp
//#include "dat1.h"

namespace N {
    float x= 0.0f;      // definicija podatka x (zato sluzi extern - definise se
    // u spoljasnjoj datoteci)
    float g(float x) {return x/2;}  // definicija funkcije g(float)
}

//      UPOTREBA PROSTORA IMENA

// Unutar prostora imena sva imena mozemo dohvatati prostim imenovanjem
// Izvan prostora imena:
// (1) dohvatanje pojedinacnog imena na jednom mestu
// Identifikator_prostora_imena::Ime_iz_prostora_imena
// (2) uvoz jednog imena
// using Identifikator_prostora_imena::Ime_iz_prostora_imena
// (3) uvoz svih imena iz prostora
// using identifikator_prostora_imena

//      PRAVILA UPOTREBE UVEZENIH IMENA

// Najprostije pravilo: potrebno da su imena jednoznacna

// Neko lokalno ime prostim navodjenjem, uvezeno ime navodjenjem

// Using namespace dva_prostora_imena
// ako se u njima koristilo isto ime koristimo nacin (1)

// Navodjenjem :: ispred funkcije doseg prostora imena se prosiruje na telo funkcije

void l() {
    int p = N::a;
    double q = M::a;

    using N::x;
    float r = x;    // N::x

    using namespace N;
    a = 1;          // A::a
    float s = g(x); // A::g(A::x)

    using namespace M;
//    int t = a;      // ! GRESKA (viseznacno - malo a u oba prostora)
    // nece se buniti prevodilac samim uvodjenjem
    int u = N::a;
    double v = M::a;

    using N::a;
    int w = a;      // N::a - opredelili smo se za jedan prostor imena
    // vise nije konflikt imena
    // Iz M opet M::a
}

//      ANONIMNI (BEZIMENI) PROSTOR IMENA

// Sluzi za nesto sasvim drugom
// Imena u anonimnom prostoru imena nije ogranicen na prostor imena

// Ona postaju globalna imena (vaze do kraja datoteke) - SA UNUTRASNJIM POVEZIVANJEM
// Kao da smo stavljali static za svaki globalni podatak - vrsi unutrasnje vezivanje

namespace {
    int a = 1;
}

int b = 2;

namespace K {   // imenovani prostor imena
    int a = 3;
    int b = 4;
}

void g() {
    int o = a;      // ::a (iz anonimnog prostora)
    int p = b;      // ::b (globalna promenljiva)
    int q = K::a;
    using namespace K;
//    int r = a;  // ! GRESKA ::a ili A::a ?
    int s = ::a;
    int t = K::a;
//    int u = b;      // ! GRESKA: ::b ili A::b ?
    int v = ::b;
    int w = K::b;
    int b = 5;  // def. lokalne promenljive b
    int x = b;  // lokalno b (NAJVECI PRIORITET)
    int y = ::b;    // globalno b
    int z = K::b;
}

//      UKLAPANJE PROSTORA IMENA

// Moguce je definisati ugnjezdene prostore imena
// Doseg spoljasnjeg prostora preko uklopljenog (obrnuto ne vazi)

// Iz unutrasnjeg prostim imenovanjem nesto iz obuhvatajuceg
// Obrnuto ne vazi
// U delu spoljasnjeg prostora imena iza unutrasnjeg prostora potrebno pisati
// ime, identifikator tog ugnjezdenog prostora imena

namespace L {
    int a = 1;
    int f() {return 2;}
}

//      STANDARDNI PROSTOR IMENA

// Imena u zaglavljima standardne biblioteke su smestena u prostoru std
// Ako navodimo <iostream.h> - nisu u prostoru std (obicna globalna imena)
// C++ preporucuje koriscenje imena zaglavlja bez .h (.h c-stil)

#include <iostream>
using namespace std;
int main() {
    int n;
    cout << "n";
}

//      ZAGLAVLJA STANDARDNIH BIBLIOTEKA

// Pandani C biblioteka - bez .h i c na pocetku
// <cstdlib> - <stdlib.h> itd...