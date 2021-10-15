#include <iostream>

using namespace std;

//      EKSPLICITNI POZIV KONSTRUKTORA

// Konstruktor se moze pozvati i eksplicitno u nekom izrazu
// Takav poziv kreira privremeni objekat klase pozivom odgovarajuceg konstruktora sa navedenim argumentima
// Isto se desava ako se u inicijalizatoru objekta eksplicitno navede poziv konstruktora

//      KONSTRUKTOR KOPIJE

// Drugi naziv - kopirajuci konstruktor
// Pri inicijalizaciji objekta x1 drugim objektom x2 iste klase x
//      - poziva se konstruktor kopije (KK, engl. copy constructor)

// Ugradjeni, implicitno definisani konstruktor kopije:
//      - vrsi inicijalizaciju clanova x1 clanovima x2 (pravi plitku kopiju)
//      - primitivni atributi (ukljucujuci pokazivace) se prosto kopiraju
//      - za klasne atribute se pozivaju njihovi KK

// Ugradjeni KK klase x se brise (suspenduje)
//      - eksplicitno: X(const X&) = delete;    // zabrana kopiranja
//      - implicitno:
//          - pisanjem premestajuceg konstruktora ili premestajuceg operatora dodele
//          - moze se restaurirati pomocu: X(const X&) = default

// Inicijalizacija ugradjenim KK ponekad nije zadovoljavajuca
//      - ako objekti sadrze podobjekte po adresi (pokazivacu ili referenci)
//      - tada programer treba da ima potpunu kontrolu nad inicijalizacijom celog objekta drugim objektom
//        iste klase

// Konstruktor kopije ima parametar tipa XX& ili const XX&
//      - konstruktor ne sme imati parametar tipa svoja klase kao jedini parametar ili ako ostali parametri
//        imaju podrazumevane vrednosti

// Konstruktor kopije se poziva sa jednim stvarnimn argument (tipa klase ciji se objekat stvara kopiranjem)

// KK se poziva kada se objekat inicijalizuje objektom iste klase i to:
//      - prilikom stavaranja trajnog, automatskog, dinamickog ili privremenog obj.
//          oblik inicijalizatora (zagrade () ili {}, simbol =) je nebitan
//      - prilikom prenosa arg. po vrednosti u funkciju (stavar se automatski obj.)
//      - prilikom vracanja vrednosti iz funkcije (stvara se privremeni objekat)

// Prevodilac sme da preskoci poziv KK (radi optimizacije)
//      - ako se stvarni objekat inicijalizuje privremenim objektom iste klase
//      - neprijatno, jer izostaju i bocni efekti - program nije prenosiv
//      - cak i u ovom slucaju mora postojati KK ili premestajuci konstruktor

class X {
public:     // kopija moze biti samo lvrednost
    X(const X&) = delete; // zabrana kopiranja (implicitnog) - takodje se suspenduje ako pravimo premestajuci konstruktor
//    X(const X&) = default; // restauriramo implicitni konstruktor
};

// KONSTRUKTOR KOPIJE
class XX {
public:
    XX(int);
    XX(const XX&);
    //...
};
XX f(XX x1) {
    XX x2 = x1;     // poziv konst. kopije XX(XX&) za x2
    return x2;      // poziv konst. kopije za privremeni
}                   // objekat u koji se smesta rezultat
void g() {
    XX xa = 3, xb = 1;  // argumenti za poziv konstruktora
    xa = f(xb);     // poziv konst. kopije samo za parametar x1,
                    // a u xa se samo prepisuje
                    // privremeni objekat rezultata, ili se
                    // poziva XX::operator= ako je definisan
}

//      PREMESTAJUCI KONSTRUKTOR

// Konstruktor koji se poziva za konstrukciju objekata istog tipa, pri cemu je izvrisni objekat na kraju zivtnog veka
//  - izvorisni objekat je nvrednost (nestajuce vrednost - xvalue, expiring value)
//  - izvorisni objekat ne mora da se sacuva
//  - mogu se samo "premestiti" njegovi dinamicki delovi u odredisni objekat
//  - nema kopiranja dinamickih delova izvorisnog objekta, dovoljna je plitka kopija
//  - premestajuci konstruktor efikasniji od kopirajuceg
//  - treba samo modifikovati izvorisni objekat - ne nacin da njegovo unistavanje ne povuce razaranje vec premestenih
//    delova u odredisni objekat

// Postavlja se din. atribut pokazivaca na nullptr zbog destruktora - da se ne bi i u premestenom objektu unistio)

// Ugradjeni premestajuci konstruktor pravi plitku kopiju originala
//  - za atribute tipa klase - zovu se njihovi premestajuci konstruktori
//  - za polja tipa pokazivaca - kopirace se samo njihove vrednosti

// Ugradjeni premestajuci konstruktor se suspenduje (brise), ako se eksplicitno definise:
//  - premestajuci konstruktor
//  - kopirajuci konstruktor
//  - destruktor
//  - operator dodele

// Parametar premestajuceg konst. je referenca na dvrednost: XX&&
//  - kao kod KK, ostali parametri moraju imati podrazumevane vrednosti

// Prevodilac ce pozvati premestajuci konstruktor
//  - ako izvorisni objekat nestaje
//  - ako u klasi postoji (ugradjeni ili napisani) premestajuci konstruktor

// Ako u klasi ne postoji premestajuci konstruktor
//  - poziva se kopirajuci konstruktor
//  - semantika nije promenjena
//  - samo moze biti promene u brzini izvrsavanja

class Niz {
    double *a;
    int n;
public:
    Niz(Niz &&niz) {
        a = niz.a;
        niz.a = nullptr;
        n = niz.n;
    }
};       // Ako ne postoji premestajuci konstruktor zove se kopirajuci konstruktor
            // (postoji i implicitni premestajuci konstruktor koji se suspenduje definicijom bilo cega)
Niz f(Niz niz) {return niz;}    // Vraca se objekat klase po vrednosti (dvrednost)

//      KONVERZIONI KONSTRUKTOR

// Konverzija izmedju tipova klasa od kojih je barem jedan klasa - definise je korisnik

// Jedna mogucnost konverzije tipova:
//  - pomocu konstruktora konverzije
//  - odredisni tip mora biti klasa

// Ako u klasi U postoji U::U(T&), ili U::U(T) gde je T klasa ili standardni tip:
//  - vrednost izaraza U(t), gde je t tipa T, je privremeni objekat tipa U
//  - to predstavlja konverziju iz tipa T u tip U

// Korisnicke konverzije ce se primenjivati automatski (implicitno)
//  - ako je jednoznacan izbor konverzije
//  - izuzev u slucaju explicit konstruktore

// Automatska konverzija mora biti neposredna:
//  - za U::U(T&) i V::V(U&) moguce je samo eksplicitno V(U(t)) <--- neposredno <-> bez adrese

// Pomocu konverzionog konstruktora nije moguce konverzija u standardni tip:
//  - ovaj nije klasa za koju korisnik moze da definisi konverzioni konstruktor

// Druga mogucnost definisanja konverzija - preklapanje kast operatora

// Konverzija argumenata i rezultata funkcije
//  - pri pozivu funkcije:
//      inicijalizuju se parametri stvarnim argumentima, uz eventualnu konverziju tipa
//      parametri se ponasaju kao automatski lokalni objekti pozvane funkcije
//      ovi objekti (ako su klasnih tipova) se konstruisu pozivom odgovarajucih konstruktora
//  - pri povratku iz funkcije:
//      konstruise se privremeni objekat koji prihvata vrednost return izraza na mestu poziva


class T {
public:
    T(int i);   // konstruktor
};
T f1(T k) {
    //...
    return 2;       // poziva se konstruktor T(2)
}
void h() {
    T k(0);
    k=f1(1); // poziva se konstruktor T(1) i dodela vrednosti
}

//      KONSTANTE KLASNOG TIPA

// Kao i globalne f-je i metodi - i konstruktor moze biti "konstantan'
//  - modifikator deklaracije i definicije constexpr
//  - prazno telo (C++14 dozvoljava naredbe koje su konstantni izrazi)
//  - za sve atribute inicijalizatori moraju biti konstantni izrazi
//  - za atribute klasnog tipa mora postojati konstantni konstruktor

// Ugradjeni podrazumevani konstruktor - konstantan - ako za atribute klase postoji konstantna inicijalizacija
// Za restaurirani podrazumevani konstantni konstruktor - nije potreban constexpr

// Konstantan objekat se stvara:
//  - konstantnim konstruktorom
//  - sa konstantnim argumentima

// Konstanan objekat se koristi efikasno kao i konstanta

class A {
    int a = 1, b = 2;   // Konstantni inicijalizatori
public:
    constexpr A(int x, int y) : a(x+y), b(x-y) {}
    A() = default;  // restauracija podrazumevanog k
};

class Beta {
    A a; int b;
public:
    constexpr Beta(int x) : b(2*x) {}
    Beta() = default;
};

void cexp() {
    constexpr A a1(3, 4);   // konstantan objekat
    int k = 1;
//    constexpr A a2(k, k+1); // ! GRESKA
//    constexpr A a3(k-1, k+1); // promenljiv objekat
    constexpr A ar(a1); // postoji ugradjeni KK
    constexpr A a5;     // postoji restauriran PK

    constexpr Beta b1(3);
    constexpr Beta b2(b1);
//    constexpr Beta b3{};      // ! GRESKA - PK nije konstantan
}


//      DESTRUKTOR (obrnut redosled od poziva konstruktora)

// Nema tip rezultata i ne moze imati parametre
// Moze da postoji najvise jedan u klasi

// Destruktor se pise kada treba osloboditi (dealocirati)
//  - memoriju koju je konstruktor zauzeo (alocirao)
//  - druge (nememorijske) resurse

// U destruktoru se clanovima pristupa kao i u nekom metodu - preko pokazivaca this

// Destruktor se implicitno poziva na kraju zivotnog veka objekta
class X2 {
public:
    ~X2() {cout << "Poziv destruktora klase X!\n";}
};

// Pri unistavanja dinamickog objekta pomocu operatora delete - destruktor se implicitno poziva
// pre oslobadjanja memorije

// Pri unistavanju dinamickog niza - destruktor se poziva za svaki element niza, po opadajucem indeksu

// Redosled poziva destruktora uvek obrnut od redosleda poziva konstruktora

// Destruktor moze i eksplicitno da se pozove:
//  - x.~X() ili
//  - px->~X() ili
//  unutar metoda klase X:this->~X()

// Eksplicitan poziv se ne preporucuje - poziv ima efekat kao i poziv metoda datog objekta
//  - objekat nastavlja da zivi

// Posle izvrsavanja tela automatski pozvanog destruktora
//  - automatski se oslobadja memorija koju je sam objekat zauzimao

class Complex {
public:
    Complex() = default;
    Complex(double _re, double _im) {
        real = _re;
        imag = _im;
    }
    Complex zbir(Complex); Complex razlika(Complex);  //metode klase
    double re(); double im();
private:
    double real = 0, imag = 0;      //atributi klase
};

int main() {
    Complex c1(1, 2.4), c2; // Implicitni poziv
    c2 = c1.zbir(Complex(3.4, -1.5));   // Privremeni objekat <-- eksplicitni poziv konstruktora
    Complex c3 = Complex(0.1, 5);   // Privremeni objekat se kopira u c3
    // (uslovno - kopirajuci konstruktor, ali kompajler moze odmah inicijalizovati atributima privremenog objekta)

    X2 x;
    x.~X2(); // ne preporucuje se jer objekat nastavlja da zivi
    //... --> ispis (poziva se implicitno destruktor kad objekat izlazi iz svog opsega)
}