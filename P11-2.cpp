#include<iostream>
#include<string>
#include<cstring>

using namespace std;

//            GENERICKI MEHANIZAM

//      POTREBA ZA GENERICKIM TIPOVIMA

// Isti algoritam nad razlicitim tipovima podataka

char maximum(char i, char j) {return i>j?i:j;}
char maximum(int i, int j) {return i>j?i:j;}
char maximum(float i, float j) {return i>j?i:j;}

// Umetanje/uzimanje iz kruznog bafera ili steka - podaci mogu biti razlicitog tipa

// Ideja da napravimo mehanizam koji dozvoljava da napisemo funkciju koja ne zavisi od tipa
// podataka nad kojim se izvrsava taj algoritam

// Napravimo sablon f-ju
// Tip sa kojim radimo parametar sablona (kasnije argument sablona konkretan tip)

// Sablon tip parametara i tip rezultata (uobicajeno)
// parametar sablona - parametar funkcije
// Sablonska funkcija - parametar sablona i parametri funkcije
// Slicno vezano i za klase - sablonska klasa - parametar koji predstavlja tip elemenata steka zamenjuje
// konkretnim tipom

// Genericki mehanizam je potpuno STATICKI - tekstualna zamena koja se desava u VREME PREVODJENJA

// Moze se napraviti delimicno prevedeni sablon - ali u nacelu smatramo da imamo izvorni kod sablona
// iz kojeg prevodilac izgenerise konkretnu funkciju/klasu

// Smisleno da se kod sablona pise u h fajlovima - koji se ukljucuje gde se koriste ti sabloni

// Posledica pisanja izvornog koda u h fajlovima - gubimo mogucnost poslovne tajne
// h fajlovi su fajlovi sa izvornim kodom (implementacijom)

// h fajl - ugovor, interfejs
// cpp - implementacija

//      DEFINISANJE SABLONA

//
//              typename        identifikator tipa
// template <   class           identifikator tipa        , (ponovo) > funkcija
//              oznaka tipa     identifikator konstante                klasa

// Identifikator tipa zamenjen konkretnim tipom
// Identifikator konstante zamenjen konkretnom konstantom

// typename i class formalno gledano potpuno ekvivalentne
// Id tipa predstavlja ime tipa ili ime klase
// Cak i ako stoji class moze biti zamenjen i primitivnim tipom

// Dogovor: zamenjujemo imenom klase - class
//          zemenjujemo imenom tipa - typename

// Oznaka tipa ne mora biti oznaka celobrojnog tipa
// od C++11 moze se naci i pokazivac ili referenca (moze biti i promenljivi)

// U nacelu moze biti celobrojni tip (to su i nabrajanja) - stvarni argument celobrojni izraz
// stvarni argument mora biti konstantni izraz

// sablon funkcije:
template <typename T> T maximum(T a, T b) {
    return a>b?a:b;
}

// sablon deklaracije (prototipa) funkcije:
template <typename T> void sort(T a[], int n);

// sablon definicije funkcije: (ako odmah dodajemo i telo)
template <typename T> void sort(T a[], int n) {
    /***/
}

// odlozeno navodjenje tipa sablonske funkcije
template <typename T, typename U>
auto f(T t, U u)->decltype(t+u) {return t+u;}
// t i u su parametri funkcije f - zelimo automatsko odredjivanje tipa rezultata
// trebao bi biti definisan operator + za T i U
// vise ne mora da se pise decltype(t+u) - opciono

// sablon klase
template <class T, int k> class Vekt { // Vekt NIJE KLASA - vec SABLON KLASE
    int duz; T niz[k]; // moze da se koristi k kao constexpr
public:
    Vekt();
    const T& operator[](int i) const{return niz[i];}
};
template <class T, int k> Vekt<T,k>::Vekt() {
    duz = k; for (int i = 0; i < k; niz[i++] = T());
}
// Smatra se obicnim konstruktorom (ne sablonom) sablonske klase
// T i k NISU PARAMETRI - VEC ARGUMENTI ODREDJENI NA OSNOVU PARAMETARA
// odredjuju se u trenutku generisanja klase

// T() - ako je T klasni tip - eksplicitni poziv konstruktora
// T() - ako je T primitivni tip - nula (rezultat int() je NULA)
// Mora ovako zbog situacije ako je T zamenjeno klasnim tipom

// Vekt je SAMO IME SABLONA, NE KLASE
// Prvi operand mora biti ime sablona zajedno sa nazivima parametara

// U definiciji metoda genericke klase, uz ime klase u operaciji :: mora da stoje
// i argumenti
// Razlog: sam identifikator genericke klase ne definise jednoznacno klasu

//      GENERISANJE FUNKCIJA

// Automatsko generisanje (na mestu poziva) i generisanje na zahtev (pisanjem deklaracije)

// Automatko generisanje moze biti na dva nacina:
// Eksplicitno zadavanje stvarnih argumenata sablon ili pomocu zadavanja argumenata funkcije (implicitno)

// Iza imena funkcije stvarni argumenti sablona (ne funkcije)
// Moguce i konverzije stvarnih argumenata funkcije u parametre funkcije

// Ukoliko parametar sablona se koristi za tip rezultata, a ne za tip parametra
// Potrebno eksplicitno navodjenje na mestu poziva funkcije
// navodjenje <> iza imena funkcije

// Ne mora se navoditi kada su parametri funkcije tipa T - sto je formalni parametar sablona
// (npr. za maksimum) - za argument sablona se vrsi zakljucivanje
// Kod implicitnog zakljucivanja nije moguce raditi konverziju tipova u neke druge

// Moguce navodjenje i prvih nekoliko argumenata funkcija da se na osnovu njih zakljuci parametar sablona

// Automatski implicitno generisanje funkcije:
// Nekad je takvo implicitno generisanje nepozeljno
// Ukoliko imamo definiciju obicne (ne sablonske funkcije) - pozovemo je sa datim tipovima
// ne vrsi se generisanje iz sablona (sprecava se implicitno generisanje funkcije) - poziva se obicno
// definisana funkcija sa datim parametrima

// Ako IPAK zelimo da koristimo funkciju generisanu iz sablona (ne eksplicitno generisano funkciju)
// eksplicitno radimo navodjenje argumenata sablona

// Generisanje na zahtev se postize:
// Deklaracijom

//template tip ime<stvarni_arg> (lista_tipova);
template int maximum<int>(int, int);

// Zelimo na zahtev da izgenerisemo funkciju
// Sabloni se ne prevode u objektni kod - tek kada se nadju na mesto poziva
// Ako hocemo da izgenerisemo konkretnu funkciju npr. za neku biblioteku - na ovaj nacin
// dobijamo kod te funkcije (ne vise sablon - nego konkretnu funkciju)

const char *maximum(const char *cp1, const char *cp2) { // definicija obicne f-je
    return strcmp(cp1, cp2) >= 0 ? cp1 : cp2;           // zelimo leksikografsko poredjenje
}   // sprecava template maximum

template float maximum<float> (float, float);   // zahtev za generisanje
// float argument sablona maksimum

int main() {
    int i1 = 1, i2 = 2; float f = 0.5;
    char c1 = 'a', c2 = 'b'; const char *a = "alfa", *b = "beta";

    int i = maximum(i1, i2);    // generise se int maximum(int, int)
    //  ili int i = maximum<int>(i1, i2); // eksplicitno automatsko generisanje

    char c = maximum(c1, c2);   // generise se char maximum(char, char)
//    int g = maximum(i1, c1);    // ! GRESKA
    int g = maximum<int>(i1, c1);  // konverzija char u int
    float h = maximum<float>(i1, f); // generise se float maximum(float, float)

    const char *v = maximum(a, b);  // POZIVA SE OBICNA F-JA, POREDI NISKE

    // Mora eksplicitno:
    const char *w = maximum<const char*>(a,b);  // POZIVA SE GEN. F-JA
                                                // POREDI POKAZIVACE (ADRESE)
}

//      GENERISANJE KLASA

// Klase se generisu prvi put kad se nadje na definiciju objekta u kojoj se koristi identifikator sablonske klase

// Pri generisanju klase generisu se i svi virtuelni metodi (odmah)

// Ostali metodi se generisu pri pozivanju

// Treba da sadrzi identifikator genericke klase, listu stavarnih arguemenata za genericke tipove i konstante unutar
// <> iza identifikatora klase

// Stvarni argument moze biti oznaka tipa i konstantni izraz (zamenjuje formalni parametar constexpr)

// Ukoliko dati izraz sadrzi operator > mora se pisati u zagradama (>)
// inace se smatra kao kraj liste argumenata sablonske klase

// Klasa se moze generisati na zahtev:
// template class ime<arg>;

// Moze se i eksplicitno imenovati koriscenjem typedef, using

// Automatsko generisanje
Vekt<int, 10> niz1; // neimenovane klase (nastale generisanjem iz sablona Vekt)
Vekt<double, 20> niz2;

class A{int i;};    // obicna klasa
Vekt<A,5> a;        // a je objekat tipa konkretne klase generisane iz sablona Vekt
// za argumente sablona - klasa A i konstantan argument 5

// Generisanje na zahtev:
template class Vekt<char, 10>;  // Generisali konkretnu klasu (ali ne imenovali)

// Generisanje na zahtev uz imenovanje tipa:
typedef Vekt<char *, 100> VektorStr;
using VektorRealnih = Vekt<float, 1000>;

/**
 using namespace std; // to import namespace in the current namespace
 using T = int; // type alias
 using SuperClass::X; // using super class methods in derived class

 class Derived : public Base {
 public:
    using Base::f;    // lift Base's f into Derived's scope -- works in C++98
    void f(char);     // provide a new f
    void f(int);      // prefer this f to Base::f(int)

    using Base::Base; // lift Base constructors Derived's scope -- C++11 only
    Derived(char);    // provide a new constructor
    Derived(int);     // prefer this constructor to Base::Base(int)
    // ...
 };
 **/

//      PODRAZUMEVANE VREDNOSTI

// Kao kod podrazumevanih vrednosti argumenata funkcija mogu se pisati i podrazumevane vrednosti arguemenata sablona
// Mogu i sablonske funkcije imati ove podrazumevane funkcije

// Mogu ih dobiti nekoliko prvih - pa cak i svi parametri
// Moze biti podrazumevano prvih n argumenata sablona (ne sa kraja)

// Dovoljno u deklaraciji/definiciji navode ove podrazumevane vrednosti
// Nije potrebno u definiciji metoda

// Ukoliko je parametar sablona neki tip onda podrazumevana vrednost moze biti ili
// primitivni ili obicna negenericka klasa ili genericka klasa sa stvarnim argumentima sabloma

// Ako je parametar sablona konstanta - pv. moze biti konstanta celobrojnog tipa

template<typename T = int, int k = 10> class Niz {};
Niz<char, 55> n1; Niz<float> n2; Niz<> n3;

// Raniji formalni parametri mogu da se koriste za odredjivanje pocetnih vrednosti kasnijih parametara

template<typename T, int k, typename U = Niz<short>, typename V = Niz<T, k>>
class B{};
// Podrazumevani cetvrti parametar sablona je Niz<T,k> - kada se smene T i k i ove ce vrednosti biti smenjene

