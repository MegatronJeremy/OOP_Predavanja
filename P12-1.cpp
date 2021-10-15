#include <iostream>
using namespace std;

//      FUNKCIJSKE KLASE KAO PARAMETRI

// I sabloni klasa i sabloni funkcija mogu imati dve vrste parametara
// Moze predstavljati ili formalni tip koji se zamenjuje stvarnim ili neke konstante

// Pojavljuje se kao problem to da funkcija NE MOZE biti parametar sablona

// Cesto je potrebno parametrizovati neki sablon funkcijom - za tabeliranje neke funkcije
// Direktno sablonu nije moguce prosledjivati
// Zato pravimo funkcijske klase

// Funkcijska klasa je bilo koja klasa koja ima preklopljen operator ()
// () preklopljen kao nestaticki metod
// Takva klasa moze posluziti kao parametar sablona

// Stvarni argument ce biti funkcijska klasa (zamenjuje formalni argument klasnog tipa)

// Mozemo neku funkciju na taj nacin proslediti sablonu

// Kod funkcijskih klasa postizemo (nevezano sa sablonima) to da mozemo da pozovemo operator
// () preko objekta date funkcijske klase - ako klasa ima definisan taj operator
// F f; <---- zovemo f() <---- poziva taj operator koji smo napisali u funkcijskoj klasi
// Sintaksno poziva kao pozivanje funkcije f, ali mi u stvari za objekat f zovemo operatorsku funkciju
// napisanu u klasi

// Sablon funkcije za tabeliranje proizvoljne funkcije:
template<typename T, class F>
void tabela(F f, T xmin, T xmax, T dx) {
    for (T x = xmin; x <= xmax; x+=dx)
        cout << x << '\t' << f(x) << endl; // <---  f je ime objekta funkcijske klase
}
// T tip podataka na x-osi - F predvidjena funkcijska klasa (formalni parametar sablona)
// Prvi parametar tabela F f je objekat funkcijske klase

// Sablon klase za tabeliranje proizvoljne funkcije:
template<typename T, class F> class Tabela {
    F f;    // Privatni atribut objekat funkcijske klase
public:
    Tabela(F fo) {f = fo;} // ako nam ne odgovara podrazumevani konstruktor
    // Formira kopirajucim konstruktorom objekat f
    // Cesto nam je dovoljan ugradjeni - podrazumevani konstruktor

    void tabela(T xmin, T xmax, T dx) {
        for (T x = xmin; x <= xmax; x+=dx)
            cout << x << '\t' << f(x) << endl;
    }
    // Opet ista f-ja (ali sad kao metod funkcijske klase)
};

#include <cmath>

// Genericka funkcijska klasa za racunanje prigusenih oscilacija
// T moze biti float, double, long double, ali cak i klasa kompleksnih brojeva
template<typename T> class Oscil {
public:
    T operator() (const T &x) const {
        return exp(-0.1*x)*sin(x);
    }
};

// Generisanje funkcije i klase za tabeliranje prigusenih oscilacija
int main() {
    tabela(Oscil<double>(), 0., 6.28, 0.314); // Generiseo konkretnu funkcija iz sablona funkcije
    // Oscil<double> () <-- podrazumevani konstruktor
    cout << endl;

    // Preko funkcijske klase
    Oscil<double> o;
    Tabela<double, Oscil<double> > t(o); // NEOPHODAN RAZMAK (inace znak >> - sintaksna greska)
    // T = double, F = Oscil<double>
    // t(o) - inicijalizujemo sa objektom o funkciju f
    t.tabela(0., 6.28, 0.314);
}

// Funkcijske klase dosta se koriste u STL-u - trebaju se dobro razumeti

//      INICIJALIZATORSKE LISTE

// Takodje se koriste u STL-u

// Inicijalizatorska lista niz podataka razdvojenih zarezima

// initialize_list ime sablona klase koja predstavlja apstrakciju inicijalizatorske liste

template<typename E> class initializer_list1 {
public:
    initializer_list1() noexcept;    // pravi praznu listu
    size_t size() const noexcept;   // broj elemenata inicijalizatora liste
    const E *begin() const noexcept;// pokazivac na prvi element liste (ne mozemo da menjamo taj podatak0
    const E *end() const noexcept;  // pokazuje IZA poslednjeg elementa inicijalizatorske liste
}; // nalazi se u zaglavlju <initializer_list>

// Postoji i konstruktor inicijalizatorske liste za neprazne inicijalizatorske liste - ali on je privatan
// Taj privatan konstruktor moze da poziva samo prevodilac
// Poziva se kod formiranja inicijalizatorske liste sa vise elemenata (prima proizvoljan broj parametara)

//      PRIMER INICIJALIZATORSKE LISTE

void f() {
    initializer_list<double> ilist{1, 2.2, 3.3F, '4', 5};   // ilist je objekat klase dobijene generisanjem iz sablona
    // za tip double
    // Svi tipovi ce se konvertovati u double brojeve (cak i char)

    // Prvi nacin ispisivanja elemenata
    int n = ilist.size(); cout << n << endl;    // 5
    const double *p = ilist.begin();            // p na prvi element inic. liste
    for (int i = 0; i < n; i++) cout << p[i] << ' '; cout << endl;

    // Drugi nacin (bez prebrojavanja elemenata
    for (const double *p = ilist.begin(); p!=ilist.end(); p++)
        cout << *p << ' ';
    cout << endl;

    // Treci nacin (for each struktura kroz koju strukturiramo)
    // For petlja za svaki element kolekcije kroz koju se moze iterirati
    for (double x : ilist) cout << x << ' '; cout << endl;
}

// Primer inicijalizatorske liste kao parametra/argumenta i rezultata funkcija
// Nece prolaziti kompilaciju
initializer_list<float> g(int x, initializer_list<double> y, char c) {
    return {(float) x, 2.2F, (float) c, 5.5F, 6L, 7LL};
}
// Problem konverzije i - ne moze implicitno u inicijalizatorskoj listi
// Rezultat je privremeni objekat - nece se produzivati zivotni vek rezultata funkcije
// Cak i ako dodeljujemo vrednost sa privremenim objektom - nece vaziti zivotni vek liste

void g() {
    initializer_list<float> a = g(1, {2,3,4,5}, 'a');   // sve vrednosti se konvertuju
    // a nece imati odgovarajuce float vrednosti koje bi vratila funkcija g

    auto b = g(1, {2,3,4,5},'a');
    // automatski se odredjuje tip objekta b na osnovu tipa rezultata g
}

//      INICIJALIZACIJA OBJEKATA INICIJALIZATORSKOM LISTOM

// Potrebno je da klasa objekta ima konstruktor ciji je parametar inicijalizatorska lista
// Ako postoje ostali parametri - moraju imati podrazumevane vrednosti

// Argumente konstruktora obicno navodimo u obicnim zagradama ()
// ali mogu da se navedu i u viticastim zagradama {}

// Ako je u pitanju objekat inicijalizatorske liste ti izrazi mogu biti razlicitih tipova (vrsice se konverzije)

// Ukoliko bi u klasi postojao konstruktor ciji je parametar inicijalizatorska lista OBAVEZNO se poziva taj
// konstruktor pri pozivu {...} OSIM U SLUCAJU KADA SE STAVI PRAZNI {} - POZIVA SE PODRAZUMEVANI KONSTRUKTOR

class A {
    int *niz; int n;
public:
    A() : niz(nullptr), n(0) {} // inicijalizuje prazan niz (LISTA INICIJALIZATORA)
    A(int x, int y) : niz(new int[2]{x,y}), n(2) {} // inicijalizacija niza sa dva clana
    // koristimo formu inicijalizatorske liste sa dva podatka {x, y} da bismo inicijalizovali listu elemenata
    A(initializer_list<int> ilist) {                // Generise se klasa za tip int
        niz = new int [n = ilist.size()];           // Dimenzionisan da dohvati velicinu i-liste
        int i = 0; for (int x : ilist) niz[i++] = x;// Pridruzujemo svaki element nizu iz liste
    }
};

// LISTA INICIJALIZATORA (U DEFINICIJI KONSTRUKTORA) NIJE ISTO STO I INICIJALIZATORSKA LISTA (KLASA)

void h() {
    A a1{1,2,3,4,5};        // A(initializer_list<int>)
    // Koristi se konstruktor ciji je parametar initializer_list

    A a2;                   // A() se poziva
    A a3{};                 // A() - NECE SE POZIVATI ilist
    A a4{1};                // A(initializer_list<int>) - 1 jedini element ilist-a
    A a5{1, 2};             // A(initializer_list<int>) - takodje se poziva
    A a6(1, 2);       // A(int, int) - konstruktor koji smo definisali
}

//      SPECIJALIZACIJA (SABLONA)

// Kada hocemo da trazimo maks. raznih tipova - celih, realnih brojeva itd...
// Svako telo funkcije izgledace isto - dovoljan jedan sablon

// Ako hocemo da izracunavamo npr. maksimum dva zadata literala stringa - zelimo da specijalizujemo
// tj. leksikografski da poredimo - opisali smo posebnu funkciju (koja ima prioritet nad sablonom)

// Taj koncept je unapredjen u specijaliziciji sablona
// Za neke vrednosti parametara sablona, ne bi trebao da se primenjuje opsti sablon, vec posebni,
// specijalizovani sablon (bilo da je sablonska funkcija ili klasa)

// Deklaracija:
//template<parametri> class GSKlasa<argumenti>;
// parametri - parametri specijalizacije sablona (moze biti ili vise ili manje parametara od originala),
// broj argumenata mora biti isti broj kao opsti sablon

// Parametri specijalizacije sablona ne mogu imati podrazumevane vrednosti argumenata sablona

// definciija:
// template <parametri> class GSklasa<argumenti>{/*...*/}
// argumenti -> nam sluze da fiksiramo neke argumente sablone (za neke specificne situacije)
// oni nam sluze da odredimo koju cemo specijalizaciju primeniti

//      VRSTE I USLOVI SPECIJALIZACIJE

// Specijalizacija moze da bude:
// delimicna: bar jedan parametar ima specijalizovani sablon
// potpuna: specijalizovani sablon NEMA NIJEDAN PARAMETAR (mozemo da izgenerisemo samo jednu klasu)

// Da bi specijalizacija bila moguce moramo imati barem deklaraciju opsteg sablona (opsteg sablona - opste genericke klase)

// Mozemo da radimo specijalizaciju samo ako nije jos generisana nijedna klasa na osnovu opsteg sablona sa istim argumentima
// Imamo opsti sablon - izgenerisanu klasu sa nekim argumentima - ne mozemo da radimo specijalizaciju sa takvim argumentima

template<typename T, int k> class Vekt {}; // opsti sablon (samo deklaracija klase tog sablona)

template<typename T, int k> class Vekt<T*, k> {};  // specijalizacija 1 (ovde ne pisemo tela - bila bi svakako razlicita od
// tela opsteg sablona - jedino to i ima smisla
// Specijalizuje T da MORA biti pokazivacki tip

template<typename T> class Vekt<T, 10> {};
// Fiksiramo k na 10 - prvi parametar ostaje promenljiv

template<int k> class Vekt<int, k> {}; // Prvi parametar fiksiramo na int
// int k - parametar specijalizovanog sablona
// argument specijalizovanog sablona int fiksira prvi parametar opsteg sablona (k ostaje otvoreno)

template<> class Vekt<void *, 10> {};  // Argumenti specijalizacije: void *, 10
// Potpuna specijalizacija (fiksira oba parametra sablona)

void j() {
    Vekt<int *, 15> n1;     // koristi se 1
    Vekt<float, 10> n2;     // koristi se 2
    Vekt<int, 20> n3;       // koristi se 3

    Vekt<void *, 10> n4;    // koristi se 4
    // Gleda se najveca specijalizacija (mogla bi i 2 da ove nema)

//    Vekt<int, 10> n5; // ! GRESKA - podjednako specijalizovani sabloni
}

// Pri generisanju se navodi onoliko argumenata koliko ima opsti sablon parametara