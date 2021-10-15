#include <bits/stdc++.h>

using namespace std;

// PREKLAPANJE IMENA FUNKCIJA (razlika ne moze biti samo povratna vrednost)
// uslov: funkcijama se razlikuje broj i/ili tipovi parametara, odnosno potpisu funkcije
// Tipovi rezultata ne moraju da se razlikuju i nije dovoljno da se samo oni razlikuju

double max(double i, double j) {
    return (i > j) ? i : j;
}
const char* max(const char *p, const char *q) {
    return (strcmp(p, q) >= 0) ? p : q;
}
double r = max(1.5, 2.5);                // max(double, double)
double p = max(1, 2.5);                  // (double) 1; max(double,double)
const char *q = max("Pera", "Mika");    // max(const char*, const char*)

// Koja ce se funkcija stvarno pozvati, odredjuje se u fazi prevodjenja (mehanizam je potpuno staticki)
// Odredjivanje se vrsi prema slaganju potpisa funkcija (uporedjuje se broj i/ili tipovi argumenata i parametara)
// Potrebno da prevodilac moze jednoznacno da odredi koja funkcija se poziva

// Prevodilac priblizno ovako prioritira slaganje tipova argumenata:
// - potpuno slaganje tipova, ukljucujuci trivijalne konverzije (npr. iz tipa T[] u tip T*, ili iz T u T& i obrnuto)
// - slaganje tipova koriscenjem standradnih konverzija (npr. char u int)
// - slaganje tipova koriscenjem korisnickih konverzija

// PRISTUP ELEMENTIMA

int &elem(int *a, int i) {
    return a[i];
}   // Omogucava menjanje elementa niza

//const int &elem(const int *a, int i) { // ne moze biti sa leve strane znaka dodele vrednosti
//    return a[i];
//} //Zbog const int *a druga funkcija moze postojati

const int &elem(const int *a, int i) { // bolje - ne valja da 2 funkcije imaju isto telo
    return elem((int*)a, i);
} // radi se implicitna konverzija u const int

void pr() {
    int a[20], i=10;
    const int b[20] = {0};
    elem(a, i) = 1;
//    elem(b, i) = 1; // ! GRESKA
    int x = elem(b, i);
}

// Za funkcije koje vracaju pokazivac:
int *adrE1(int *a, int i) {
    return a+i;
}
const int *adrE1(const int *a, int i) {
    return a+i;
}   // Slicno vazi za polja struktura

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

[[noreturn]] // funkcija se ne vraca (npr. exit(parametar))
// ako postoji return - posledice nepredvidive

// ::, new, delete, .*, ->*, typeid, throw (izuzeci),
// alignof (udaljenost u bajtovima do sl. slobodne mem. lokacije), cast operatori - novi u c++

//Postfiksne varijante ++ i -- imaju visi prioritet
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
    //  STATIC CAST (staticki cast za prenosive konverzije (za razlicite platforme; prevodioce))
    //  izmedju numerickih tipova (ukljucujuci i enum tip), izmedju pokazivaca proizvoljnih tipova i void*
    //  nestandardne konverzije (koje definise programer)
    //  implicitno za bezbedne, a eksplicitno za nebezbedne (void* -> pokazivac na tip, int -> enum)

    float a = 5.0; int i = static_cast<int> (a);
            //kao: int i = (int) a
    void *p = static_cast<void *> (&i); // moze void *p = &i (bezbedna konverzija)
    int *q = static_cast<int *> (p); // mora eksplicitni kast - preporuka staticka konverzija

    // nullptr (tipa void*) umesto 0 ili NULL (nullptr moze da se dodeljuje bez kasta)

    //  REINTERPRET CAST
    //  namenjen konverziji tipova bez logicke veze:
    //  izmedju celobrojnih vrednosti i pokazivaca, izmedju pokazivaca ili referenci na razne tipove
    //  nema pretvaranja vrednosti - ista se samo razlicito interpretira
    //  Konverzija je nebezbedna

    int j = 1155;
    short *pj = reinterpret_cast<short *>(j); // vrednost konvertujemo u pokazivac short (dobija adresu 1155)
//    int k = reinterpret_cast<int>(pj); // k==j
    float *qj = reinterpret_cast<float *>(&j); //pristupamo lokaciji j kao float-u
    float &r = reinterpret_cast<float &>(j); // referenca na float

    //  CONST CAST
    //  Namenjen uklanjanju ili dodavanju const-a
    //  Dodavanje specifikatora je bezbedno, ali uklanjanje nije (jer omogucava promenu vrednosti nepromenljivog podatka)
    int l = 1;
    const int m = l;
    int *pm = const_cast<int *> (&m); //mora eksplicitno - menja se const lokacija - postaje promenljivi pokazivac
    *pm = 0; // OK

    double pi = 3.14;
    const double &cpi = const_cast<const double &>(pi);
                    // ili : const double &cpi = pi; - bezbedna konverzija
    pi = 0.0;       // OK
//    cpi = 0.0;    // ! GRESKA

    // dynamic_cast <tip_pokazivaca_ili_reference> (izraz)
}

int main() {
    cast();
    return 0;
}