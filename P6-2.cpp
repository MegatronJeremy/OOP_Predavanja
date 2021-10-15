// max(a, b) - globalna prijateljska funkcija; a.max(b) - metod klase <--- citljivije preko globalne f-je
class Y;
class X {
    friend Y;   // ako je Y definisana ili deklarisana
    friend class Z; // ako Z jos nije ni def. ni dek.
};
class Proizvod {
private:
    friend class Fabrika;
    Proizvod(); //konstruktor je dostupan samo klasi fabrika;
};

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

// U ugnjezdenoj klasi mogu direktno da se koriste indentifikatori: enumi, tipovi i staticki clanovi iz okruzujuce klase
// Ugnjezdena klasa je implicitno prijatelj okruzujucoj klasi (obrnutoo ne vazi)
int x, y;
class Spoljna {
public:
    int x; static int z;
    class Unutrasnja {
        void f(int i, Spoljna *ps) {
//            x = i;      // ! GRESKA: nepoznat objekat klase Spoljna (sakrilo globalno ime x)
//            Spoljna::x = i;     // ! GRESKA: isti uzrok
            z = i;  // pristup statickom clanu spoljna
            ::x = i;        // pristup globalnom x; (unarni operator za pristup glob. prom.)
            y = i;      // pristup globalnom y;
            ps->x = i;      // pristup Spoljna::x objekta *ps;
        }
    };
};
//Unutrasnja u;       // ! GRESKA: nije u dosegu
Spoljna::Unutrasnja u;      // u redu;

// Lokalne klase se definisu unutar funkcija (doseg u tom bloku)
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

//POKAZIVACI NA CLANOVE KLASE
class Alfa { public: int a, b; };
int main() {
    int Alfa::*pc;      // pc je pokazivac na int clanove klase Alfa
    Alfa alfa, *beta;
    beta = &alfa;       // beta je pokazivac na objekat klase

    pc = &Alfa::a;      // pc pokazuje na clanove a objekata klase Alfa (uzimenja relativne adrese u odnosu na pocetak objekta klase Alfa)
    alfa.*pc = 1;       // alfa.a=1
    beta->*pc = 1;      // beta->a=1

    pc = &Alfa::b;      // pc pokazuje na clanove b objekata klase Alfa
    alfa.*pc = 2;       // alfa.b = 2;
    beta->*pc = 2;      // beta->b = 2;
}