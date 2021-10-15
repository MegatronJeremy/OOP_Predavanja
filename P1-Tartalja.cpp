class Publikacija {
public:
    Publikacija();                  //Podrazumevani konstruktor (suspenduje se kad napisemo drugi)
    Publikacija(int, char *n);        //Konstruktor sa dva argumenta
    virtual void unos();            //virtual metoda nadjacava metodu u osnovnoj klasi (ako su iste)
    virtual void ispis();
private:
    int id;
    char naslov[150];
};

#include <iostream>
using namespace std;
void Publikacija::unos() {
    cout << "Id? ";
    cin >> id;
    cout << "Naslov? " << endl;
    cin >> naslov;
}

void Publikacija::ispis() {
    cout << "Id: " << id << ", Naslov: "<< naslov << endl;
}

class Casopis: public Publikacija {
public:
    Casopis();
    Casopis(int, int, int, char *);
    void unos();  //treba implementovati
    void ispis(); //redefinicija funkcije Publikacija::ispis()
private:
    int broj, god;
};

// ...implementacija

void ispisi_sve(Publikacija *p[], int n) { //neke su knjige, neke su casopisi
    for (int i = 0; i < n; i++) {
        p[i]->ispis(); //pokazivac na objekat (metod objekta -> ispis)
        cout << endl;
    }
}

#include <cstring>
Publikacija::Publikacija() {}
Publikacija::Publikacija(int i, char *n) {
    id = i; strcpy(naslov, n);
}

class LosBroj {
    int broj;       //private po defaultu
public:
    LosBroj(int i) { broj = i; }
    void poruka() { cout << "Nedozvoljen broj " << broj << " !" << endl; }
};

void Casopis::unos() {
    Publikacija::unos();
    try {
        cout << "Broj? "; cin >> broj;
        if (broj < 1 || broj > 12) throw LosBroj(broj);
        cout << "Godiste? "; cin >> god;
    } catch (LosBroj izuzetak) {
        izuzetak.poruka();
        broj = 0; god = 0;
    }
}

template <class T> class SablonPublikacija {
    T id; //identifikator proizvoljnog tipa (ne samo int - vec neki string)
    //...
};

int main() {
    SablonPublikacija<int> knjiga; //generisana klasa
    Publikacija knjiga1(1, "Alhemicar"), knjiga2;
    knjiga1.ispis();
    knjiga2.unos();
    knjiga2.ispis();
    return 0;
}