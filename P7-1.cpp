//      POJAM PREKLAPANJA OPERATORA

// C++ dozvoljava preklapanje operatora
//  - drugi termin: preopterecenje operatora (operator overloading)
//  - definisu se nova znacenja operatora za korisnicke tipove (klase)
//  - princip je slican kao kod preklapanja imena funkcija

// Preklopljeni operatori za klasne tipove su specijalne operatorske funkcije

// Operatorske funkcije nose ima operator@ - @ predstavlja neki operator ugradjen u jezik

// Pozivanje operatorskih funkcija u izrazima:
//  izraz t1@t2 se tumaci kao:
//      - operator@(t1,t2)  // za operatorsku prijateljsku funkciju klase
//      - t1.operator@(t2)  // za operatorski metod klase

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

    friend Kompleksni operator~(Kompleksni); // unarni operator kroz globalnu funkciju

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
// Ne mogu da se menjaju znacenja opeartora za primitivne (standardne) tipove podataka
// Ne mogu da se uvode novi simboli za operatore
// Ne mogu da se menjaju osobine operatora: n-arnost, prioritet i asocijativnost

// Posebna ogranicenja: =, i++, i--, [], (), ->, (tip), new, delete

// Unapred definisani operator za korisnicki tip: = & . , (dodela vr, uzimanje adr, pristup clanu, lancanje)
// Dok se ne preklope (osim .), imaju podrazumevano znacenje

// Za izvedene (pokazivacke tipove) definisani su: * -> [] (indirektno adr, posr. pristup clanu, indeksiranje)
// Dok se ne preklope i oni imaju podrazumevano znacenje

// Vracene vrednosti operatorskih funkcija mogu da budu bilo kog tipa - moze i void
// Ako se simbol sastoji od slova (npr. new) mora se pisati odvojeno od kljucne reci operator

// Operatorske f-je ne mogu da imaju podrazumevane vrednosti argumenata

// Operatorski metodi ne mogu biti staticki (osim new i delete)

// Deo potpisa operatorskog metoda cine i modifikatori tekuceg objekta: const, volatile, & i &&

// Postojeci bocni efekti kod operatora za primitivne tipove ne podrazumevaju se za preklopljene operatore
//  - bocni efekti postoje kod:
//      operatora ++ i -- (prefiksnih i postfiksnih)
//      svih operatora dodele (=, +=, -=, *=, ...)
// Moze se preklopiti svaki od njih tako da nema bocni efekat (nije dobra praksa)
// Moze se napraviti bocni efekat kod operatora koji ga inace nema (ni to nije dobra praksa)

// Veze koje postoje izmedju operatora za primitivne tipove ne podrazumevaju se za preklopljene operatore
// npr. a+=b ne znaci automatski a=a+b

// Podrazumevano znacenje operatora = je kopiranje objekta clan po clan, operator = vraca lvrednost

// Operatorske funkcije mogu biti:
//  metodi ili globalne (prijateljske) funkcije

// Kod globalne operatorske funkcije bar jedan parametar mora biti klasnog tipa

// Ako je @ binarni operator (na primer +), on moze da se realizuje:
//  - kao metod klase X:        <tip> operator@(X)
//      poziv a@b se tumaci kao:    a.operator@(b)
//  - kao globaslna (prijateljska) funkcija: <tip> operator@(X,X)
//      poziv a@b se tumaci kao:    operator@(a,b)
// Nije dozvoljeno u programu da se nalaze obe ove funkcije

// Ako levi operand binarne operacije treba da bude standardnog tipa
//  --> mora se deklarisati globalna funkcija
//  - razlog: kod operatorskog metoda levi operand je skriveni argument
//      skriveni argument je uvek tipa klase ciji je metod f-ja clanica
//      standardni tipovi nisu klasni tipovi
//  - primer: Kompleksni operator-(double d, Kompleksni c)
//  - po pravilu, ovakva f-ja treba da bude prijatelj klasi drugog parametra (operanda)

// Operatorski metod ne dozvoljava konverziju levog operanda

int main() {

}
