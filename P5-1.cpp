#include <iostream>

using namespace std;

// Modifikatori metoda & i &&
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

// KONSTRUKTOR NIJE METOD VEC FUNKCIJA KLASE
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

class Deo;

class Kontejner {
public:
    Kontejner() : deo(this) {}      // deo pokazuje na kontejner
private:
    Deo deo;  // Atribut klase kontejner
};

class Deo {
public:
    Deo(Kontejner *kontejner) : mojKontejner(kontejner) {}  // deo dobija pokazivac koji upisuje u mojKontejner
private:
    Kontejner *mojKontejner;
};

// DELEGIRAJUCI KONSTRUKTOR
class T {
public:
    T(int i) {}
    T():T(1) {} // delegirajuci: T(), ciljni: T(int) -- preko liste inicijalizatora
    T(char c) : T(0.5) {}   // ! GRESKA - rekurzija
    T(double d) : T('a') {}
};

int main() {

}
