//      POJAM IZUZETAKA

// Posebni dogadjaji koje treba posebno obradjivati (izvan osnovnog toka programa)
// Kada se u nekoj funkciji javi greska - obradjuje se na nacin koji ne zamagljuje osnovnu obradu

// Bez posebnog mehanizma obrade izuzetaka dva problema:
// Problem "migracije udesno" i "propagacije unazad"

// Signaliziramo preko rezultata funkcije
// Migracija udesno
//  if (f1()) { // status == OK ... idemo dalje
//      if (f2()) {
//          if (f3()) {
//           } else {   // obrada greske f3()
//           }
//      } else {        // obrada greske f2()
//      }
//  } else {            // obrada greske f1()
//  ]

// Propagacija unazad - npr g2 ne zna da obradi gresku iz g3 - propagira se unazad do g1

//      IZUZECI U JEZIKU C++

// Vrsi se implicitna propagacija izuzetaka unazad

// throw - bace se izuzetak
// Moze biti ili objekat klase ili objekat primitivnog tipa (ugradjenog)

// Obrada u catch grani
// Mogu postojati posebne catch grane za posebne izuzetke
// Handleri - rukovaoci
// Dostavlja se objekat izuzetka kao argument

// Posle uspesne obrade izuzetka, nastavlja se obrada POSLE SVIH CATCH BLOKOVA (ne vraca se nazad)

// Ukoliko ne postoji odgovarajuca catch grana - automatski se propagira izuzetak unatrag

// try - kljucna rec
// catch(...) - univerzalni rukovalac - proguta izuzetak bilo kog tipa
// ... - terminalni simbol
// ima smisla staviti kao poslednju catch granu (ako nismo nasli odgovarajuci tip izuzetka)

// Definicija rukovaoca lici na definiciju funkcije (ime f-ja kljucna rec catch - argument bacen izuzetak)
// Kada se izvsi neka catch grana, naredne se preskacu, obrada nakon poslednje catch grane
// Razlika od poziva funkcije
// Ako se predju sve catch grane - propagira se u spoljasnjem try bloku (ili van neke funkcije - u pozivajuci kod)
//  sve do main-a

void f() {
    try {
        // radi();  // moze baciti izuzetak
    } catch (const char *pz) {
        // Obrada izuzetka tipa znakovnog niza
    } catch (const int i) {
        // Obrada izuzetka celobrojnog tipa
    } catch (...) {
        // Obrada izuzetka proizvoljnog tipa
        // koji nije jedan od gornjih
    }
    // Naredba nakon poslednje catch grane
}

// Prijavljivanje izuzetak naredbom throw izraz <-- throw se smatra operatorom (izraz je operand)
//  vrednost izraza se izracunava i prenosi rukovaocu kao argument

// Moze se pojaviti eksplicitnom throw naredbom ili funkcijom koja baca izuzetak

// Moze se baciti iz obicnih globalnih funkcija, operatorskih funkcija, metoda klase, konstruktora, destruktora... nema ogranicenja

// Dinamicki ugnezden try (vreme izvrsenja)
//  Funkcija koja vraca izuzetak

// Staticki ugnezden try
//  Try blok u try bloku direktno

// Mozemo u nekoj catch grani i delimicno da obradimo izuzetak
// Koristimo operator throw; (bez izraza) - prosledjuje delimicno obradjen izuzetak u catch grani,
//  EKSPLICITNO propagira unazad (da ga obradjuje neka druga catch grana)

//      SPECIFIKACIJA IZUZETAKA FUNKCIJE

// Smatra se zastarelom
// Ako ne specificiramo - moze funkcija bacati bilo kakav izuzetak

// Iza liste parametara f() throw(niz_identifikatora)
// Ako se stavi samo throw() klauzula - takva funkcija ne sme bacati izuzetak
// throw(tip1, tip2, tip3) - tipovi koje data funkcija sme da baca

/*
void radi(...) throw(const char*, int) {
    if (...) throw "Izuzetak!";
    if (...) throw 100;
    if (...) throw Tacka(0, 0); // GRESKA : nije naveden tip izuzetka tacka
}
*/

// U nadjacanom metodu osnovne klase kod izvodjenja sme da se SUZI lista ili da se bacaju ISTI izuzeci

// Izbacen je u C++11 - problem kod dugackih lanaca poziva f1() -> f2() -> f3() -> ... f785()
// Ako treba da baci f785() novi tip izuzetka, potrebno modifikovati sve ostale - otezava odrzavanje koda
// Vise se ne preporucuje

//      MODIFIKATOR I OPERATOR NOEXCEPT

// MODIFIKATOR:

// Ukoliko funkcija moze da baci izuzetak noexcept(false)
// Funkcija ne sme da baci izuzetak - noexcept(true)

// Isto mesto throw klauzula - iza liste parametara

// noexcept ima rezultat izraza (evaluira se u vreme prevodjenja)
// Oznacava da li moze ili ne moze da baci izuzetak - konstantan boole-ov izraz

// Moze i samo noexcept == noexcept(true) == throw()

// OPERATOR:

// noexcept(izraz) - rezultat logickog tipa
// izraz moze biti proizvoljnog tipa, cak i void
// Proverava se da li bi se u slucaju izvrsenja takvog izraza mogao baciti izuzetak

// Takav izraz se takodje ne izracunava (isto u toku prevodjenja)
// Moze se naci noexcept operator i kao izraz u noexcept modifikatoru

void l() noexcept {}    // ne baca
int g() noexcept(false) {return 0;} // moze baciti izuzetak
double h() {return 0.0;}    // moze da baca
int i() throw() {return 0;} // ne baca
//void j() throw(int, double) {}  // moze da baca

void k() {
    bool p = noexcept(f());     // true
    bool q = noexcept(g());     // false
    bool r = noexcept(h());     // false
    bool s = noexcept(i());     // true
//    bool t = noexcept(j());     // false

    bool v = noexcept(new int); // false
    // moze da baci bad_alloc izuzetak - nema mesta na heap-u
}

//      PRIHVATANJE IZUZETAKA - PRAVILA

// Catch grana - parametar tipa R
// catch(R)

// Rukovalac tipa R moze da prihvati izuzetak tipa I ako:
//  R i I su isti tip   <-- identicno - moze
//  R je javna osnovna klasa za izvedenu klasu I  <-- objekat izvedene klase moze biti bacen kao izuzetak
//      i prihvacen ako je R javna osnovna klasa
//  R i I su pokazivacki / upucivacki tipovi i I standardno moze da se konvertuje u R

// Rukovaoc izvedenog tipa osnovne klase pre tipa osnovne klase (proguta i izuzetke izvedenih klasa)
// Nikad catch(O) pa... catch (I) - u evaluaciji se nikad ne stize do obradjivanja izuzetaka izvedene klase

// Univerzalni rukovalac guta sve izuzetka - na kraj jedino ima smisla staviti ga


