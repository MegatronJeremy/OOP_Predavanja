#include <iostream>

using namespace std;

class Kompleksni {
public:
    Kompleksni(double r = 0.0, double i = 0.0);

//    Kompleksni operator+(Kompleksni c) {      // implementacija kroz nestaticki metod
//        return Kompleksni(real + c.real, imag + c.imag);
//    };

    friend Kompleksni operator+(Kompleksni, Kompleksni); // implementacija kroz globalnu funkciju
    friend Kompleksni operator-(Kompleksni, Kompleksni);

    Kompleksni operator!(); // unarni operator

    friend Kompleksni operator~ (Kompleksni); // unarni operator kroz globalnu funkciju

//    Kompleksni operator-(Kompleksni);   // binarni operator - kao metod

private:
    double real, imag;
};
Kompleksni::Kompleksni(double r, double i) : real(r), imag(i) {}
Kompleksni operator+(Kompleksni c1, Kompleksni c2) {
    Kompleksni c;
    c.real = c1.real + c2.real;
    c.imag = c1.imag + c2.imag;
    return c;
}
Kompleksni operator-(Kompleksni c1, Kompleksni c2) {
    return Kompleksni(c1.real-c2.real, c1.imag - c2.imag);  // Eksplicitni poziv privremenog objekta
}

void komp() {
    Kompleksni c1(1.0, 1.0), c2(2.0, 2.0), c3, c4;
    c3 = c1 + c2;       // Poziva se operator+(c1,c2)
    c4 = c1 - c3;       // Poziva se operator-(c2,c3)
};
// Preklapanje operatora nije moguce za . .* :: ?: <--- tacke; sizeof, alignof, typeid, throw <--- kljucne reci
// Unapred definisani operator za korisnicki tip: = & . , (dodela vr, uzimanje adr, pristup clanu, lancanje)
// Za izvedene (pokazivacke tipove) definisani su: * -> []
// Operatorski metodi ne mogu biti staticki (osim new i delete)

// Podrazumevano znacenje operatora = je kopiranje objekta clan po clan, operator = vraca lvrednost

int main() {

}
