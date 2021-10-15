#include <iostream>
using namespace std;

//      APSTRAKTNI DESTRUKTOR

// Hocemo da klasa ima sve konkretne funkcije (sa implementacijom), ali ne zelimo da se prave objekti te klase
// Resava se definisanjem apstraktnog destruktora

// Virtuelni destruktor, umesto tela = 0 u definiciji klase

// Uopste nije apstraktan (iako se zove tako)
// Izvan klase pisemo definiciju

class O {
public:
    virtual ~O() = 0;
};  // Ne moze se napraviti objekat osnovne klase

O::~O() {}

class I : public O {};

void t1() {
//  O o;      // ! GRESKA
    I i;        // U redu
}

//      GENERALIZACIJA I KONKRETIZACIJA

// Apstraktne klase osnovica daljoj konkretizaciji

// Primer: apstraktna klasa Figura (ne zna se uopsteno izracunavanje povrsine - znamo da je ima)
// U daljim klasama polimorfno redefinisemo apstraktne metode

// Ako ne redefinisemo apstraktni metod u izvedenoj klasi, ona ce biti isto apstraktna

// Ne mozemo praviti objekte apstraktne klase (ali je potreban konstruktor apstraktne klase)
// Objekat izvedene klase implicitno poziva konstruktor osnovne (apstraktne) klase
// Potrebna dodela vrednosti ili inicijalizacija atributa osnovne klase

//      PROBLEM KONVERZIJE NANIZE

// Kada crtamo graf izvodjenja (UML) - osnovna klasa gore - izvedena dole
// Konverzija od osnovne prema izvedenoj klasi - nebezbedna
// Konverzija navise - bezbedna (moze se raditi implicitno)

// Pokazivac na osnovnu klasu - postavimo da pokazuje na objekat izvedene klase
// Implicitno ga konvertujemo na pokazivac u osnovnu klasu

// Obrnuto nije bezbedno - pokazivac na osnovnu klasu konvertujemo u pokazivac na izvedenu
// Ne znamo da li u tom trenutku pokazuje na objekat zeljene izvedene klase
// Ako pokazuje na objekat osnovne ili neke druge klase, ne valja ta konverzija

// C++ predvideo cetvrtu vrstu cast operatora - dinamicki cast (vrsi proveru u VREME IZVRSENJA)
// Posmatra da li je nebezbedna konverzija u datom trenutku bezbedna

// dynamic_cast<izvedena klasa*>(pokazivac)
// dynamic_cast<izvedena klasa&>(referenca)

// Pokazivac/referenca da budu na objekat polimorfne osnovne klase (koja ima bar jednu virtuelnu funkciju)
// Konverzija se radi uzimajuci u obzir tip objekta na koji upucuje pokazivac/referenca
// U suprotnom se radi staticko vezivanje (ne funkcionise kako treba)

// Ako pokazivac ne pokazuje na objekat izvedene klase u koju se vrsi konverzija:
// Za pokazivac rezultat je nullptr
// Za referencu baca se izuzetak bad_cast

class A {public: virtual void vm() {}}; // polimorfna klasa
class B: public A{};
class C: public A{};

void f() {
    A *pa = new B();    // Bezbedna - implicitna konverzija
    // Pokazivac na izvedenu konvertujemo u pokazivac na osnovnu

    // Konverzije u suprotnom smeru:
    B *pb = dynamic_cast<B*>(pa);
    // Pokazivac na osnovnu klasu konvertujemo u pokazivac na izvedenu
    // Nebezbedna generalno - ali ovde bezbedna (pa pokazuje na objekat klase B)

    B *pc = dynamic_cast<B*>(pa);   // pc == nullptr
    // Greska - u vreme izvrsenja ce se otkriti (pokazuje na objekat klase B - ne C)

    // Ista prica sa referencama
    B &rb = dynamic_cast<B&>(*pa);
    // Mozemo - po tipu referenca na izvedena klasa na koju upucuje referenca

    C &rc = dynamic_cast<C&>(*pa);  // bad_cast
    // Nije klasa C upucivani objekat
}

//      DINAMICKO ODREDJIVANJE TIPA

// Dozvoljeno u vreme izvrsenja odredjivati tip izraza
// typeid(izraz)
// typeid(tip)
// Dve varijante (u zavisnosti od operanda)

// Poredimo tip izraza sa zadatim tipom

// Izraz moze biti proizvoljnog tipa, ili korisnickog (klasnog) ili ugradjenog (primitivnog) tipa

// Vrednost izraza - bocni efekat - se nece desiti
// Samo za odredjivanje tipa izraza

// Za odredjivanje dinamickog tipa (npr. koji se svodi na pokazivac na objekat - po tipu objekat
//      mora biti objekat polimorfne klase - radi se dinamicki, u suprotnom staticki)

// Ako se dereferncirani nullptr javlja  u typeid (typeid(*p)) - vraca se izuzetak bad_typeid

// Rezultat: const type_info& <--- referenca na nepromenljivi objekat type_info
// type_info u typeinfo zaglavlju

// U vreme izvrsenja otkrivamo tipove - introspekcija, refleksija, program saznaje stvari o samom sebi

//      KLASA TYPE_INFO

// Tip iz <typeinfo>
// Metodi klase type_info:
//  bool operator==(const type_info&) const;
//  bool operator!=(const type_info&) const;

//  bool before(const type_info&) const;
//  Sluzi nam da utvrdimo da li su dva objekta uredjena (na neki ocekivani nacin)
//  Zavise od implementacije prevodioca (on i after)
//  Before uredjuje tipove po leksikografskom redosledu imena tipova
//  Tip klasa A pre klase B, tip float pre int

//  const char *name() const;
//  Vraca nepromenljivi c string (neko logicno ime tipa)

// Svi metodi su const tipa
// Typeinfo nema javne konstruktore (ni podrazumevani konstruktor)
// Konstruktor kopiranja nije javan
// Ne mozemo praviti objekte, podatke tipa typeinfo

// Objekti type_info se prave SAMO pomocu typeid operatora
// Posledica je da ne mozemo type_info objekat kao argument po vrednosti, samo po referenci
// Po vrednosti - konstruktor kopije/ premestanja
// Operator dodele takodje privatan

class O1{};  // nepolimorfna klasa
class I1: public O1{public: virtual void f(){}};    // Polimorfna klasa
class II: public I1{};          // Polimorfna klasa (nasledjen f())

int main() {
    O1 *po = new I1;    // pokazivac na osnovnu (tip pokazivanog je O - staticna klasa)
    I1 *pi = new II;    // pokazivac na izvedenu
    cout << (typeid(*po)==typeid(I1)) << endl;  // 0 - klasa O je NEPOLIMORFNA (staticko odlucivanje)
    cout << (typeid(*pi)==typeid(II)) << endl;  // 1 - Radi se dinamicka provera tipa objekta
    cout << typeid(O1).name() << endl;  // O1
    cout << typeid(*po).name() << endl; // O1 - tip OSNOVNE KLASE (iako pokazuje na objekat izvedene - ali je nepolimorfna izvedena klasa - po tipu pokazivaca NE objekta)
    cout << typeid(*pi).name() << endl; // II - polimorfna osnovna klasa - PO TIPU OBJEKTA (na koji se pokazuje)
    cout << typeid(po).name() << endl;  // O * - tipovi pokazivaca
    cout << typeid(pi).name() << endl;  // I *
    int m[100][20];
    cout << typeid(m).name() << endl;   // int[100][20]
}

//      ZLOUPOTREBA ODREDJIVANJA TIPA

// Ne sme se svesti program da proverava tip, pa posle takve provere pozivamo neki metod
// To je centralizacija logike (u nekom switch-u - otezava odrzavanje)

// Potrebno je izvrsiti decentralizaciju odgovornosti na neku klasu u kojoj je metod opisan (ne na onoga ko poziva metod)

// Zvace se metod osnovne - ili objekat izvedene klase - mehanizam dinamickog vezivanja
// Blagodet OO programiranja (decentralizacija odgovornosti - svaka cklasa definise na svoj nacin - odlucuje se na osnovu tipa objekta na koji se upucuje/pokazuje)


//      VISESTRUKO NASLEDJIVANJE (MULTIPLE INHERITANCE)

// Nasledjivanje osobina od vise klasa koje nisu jedna drugoj vrsta

// Npr. konj je i prevozno sredstvo i zivotinja (nisu osnovne klase u medjusobnom odnosu izvodjenja)
// Nova klasa iz dve klase visestrukim izvodjenjem (visestruko nasledjivanje)

// Neki smartphone - i telefon i racunar (telefon nije racunar i obrnuto)

// Nabrajamo iza deklaracije
// Public : nasledjuje i pravo pristupa kada se pristupa preko objekta izvedene klase, nasledjuje i ugovor
// Private : samo strukturu podataka, atribute i operacije (samo implementacije)
// class I: public O1, public O2, public O3 {}

//      KONSTRUKCIJA I DESTRUKCIJA

// Vise osnovnih klasa, redosled konstrukcije redom konstruktora osnovnih klasa u deklaraciji pri izvodjenju
//  kako su navodjeni
// Posle osnovnih klasa, atributi izvedene klase i na kraju telo konstruktora izvedene klase

// Destruktori uvek obrnutim redosledom od izvrsavanja konstruktora
// Prvo izvedene klase s desna u levu odozdo navise pa isto, po listi u deklaraciji izvodjenja

//      Problem "dijamant strukture"

// Istoimeni atributi, metode - nasledjuju se duplikati
// Potenciran kod dijamant strukture - iz jedne osnovne klase iz izvedenih klasa izvedene nove klasa
// Nasledje iz osnovne klase (na vrhu) se kroz 2 ili vise grane nasledjuje i na dnu

class D {public: int i;};   // na vrhu hijerarhije
class X : public D{};
class Y : public D{};
class Z : public X, public Y{};

// Imamo dve grane nasledjivanja atributa i metoda iz klase D (jedna grana iz X druga iz Y)
// Objekat klase Z ima dva atributa i

// Dva puta se izvrsava konstruktor klase D kada se vrsi konstrukcija klase Z
// Konstrukcija podobjekta X i Y pa njihove podobjekte

// U nekim metodima klase Z, mozemo razlikovati preko operatora ::
void g() {
    Z z;
    z.X::i;
    z.Y::i;
}

// Najcesce nezeljeno

// Radimo izvodjenje iz virtuelnih osnovnih klasa da bismo resili ovaj problem

class D1 {public: int i;};
class X1 : virtual public D1 {};
class Y1 : virtual public D1 {};    // Bilo koji da ukinemo imamo dva nasledja
class Z1 : public X, public Y {};

// Imamo samo jedno nasledje i
// Samo jedan konstruktor klase D
// Da imamo jos nevirtuelno izvedene klase P i Q - i Z visestruko izvodi i iz njih - ukupno 3 kopije i

// Ako ne redefinisemo neki metod iz klase D - jednom se nasledjuje u svakom slucaju
// Ako ga redefinisemo u X ili Y - imamo dve razlicite implementacije istog metoda
// Kada bi se zvao za objekat klase Z, zove se njegova redefinicija
// Ako redefinisemo i u X i Y - PROBLEM - DVOZNACNO

//      REDOSLED KONSTRUKCIJE

// Konstruktori virtuelnih osnovnih klasa UVEK pre konstruktora nevirtuelnih osnovnih klasa
// na istoj dubini grafa izvodjenja

// Najpre konstruktori osnovnih virtuelnih klasa na vrhu grafu izvodjenja, pa onda s leva u desno konstruktori nevirtuelnih
// osnovnih klasa, pa atributi
// Konstruktori virtuelnih osnovnih klasa SAMO JEDNOM, nevirtuelnih koliko ima OBJEKATA

class B1 {
public: B1() {cout << " B";};
};

class X2 : virtual public B1 {  // moze biti virtuelno ili nevirtuelno
public: X2() {cout << " X";}
};

class Y2 : virtual public B1 {  // moze biti virtuelno ili nevirtuelno
public: Y2() {cout << " Y";}
};

class Z2 : public X2, public Y2 {
public: Z2() {cout << " Z" << endl;}
};

// B X Y Z
// Jednom konstruktor klase B, prva osnovna X u listi, pa Y pa Z na kraju

class B2 {
public: B2() {cout << " B";};
};

class X3 : public B1 {  // moze biti virtuelno ili nevirtuelno
public: X3() {cout << " X";}
};

class Y3 : virtual public B1 {  // moze biti virtuelno ili nevirtuelno
public: Y3() {cout << " Y";}
};

class Z3 : public X2, public Y2 {
public: Z3() {cout << " Z" << endl;}
};

// B B X Y Z
// Prvo B je B ZA INICIJALIZACIJU PODOBJEKTA U Y (nasledjenog), pa B iz X, pa X, pa Y, pa Z (redom)

class B3 {
public: B3() {cout << " B";};
};

class X4 : virtual public B1 {  // moze biti virtuelno ili nevirtuelno
public: X4() {cout << " X";}
};

class Y4 : public B1 {  // moze biti virtuelno ili nevirtuelno
public: Y4() {cout << " Y";}
};

class Z4 : public X2, public Y2 {
public: Z4() {cout << " Z" << endl;}
};

// B X B Y Z
// Prvo konstruktor klase B, pa konstruktor klase X, pa konstrukcija podobjekta Y itd..

class B4 {
public: B4() {cout << " B";};
};

class X5 : virtual public B1 {  // moze biti virtuelno ili nevirtuelno
public: X5() {cout << " X";}
};

class Y5 : virtual public B1 {  // moze biti virtuelno ili nevirtuelno
public: Y5() {cout << " Y";}
};

class Z5 : public X2, virtual public Y2 {
public: Z5() {cout << " Z" << endl;}
};

// B Y X Z
// Jednom izvrsenje konstruktora B, Y SE IZVRSAVA PRE (IMA PRIORITET VIRTUELNA KLASA)

// virtual public X, virtual public Y - B X Y Z

// Vrsi se podrazumevani konstruktor virtuelne osnovne klase (kada se izvrsava)
// U listi inicijalizatora klase X ili Y stavili : , ne bi se pozivao taj konstruktor, vec podrazumevani
//  virtuelne osnovne klase
//class X4 : virtual public B1 {  // moze biti virtuelno ili nevirtuelno
//public: X4() : B1(int) {cout << " X";} <--- NE POZIVA SE TAJ KONSTRUKTOR (VEC PK VIRTUELNE OSNOVNE KLASE)
//};
