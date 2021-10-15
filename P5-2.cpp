#include <iostream>
#include "Klase.h"

using namespace std;

class Y {
public:     // kopija moze biti samo lvrednost
    Y(const Y&) = delete; // zabrana kopiranja (implicitnog) - takodje se suspenduje ako pravimo premestajuci konstruktor
//    Y(const Y&) = default; // restauriramo implicitni konstruktor
};

// KONSTRUKTOR KOPIJE
class XX {
public:
    XX(int);
    XX(const XX&);
    //...
};
XX f(XX x1) {
    XX x2 = x1;     // poziv konst. kopije XX(XX&) za x2
    return x2;      // poziv konst. kopije za privremeni
}                   // objekat u koji se smesta rezultat
void g() {
    XX xa = 3, xb = 1;  // argumenti za poziv konstruktora
    xa = f(xb);     // poziv konst. kopije samo za parametar x1,
                    // a u xa se samo prepisuje
                    // privremeni objekat rezultata, ili se
                    // poziva XX::operator = ako je definisan
}

// PREMESTAJUCI KONSTRUKTOR (postavlja se din. atribut na nullptr zbog destruktora - da se ne bi i u premestenom objektu unistio)
class Niz {
    double *a;
    int n;
public:
    Niz(Niz &&niz) {
        a = niz.a;
        niz.a = nullptr;
        n = niz.n;
    }
};       // Ako ne postoji premestajuci konstruktor zove se kopirajuci konstruktor (postoji i implicitni premestajuci konstruktor
            // koji se suspenduje definicijom bilo cega
Niz f(Niz niz) {return niz;}    // Vraca se objekat klase po vrednosti (dvrednost)

// KONVERZIONI KONSTRUKTOR (konverzija izmedju tipova klasa - mogu se cak i implicitno izvrsavati ako je jednoznacan izbor konverzije -
// - EXPLICIT - DA SE NE IZVRSAVAJU)
class T {
public:
    T(int i);   // konstruktor
};
T f1(T k) {
    //...
    return 2;       // poziva se konstruktor T(2)
}
void h() {
    T k(0);
    k=f1(1); // poziva se konstruktor T(1) i dodela vrednosti
}

// DESTRUKTOR (obrnut redosled od poziva konstruktora)
class X2 {
public:
    ~X2() {cout << "Poziv destruktora klase X!\n";}
};

int main() {
    Complex c1(1, 2.4), c2; // Implicitni poziv
    c2 = c1.zbir(Complex(3.4, -1.5));   // Privremeni objekat <-- eksplicitni poziv konstruktora
    Complex c3 = Complex(0.1, 5);   // Privremeni objekat se kopira u c3 (uslovno - kopirajuci konstruktor, ali kompajler moze odmah

   // inicijalizovati atributima privremenog objekta

    X2 x;
    x.~X2(); // ne preporucuje se jer objekat nastavlja da zivi
    //... --> ispis (poziva se implicitno destruktor kad objekat izlazi iz svog opsega)
}