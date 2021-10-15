#include <iostream>

using namespace std;

enum RadniDan{Pon, Uto, Sre, Cet, Pet};
RadniDan rdan = Pon;

enum OsnovnaBoja{Crvena, Zelena, Plava};
int OsnovnaBoja;
enum OsnovnaBoja b1 = Plava; // Kao u C-u
//OsnovnaBoja b2 = Zelena; // ! GRESKA

enum Dani {PO=1, UT, SR, CE, PE, SU, NE, POSLEDNJI=7}; // NE == 7 i POSLEDNJI == 7
//enum ime : pripadajuci_tip {imenovane_konstante}; // definisanje tipa umesto inta
//enum Broj : char {NAJMANJI = 1, NAJVECI = 1000};  ! GRESKA (prekoracenje char-a)

enum SemaforPesaci {CRVENO, ZELENO};
//enum SemaforVozila {ZELENO, ZUTO, CRVENO}; // ! GRESKA
enum struct SemaforPesaci2 {CRVENO, ZELENO}; // Doseg unutar zagrade (koristimo struct ili klasu)
enum struct SemaforVozila {ZELENO, ZUTO, CRVENO}; // Potrebno koristiti :: za prosirivanje dosega

struct X {
    int a;
    mutable int b;
};

void mtbl() {
    X x1;
    const X x2{};
    x1.a = 1;
    x1.b = 2;
//    x2.a = 3;     // ! GREKSA OBICNO POLJE
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

Tacka *pt;
void f() { pt = new Tacka(-1.1, 0.2); }

void din_obj() {
    // ako nema memorije vraca se bad_alloc umesto NULL (ili nullptr)
    X *x = new (nothrow) X; // izbegava se bacanje izuzetka

    int *pi = new int;
    Tacka *pt1 = new Tacka(5.0, 5.0);
    f();
    delete pt;  // delete vraca void (prvo destruktor za objekat pa se oslobadja zauzeti prostor); ako nije inicijalizovan obj. nema efekta
    Tacka2 *pt2 = new Tacka2[10]; // moze se inicijalizovati i niz objekata (da ga ima ovde)
    delete []pt2;    // unisti cijeli niz, redosled konstrukcije po rastucem indeksu, a za destrukcije obrnuto
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
