// Ponekad su globalne prijateljske funkcije pogodnije od metoda:
//  - metod mora da se pozove za objekat date klase,
//    dok globalnoj funkciji moze da se dostavi i objekat drugog tipa
//          nije moguce konverzija skrivenog argumenta u drugi tip

//  - kada funkcija treba da pristupa privatnim clanovima vise klasa,
//    prijateljska globalna funkcija je "simetricno" resenje
//          nisu potrebni javni metodi u "ostalim" klasama

// Ponekad je notaciono pogodnije da se koriste globalne funkcije (f(x)) nego metodi (x.f())
// max(a, b) - globalna prijateljska funkcija; a.max(b) - metod klase <--- citljivije preko globalne f-je

// Ako su svi metodi klase X prijateljske funkcije klasi X, onda je X prijateljska klasa (friend class) klasi X

class X;
class X {
    friend X;   // ako je X definisana ili deklarisana
    friend class Z; // ako Z jos nije ni def. ni dek.
};
// Svi metodi klase X mogu da pristupaju privatnim clanovima klase X
// Prijateljske klase se tipicno koriste kada neke dve klase imaju tesnje medjusobne veze

class Proizvod {
private:
    friend class Fabrika;
    Proizvod(); //konstruktor je dostupan samo klasi fabrika;
};

//      STRUKTURE

struct a {
    //...    <-- podrazumevana sekcija javna
private:
    //...
};
// isto sto i:
class A {
public:
    //...    <-- podrazumevana sekcija privatna
private:
    //...
};
// U C++ struktura moze imati i metode

// Struktura se tipicno koristi:
//  - za definisanje struktuiranih podataka koji ne predstavljaju apstrakcijum
//    odnosno nemaju bitno ponasanje (nemaju znacajnije operacije)

// Strukture tipicno poseduju samo konstruktore i eventualno destruktore

//      UGNEZDJENE KLASE

// Klase mogu da se deklarisu ili deifnisu unutar definicije druge klase
// Ugnezdjivanje se koristi kada neki tip (npr. klasa) semanticki pripada samo datoj klasi
//  - povecava se citljivost programa
//  - smanjuje se potreba za globalnim tipovima

// Unutar definicije klase se mogu navesti i
//  - definicije nabrajanja (enum) i  tipova (typedef)

// Ugnezdjena klasa (tip) se nalazi u dosegu imena okruzujuce klase
//  - izvan okruzujuce klase imenu ugnezdjene klase se moze pristupiti
//    samo preko operatora prosirenja dosega imena ::

// Iz okruzujuce klase do clanova ugnjezdene moguc je samo pristup:
//  - pomocu operatora ., ->, i ::

// Doseg imena okruzujuce O se proteze na ugnezdjenu klasu U
//  - ali iz U do clanova objekta O je moguc samo pristup preko . i ->

// U ugnezdjenoj klasi mogu direktno da se koriste samo identifikatori:
//  - tipova iz okruzujuce klase
//  - konstanti tipa nabrajanja iz okruzujuce klase
//  - statickih clanova iz okruzujuce klase
// To vazi ako ime nije sakriveno imenom clana ugnezdjene klase

// Pristup statickom clanu ugnezdjene klase izvan okruzujuce:
//  <id okruzujuce>::<id ugnezdjene>::<id statickog clana ugnezdjene>

// Ugnjezdena klasa je implicitno prijatelj okruzujucoj klasi (obrnuto ne vazi)
//  - ima pravo pristupa privatnoj sekciji okruzujuce
//  Okruzujuca klasa nije prijatelj ugnezdjene
//  - mora se eksplicitno proglasiti prijateljem da bi mogla da pristupi privatnoj sekciji

int x, y;
class Spoljna {
public:
    int x; static int z;
    class Unutrasnja {
        int k;
        void f(int i, Spoljna *ps) {
//            x = i;      // ! GRESKA: nepoznat objekat klase Spoljna
//            Spoljna::x = i;     // ! GRESKA: isti uzrok
            z = i;  // pristup statickom clanu spoljna
            ::x = i;        // pristup globalnom x; (unarni operator za pristup glob. prom.)
            y = i;      // pristup globalnom y;
            ps->x = i;      // pristup Spoljna::x objekta *ps;
        }
        friend Spoljna;
    };
    void g(int i, Unutrasnja *pu) {
        pu->k = i;  // Dozvoljeno - unutrasnja deklarisala spoljnu prijateljem
    }
};
//Unutrasnja u;       // ! GRESKA: nije u dosegu
Spoljna::Unutrasnja u;      // u redu;


//      LOKALNE KLASE
// Lokalne klase se definisu unutar funkcija (doseg u tom bloku)

// Identifikator lokalne klase ima doseg (oblast vazenja) od deklaracije do kraja bloke
// u kojem je deklarisan

// Unutar lokalne klase iz okruzujuceg dosega je dozvoljeno samo koriscenje:
//  - identifikatora tipova
//  - konstanti tipa nabrajanja
//  - trajnih podataka (statickih atributa, statickih lokalnih i globalnih)
//  - spoljasnjih (eksternih) podataka i funkcija

// Metodi lokalne klase moraju da se definisu unutar definicije klase

// Lokalna klasa ne moze da ima staticke (zajednicke) atribute

int x1;
void f() {
    static int s;
    int x1;
    extern int g(); // eksterna globalna funkcija
    class Lokalna {
    public:     // inline metodi
//        int h() { return x1; }   // ! GRESKA: x je automatska prom.
        int j() { return s; }   // OK: s je staticka promenljiva
        int k() { return ::x1; }    // OK: x je globalna promenljiva
        int l() { return g(); }     // OK: g() je spoljasnja funkcija
    };
}
//Lokalna *p = 0;     // ! GRESKA: nije u dosegu

//      POKAZIVACI NA CLANOVE KLASE
// Dodelom vrednosti pokazivacu na clanove klase oznaci se neki clan klase
// Analogija: kao sto se indeksom oznaci komponenta niza

// Pokazivac na clanove klase se deklarise:
//  <tip clana klase><klasa>::*<identifikator pokazivaca clana>

// Formiranje adrese clanova klase:
//  <identifikator pokazivaca clana>=&<klasa>::<clan klase>

// Pristup clanova pomocu pokazivaca na clanove klase:
//  <objekat klase>.*<identifikator pokazivaca clana> ili
//  <pokazivac na objekat klase>->*<identifikator pokazivaca clana>

// Operatori .* i ->* su prioriteta 14 i asocijativnost je sleva-udesno

class Alfa { public: int a, b; };

int main() {
    int Alfa::*pc;      // pc je pokazivac na int clanove klase Alfa
    Alfa alfa, *beta;
    beta = &alfa;       // beta je pokazivac na objekat klase

    pc = &Alfa::a;      // pc pokazuje na clanove a objekata klase Alfa (uzimanje relativne adrese u odnosu na pocetak objekta klase Alfa)
    alfa.*pc = 1;       // alfa.a=1
    beta->*pc = 1;      // beta->a=1

    pc = &Alfa::b;      // pc pokazuje na clanove b objekata klase Alfa
    alfa.*pc = 2;       // alfa.b = 2;
    beta->*pc = 2;      // beta->b = 2;
}