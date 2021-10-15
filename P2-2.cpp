/**/
typedef unsigned long long int Ceo1;
using Ceo2 = unsigned long long int; // isto kao Ceo1
typedef int Niz1[10]; // ne moze: typedef int[10] Niz1
using Niz2 = int[10];
typedef int (*PFun1) (int, int);
using PFun2 = int (*) (int, int);
/**/

/*
//decltype (izraz1) promenljiva // izraz1 se ne izracunava
int x = 1;
double y = 1.5;
decltype(x) a = x;      // int a (pridruzujemo tip x sa vrednoscu x kao inicijalizaciju)
decltype(++x+y) b=++x+y; // double b    b==3.5 (bez bocnih efekata u prvoj zagradi)
decltype(y) c = 2;      // double c     c==2.0
decltype(x) d = 2.5;    // int d    d==2
*/

/*
//auto int a = 10; // ! GRESKA
int x = 1;
double y = 2.5;
auto a = x;     // int a
auto b = ++x + y;   // double b
auto c = &a;    // int *c
*/

/*
auto f() {return 1;}    // tip rezultata je int
auto g();       // tip rezultata je neodredjen (samo deklaracija funkcije)
//auto a=g();     // ! GRESKA
auto g() {return 0.5;}      // tip rezultata je double
auto b = g();       // tip b je double
*/

const float pi = 3.14f; const char plus = '+'; // umesto define za nepromenljive podatke (simbolicke konstante - ovako je tipizirano)
int i = 10; const int c = i;


char niz[] = {'a', 's', 'd', 'f', 'g', 'h', '\0'};
const char *pk = niz;   // pokazivac na konstantu
//pk[3] = 'a';        // ! GRESKA
//pk = "qwerty";  // ispravno (neki drugi string)

char *const kp = niz; // konstantni pokazivac na promenljivu
//kp[3] = 'a';        //ispravno
//kp = "qwerty";        // ! GRESKA

const char *const kpk = niz;    // konstantni pokazivac na konstantu
//kpk[3] = 'a';         // ! GRESKA
//kpk = "qwerty";       // ! GRESKA

char *strcpy(char *p, const char *q); //q zelimo da kopiramo
const char* h();
// *f() = 'a';  // ! GRESKA

#include <string>
using namespace std;
string f(string a) {
    string b = "Pozdrav!";
    if (a=="***") b = a + " " + b;
    return b;
}
string x = f("");