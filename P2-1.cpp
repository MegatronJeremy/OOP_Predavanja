#include <iostream>
using namespace std;

// DEKLARACIJA je iskaz koji samo uvodi neko ime (identifikator) u program i govori provodiocu kojoj jezickoj kategoriji pripada ime
// IME se moze koristiti samo ako je prethodno barem deklarisanje
// DEFINICIJA je ona deklaracija koja: 1. kreira objekat (dodeljuje mu memorijski prostor), navodi telo funckije ili u potpunosti navodi strukturu korsnickog tipa (ukljucujuci klase u C++)

// U programu moze postojati: samo jedna definicija jednog objekta, funkcije i tipa, i proizvoljno mnogo deklaracija

// Na jeziku C++ definicija objekta je naredba, pa se moze naci bilo gde u programu (objekat moze biti inicijalizovan u definiciji)

// Objekat je nesto u memoriji sto ima stanje, ponasanje i identitet

// Objekat u sirem smislu (podatak): 1. definisano podrucje u memoriji, u toku izvrsavanja programa
// 2. primerak proizvoljnog tipa (ugradjenog ili korisnickog)

// Objekat u uzem smislu: primerak (instanca) klase

// funkcija je u memoriji, ali nije objekat (nema stanje)
// podatak primitivnog tipa (koji je objekat u sirem smislu) nema identitet

// Promenljiva je lokacija u kojoj se cuva podataka koji nije konstantan
// globalna ili lokalna, staticka, automatska, dinamicka, privremena (tranzijentna)

// lvrednost je izraz koji upucuje na objekat (u sirem smislu) ili funkciju
// promenljiva lvrednost je ona lvrednost koja nije ime funkcije, ime niza, ni konstantni objekat

// Operatori ciji operandi moraju biti lvrednosti: unarni &, ++ i --, levi operandi operatora dodele
// Operatori ciji su rezultati lvrednost: unarni *, [], prefiksni ++ i --, kao i operatori dodele

// dvrednost je izraz koji nije lvrednost

int a = 1; //staticka globalna promenljiva
void h() {
    int b = 1;  // inicijalizuje se samo jednom (automatski objekat na steku) -> svaki put kad se ulazi u f-ju
    static int c = 1; // inicijalizuje se samo jednom u memoriji za stat. alokaciju
    cout << "a=" << a++ << " b=" << b++ << " c=" << c++ << endl;
}

// Oblast vazenja (doseg) imena
// Globalna imena: van svih funkcija i klasa - deo teksta od mesta deklaracije do kraja datoteke
// Lokalna imena: imena deklarisana unutar bloka, ukljucujuci i blok tela funkcije - od mesta deklarisanja, do zavrsetka doticnog bloka
// Sakrivanje imena, pristup sakrivenom globalnom imenu: navodjenjem operator :: ispred imena
// Pristup sakrivenom imenu spoljasnjeg bloka nije moguc

int x = 0; //globalno x
void f() {
    int y = x, // lokalno y, globalno x;
        x = y; // lokalno x, sakriva globalno x
    x = 1;    // pristup lokalnom x
    ::x=5;   // pristup globalnom x
    {
        int x;  //lokalno x, sakriva prethodno x
        x = 2;  //pristup drugom lokalnom x
    }
    x = 3;  //pristup prvom lokalnom x
}
int *p = &x;    //uzimanje adrese globalnog x

// U telu for petlje definicje promelnjive je promenljiva for naredbe

// U uslovu if se moze definisati celobrojna ili pokazivacka promenljiva
// doseg do kraja else grane
// if (int k = i+j) {} else {}

// Formalni argumenti (parametri) funkcije kao lokalne promenljive deklarisane u bloku tela funkcije:
// void f(int x) {int x; } // !GRESKA

void k() {
    for (int i = 0; i < 10; i++);
//    if (i==10); // !GRESKA (po standardu) (MS VC++ v.6 ispravno)

    for (int i = 9; i >= 0; i--);
//    Po standardu je ispravno (MS VC++ v.6 greska)
}

// Oblast vazenja strukture/klase imaju svi njeni clanovi

// Imenu koje ima oblast vazenja klase, van te oblasti, moze se pristupiti preko: . , -> , ::

// Oblast vazenja funkcije imaju samo labele (goto naredbe)
// mogu se navesti bilo gde unutar tela funkcije, a u dosegu su u celoj funkciji

class X {
public:         // ili:
    int x;      // void f(); - deklaracije metode f
    void f();   // int x; - deklaracija atributa x
};

void X::f() {//moze samo ime x unutra ...x...
}   // :: prosirenje dosega

void g() {
    X xx, *px;
    px = &xx;
    xx.x = 0;   // moze: xx.X::x; ali nema potrebe (tacka prosiruje doseg imena klase veliko X)
    xx.f();     // moze: xx.X::f(); ali nema potrebe
    px->x=1;
    px->f();
}
/**/

// Zivotni vek objekta: vreme u toku izvrsavanja programa u kojem objekat postoji i za koje mu se moze pristupati
// Po zivotnom veku, objekti se dele na: staticke, automatske, dinamicke, tranzijentne (privremene)
// Vek atributa klase = vek objekta kojem pripadaju
// Vek parametra = vek automatskog objekta

// Automatski objekat je lokalni objekat koji nije deklarisan kao static
// zivotni vek od definicije do napustanja oblasti vazenja, kreira se iznova, prostor se alocira na steku

// Staticki objekat je globalni objekat ili lokarlni deklarisan kao static
// zivotni vek od izvrsavanja definicije do kraja izvrsavanja funkcije main()
//      Globalni staticki objekti - kreiraju se samo jednom, na pocetku izvrsavanja programa
//                                  kreiraju se pre koriscenja bilo koje funkcije ili objekta iz istog fajla
//                                  nije obavezno da se kreiraju pre poziva funkcije main()
//      Lokalni staticki objekti - pocinju da zive pri prvom nailasku toka programa na njihovu definiciju

// Specijalne (nisu rezervisane) reci (specifikatori): final i override

// Stroga tipizacija: svaki objekat ima svoj tacno odredjeni tip, objekti razlicitih tipova se ne mogu proizvoljno zamenjivati
// C++ u manipulisanju primitivnim tipovima labavo tipiziran, a klsanim tipovima strogo tipizirani jezik

/**/
int main() {
    while(a<3) h(); // za prvi primer

    int i = 0; // i je lvrednost (u kasnijim izrazima)
    int *p = &i; //p je lvrednost (u kasnijim izrazima) - upucuje na mem lokaciju sa adresom
    *p = 7; // *p je lvrednost

    int *q[100];
    q[10]=&i; // q[10] je lvrednost
    *q[10]=1; // *q[10] je lvrednost
    //q = &i; // ! GRESKA: ime niza nije promenljiva lvrednost

    int a=1, b=2, c=3;
    (a=b)=c; // (a=b) je lvrednost - U c++ samo
    // (a+b)=c; // ! GRESKA: (a+b) nije lvrednost
    ++ ++i;  // ++(++i)
    //i++ ++; // ! GRESKA: postinkrement ne daje lvrednost

    long x = 5; int y = 0, z = 0;
    (x?y:z)=1; // x?y=1:z=1
    // (x?10:z)=2 // ! GRESKA: 10 nije lvrednost (konstanta je dvrednost, 10=2 bi bilo)
}
/**/