//          STANDARDNA BIBLIOTEKA SABLONA

// Mehanizam sablona da neki cesti tipovi elemenata budu parametri sablona.
// Svi identifikatori u prostoru imena std, ali neki i u podprostorima std-a

//      GRUPE SABLONA

// Usluzne funkcije i klase
//  - relacioni operatori, funkcijske klase

// Jednostavne strukture podataka
//  - par, kopmpleksan broj

// Zbirke podataka i iteratori
//  - vektor, red, lista, stek, mapa, skup, tekst, niz bitova

// Algoritmi
//  - pretrazivanje, uredjivanje (sort), spajanje (merge)

//      SABLONI RELACIONIH OPERATORA

// Postoji 6 relacionih operatora: == != < > <= >=
//  - 4 od 6 se mogu izraziti pomocu 2: == i < (i logickih)

// Potrebno samo preklopiti == i <
// Ostala 4 operatora se generisu

// Nalaze se u zaglavlju <utility>, u prostoru std::rel_ops

// template<typename T> bool operator@@ (const T&, const T&);

class Pravoug {
    float a, b;
public:
    Pravoug(float str_a=1, float str_b=1) {a = str_a; b = str_b;}
    float P() const {return a*b;}
};
bool operator==(Pravoug x, Pravoug y) {return x.P()==y.P();}
bool operator<(Pravoug x, Pravoug y) {return x.P()<y.P();}

#include <utility>
using namespace std::rel_ops;
/*
void k {
    Pravoug p1, p2(2,1);
    if (p1>p2) {}   // generise se > !Automatsko generisanje iz sablona
}
*/

//      FUNKCIJSKE KLASE/STRUKTURE

// Funkcijska klasa (FK):
//  - klasa koja realizuje preklapanje operatorske funkcije operator()

// Funkcijska strukture (FS) se realizuje na isti nacin

// Neke genericke klase/funkcije zahtevaju funkcijska klase/strukture
// Postoje gotove funkcijske strukture u STL (u zaglavlju functional)
// Postoje unarne i binarne, aritmeticke, logicke i relacione operacije

//      OPSTI OBLICI FUNKCIJSKIH STRUKTURA

// Unarna aritmeticka operacija
template <typename T> struct ime {
    T operator() (const T&); // Jedan parametar? Nece raditi nad objektom this (moramo preklopiti kao metod)
};

// Binarna aritmeticka operacija
template <typename T> struct ime1 {
    T operator() (const T&, const T&);
};

// Unarna logicka operacija
template <typename T> struct ime2 {
    bool operator() (const T&);
};

// Binarna logicka ili relaciona operacija
template <typename T> struct ime3 {
    bool operator() (const T&, const T&);
};

//      NAZIVI FUNKCIJSKIH STRUKTURA

// Unarna aritmeticka operacija:
//  - negate
//  - realizuje se pomocu unarnog operatora -
//  - potrebno je da je oprator-() realizovan za dati tip (argument)

// Binarne aritmeticke operacije:
//  - plus, minus, multiplies, divides, modulus
//  - realizuju se pomocu: +, -, *, /, %

// Relacijske operacije:
//  - equal_to, not_equal_to, greater, less, greater_equal, less_equal
//  - realizuju se pomocu: ==, !=, >, <, >=, <=

// Binarne logicke operacije:
//  - logical_and, logical_or
//  - realizuju se pomocu: &&, ||

// Unarna logicka operacija:
//  - logical_not
//  - realizuje se pomocu: !

//      KORISCENJE FUNKCIJSKIH STRUKTURA

// Neposredno se ugradjuju u kod (inline funkcije - dobijaju na efikasnosti)
// Klasa - struktura (prakticno isto)

// Podrazumevani argumenti formalnih parametara sablona:

// Navedene genericke FS
//  - mogu da se koriste za standardne proste tipove
//  - za klasne tipove je neophodno preklopiti odgovarajuce operatore

// U navedenim generickim FS
//  - operatorska funkcija operator() se neposredno ugradjuje u kod
//  - ne gubi se na efikasnosti

#include <iostream>
#include <functional>
using namespace std;

template <typename T, class Op>
void radi(const T a[], const T b[], T c[], int n) {
    Op op;
    for (int i = 0; i < n; i++) c[i] = op(a[i], b[i]);
}   // Pravi treci niz na osnovu para 2 ulazna niza
    //  Op je funkcijska struktura

template <typename T>
struct Zbir_kvadrata {
        T operator() (const T &a, const T &b) {return a*a + b*b;}
    };
// Nasa funkcijska struktura (sablonska)

void f() {
    int a[10], b[10], c[10], n;
    cin >> n;
//     citaj(a,n); citaj(b,n);
    radi<int, plus<int> > (a,b,c,n); // Generisana funkcijska struktura plus za tip int (bibliotecka)
    radi<int, Zbir_kvadrata<int> > (a,b,c,n); // MORA postojati blanko znak (inace se stapaju u token >> ?)
    // Iz istog sablona generisemo drugu funkciju (nasu napisanu)
}

//      PAROVI PODATAKA

// Par - dva podatka porizvoljnih tipova

// Struktura, javni atributi
template<typename A, typename B> struct Pair {
    A first; B second;
    Pair() : first(A()), second(B()) {}
    // first konstruisemo pomocu A() - za klasni tip PK klase A
    // ako je A primitivni tip (npr. int) - prevodi se kao nula ugradjenog tipa

    Pair(const A&, const B&);

    template<typename C, typename D> Pair(const Pair<C,D> &);
    // Genericki konstruktor genericke strukture (klase)
    // Za ovakav konstruktor moraju postojati konverzije C u A i D u B
};
//template<typename A, typename B>
//bool operator@@(const pair<A,B> &, const pair<A,B>&);

// Moze biti jedan od 6 relacionih: ==, !=, <, <=, >, >=
//  - ostali relacioni operatori se izvode iz == i <
//  - u klasama A i B dovoljno imati == i <

//template<typename A, typename B>
//pair<A,B> make_pair(const A&, const B&);

// Parovi jedino ne mogu biti nizovski tipovi
void g() {
    pair<float, int> p; pair<int, char> q(1, 'a');
    cout << p.first << ' ' << p.second << endl;
    cout << q.first << ' ' << q.second << endl;
}

//      KOMPLEKSNI BROJEVI

// U biblioteci stl postoji genericka klasa complex u zaglavlju <complex>
// - template <typename T> class complex;
// Moze T biti ceo broj, realan broj, imaginaran broj, float...

// Postoje potpune specijalizacije sablona za: float, double, long double
// (videti specijalizacije sablona)

// Klasa podrzava sve operacije kao sa bilo kojim numerickim tipom:
//  - aritmeticke: +, -, *, /, =, +=, -=, *=, /= i relacione == i !=

// Konstruktor: complex(const T& re = T(), const T& im = T());
// Metodi: T real() const; T imag() const;
// F-je:
// T real(const complex<T> &z); T imag(const complex<T> &z);
// T abs(const complex<T> &z): T arg(const complex<T> &z);
// T norm(const complex<T> &z); // kvadrat potega
// copmlex<T> polar(const T& r, const T& fi); // poteg i faza
// complex<T> conj(const complex<T> &z);

// slicno za: sqrt, exp, log, log10, sin, cos, tan, sinh, cosh, tanh
// za: pow(a,b)
//  - ako je a complex, b = {int, realan broj, complex}
//  - ako je a realno, b je tipa complex

//      ZBIRKE PODATAKA

// Zbirke su objekti koji sadrze podatke nekog tipa
// Mogu da sadrze objekte ili da sadrze primitivne podatke

// Takve kolekcije omogucavaju da u njih dodajemo nove elemente, dodajemo postojece i izbacujemo
// one koji nam nisu potrebni.

// Unutrasnje strukture zbirke uticu na efikasnost operacija i na zauzece memorije.

// Dodavanje i izbacivanje - slicna slozenost.
// Pristup elementu - zavisi.

// Vektori - mali utrosak memorije, brz pristup, sporo umetanje i izbacivanje (sekvencijalno pomeranje)
// Lista - veci utrosak memorije, spor pristup, brzo umetanje i izbacivanje (direktno prevezivanje)

// Osnovne grupe zbirki:
//  - sekvencijalne - pristup sekvencijalan
//  - asocijativne - brz pristup O(logn)
//  - neuredjene asocijativne - brz pristup O(1), O(n) u najgorem slucaju

// Ugovori (interfejsi) razlicitih zbirki su dosta slicni
// Klase zbirki su nezavisne (nemaju zajednickog pretka)
// Za svaku zbirku klasnih tipova od nas se ocekuje da za taj element obezbedimo:
//  - destruktor, operator=, K, KK, PK, a za asocijativne zbirke == i <

// Vec dobra praksa da klasa ima destruktor, operator, itd.

//      ELEMENTI ZBIRKE

// Prilikom stavljanja u zbirku - konstruktor kopije
// Prilikom izbacivanja iz zbirke - element se unistava (destruktor)
// Ako sadrze samo pokazivace, kopiraju se samo pokazivaci, ne objekti

// Prvi element nema prethodnika, poslednji nema sledbenika

// Zbirka od [0:n]
// Tekuci element onaj kome je trenutno moguc pristup - preko iteratora

//      ITERATORI

// Ugnjezdena klasa u klasi zbire
// Objekti - pametni pokazivaci

// Iterator pokazuje na tekuci element zbirke, mozemo se sa njim pomerati na sledeci itd.
// Pomocu dva iteratora mozemo da znamo da li pokazuju na isti ili razlicite elemente

// Mozemo ga postaviti na pocetni ili na poslednji (ili ispred prvog ili iza poslednjeg elementa zbirke)

//      ITERATORI KAO PAMETNI POKAZIVACI

// Iteratori koji su objekti pokazuju na elemente strukture koja cini zbirku
// Operacije nad operatorima realizovane su preklapanjem operatora

// *i - pristup tekucem elementu
// i+1 - naredni element
// i-1 - prethodni element

//      VRSTE ITERATORA

// Ne tipovi iteratora, vec kategorije, vrste iteratora

// Izlazni
//  - omogucava samo postavljanje tekuceg elementa i kretanje unapred

// Ulazni
//  - omogucava samo dohvatanje vrednosti tekuceg elementa i kretanje unapred

// Jednosmerni
//  - omogucava radnje izlaznih i ulaznih operatora

// Dvosmerni
//  - omogucava radnje jednosmernih iteratora + kretanje unazad

// Sa proizvoljnim pristupom
//  - omogucava radnje dvosmernih iteratora + pristup zeljenom elementu po rednom broju

//      TIPOVI ITERATORA

// Tipovi iteratora su nezavisni od "vrste" iteratora

// 4 klase: iterator, const iterator, reverse iterator, const reverse iterator

// Sama zbirka odredjuje vrstu iteratora (jedne od ovih vrsta)

// Programer kada treba da napravi iterator odredjuje tip kao jednu od 4 klase (u zavisnosti sta zeli da radi)

//      OSOBINE TIPOVA ITERATORA

// iterator: i+1 - sledeci
// riterator: i+1 - prethodni (sledeci u smeru poslednji->prvi)

// konstantni su za nepromenljive zbirke
// i++ isto

//      TIPOVI ZBIRKI

// Nizovi (array)
// Vektor (vektor)
// Redovi sa dva kraja (deque)
// Liste (list) i jednosmerne liste (forward_list)
// Specijalne zbirke (queue, priority_queue, stack)
// Preslikavanja (map, multimap)
// Skupovi (set, multiset)
// Tekstovi (string)
// Nizovi bitova (vector<bool>, bitset)

//      VEKTORI

// 1-D nizovi neogranicenog kapaciteta

// Ne moramo zauzimati nepotrebno mnogo memorije, kako rastu zahtevi za memoriju tako se povecava kapacitet
// Moguc vrlo efikasan pristup po proizvoljnom redosledu - smestaju se sukcesivno u memoriju
// Efikasno dodavanje na kraj - osim ako dolazi do proboja kapaciteta (kopira se niz u novi prostor sa vecim kapacitetom)
// Dodavanje/izbacivanje unutar vektora neefikasno - pomeranje od tekuceg elementa ubacenog pa sa svim elementima nadalje

// Karakteristicna automatska promena kapaciteta - ne definise standard vec kompajler (neki za pola, neki dupliraju, itd...)

// Iterator u klasi vektor vrste iterator sa proizvoljnim pristupom

//      KLASA VEKTOR

// Deklaracija se nalazi u zaglavlju <vector>

/*
template <typename E> class vector {
// E je tip elementa vektora

// Klasa vektor poseduje:
// PK (prazan vektor)
// KK, KP

    vector(unsigned vel, const E& x=E()); // elementi dobijaju vrednost koja je kopija x
// Podrazumevani konstruktor - ili podrazumevani primitivni tip - nula

    template<class It> vector (It prvi, It posl);
// sablonski konstruktor sa sablonskim parametrom klase iterator
// kopira elemente neke zbirke iz intervala [prvi, posl)
// posl pokazuje IZA poslednjeg elementa koji ce se kopirati

// destruktor
// operator=

    void assign(unsigned n, const E& x=E());
    // dodeljuje se n elemenata x
    template<class It> void assign(It prvi, It posl);
    // pridruzuje se vektor koji je napravljen od niza elemenata iz zbirke od elementa [prvi,posl)
    // sablonski metod u sablonskoj klasi

    unsigned size() const;
    // vraca broj elemenata vektora

    unsigned capacity() const;
    // kapacitet vektora u trenutno rezervisanoj memoriji

    unsigned max_size() const;
    // koliko maksimalno bi moglo biti u vektoru (posmatra kompletan adresni prostor)
    // na 32-bitnoj masini int od 4 bajta - 32 bita 4gb
    // max_size vraca 4gb - ne zna se da li imamo toliko uopste

    bool empty() const;
    // da li je prazan vektor

    void resize(unsigned vel, const E &x = E());
    // zadaje se nova velicina i element na osnovu kojeg se dopune preostajuci elementi
    // ako smo smanjili velicinu - ostali unisteni

    void reserve(unsigned n);
    // Sa zadatim n rezervise prostor koliki zelim za vektor (moze i da se poveca ili smanji prostor)
    // Rec je o kapacitetu - ali nece biti moguce smanjiti kapacitet manje od size
};
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v(1000); // vektor dimenzije 1000 (poziva se podrazumevani int() = 0)
    cout << "size=" << v.size() << " max_size=" << v.max_size() << " capacity=" << v.capacity() << endl;
    v.push_back(1);
    cout << "size=" << v.size() << " max_size=" << v.max_size() << " capacity=" << v.capacity() << endl;
}

//      METODI KLASE VECTOR

// iterator begin();
// const_iterator begin() const;
// iterator end();
// const_iterator end() const;
// reverse_iterator rbegin();
// const_reverse_iterator rbegin() const;
// reverse_iterator rend();     // ispred prvog elementa vektora
// const_reverse_iterator rend() const;

void p() {
    vector<int> v(10);
    typedef vector<int>::iterator Vit;
    typedef vector<int>::reverse_iterator Vrit;

    for (Vit i = v.begin(); i != v.end(); cin >> *i++);
    // *i je operator preklopljen za iterator - pametni pokazivac
    // ++ je takodje operator iteratora koji ga prebacuje na sl element
    // ++ visi prioritet ali odlozeno dejstvo

    for (Vrit i = v.rbegin(); i != v.rend(); cout << *i++ << ' '); cout << endl;
    // ide unatraske - rbegin() poslednji elementi vektora
    // v.rend() pokazuje ispred prvog elementa vektora
    // opet i++ jer nas pomera u zeljenom smeru - ovaj slucaj reverzni smer
}

// E& operator[] (unsigned ind);
// const E& operator[] (unsigned ind) const;
// E& at(unsigned ind); // 0 <= ind <= size(), inace baca out_of_range
// const E& at(unsigned ind) const;
// E& front();
// const E& front() const;
// E& back();
// const E& back() const;
// void push_back(const E& x);
// void pop_back();

// iterator insert (iterator poz, const E& x=E());
// void insert(iterator poz, unsigned n, const E& x=E());
// template<class It> void insert(iterator poz, It prvi, It posl);
// iterator erase(iterator poz);    // vraca iterator koji pokazuje na onaj koji je sad tekuci (na mestu poz)
// iterator erase(iterator prvi, iterator posl);    // izbacivanje od prvog do poslednjeg ne racunajuci poslednji
// void clear();
// void swap(vector<E> &v);

//      GLOBALNA FUNKCIJA SA vector ARG

// Leksikografsko poredjenje 2 vektora:
// bool operator@@(const vector<E> &v1, const vector<E> &v2);
// v1==v2 ako imaju jednak broj elemenata i ako su odgovarajuci elementi e1==e2

// v1<v2 ako kod prvog para razlicitih elemenata e1 < e2
// ili ako je v1 kraci od v2, a svi e1==e2

void j() {
    vector<int> v; int k;
    cout << "niz? ";
    while (cin >> k, k!=9999) {
        if (v.size() == v.capacity()) v.reserve(v.size()+10);
        //  bez eksplicitne rezervacije - duplira se kapacitet
        v.push_back(k);
    }
    v.reserve(v.size());    // ne mora imati efekat
    int s=0; for(unsigned i=0; i < v.size; s+=v[i++]);
    cout << "S=" << s;
}