// Preporucen redosled: public -> protected -> private

class Complex {
public:
    Complex zbir(Complex); Complex razlika(Complex);  //metode klase
    float re(); float im();
private:
    float real, imag;      //atributi klase
};

class Kompleksni1; // Samo definicija (dovoljno za pokazivac i referencu na klasu) - objekat nije moguc
// automatski podaci - sama definicija ; static definicija - memorija za staticke podatke zasebno

//KLJUCNA REC THIS -> POKAZIVAC NA TEKUCI OBJEKAT (ZA KOJI JE POZVAN DATI METOD)
//klasa X, this je tipa X *const this
Complex Complex::zbir(Complex c) {
    Complex t;
    t.real=this->real+c.real; t.imag=this->imag+c.imag;         //isto kao dole
//    Complex t = *this; // u t se kopira tekuci objekat
//    t.real+=c.real; t.imag+=c.imag;
    return t;       // t je na steku, vraca se samo rezultat po vrednosti (ok)
}
// objekat.f() se prevodi kao f(&objekat) <- &objekat je THIS (skriveni metod)

// Metod inspector, selector ne menja stanje objekta (const <- mada se moze neposredno promeniti (konverzijom npr.))
// Metod mutator, modifier menja stanje objekta
// Za const objekte moze se zvati samo inspektorski metod

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
// Const volatile (znaci da neko drugi moze da menja stanje objekta)