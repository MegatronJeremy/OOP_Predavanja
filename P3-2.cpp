#include <iostream>

using namespace std;

// C++ izvedeni tip reference na objekat

void f(int i, int &j) {
    i++;
    j++;
}

// Referenca se deklarise upotrebom znaka & ispred imena, alternativno ime za neki objekat (alias, sinonim)
// U definiciji mora da se inicijalizuje objektom na koga ce upucivati
// Od inicijalizacije referenca postaje sinonim za objekat na koga upucuje

// Referenca je slicna konstantnom pokazivacu na objekat datog tipa
// Pri inicijalizaciji dobija vrednost adrese objekta kojim se inicijalizuje
// Nema nacina da se posle inicijalizacije vrednost reference promeni

void ref() {
    int &j = *new int(2);       // j upucuje na dinamicki objekat 2
    int *p = &j;                // p je pokazivac na isti objekat
    (*p)++;                     // objekat postaje 3
    j++;                        // objekat postaje 4
    delete &j;                  // isto kao i delete p
}

// Ako je referenca tipa reference na nepromenljiv podatak, objekat na koji ona upucuje se ne sme promniti preko te reference
// Ne postoje nizovi referenci, pokazivaci na reference, ni reference na reference
// Referenca na pokazivac je dozvoljena:
int i = 5, *p = &i, *&rp = p;

// Reference (na lvrednost) moze i da se vrati kao rezultat funkcije
// U tom slucaju funkcija treba da vrati referencu na objekat koji traje (zivi) i posle izlaska iz funkcije

void lv_ref() {
    int i = 1;      // celobrojni objekat i
    int &j = i;     // j upucuje na i
    i = 3;          // menja se i
    j = 5;          // opet se menja i
    int *p = &j;    // isto sto i &i
    j+=1;           // isto sto i i+=1
    int k = j;      // posredan pristup do i preko reference
    int m = *p;     // posredan pristup do i preko pokazivaca
}

// Sistmatski obilazak elemenata niza
// for (tip prom : niz) naredba <-- prom u svakom ciklusu petlje sadrzi kopiju tekuceg elementa niza
void for_each() {
    int niz[5] = {1, 2, 3, 4, 5};
    int s = 0; for (int k : niz) s+=k; cout << s << endl;   // 15
    for (int &k : niz) k*=2;
    for (int k : niz) cout << k << ' '; cout << endl;       // 2 4 6 8 10
}

// dvrednost je izraz koji nije lvrednost
void rv_ref() {
    int i = 1;              // i je promenljiv podatak
    const int ci = i;       // ci je nepromenljiv podatak - ne simbolicka konstanta (kao za define)

    // REFERENCE NA DVREDNOSTI - osnovni_tip && (dvrednost - literal, aritmeticki, relacijski, logicki i adresni izraz)
//    int &&rd1 = i;        // ! GRESKA - i je (promenljiva) lvrednost
//    int &&rd2 = ci;       // ! GRESKA - ci je (nepromenljiva) lvrednost
    int &&rd3 = i+1;        // (i+1) je promenljiva dvrednost - nastaje privremeni objekat
    int &&rd4 = 10;         // 10 je nepromenljiva dvrednost (literal) - ali mozemo vrsiti promenu jer nije deklarisana kao const
    rd3++; rd4++;   // rd3 == 3, rd4 == 11

    // Ne mogu da se menjaju podaci na koje upucuje dvrednost ako je taj podatak nepromenljiv
//    const int &&crd1 = i;     // ! GRESKA (lvrednost)
//    const int &&crd2 = ci;    // ! GRESKA (lvrednost)
    const int &&crd3 = i + 1;   // promenljiva dvrednost
    const int &&crd4 = 10;      // nepromenljiva dvrednost
//    crd3++; crd4++;     // ! GRESKA (konstantne reference)
}

//  FUNKCIJE KOJE VRACAJU REFERENCE
int &f0(int &i) {int &r = *new int(i); return r;}   // OK - ELEMENT NA HEAPU (NE UNISTAVA SE)
int &f1(int &i) {return *new int(i); }         // OK
int &f2(int &i) {return i; }    // OK - ZIV ELEMENT

int &f3(int &i) {int r = i; return r;} // ! GRESKA (r je na steku - lokalna promenljiva)
int &f4(int i) {return i;} // ! GRESKA (preneseno po vrednosti - kopija stvarnog argumenta)
int &f5(int &i) {int r = *new int(i); return r;} // ! GRESKA (mrtva promenljiva)
int &f6(int &i) {int j = i, &r = j; return r;} // ! GRESKA (referenca na dealociran stek)
// REZULTAT POZIVA FUNKCIJE JE LVREDNOST SAMO AKO FUNKCIJA VRACA REFERENCU

inline int inc(int i) {return i+1;} // INLINE FUNKCIJE se neposredno ugradjuju u kod ??? ali to komplajler ionako vec radi bez navodjenja????
// znaci BESKORISNO

class C {
    int i;
public:
    int val() {     //podrazumeva se inline metod (otkriva se "poslovna tajna" - vidi se u kodu)
        return i;
    }
};

class D {
    int i;
public:
    int val();      // nije ovde definisana metoda klase
};

inline int D::val() {       // isto dodje ako napisemo definiciju i van klase na ovaj nacin
    return i;
}

// Prevodilac ne mora da postuje zahtev za neposrednu ugradjivanje
// Ako se ugradjena funkcija koristi u vise datoteka, u svakoj datoteci mora da se nadje njena
// potpuna definicija (datoteka zaglavlja najbolje)

// PROBLEM SA MAKROIMA
#define max(i, j) ((i) > (j)) ? (i) : (j)
void macro() {
    int k = 1, l = 2;
    max(k++, l++); // Dva puta se inkrementiraju! Problem!
    // ((k++) > (l++)) ? (k++) : (l++)
    // Umesto ovoga koristimo inline max funkciju!
}

inline int maxI(int i, int j) {
    return i > j ? i : j;
}

class Kompleksni {
    float real; float imag;
public:
    Kompleksni(float, float);
};

// PODRAZUMEVANE VREDNOSTI FUNKCIJE
Kompleksni::Kompleksni(float r, float i = 0) {
    // podrazumevani argument mogu biti samo poslednji (r = 0, i) - greska
    real = r; imag = i;
}
// Podrazumevane vrednosti su proizvoljni izrazi
// - izracunavaju se svaki put pri pozivu funkcije

void param() {
//    Kompleksni c1, c2(0), c3(0, 0); // sva tri objekta (0, 0) (kada je Kompleksni(float r = 0, float i = 0))
}

// Za paremetre tipa ref. na dvrednost ne postoji bocni efekat (za njih const nema smisla)
// Takav parametar je privremeni podatak koji nije vidljiv van funkcije
void povecaj(int &&a) {a++;}

int main() {
    int si = 0, sj = 0;
    f(si, sj);
    cout << "si=" << si << ", sj=" << sj << endl;   //Izlaz: si = 0, sj = 1

    // *new int(2) - vraca vrednost dinamickog pokazivaca (zelimo referencu na vrednost - ne na pokazivac)
    int &j = *new int(2); // j upucuje na dinamicki objekat 2 (prostor na heapu) - a[n] vs int *a = new int[n] (stack vs heap)
//                                         - stack se automatski brise pri izlasku iz opsega domena f-je
    int *p = &j;          // p je pokazivac na isti objekat
    (*p)++;               // objekat postaje 3
    j++;                  // objekat postaje 4
    delete &j;            // isto kao i delete p
    // ne postoji nizovi referenci, reference na reference, pokazivaci na reference
    int i = 5, *pi = &i, *&rp = p; //poslednje referenca na pokazivac (dozvoljeno)

    for_each();

    Kompleksni c1{0,0}, c2(0), c3(0,0); // sva tri objekta (0,0)

    int x = 1;
    povecaj(x+1);   // x+1 je dvrednost; pri izlasku: a==3
//    povecaj(x);     // ! GRESKA (lvrednost)
}