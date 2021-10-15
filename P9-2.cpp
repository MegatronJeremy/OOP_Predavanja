//      POZIVANJE VIRTUELNIH METODA

class Osnovna {public: virtual void f();};
class Izvedena : public Osnovna {public: void f();};    // Polimorfna redefinicija metod f()
// Automatski je u izvedenoj klasi virtuelni metod

void g1(Osnovna b) {b.f();}     // Po vrednosti (slajsovanje - odseca se virtual u izvedenoj)
void g2(Osnovna *pb) {pb->f();} // Po pok. na osnovnu klasu
void g3(Osnovna &rb) {rb.f();}  // Po ref. na osnovnu klasu
// g2 i g3 indirektni pristupi

int main() {
    Izvedena d;
    g1(d);          // Inicijalizujemo obj. osnovne klase obj. izvedene // Osnovna::f
    g2(&d);         // Po adresi            // Izvedena::f
    g3(d);       // Po referenci         // Izvedena::f
    Osnovna *pb = new Izvedena; pb->f();    // Izvedena::f (objekat izvedene klase)
    Osnovna &rb = d; rb.f();                // Izvedena::f
    Osnovna b=d; b.f();   // Samo inicijalizujemo objektom izvedene (objekat je osnovne klase)
    delete pb; pb = &b; pb->f();    // Pozivaju se Osnovna::f (pb pokazuje na obj. osnovne klase)
}

//      MODIFIKATORI OVERRIDE I FINAL

// Problem: implicitna polimorfnost metoda izvedene klase (ne moramo navoditi virtual u izvedenoj klasi)
// moze biti neprijatna

// Projektant osnovne klase resio da modifikuje osnovnu klasu i napravio virtuelni metod koji se poklopio
// sa metodom koji postoji u izvedenoj klasi - nije bila ideja

// Uvodi se modifikator override - iza liste parametara: govori eksplicitno da metod u izvedenoj klasi
// treba da bude nadjacanje osnovne klase.

// Modifikator final - na istom mestu kao override - govori da takav metod nije dozvoljeno polimorfno redefinisati

// Nisu kljucne reci u smislu rezervisanih reci zbog starijih verzija (moze postojati kao identifikator, ali nije preporucljivo)

// Moguca i kombinacija - override final - postizemo da je u toj klasi metod redefinicija metoda osnovne klase, ali se ne moze
// vise redefinisati u izvedenim klasama

class A {
public:
    virtual void vm1();
    virtual void vm1(int);
    void m1();
};

class B : public A {
public:
    void vm1() override;            // Predstavlja polimorfnu redefiniciju A::vm1()
    void vm1(int) override final;   // isto za A::vm1(int) i vise se ne izvodi
//    void vm1(float) override;   // ! GRESKA - ne postoji A::vm1(float)
//    void vm2() override;        // ! GRESKA - isto
//    void m1() override;    // ! GRESKA - A::m1() nije virtuelan metod
//    void m2() final;       // ! GRESKA - B::m2() nije virtuelan metod
};

class C : public B {
public:
//    void vm1(int);  // ! GRESKA - B::vm1(int) je konacan metod (implicitno je override)
    virtual void vm1(); // Moze i bez i sa virtual (virtual je implicitan)
};

int override = 1; int final = 2;    // Ne treba raditi, ali je moguce koristiti ih kao identifikatore

//      DINAMICKO VEZIVANJE
// eng. dynamic binding

// Mehanizam na kojem se zasniva polimorfizam - obezbedjuje da se metod koji se poziva odredjuje:
//  - po tipu objekta
//  - ne po tipu pokazivaca ili reference na objekat

// Ne mozemo znati u vreme prevodjenja - mehanizam je dinamicki (zavisi od vremena izvrsenja)
// Mehanizam preklapanja imena funkcija je staticki - prevodilac donosi odluku na mestu poziva metoda

//      IMPLEMENTACIJA VIRTUELNIH POZIVA

// Mehanizam mora biti efikasan - ali nije efikasan kao staticko vezivanje

// Imamo sistem indirektnih poziva (dovoljno efikasan da stvari rade brzo)

// Kada u klasi imamo virtuelni metod - svaki metod se prevodi - zna se gde su metodi smesteni u memoriji

// Za svaku polimorfnu klasu se pravi tabela pokazivaca na virtuelne metode date klase
//  TVF - Tabela Virtuelnih Funkciju

// U svakom redu tabele nalazi se pokazivac na odgovarajuci metod (adresa u memoriji)

// Objekat polimorfne klase sadrzi pokazivac na odgovarajucu tabelu virtuelnih funkcija
// (njegove klase)

class O {
public:
    int a;
    virtual void f();
    virtual void g();
};

class I : public O {
   int b;
public:
    void g();
};

void m() {
    I i;
    O *po = &i;
    po->g();    // (*(po->TVFp[1])) (po) <-- po u zagradi je skriveni argument (pokazivac na tekuci objekat)
    // objekat i ima pokazivac na tabelu TVFp (za klasu I)

    // u klasi i pokazivac na f-ju f() pokazuje na funkciju f iz klase O (nije redefinisana)
    // TVFp[0] pokazuje na f-ju iz osnovne klase O koja se nasledjuje

    // funkcija g() je redefinisana i smestena je na TVFp[1] - pokazuje na svoju metodu klase
    // NE na nasledjenu (TVFp za i ne cuva adresu g() osnovne klase)
}

//      OSOBINE POLIMORFNIH METODA

// Virtuelni (polimorfni) metodi ne mogu biti staticki

// Staticki metod ne moze biti virtuelan (vezan je za klasu, ne za objekat)

class X{
public:
    virtual void m() const {};
    static void s(const X&);    // prosledjujemo ref. ili pokazivac na objekat ciji polimorfni metod zovemo
};                              // zelimo polimorfno ponasanje u statickom metodu
void X::s(const X &x) {x.m();}  // Pozivamo virtuelni metod -> dobijamo virtuelno ponasanje

// Globalne prijateljske funkcije ne mogu biti polimorfne (ne pripada klasi)
// To je globalna funkcija - radimo slicno kao za staticki metod

// Virtuelni metodi mogu biti prijatelji drugih klasa - ne postoji ogranicenje

//      VIRTUELNI DESTRUKTOR

// Konstruktor se poziva pre nego sto objekat postoji (alociran je prostor, ali nije inicijalizovan pokazivac na TVF)
// --> konstruktor ne moze biti virtualan

// Destruktor moze biti virtuelna funkcija - poziva se nakon sto je kreiran sam objekat

// Destruktor osnovne klase ce se uvek izvrsiti, ali za izvedenu klasu nije sigurno, jer nismo napravili virtuelni destruktor

// Sva je prilika da i destruktor treba da bude virtuelan

// Ne trebamo da pozivamo destruktor za objekat osnovne klase eksplicitno (implicitno se poziva)
// Kao sto se implicitno poziva i konstruktor

class OVD {public: virtual ~OVD();}; // OVD - osnovna klasa sa virtuelnim destruktorom
class IVD: public OVD {public: ~IVD();};    // automatski je virtualan

class OnVD {public: ~OnVD();};                  // nevirtuelni destruktori
class InVD : public OnVD {public: ~InVD();};

// Funkcije za oslobadjanje memorije, radimo preko pokazivaca delete
void oslobodi (OVD *pb) {delete pb;}
void oslobodi (OnVD *pb) {delete pb;}

void h() {
    OVD *pb = new OVD; oslobodi(pb);        // ~OVD() <-- objekat osnovne klase (dati objekat)
    IVD *pd = new IVD; oslobodi(pd);        // ~IVD(), ~OVD() <-- desava se ono sto ocekujemo
    OnVD *pbn = new OnVD; oslobodi(pbn);    // ~OnVD() <-- u redu
    InVD *pdn = new InVD; oslobodi(pdn);    // ~OnVD() <-- ! Pokazivac na izvedenu klasu prosledjujemo kao pokazivac na osnovnu klase
    //  Poziva samo destruktor osnovne klase <-- vrsi se staticko vezivanje, nema polimorfizma, tip pokazivaca odredjuje destruktor
}

// TVFp je tabela pokazivaca SAMO NA FUNKCIJE KOJE SU VIRTUELNE - ZA DRUGI PAR KLASA NJIH NEMA

//      NIZOVI I IZVODJENJE

// Ne mozemo imati nizove referenci, mozemo niz pokazivaca

// Niz nije objekat, ne postoji klasa niza

// Problem: niz objekata izvedene klase prenesemo funkciji kao niz objekata osnovne klase

#include <iostream>
using namespace std;

class Osnov {public: int bi;};
class Izveden : public Osnov {public: int di;}; // nasledjeni bi i spec. di
void k(Osnov *b, int i) { cout << b[i].bi; }    // pokazivac na osnovnu klasu
// ispisemo i-ti element

void m2() {
    Izveden d[5]; // niz isto sto i pokazivac
    d[2].bi = 77;
    k(d,2);    // niz objekata izvedene klase razlicite velicine od niz objekta osnovne klase
    // Pristupamo pogresnoj memorijskoj lokaciji
    // Nece se ispisati 77
}

// Resenje: pri baratanju sa nizovima ne radimo sa nizovima objekata (po vrednosti)
// Vec sa nizovima POKAZIVACA na objekte

void p(Osnov **b, int i) {cout << b[i]->bi;}
void c() {
    Osnov b1; Izveden d1, d2;
    Osnov *b[5];  // b se moze konvertovati u Osnovna**
    b[0] = &d1; b[1] = &b1; b[2] = &d2; d2.bi = 77;
    p(b,2);    // Ispisace se 77
}
// Svi pokazivaci su ISTE velicine (nije nam bitan pokazivani objekat u tom smislu)

// Nije dozvoljena implicitna konverzija Izvedena** u Osnovna**

void z() {
    Izveden *d[5];  // d je tipa Izvedena**
//    p(d,2);     // ! GRESKA, nije validna konverzija
}

//      APSTRAKTNI METODI I KLASE

// Primer: figura je osnovna klasa sa praznim metodom
// Nema smisla praviti objekat tipa figura

// Logicnije proglasiti metod "apstraktnim" - cisto virtuelna funkcija
// Umesto tela u viticastim zagradama stoji = 0

// Ima smisla praviti objekte izvedene iz klase, ne objekte apstraktne klase
// Apstraktni metod cini klasu apstraktnom - ne dozvoljava pravljenje objekta

// Moguce je praviti POKAZIVACE i REFERENCE tipa apsktraktne klase
// Pokazuju na objekte izvedene klase od osnovne

// U izvedenoj klasi se napravi redefinicija apstraktnih metoda

class Os {
public:
    virtual void cvf() = 0; // apskratkni metod
    virtual void vf();      // virutelni metod
};

class Izv : public Os {
public:
    void cvf();
};

void m3() {
    Izv izv, *pi = &izv;
//    Os osn;       //  ! GRESKA: Objekat apstraktne klase
    Os *po = &izv;
    po->cvf();      // poziva se Izvedena::cvf()
    po->vf();       // poziva se Osnovna::vf()
}