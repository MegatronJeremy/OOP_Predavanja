//      POJAM SPECIJALIZACIJE OPSTEG
// Klasa objekata (B) podvrsta druge klase (A)
// Objekat klase B je (is-a) i objekat klase A
// B je izvodjena klasa klase A (nasledjuje karakteristike (strukturne i ponasanja) - atribute i metode)

// objektno-bazirani jezik ne podrzava izvodjenje klasa
// objektno-orijentisani podrzava i nasledjivanje

// Izvedena klasa:
// ime modifikator : {virtual} {public, protected, private} ime osnovne klase {, <-- opet ponovo sve (visetruko izvodjenje)}
// Modifikator final - konacna klasa <-- ne moze se izvoditi vise iz nje

class A {};
class B {};
class C: A{};
class D: A, B{};
class E final: D{};
//class F: E{};   // ! GRESKA: klasa E je konacna
int final = 55; // final kao ime globalne promenljive (dopusteno)

class Osnovna {
    int i;      // atribut osnovne klase
public:
    void f();   // metod osnovne klase
};

class Izveden: public Osnovna { // javno izvedena iz osnovne (pravo izvodjenje)
    int j;      // atribut izvedene klase
public:         // nasledjen je: int i;
    void g();   // metod izvedene klase
};              // nasledjen je: void f();

int main() {
    Osnovna b;
    Izveden d;
    b.f();
//    b.g();      // ! GRESKA: g() je metod izvedene klase, a b je objekat osnovne
    d.f();        // objekat izvedene klase d ima i metod f()
    d.g();        // i metod g()
}

// Izvedena klasa ne nasledjuje iz osnovne klase:
// konstruktore
// destruktor
// operator= (operator dodele vrednosti)

// Kao i za osnovne klase, postoje ugradjeni (implicitno definisani) konstruktori, destruktor i operatori dodele

//      PRAVA PRISTUPA
// labela protected: (u osnovnoj klasei) <--- posebno pravo pristupa - zasticeno
// moze da im se pristupi kao nasledjenim clanovima iz metoda izvedene klase (ne preko objekta osnovne klase)

class Osnov {
    int pb;
protected:
    int zb;
public:
    int jb;
};

class Izved : public Osnov {
public:
    void m(int x) {
        jb = zb = x; // moze da se pristupi javnom i zasticenom clanu
//        pb = x; // ! GRESKA: privatnom clanu ne moze da se pristupi imenovanjem (samo metodima osnovne klase)
        Osnovna o;
//        o.zb = x;    // ! GRESKA: ne moze preko objekta osnovne klase
    }
};
void f() {
    Osnov b;
//    b.pb = 1;   // ! GRESKA: privatan clan
//    b.zb = 1;   // ! GRESKA: zasticeni clan
    b.jb = 1;   // u redu - pristup javnom clanu
}

//      NACINI IZVODJENJA
// moze biti javno, zasticeno i privatno (nije pravo izvodjenje - ne moze da zameni objekat osnovne klase)
// javno izvodjenje nasledjuje pravo pristupa clanovima (osim privatnom clanu)
// nacin izvodjenja odredjuje pravo pristupa clanovima iz osnovne klase

// javno -> javni, zasticen, privatan (originalna prava pristupa)
// zasticeno -> zasticen, zasticen, privatan (javni postaje zasticeni)
// privatno -> privatan, privatan, privatan (samo strukturno izvodjenje)

//      EKSPLICITNA PROMENA PRAVA PRISTUPA
// moze se podici, restaurirati, delimicno restaurirati pravo pristupa
// using klasa::clan (samo za clanove za koje postoji pravo pristupa u osnovnoj klasi)
// moze i samo klasa::clan uz upozorenje

class O {
    int pb;
protected:
    int z1b, z2b;
public:
    int j1b, j2b;
};
class PI : O {
public:
    using O::j1b;   // vracanje originalnog prava pristupa
    using O::z1b;   // povecanje prava pristupa
    PI() { z2b = 1; }   // moze se pristupiti iz metode izvedene klase iako je privatni clan (kao zasticeni atribut)
protected:
    using O::j2b;   // delimicno vracanje prava pristupa
};

class IPI: public PI{
public:
    IPI() {
        j1b = 0;    // Javno pravo pristupa
        j2b = 0;    // Pravo pristupa delimicno restauirano
        z1b = 0;    // Javno pravo pristupa
//        z2b = 0;    // ! GRESKA  <-- izgubio status zasticenog clana (privatnom clanu se ne moze pristupati iz izvedene)
    }
};

int main2() {
    PI pi;
    pi.j1b = 0; // javni clan klase PI
//    pi.j2b = 0; // ! GRESKA: zasticen clan klase PI
    pi.z1b = 0; // javni clan klase PI
//    pi.z2b = 0; // ! GRESKA: privatni clan klase PI
    return 0;
}