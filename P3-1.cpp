#include <iostream>

using namespace std;

// Identifikatori nabrajanja, struktura i unija mogu da se koriste kao oznaka tipa
// Nije potrebna kljucna rec enum, struct, union

enum RadniDan{Pon, Uto, Sre, Cet, Pet};
RadniDan rdan = Pon;

enum OsnovnaBoja{Crvena, Zelena, Plava};
int OsnovnaBoja;            // objekat (promenljiva) u dosegu sa istim identifikatorom
// identifikator oznacava objekat, a ne tip

enum OsnovnaBoja b1 = Plava; // Kao u C-u
//OsnovnaBoja b2 = Zelena; // ! GRESKA

// Tip nabrajanja definise niz simbolickih konstanti
// Za podatke tipa nabrajanja definisana je samo operacija dodele vrednosti nabrajanja promenljivoj istog tipa
//      Eksplicitna konverzija celobrojne vrednosti u tip nabrajanja je obavezna
//      Ne otkriva se greska konvertovana vrednost nije u opsegu nabrajanaj
// Automatska konverzija u int

enum Dani {PO=1, UT, SR, CE, PE, SU, NE, POSLEDNJI=7}; // NE == 7 i POSLEDNJI == 7
void d() {
    Dani dan = SR;
//  Dani d = 3;             // ! GRESKA, obavezna eksplicitna konverzija
//  dan++;                  // ! GRESKA, nije definisana operacija ++
    dan = (Dani) (dan + 1); // implicitna promocija dan u int pa eksplicitna konverzija rezultata
    if (dan < NE) {}        // dozvoljeno je i: dan < 7
    dan = (Dani)8;          // Ne pojavljuje se (logicka) greska
}

//  enum ime : pripadajuci_tip {imenovane_konstante}; // definisanje tipa umesto inta
//  enum Broj : char {NAJMANJI = 1, NAJVECI = 1000};  ! GRESKA (prekoracenje char-a)

enum Days : char {MO, TU, WE, TH, FR, SAT, SUN};
Days dan = (Days) 10;   // greska koju ne otkriva prevodilac

// Imenovane konstante nabrajanja imaju isti doseg kao i imena odgovorajucih tipova nabrajanja
enum SemaforPesaci {CRVENO, ZELENO};
//enum SemaforVozila {ZELENO, ZUTO, CRVENO}; // ! GRESKA

// Modifikator struct ili class iza enum:
enum struct SemaforPesaci2 {CRVENO, ZELENO}; // Doseg unutar zagrade (koristimo struct ili klasu)
enum struct SemaforVozila {ZELENO, ZUTO, CRVENO}; // Potrebno koristiti :: za prosirivanje dosega

SemaforPesaci semP = SemaforPesaci::CRVENO;
//SemaforVozila semV = ZUTO;  // ! GRESKA - nije u dosegu

// Obavezna eksplicitna konverzija u ceo broj
int i = (int) SemaforVozila::ZUTO;

// Lista vrednosti u zagradama (inicijalizatorska lista): {vrednost, vrednost,... vrednost}
// Mogu da se koriste za incijalizaciju svih vrsta podataka (cak i za proste tipove)
// Greska je ako na neku vrednost treba primeniti nebezbednu konverziju tipa

//int j = {5.5}; // ! GRESKA

// Vrednosti se dodeljuju redom elementima niza, odnosno poljima strukture (za unije - tako se moze postaviti samo prvo polje)
// Manjak vrednosti nulama - visak je greska
// Inic. lista je bezimeni podatak ciji tipovi vrednosti zavise od okruzenja
// Mogu da se koriste i pri dodeli vrednosti, osim za nizove
// Argumenti funkcija i izrazi u naredbama return mogu biti ovakve liste

void l() {
    int i1 = {1}, i2{1}, i3 = {i1 + i2};
    i1 = {2};
//    int i4 = {0.5}; // ! GRESKA - nije bezbedno
    int *pi = {&i1};
    int n1[5] = {1, 2, 3}, n2[5] {1, 2, 3}, n3[]{1,2,3};
    int m[][3]{{1,2}, {}, {1,2,3}};
//    n1 = {4,5,6};   // ! GRESKA
    struct S1{int a, b;};
    S1 s11 = {1,2}, s12{1,2}; s11={3,4};

    struct S2{int a; S1 b; int c[3];};
    S2 s21 = {1, {2,3}, {4,5,6}}, s22{1,2,3,4,5,6};
    s21 = {6, {5,4}, {3,2,1}};
}

// Unija bez imena predstavlja jedan objekat koji sadrzi u raznim trenucima podatke razlicitih tipova
// Identifikatori clanova imaju datotecki ili blokovski doseg, a ne strukturni kao kod unije sa imenom
// Clanovi bezimenih unija koriste se kao obicne promenljive
void j() {
    union{
        int i;
        double d;
        const char *pc;
    };
    i = 55; d = 123.456; pc = "ABC";
}
// Unija za koju je definisan barem jedan objekat ili pokazivac, ne smatra se bezimenom iako nema ime

// Uvek promenljiva polja (mutable)
struct X {
    int a;
    mutable int b;  // uvek moze da se menja (cak i za nepromenljiv objekat strukture)
};

void mtbl() {
    X x1;
    const X x2{};
    x1.a = 1;
    x1.b = 2;
//    x2.a = 3;     // ! GRESKA OBICNO POLJE
    x2.b = 4;       // ZA MUTABLE NE VAZI
}

struct Tacka {
    double a, b;
    Tacka(double a_, double b_) {
        a = a_;
        b = b_;
    };
};

struct Tacka2 {
    double a, b;
};

// Operator new alocira potreban prostor u memoriji za objekat datog tipa i zatim poziva konstruktor tipa

// Dinamicki objekat nastaje kada se izvrsi operacija new, a traje sve dok se ne izvrsi operacija delete

// Operator delete ime jedan operand tipa pokazivaca nekog tipa
// Ako pokazivac ne ukazuje na objekat kreiran pomocu new, posledice delte su nepredvidive
// Ako je pokazivac nullptr, delete nema efekta
// delete vraca void

Tacka *pt;
void f() { pt = new Tacka(-1.1, 0.2); }

void din_obj() {
    // ako nema memorije vraca se bad_alloc umesto NULL (ili nullptr)
    X *x = new (nothrow) X; // izbegava se bacanje izuzetka

    int *pi = new int;  // Vraca pokazivac na kreirani objekat
    Tacka *pt1 = new Tacka(5.0, 5.0);
    f();

    delete pt;  // delete vraca void (prvo destruktor za objekat pa se oslobadja zauzeti prostor); ako nije inicijalizovan obj. nema efekta

    Tacka2 *pt2 = new Tacka2[10]; // moze se inicijalizovati i niz objekata (da ga ima ovde)
    // Sve dimenzije niza osim prve treba da budu konstantni izraz
    // Promenljiv izraz mora biti takav da moze da se izracuna u trenutku izvrsavanja naredbe sa operatorom new

    delete []pt2;    // unisti cijeli niz, redosled konstrukcije po rastucem indeksu, a za destrukcije obrnuto

    // Redosled konstrukcije elemenata je po rastucem indeksu, dok je destrukcija po obrnutom redosledu
}

int main() {
    Dani dan = SR;
//    Dani d = 3; // ! GRESKA, obavezna eksplicitna konverzija
//    dan++; // ! GRESKA, nije definisana operacija ++
    dan = (Dani) (dan+1); // implicitna promocija dan u int (kad se sabere sa 1) pa eksplicitna konverzija rezultata
    if (dan < NE) {}    // dozvoljeno je i: dan < 7 (u relacionim izrazima)
    dan = (Dani) 8;     // ne prijavljuje se (logicka) greska

    SemaforPesaci2 semP = SemaforPesaci2::CRVENO;
//    SemaforVozila semV = ZUTO; // ! GRESKA - nije u dosegu
    int i =  (int) SemaforVozila::ZUTO; // Potrebna i za int eksplicitna konverzija kod structa (ili kod klase)

//  int j = {5.5}; // ! GRESKA (koriscenje inicijalizatorske liste ne vrsi implicitnu konverziju)
//  lista ne moze koristiti inicijalizatorsku listu za dodelu vrednosti
//  unija moze imati samo jednu vr. in. liste (za sva polja) - jer se gleda redosled clanova
//  int a[20] = {1}; //(prvo polje samo 1 - ostatak nule)

    int i1 = {1}, i2{1}, i3={i1+i2}; // OPERATOR INICIJALIZUJE VREDNOSTI
    i1 = {2}; // OPERATOR DODELE VREDNOSTI
//    int i4 = {0.5}; // ! GRESKA - nije bezbedno
    int *pi = {&i1};
    int n1[5] = {1,2,3}, n2[5]{1,2,3}, n3[]{1,2,3};
    int m[][3] {{1,2},{},{1,2,3}}; // 1 2 0  0 0 0  1 2 3
//    n1={4,5,6}; // ! GRESKA
    struct S1{int a, b;};
    S1 s11={1, 2}, s12{1,2}; s11={3,4}; // Dodela vrednosti moguca!
    struct S2{int a; S1 b; int c[3];};
    S2 s21 = {1, {2,3}, {4,5,6}}, s22{1,2,3,4,5,6};
    s21 = {6, {5,4}, {3,2,1}}; // Opet dodela moguca, cak i za listu!

    union {int k; double d; char *pc; };        // bezimena unija (polja unije globalne promenljive)
    k = 55; d = 123.456; pc = "ABC";
    return 0;
}
