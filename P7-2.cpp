#include <iostream>
#include <cstring>

using namespace std;

// copy-and-swap idiom (alternativa kopiraj(x), premesti(x), brisi) <-- this i kopija na steku se zamene


class Tekst {
public:
    Tekst(const char* niz);
    Tekst(const Tekst &t) { kopiraj(t); }
    Tekst(Tekst &&t) { premesti(t); }
    Tekst &operator=(const Tekst&);
    Tekst &operator=(Tekst&&);
    ~Tekst(){ brisi(); }
private:
    char *niska;
    void kopiraj(const Tekst &t) {
        niska = new char[strlen(t.niska)+1];
        strcpy(niska, t.niska);
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
    Tekst a("Pozdrav!"), // Tekst(const char*)
            b = a,          // Tekst(const Tekst&)
            c = Tekst("123");   // Tekst(Tekst&&), a mozda moze i jedan konstruktor (optimizacija)
    a = b;      // Tekst::operator=(const Tekst&); (b je stabilan objekat)
    b = Tekst("ABC");   // Tekst::operator=(Tekst&&);   (nestajuci objekat)
}

// prefiksni ++ i -- vracaju lvrednost a postfiksni vracaju dvrednost
// preklapanje operatora [] <-- jedna za promenljive i jedna za const zbirke
// operator() <-- za funkcijske klase (funkcijske objekte)
// operator->() <-- pametni pokazivaci (binarni operator, * je unarni operator)

struct X{int m;};
class Xptr { // pametni pokazivac
    X *p; // glupi pokazivac
    int bp;
public:
    Xptr(X *px) : p(px), bp(0) {} // konstruktor
    X &operator*() {bp++; return *p;}
    X *operator->() {bp++; return p;}
};

void smart() {
    X x; Xptr pp = &x;  // poziva se konstruktor
    (*pp).m=1;      // poziva se (pp.operator*()).m;
    int i=pp->m;    // poziva se (pp.operator->())->m;
}