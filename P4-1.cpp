#include <bits/stdc++.h>

using namespace std;

//PREKLAPANJE IMENA FUNKCIJA (razlika ne moze biti samo povratna vrednost)
double max(double i, double j) {
    return (i > j) ? i : j;
}
const char* max(const char *p, const char *q) {
    return (strcmp(p, q) >= 0) ? p : q;
}

int &elem(int *a, int i) {
    return a[i];
}
//const int &elem(const int *a, int i) { // ne moze biti sa leve strane znaka dodele vrednosti
//    return a[i];
//} //Zbog const int *a druga funkcija moze postojati

const int &elem(const int *a, int i) { // bolje - na valja da 2 funkcije imaju isto telo???
    return elem((int*)a, i);
} // radi se implicitna konverzija u const int

int *adrE1(int *a, int i) {
    return a+i;
}
const int *adrE1(const int *a, int i) {
    return a+i;
}

void name_overloading() {
    double r = max(1.5, 2.5); // max(double, double) double literali
    double p = max(1, 2.5); // (double)1; max(double, double)
    const char *q = max("Pera", "Mika"); // max(const char*, const char*) - C-string (niz niski)

    int a[20], i = 10;
    const int b[20] = {0};
    elem(a, i) = 1;
//    elem(b, i) = 1; //!GRESKA - konstantna lvrednost
    int x = elem(b, i);
    *adrE1(a, i) = 2;  //adresa na a+i - treba derefencirati *(a+i)
//    *adrE1(b, i) = 2;  // ! GRESKA
    int y = *adrE1(b, i);
} //Prioriteti slaganja funkcija: Slaganje tipova -> Standardne konverzije -> Korisnicke konverzijeo

[[napomena]] // anotacije prevodioc moze da zanemari
[[noreturn]] // funkcija se ne vraca

// ::, new, delete, .*, ->*, typeid, throw (izuzeci),
// alignof (udaljenost u bajtovima do sl. slobodne mem. lokacije), cast operatori - novi u c++

//Prefiksni ++ i -- rezultat je lvrednost
void operatori() {
    int x = 1, a = 0, b = 0;
    ++x = b;    //lvrednost
    //    x++ = b; //dvrednost
    x?a:b=1; //if(x) a=1; else b=1; //Rezultat ternarnog izraza je lvrednost
}

//Prioriteti operatora (najmanji -> najveci):
// , ; throw ; =, +=, -=, /=... ; ?: ; || ; && ; | ; ^ ; & ; ==, !=; (operatori dodele grupisu <-)
// <, <=, >, >= ; <<, >> ; +, - ; *, / ; .*, ->* ; !, ~, ++a, --a, +, *, &, (tip) sizeof, alignof, new, delete ;
// a++, a--, specificni_cast(4) typeid, [], (), '.', -> ; :: <- najveci prioritet ima

// CASTOVANJE ( C-cast (tip) izraz nije preporucljiv za koristenje zbog bezbednosti - ALI moze se sve ovde uraditi preko njega)
void cast() {
    //STATIC CAST (staticki cast za prenosive konverzije (za razlicite platforme; prevodioce)
    float a = 5.0; int i = static_cast<int> (a);
            //kao: int i = (int) a
    void *p = static_cast<void *> (&i); // moze void *p = &i (bezbedna konverzija)
    int *q = static_cast<int *> (p); // mora eksplicitni kast - preporuka staticka konverzija
    // nullptr (tipa void*) umesto 0 ili NULL (nullptr moze da se dodeljuje bez kasta)

    //REINTERPRET CAST
    int j = 1155;
    short *pj = reinterpret_cast<short *>(j); // vrednost konvertujemo u pokazivac short (dobija adresu 1155)
//    int k = reinterpret_cast<int>(pj); // k==j
    float *qj = reinterpret_cast<float *>(&j); //pristupamo lokaciji i kao float
    float &r = reinterpret_cast<float &>(j); // referenca na float

    //CONST CAST
    int l = 1;
    const int m = l;
    int *pm = const_cast<int *> (&m); //mora eksplicitno - menja se const lokacija - postaje promenljivi pokazivac
    *pm = 0; // OK

    double pi = 3.14;
    const double &cpi = const_cast<const double &>(pi);
                // ili : const double &cpi = pi; - bezbedna konverzija
    pi = 0.0; // OK
//    cpi = 0.0; // ! GRESKA
}

int main() {
    cast();
    return 0;
}