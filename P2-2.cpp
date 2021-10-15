// Konverzija potrebna za:
// operatore ugradjenih tipova
// naredbe (if, for, do, while, switch)
// inicijalizacija objekta jednog tipa pomocu objekta drugog tipa

// Konverzija tipa moze biti:
// standardna - ugradjena u jezik ili
// korisnicka - definise je programer za svoje tipove

// Standardne konverziju su, na primer:
// Konverzije iz tipa int u tip float, ili iz tipa char u tip int, i sl.

// Konverzija tipa moze biti:
//      - implicitna - prevodilac automatski vrsi (ako je dozvoljena)
//      - eksplicitna - zahteva programer

// C kast, 4 C++ kast operatora, konverzioni konstruktor

/**/
void l(){
    typedef unsigned long long int Ceo1;
    using Ceo2 = unsigned long long int; // isto kao Ceo1

    typedef int Niz1[10]; // ne moze: typedef int[10] Niz1
    using Niz2 = int[10];

    typedef int (*PFun1)(int, int);
    using PFun2 = int (*)(int, int);
}
/**/

/**/
//decltype (izraz1) promenljiva // izraz1 se ne izracunava
void k() {
    int x = 1;
    double y = 1.5;
    decltype(x) a = x;      // int a (pridruzujemo tip x sa vrednoscu x kao inicijalizaciju)
    decltype(++x + y) b = ++x + y; // double b    b==3.5 (bez bocnih efekata u prvoj zagradi)
    decltype(y) c = 2;      // double c     c==2.0
    decltype(x) d = 2.5;    // int d    d==2
}
/**/

/**/
// Modifikator auto u jeziku C - automatska promenljiva (neobavezno)
// C++: automatsko odredjivanje tipa na osnovu izraza incijalizatora
void h() {
//    auto int a = 10; // ! GRESKA
    int x = 1;
    double y = 2.5;
    auto a = x;     // int a
    auto b = ++x + y;   // double b
    auto c = &a;    // int *c
}
/**/

/**/
auto f() {return 1;}    // tip rezultata je int
auto g();       // tip rezultata je neodredjen (samo deklaracija funkcije)
//auto a=g();     // ! GRESKA
auto g() {return 0.5;}      // tip rezultata je double
auto b = g();       // tip b je double
/**/

// Konstantni tip je izvedeni tip - specifikator const

const float pi = 3.14f; const char plus = '+'; // umesto define za nepromenljive podatke (simbolicke konstante - ovako je tipizirano)
int i = 10; const int c = i;    // moze da se i inicijalizuje nekonstantnim izrazom

// Za simbolicke konstante prevodilac ne mora da alocira memorijsku lokaciju

void m() {
    char niz[] = {'a', 's', 'd', 'f', 'g', 'h', '\0'};
    const char *pk = niz;   // pokazivac na konstantu
//    pk[3] = 'a';        // ! GRESKA
    char a[] = "qwerty";
    pk = a;  // ispravno (neki drugi string)

    char *const kp = niz; // konstantni pokazivac na promenljivu
    kp[3] = 'a';        //ispravno
//    kp = "qwerty";        // ! GRESKA

    const char *const kpk = niz;    // konstantni pokazivac na konstantu
//    kpk[3] = 'a';         // ! GRESKA
//    kpk = "qwerty";       // ! GRESKA
}

char *strcpy(char *p, const char *q); //q zelimo da kopiramo

// Vracena vrednost pokazivac na konstantu (ne moze se menjati ta vrednost)
const char *n() {return "abc";};
// *n() = 'a';  // ! GRESKA

// Konstantan izraz - vrednost moze da se izracuna za vreme prevodjenja
// Svi operandi u konstantnim izrazimu moraju biti konstantni
// Konstantan podatak se uvodi modifikatorom constexpr
// Inicijalizator mora biti konstantan izraz
// Konst. podatak je staticki i ima unutrasnje povezivanje (implicitno static)
// Razlika u odnosu na nepromenljivi podatak koji se uvodi sa const

void v() {
    int a = 1;              // Promenljiv podatak (promenljiva)
    const int b = a;        // nepromenljiv podatak
    const int C = 1;        // imenovana (simbolicka) konstanta
    constexpr int d = 1;    // konstantan podatak
    constexpr int e = d + C;
//    constexpr int f = a;    // ! GRESKA
//    constexpr int g = b;    // ! GRESKA
}

// Konstantne funkcije deklarisene i definisane modifikatorom constexpr na pocetku
// Sugestija prevodiocu da izracuna rezultat funkcije u toku prevodjenja
// Rezultat konstantan podatak
// Ako ne moze da se izracune vrednost na mestu - nije greska (rezultat nije konstantan podataka)
// Ne smeju imati bocne efekte

int C = 1;
constexpr int duplo(int x) {return 2*x;}
constexpr int a = duplo(1);  // a == 2
//constexpr int B = duplo(C);    // ! GRESKA
int M = duplo(C);               // M == 2

// Prostor imena grupise globalna imena
// namespace identifikator { sadrzaj } <-- sadrzaj: globalni podaci, funkcije, tipovi i ugnezdeni prostori
// pristup imenu i iz nekog prostora A: A::i (slozeno ime - razresenje dosega)
//                                      using A::i; (uvoz imena)
//                                      using namespace A; (uvoz svih imena iz prostora)

// Literal C++ niske je const char*, za razliku od literala C-niske (char*)

#include <string>
using namespace std;
string f(string a) {
    string b = "Pozdrav!";
    if (a=="***") b = a + " " + b;
    return b;
}
string x = f("");