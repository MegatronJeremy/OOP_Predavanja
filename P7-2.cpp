//      INICIJALIZACIJA I DODELA VREDNOSTI

// Inicijalizacija objekta pri kreiranju i dodela vrednosti se razlikuju
//  - inicijalizacija podrazumeva da objekat jos ne postoji
//  - dodela podrazumeva da objekat sa leve strane operatore vec postoji

// Inicijalizacija se vrsi uvek kada se kreire objekat:
//  - staticki, automatski, dinamicki, privremeni i klasni clan

// Inicijalizacija poziva konstruktor, a ne operator dodele
//  - konstruktor se poziva cak iako je notacija za incijalizaciju simbol =
//  - ako je izraz sa desne strane simbola =
//      istog tipa kao i objekat koji se kreira, poziva se konstruktor kopije ili premestanja
//      razlicitog tipa u odnosu na objekat koji se kreira, poziva se konstruktor konverzije
//      u oba slucaja moze biti pozvan i konstruktor sa vise parametara,
//      ako ostali parametri imaju podrazumevane vrednosti

// Dodelom se naziva izvrsavanje izraza sa operatorom dodele =
//  - operator doedle se moze preklpiti pisanjem operatorske funkcije operator=

// Podrazumevano znacenje operatora = je kopiranje objekta clan po clan
//  - pri kopiranju atributa primitivnog tipa vrsi se kopiranje vrednosti
//  - pri kopiranju atributa tipa klase
//      pozivaju se operatori = odgovarajucih klasa atributa
//  - pri kopiranju clana klase tipa pokazivaca
//      kopirace se samo taj pokazivac, a ne i pokazivana vrednost/objekat
//      kada treba kopirati i pokazani objekat treba da se preklopi operator=

// Operatorska funkcija operator= mora biti nestaticki metod
// Ugradjena varijanta vrsi plitko kopiranje

// Najcesca realizacija:
//  - prvo se ispita da nije slucaj poziva a=a; ako jeste, nista se ne radi
//  - zatim se unistavaju stari delovi levog operanda
//    (nije neophodno, pogotovo ako su novi delovi iste velicine)
//  - zatim se kopiraju (ili premestaju) delovi desnog operanda

class X{
public:
    X &operator=(const X &x);
};

X& X::operator=(const X &x) {
    if (&x != this) {
        // unistavaju se delovi starog *this;
        // formiraju se novi delovi;
        // kopira se sadrzaj iz x
    }
    return *this;
}
// copy-and-swap idiom (alternativa kopiraj(x), premesti(x), brisi) <-- this i kopija na steku se zamene

// Postoji kopirajuca i premestajuca varijanta operatora dodele
// Premestajuca se primenjuje na nvrednosti, odlucuje prevodilac
// Nema razlike u semantici, samo u efikasnosti

// Obe varijante imaju ugradjene (implicitne) definicije
//  - atributi primitivnog tipa se prosto kopiraju
//  - atributi klasnog tipa se formiraju kopirajucim/premestajucim operatorom=

// Ugradjena kopirajuca dodela se brise
//  - ako se u klasi definise premestajuci konstruktor ili premestajuca dodela
//  - moze se restaurirati sa =default

// Ako u klasi ne postoji premestajuca dodela, koristi se kopirajuca dodela

#include <iostream>
#include <cstring>

using namespace std;

class Tekst {
public:
    Tekst(const char* niz);
    Tekst(const Tekst &t) { kopiraj(t); }     // kopirajuci konstruktor
    Tekst(Tekst &&t) { premesti(t); }     // premestajuci konstruktor
    Tekst &operator=(const Tekst&);          // kopirajuci operator=
    Tekst &operator=(Tekst&&);               // premestajuci operator=
    ~Tekst(){ brisi(); }                     // destruktor
private:
    char *niska;
    void kopiraj(const Tekst &t) {
        niska = new char[strlen(t.niska)+1]; // zauzimanje prostora
        strcpy(niska, t.niska);              // kopiranje niske
    }
    void premesti(Tekst &t) {niska = t.niska; t.niska = nullptr;}
    void brisi() {delete []niska; niska = nullptr;}
};

Tekst &Tekst::operator=(const Tekst &t) {
    if (&t!=this) {
        brisi();
        kopiraj(t);
    }
    return *this;
}
Tekst &Tekst::operator=(Tekst &&t) {
    if (&t!=this) {
        brisi();
        premesti(t);
    }
    return *this;
}

void equ() {
    Tekst a("Pozdrav!"),        // Tekst(const char*)
            b = a,                  // Tekst(const Tekst&)
            c = Tekst("123");   // Tekst(Tekst&&), a mozda moze i jedan konstruktor (optimizacija)
    a = b;                          // Tekst::operator=(const Tekst&); (b je stabilan objekat)
    b = Tekst("ABC");           // Tekst::operator=(Tekst&&);   (nestajuci objekat)
}

// Za preklapanje prefiksnih oblika operatora ++ i --:
//  - koriste se uobicajene operatorske funkcije
//      u obliku metoda klase T:                    T &operator@@()
//      u obliku globalne (prijateljske) funkcije:  T &operator@@(T&)

// Za preklapanje postfiksnih oblika operatora ++ i --:
//  - operatorska funkcija sadrzi i jedan dodatni argument tipa int i to:
//      u obliku metoda klase T:                    T operator@@(int)
//      u obliku globalne (prijateljske) funkcije:  T operator@@(T&, int)
// Ako se za poziv funkcije koristi postfiksni ++ ili --
//  -> parametar tipa int ima vrednost 0
// Ako se za poziv funkcije koristi notacija
//      t.operator@@(k) ili operator@@(t,k) gde je @@ ili ++ ili --
//  -> moze biti k!=0

// Operator [] je binarni operator kojem odgovara funkcija operator[]()
// Operatorska funkcija mora da bude nestaticki metod
//  - funkcija operator[]() ne moze da bude globalna (prijateljska) funkcija
// Parametar:
//  - kod standardnog indeksiranja indeksni izraz mora biti celbrojnog tipa
//  - kod preklopljenog operator [] indeksni izraz moze biti proizvoljnog tipa
// Pozivanje:
//  - zbirka[ind] je ekvivalent izrazu zbirka.operator[](ind)
// Preklapanje operator [] u nekoj klasi omogucava izraze sa o[i], gde je o objekat date klase
// Dva potpisa funkcija:
//  Tip &operator[](indeks);                // za promenljive zbirke
//  const Tip &operator[](indeks) const;    // ze nepromenljive zbirke
// obj[ind] != *(obj+ind)

// Operator () je binarni operator kojem odgovara funkcija operator()()
// operator()() mora da bude nestaticki metod
//  - funkcija operator()() ne moze da bude globalna (prijateljska) funkcija
// operator() <-- za funkcijske klase (funkcijske objekte)

// Operator -> je binarni operator, medjutim, preklapa se kao unarni funkcijom operator->()
// Operatorska funkcija operator->() mora da bude nestaticki metod
//  - funkcija operator->() ne moze da bude globalna (prijateljska) funkcija
// Parametri:
//  - funkcija operator->() mora biti bez parametara (unarni operator)
// Pozivanje:
//  - o->clan je ekvivalent izrazu (o.operator->())->clan
// Rezultat:
//  - treba da bude tipa pokazivaca na objekat klase koja sadrzi clan ili
//  - objekat (ili referenca) klase za koju je takodje definisan operator->
// operator->() <-- pametni pokazivaci (binarni operator, * je unarni operator)

// Odbrojavaju se indirektni pristupi objektu (strukture)
struct Y{int m;};
class Yptr {    // pametni pokazivac
    Y *p;       // glupi pokazivac
    int bp;
public:
    Yptr(Y *py) : p(py), bp(0) {}       // konstruktor
    Y &operator*() {bp++; return *p;}
    Y *operator->() {bp++; return p;}
};

void smart() {
    Y y; Yptr pp = &y;      // poziva se konstruktor
    (*pp).m=1;              // poziva se (pp.operator*()).m;
    int i=pp->m;            // poziva se (pp.operator->())->m;
                            // bp == 2
}