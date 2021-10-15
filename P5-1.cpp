#include <iostream>

using namespace std;

//      MODIFKATORI METODA & i &&
// Bez modifikator & ili && metod se moze primeniti na lvredsnot i dvrednost
// Modifikator & - tekuci objekat moze biti smao lvrednost
// Modifikator && - tekuci objekat moze biti samo dvrednot
// Deo potpisa metoda - mogu da postoje metodi ciji se potpisi razlikuju samo po ovom modifikatoru
class U {
public:
    int f() & {return 1;}   // objekat moze biti samo lvrednost
    int f() const& {return 2;} // samo const lvrednost
    int f() && {return 3;} // objekat moze biti samo dvrednost
};
void modifs() {
    U u1;
    const U u2 = u1;
    int i = u1.f(); // 1
    int j = u2.f(); // 2
    int k = U().f(); // 3 (eksplicitni poziv konstruktora - dodeljuje dvrednost)
}

//      KONSTRUKTOR - NIJE METOD VEC FUNKCIJA KLASE

// definise pocetno stanje objekta
// nema tip rezultata (cak ni void)
// ima proizvoljan broj parametara proizvoljnog tipa
//      - osim tipa klase ciji je konstruktor, ukoliko je jedini ili prvi, a ostali imaju PVA (podrazumevane vrednosti?)
//      - dozvoljen je tip pokazivaca i referenci na lvrednost i dvrednost date klase

// Uvek se implicitno poziva prilikom kreiranja objekta
// Pristup clanovima objekta unutar tela konstruktora - kao i u bilo kojem drugom metodu - this
// Konstruktor, kao i svako metod, moze biti preklopljen

// Podrazumevani konstruktor (PK):
//      - konstruktor koji se moze pozvati bez stvarnih argumenata (nema parametre ili ima sve parametre sa podr. vrednostima)

// Ugradjeni (implicitno definisan) podrazumevani konstruktor je:
//      - bez parametara i ima prazno telo

// Ugradjeni PK postoji samo ako klasa nije definisala ni jedan konstruktor:
//      - definisanjem nekog konstruktore se suspenduje (brise) ugradjeni PK
//      - moze da se restaurira navodjenjem deklaracija iza koje stoji = default

// Kada se kreire niz objekata neke klase, poziva se PK za svaki element
//      - redosled poziva PK elemenata je po rastucem redosledu indeksa

//      POZIVANJE KONSTRUKTORA

// Konstruktor se uvak poziva kada se kreira objekat klase:
//      - kada se izvrsava definicija statickog objekta
//      - kada se izvrsava defincija automatskog objekta
//      - kada se stvara dinamicki objekat operatorom new
//      - kada se stvarni argument klasnog tipa prenosi u formalni (parametar se incijalizuje stvarnim arg.)
//      - kada se kreira privremeni objekat, pri povratku iz funkcije (inicijalizuje se izrazom iz return naredbe)

//      ARGUMENTI KONSTRUKTORA

// Pri stvaranju objekta moguce je navesti inicijalizator iza imena
// Inicijalizator sadrzi listu argumenata konstruktora u zagradama
//      - zagrade mogu biti () ili {}
//      - ako se lista navodi u zagradam {}, moze se i pisati i = {...}
//      - nisu dozvoljene prazne zagrade () - to bi se prevelo kao deklaracija funkcije
// Moguca je i notacija <objekat> = <vrednost> - ukoliko se konstruktor moze pozvati sa samo jednim argumentom
// Poziva se onaj konstruktor koji se najbolje slaze po potpisu - kao kod preklapanja imena funkcija
// Konstruktor moze da ima podrazumevane vrednosti argumenata

class X {
    char a;
    int b;
public:
    X();
    X(char, int = 0);
    X(const char*); // nepromenljiva niska znakova
//    X(X); // ! GRESKA (ime date klase)
    X(X*);
    X(X&);      // Kopirajuci konstruktor
    X(X&&);     // Premestajuci konstruktor
};

X f() {
    X x1; // X()
    X x2{}; // X()
    X x3={}; // X()
    X x();  // dekl. f - je
    return x1;  // X&& <- privremeni objekat (Premestajuci konstruktor)
}

void g() {
    char c = 'a';
    const char *p = "Niska";
    X x1(c); // X(char, int = 0)
    X x2 = c;
    X x3(c, 10);
    X x4{c, 20};
    X x5 = {c, 30};
    X x6(p);    // X(const char*)
    X x7(x1);   // X(X&)
    X x8{x1};
    X x9 = {x1};
    X x10 = f(); // X(X&&) <-- = nije dodela vrednosti vec inicijalizacija
    X *p1 = new X; // X()
    X *p2 = new X();
    X *p3 = new X(c); // X(char, int)
    X *p4 = new X{c, 10};
}

//      KONSTRUKCIJE CLANOVA

// Pre izvrsavanja tela konstruktora
//      - incijalizuju se atributi prostih tipova
//      - pozivaju se konstruktori atributa klasnih tipopva
// Inicijalizatori mogu da se navedu i u zaglavlju definicije (ne deklaracije) konstruktora, iza znaka :
// Ako atribut ima inicijalizator u telu klase i u definiciji konstruktora, primenjuje se inicijalizator iz definicije
// konstruktora

class YY {
public:
    YY(int j) {};
};

class XX {
    YY y;
    int i = 0;  // Primitivan tip (nije bio dozvoljen inicijalizator ranije)
public:
    XX(int);
};
XX::XX(int k) : y(k+1), i(k-1) {};  // y = k + 1, i = k - 1 <-- Gazi se podr. vr.

// Inicijalizacija atributa - redosledom navodjenja u klasi
//  - bez obzira da li su primitivnog ili klasnog tipa
//  - bez obzira na redosled u listi inicijalizatora

// Navodjenje inicijalizatora u zaglavlju definicije konstruktora predstavlja
// specifikaciju inicijalizacije clanova

// Inicijalizacija je razlicita od operacije dodele koja se moze vrsiti jedino unutar tela konstruktora

// Inicijalizacija je neophodna:
//  - kada ne postoji podrazumevani konstruktor klase atributa
//  - kada je atribut nepromenljiv podatak
//  - kada je atribut referenca

// Do C++11 nije bila dozvoljena inicijalizacija atributa u definiciji klase
//  - jedini nacin je bio kroz inicijalizatore u definiciji konstruktora

//      PRIMER KONSTRUKCIJE

// Primer konstrukcije dva objekta od kojih jedan sadrzi drgi:
//  - objekat klase Kontejner sadrzi po vrednosti objekat klase Deo, pri cemu objekato
//    deo treba "zna" ko ga sadrzi

class Kontejner;

class Deo {
public:
    Deo(Kontejner *kontejner) : mojKontejner(kontejner) {}  // deo dobija pokazivac koji upisuje u mojKontejner
private:
    Kontejner *mojKontejner;
};

class Kontejner {
public:
    Kontejner() : deo(this) {}      // deo pokazuje na kontejner
private:
    Deo deo;  // Atribut klase kontejner
};

//      DELEGIRAJUCI KONSTRUKTOR

// U listi inicijalizatora definicije delegirajjuceg konstruktora moze da se navede
// poziv drugog (ciljnog) konstruktora iste klase

// Tada se pre izvrsenja tela delegirajuceg konstruktora izvrsava ciljni
// Kad se navodi ciljni konstruktor, u listi inicijalizatora sme da postoji samo on
// Ako dolazi do neposrednog ili posrednog rekurzivnog delegiranja - greska
//      - ne otkriva prevodilac, ulazi se u beskonacnu rekurziju

class T {
public:
    T(int i) {}
    T():T(1) {} // delegirajuci: T(), ciljni: T(int) -- preko liste inicijalizatora
//    T(char c) : T(0.5) {}
//    T(double d) : T('a') {} // ! GRESKA - rekurzija
};

int main() {

}
