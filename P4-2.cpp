//      KLASA je struktuirani korisnicki tip koji obuhvata:
// podatke koji opisuju stanje objekta klase
// funkcije namenjene definisanju operacija nad podacima klase

// Klasa je formalni opis apsktrakcije koja ima internu implementaciju i javni interfejs
// Primerak (instanca, pojava) klase naziva se objektom te klase
// Podaci koji su deo klase nazivaju se podaci clanovi klase (data members), polja ili atributi
// Funkcije koje su deo klase nazivaju se funkcije clanice (member functions), primitivne operacije, metodi

//      KOMUNIKACIJA OBJEKATA
// objekti klasa komuniciraju (saradjuju) da ostvare slozene funkcije
// Poziv metoda se naziva upucivanjem poruke objektu klase
// Objekat klase moze da menja svoje stanje predstavljeno atributima kada se pozove njegov metod,
// odnosno kada mu se uputi poruka
// Objekat koji salje poruku (poziva metod) naziva se objekat-klijent
// Objekat koji prima poruku (ciji se metod poziva) je objekat-server
// Iz svog metoda objekat moze pozivati metod drugog objekta
//      - pozvan metod moze biti clan iste ili druge klase
//      - tok kontrole "prolazi kroz" razne objekte koji komuniciraju
// Unutar metoda, clanovima objekta ciji je metod pozvan pristupa se navodjenjem njihovog imena

//      PRAVA PRISTUPA
// Svaka sekcija zapocinje labelom sekcije (kljucna rec)
// Clanovi (podaci ili funkcije) klase iza kljucne reci private:
//      - nazivaju se privatnim (engl. private) clanovima:
//      - zasticeni su od pristupa slpolja (kapsulirani su)
//      - njima mogu pristupati samo metodi klase (i prijatelji)
// Clanovi iza kljucne reci public:
//      - nazivaju se javnim (public) clanovima:
//      - dostupni su spolja bez ogranicenja
// Clanovi iza kljucne reci protected:
//      - nazivaju se zasticenim (protected) clanovima:
//      - dostupni su metodima date klase, kao i klasa izvedenih iz te klase
//      - nisu dostupni ostalim funkcijama

// Preporucen redosled: public -> protected -> private

// Moze biti vise sekcija iste vrste
// Podrazumevana sekcija (do prve labele) je privatna
// Kontrola pristupa clanovima nije stvar objekta, nego klase:
//      - metod klase X pozvan za objekat o1
//        moze da pristupi privatnim clanovima drugog objekta o2 iste klase X
// Kontrola pristupa clanovima je odvojena od koncepta dosega imena:
//      - najpre se, na osnovu oblasti vazenja imena i njihove vidljivosti, oredjuje entitet
//        na koga se odnosi dato ime na mestu obracanja u programu
//      - zatim se odredjuje da li je tom entitetu dozvoljen pristup sa tog mesta

//      DEFINISANJE KLASE

// Atributi
//  - mogu da budu i inicijalizovani
//  - ne mogu da budu tipa klase koja se definisi, ali mogu biti pokazivaci ili reference na tu klase

// Metodi
//  - u definiciji klase mogu da se deklarisu (navodi se prototip) ili definisi (navodi se i telo)
//  - funkcije koje su definisane u definiji klase:
//       mogu pristupati clanovima klase direktnim navodjenjem imena tih clanova, i inline su
//  - funkcije koje su samo deklarisane u definiciji klase:
//       moraju biti definisane kasnije, izvan definicije klase,
//       treba prosiriti doseg klase (<ime_klase>::<ime_funkcije>) za pristup imenima clanova

// Vrednost rezultata, kao i parametri mogu biti tipa klase ciji su clanovi kao i tipa pokazivaca
// ili reference na tu klase

// Definicija klase mora biti prisutna tamo gde se klasa koristi
//  - zato se definicija klase uobicajeno pise u datoteci zaglavlju (*.h)

// Primer definicije klase
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

// Nepotpuna definicija klase (bez tela) - deklaracija
class Kompleksni1; // Samo definicija (dovoljno za pokazivac i referencu na klasu) - objekat nije moguc

// Primerci klase se definisu na nacin koji je uobicajen za definisanje objekata standardnih tipova:
//  - identifikator klase se koristi kao oznaka tipa, npr Kompleksni c

// Za svaki objekat klase formira se poseban komplet svih nestatickih atributa te klase
// Nestaticki metodi klase se pozivaju za objekte klase

// Lokalne staticke promenljive metoda
//  - su zajednicke za sve objekte date klase
//  - zive od prvog nailaska na njihovu definiciju do kraja programa
//  - imaju sva svojstva lokalnih statickih promenljivih globalnih funkcija

//      PODRAZUMEVANE OPERACIJE
// Podrazumevano je moguce:
//  - definisanje objekata, pokazivaca i referenci na objekte i nizova objekata klase
//  - dodela vrednosti (operator =) jednog objekta drugom
//  - uzimanje adrese objekata (operator &)
//  - posredno pristupanje objektima preko pokazivaca (operator *)
//  - neposredno pristupanje atributima i metodima preko pokazivaca (operator ->)
//  - pristupanje elementima nizova objekata (operator [])
//  - prenosenje objekata kao argumenata i to po vrednosti, referenci ili pokazivacu
//  - preklapanje operatora (pisanjem odgovarajucih operatorskih funkcija)

// automatski podaci - sama definicija ; static definicija - memorija za staticke podatke zasebno

//      KLJUCNA REC THIS -> POKAZIVAC NA TEKUCI OBJEKAT (ZA KOJI JE POZVAN DATI METOD)

// Unutar svakog nestatickog metoda - implicitni (podrazumevani, ugradjeni) lokalni pokazivac this
// Tip ovog pokazivaca je "konstantni pokazivac na klasu ciji je metod clan"
// klasa X, this je tipa X *const this

Complex Complex::zbir(Complex c) {
    Complex t;
    t.real=this->real+c.real; t.imag=this->imag+c.imag;         //isto kao dole
//    Complex t = *this; // u t se kopira tekuci objekat
//    t.real+=c.real; t.imag+=c.imag;
    return t;       // t je na steku, vraca se samo rezultat po vrednosti (ok)
}

// Pristup clanovima objekta ciji je metod pozvan obavlja se neposredno
// Implicitno je to pristup preko pokazivaca this i operatora ->

// this je jedan skriveni argument metoda

// objekat.f() se prevodi kao f(&objekat) <- &objekat je THIS (skriveni metod)

// Primeri koriscenja:
//  - tekuci objekat treba vratiti kao rezultat metoda
//  - adresa tekuceg objekta je potrebna kao stvarni argument poziva neke funkcije
//  - tekuci objekat treba ukljuciti u listu

//      INSPEKTORI I MUTATORI

// Metod inspector, selector ne menja stanje objekta (const <- mada se moze neposredno promeniti (konverzijom npr.))
// Metod mutator, modifier menja stanje objekta
// Za const objekte moze se zvati samo inspektorski metod
// Const je jedan od 4 modfikatora metod (volatile, & i &&)

// Deklarisanje metoda kao inspektora je samo notaciona pogodnost i "stvar lepog ponasanja"
//      - to je obecanje projektanta klase da funkcija ne menja stanje objekta
//      - prevodilac nema nacina da osigura da inspektor ne menja neke atribute (eksplicitna konverzija)

// U inspektoru tip pokazivaca this je const X*const
// Pokazivac this pokazuje na nepromenljivi objekat

// Za nepromenljive objekte klase nije dozvoljeno pozivati metod koji nije deklarisao da je inspektor

class X {
public:
    int citaj() const { //inline metodi
        return i;
    }
    int pisi(int j = 0) {
        int t = i; i = j; return t;
    }
private:
    int i;
};

// Suprotnost const je volatile metod (stanje objekta je nepostojano) - moze se promeniti stanje objekta
// Pri izvrsenju nepostojanog metoda f objekat (*this) moze promeniti stanje nezavisno od toka funkcije f
// Modifikator volatila - napomena prevodiocu da ne vrsi neke optimizacije
class X1 {
public:
    X1() {kraj = false;}
    int f() volatile {      // da nije volatile, moguca optimizacija:
        while (!kraj) {/*...*/}     // if (!kraj) while() {/*...*/} - menja se semantika programa
    }                       // u telu (...) se ne menja kraj
    void zavrseno() {kraj = true;}  // deklaracijom volatile ovim se ne menja gornja metoda
private:
    bool kraj;
};
// Metod volatile moze da se poziva za nepostojane i promenljive objekte
// Metod const volatile moze se pozvati za sve vrste objekata: - promenljive, nepromenljive i nepostojane objekte
// Const volatile (znaci da neko drugi spolja moze da menja stanje objekta)


int main() {
    Complex c, c1, c2;
    c = c1.zbir(c2);

    X x; const X cx{};
    x.citaj();  // u redu: inspektor promenljivog objekta
    x.pisi();   // u redu: mutator promenljivog objekta
    cx.citaj(); // u redu: inspektor nepromenljivog objekta
//    cx.pisi(); // ! GRESKA: mutator nepromenljivog objekta
    return 0;
}