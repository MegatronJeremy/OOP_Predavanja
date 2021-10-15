//      PROSLEDJIVANJE OBJEKTA IZUZETKA

// Prevodilac moze da bira da li da koristi vec formirani objekat ili da formira kopiju
// (privremeni objekat nastao kao rezultat izraza u throw ili lokalna automatska prom. iz try bloka)

// U klasi izuzetka morao bi da postoji kopirajuci i/ili premestajuci konstruktor i destruktor takvog objekta.

// Taj objekat ce biti ziv sve do kraja njegove obrade.
// Ukolike se ne nadje odgovarajuca catch grana iz try bloka on se prosledjuje na prethodni nivo try bloka.
// Moze biti i staticki (spoljasnji i unutrasnji try blok) i dinamicki obuhvatajuci try blok (u nekoj funkciji u kojoj je try blok)
// Dinamicko ugnjezdeni - jedna funkcija poziva drugu.

// Objekat izuzetka ce biti ziv do kraja obrade takvog izuzetka.
// Moze putovati unatrag sve do main-a (nekog try - catch bloka u main-u)

//      OBRADA IZUZETKA U UGNJEZDENIM try

// Ukoliko se ne pronadje rukovalac, catch grana, automatski se izuzetak prosledjuje na prethodni nivo try bloka
// (na mesto poziva funkcije ili napustanja unutrasnjeg try bloka).

// Naredbe iza poslednje catch grane se ne izvrsavaju (ukoliko nije nadjena odgovarajuca catch grana)

// Ukoliko u catch grani bacimo izuzetak (mapiramo ga u drugi izuzetak ILI samo throw; - baca se izuzetak istog tipa)
// automatski se prosledjuje baceni izuzetak unatrag (objekat i dalje ziv - bice i ziv u catch grani spoljasnjeg try bloka
// - tamo se pojavljuje kao argument i obradjuje se)

//      UNISTAVANJE LOKALNIH OBJEKATA

// Potrebno dobro voditi racuna o ovome.

// Obrada se nastavlja ili u catch grani iza try bloka ili se ide na prethodni nivo try bloka.
// Tekuci try blok definitivno napusten - lokalni automatski objekti definisani u unutrasnjem try bloku su unisteni, dealocirani.

// POSLEDICA: ako smo prosledili pokazivac/ referencu na lokalni automatski objekat try bloka - NECE BITI ZIV KADA SE UDJE U CATCH
// GRANU - ne moze se poslati kao izuzetak pokazivac ili referenca (na lokalni automatski objekat)
// MORA pokazivati na objekat koji je ziv pri izlasku iz try bloka - neki objekat alociran na heap-u.

// Izuzetak moze biti bacen i iz konstruktora - kada se tako nesto desi prethodno stvoreni klasni atributi i nasledjeni podobjekti se
// UNISTAVAJU (zovu se njihovi destruktori) - voditi racuna.

//      FUNKCIJSKA NAREDBA TRY

// C++11 - moguce povezati funkciju sa try blokom (blok f-ja istovremeno i try blok)

// Sintaksa:
// tip fun(parametri) try { /* telo funkcije */ }
// catch (parametar1) { /* telo rukovacu 1 */ }
// catch (parametar2) { /* telo rukovaoca 2 */ }

// U catch blokovima MOGU se koristiti parametri funkcije, ali ne lokalne automatske prom.
// catch grane (njima se ne moze pristupati).
// Ukoliko nije void potreban return izraz
// Ako dodje do izuzetka CATCH GRANA MORA IMATI RETURN IZRAZ (povratna vrednost date funkcije)

// Funkcijske try naredbe sluze da bi se pored regularne obrade odradila i obrada izuzetka.
// Moguce da se u catch grani ne odradi potpuno izuzetak, tada potrebno iz catch grane baciti izuzetak.

// Funkcija koja je metod neke klase, moze se pojaviti modifikator (const npr.)
// PRE KLJUCNE RECI TRY, throw klauzula takodje pre kljucne reci try
// try NEPOSREDNO ISPRED tela funkcija

int f(int x) try {    // regularno bacanje izuzetaka tipa double
    int y = 0;
    if (0) throw 1; // baca se i obradjuje
    if (2) throw 2.0; // baca se i propagira dalje (ako stoji throw(double) moze da baca)

    return x + y;
} catch (int g) {
    int a = x;      // u redu (x parametar f-je)
//    int b = y;      // y lokalna automatska prom try bloka - nije u dosegu u catch grani
    return -1;      // potreban return u izuzetnoj situaciji
}

//      FUNKCIJSKI TRY U KONSTRUKTORU

// I konstruktor je funkcija u kojoj moze biti bacen izuzetak.
// Obradjuju se u try bloku u kojoj se pravi konstrukcija objekta.
// Ukoliko iz konstruktora izleti izuzetak, pokusaj prvi iza try bloka.

// try ispred tela konstruktora, catch grane iza zatvorene viticaste zagrade.
// Omogucava hvatanja izuzetaka iz inicijalizatora primitivnog tipa (iz neke funkcije koja baca izuzetak)
// Moze da se hvata iza catch grane.

// Ako se desi izuzetak pri konstrukciji atributa klasnog tipa, isto se moze hvatati u catch grani konstruktorskog try-a
// Konstruktor osnovne klase moze baciti izuzetak, takodje moze da se baca i obradi u catch grani.

// Ne pise se uvek neposredno pre otvorene viticaste zagrade UKOLIKO POSTOJI LISTA INICIJALIZATORA (PISE SE IZA TRY-A - ISPRED TELA)

// Ukoliko pokusamo da pristupamo u catch grani konstruktorskog try bloka atributima ili nasledjenom podobjektu - posledice
// su nepredvidive.
// Isto kao funkcijski try i catch blok - pristup nekoj lokalnog promenljivi funkcijske try naredbe.
// U trenutku kada se desi izuzetak moguce da nisu svi atributi konstruisani, ali se za njih pozvao destruktor pri bacanju izuzetka
// (npr. f-ja inicijalizatora atributa - vec smo konstruistali neke atribute klasnog tipa - obrnutim redosledom konstrukcije se pozivaju
// destruktori)

// U catch grani vec sve unisteno (od atributa i nasledjenih podobjekata)

// Kod konstruktorskog try bloka, bez obzira sto smo delimicno obradili izuzetak u catch grani, prekinuto je stvaranje objekta
// automatski ce biti izuzetak bacen dalje unatrag, kao da je rukovalac zavrsen naredbom throw;

// Ukoliko se desi neka fatalna greska moze pozvati exit(int) - vraca kontrolu operativnom sistemu

// U funkcijskom try bloku u konstruktoru ne mozemo imati istovremeno noexcept - TAKAV KONSTRUKTOR UVEK MOZE BACITI IZUZETAK
// Moze se delimicno obraditi u catch grani - ali bez obzira na to - BACA IZUZETAK UNATRAG (nije uspesno stvoren objekat - razlog)

class A {
public:
    A(int x) { if (x) throw 'x';}
    A(char x) { if (x) throw 2;}
};
class B {
    A a1 = A(3);        // Poziva se A(int x)
    A a2;
    int x;
public:
    B() try : a2('a') { // izuzetak tipa int
        if (x) throw 4.0;  // izuzetak tipa double
    } catch (double g) {   // rukovalac za tip double
        A a3(a1);          // ! GRESKA - a1 unisten
                            // a1 postao nedefinisan (pozvao se destruktor za njega)
    } catch (char g) {     // rukovalac za tip char

    }                      // nije obradjen tip int (baca se onome ko poziva konstruktor)
};

//      NEPRIHVACENI IZUZETKI

// Neki izuzetak moze biti neuhvacen catch granom u main-u, do kojeg je prosledjen unazad

// Takav izuzetak se smatra neuhvacenim/ neprihvacenim
// Poziva se sistemska funkcija void terminate();
// Iz nje se poziva funckija void abort() koja prekida izvrsenje programa

// Programer moze da upravlja sta terminate poziva (podrazumevano abort)

// Pomocu funkcije set_terminate() moze da se promeni f-ja
// Prosledjuje joj se pokazivac na funkciju na koju zelimo da poziva
// Ne treba da ima parametra, treba da ima tip rezultata void (kao abort)

// set_terminate() vraca pokazivac na prethodno pozivanu funkciju (inicijalno abort)
// Ako smo vec promenili i dali neku nasu funkciju - ponovnim pozivom vraca pokazivac na nasu funkciju
// (za kasnije restauriranje funkcije)

//      ZAMENA ZA ABORT()

// typedef void (*PF) (); - pokazivac na f-ju bez parametara i vraca void (deklaracija abort-a)
// PF set_terminate(PF pf)

// Iz (*pf) treba pozivati ili exit(int) ili abort() - za povratak u os

// Nije dozvoljeno da se u nasoj funkciji poziva return - ne zna gde da se vrati (nema povratka u main)
// Koristenje za ispisivanje neke poruke operativnom sistemu

//      NEOCEKIVANI IZUZECI

// Ako bi se desio neki izuzetak koji nije na spisku naznacenih, vrsi se funkcija void unexpected()
// Iz nje se podrazumevano poziva terminate()

// Pomocu set_unexpected() - postavljamo neku nasu funkciju (na isti nacin kao za terminate)
// set_unexpected() nema nikakav rezultat - void, nema parametre - treba isto tako biti nasa funkcija

//      ZAMENA ZA TERMINATE()

// typedef void (*PF) ();
// PF set_unexpected(PF pf);

// Iz korisnicke f-je treba:
// Pozvati exit(int), abort() ili terminate() (moze i on)
// Baciti izuzetak SA THROW LISTE DOZVOLJENIH (pozvan je izuzetak koji ne treba bacati)
// ILI baciti bad_exception (sistemski izuzetak)

// Pokusaj povratka sa return iz (*PF) dovodi do nasilnog prekida programa abort() funkcijom

//      STANDARDNI IZUZECI

// U zaglavlju <exception> postoji klasa exception
// Korena klasa za klase izuzetaka (standardni izuzeci iz nje izvedeni)
// Preporuka da se korisnicki izuzeci takodje iz nje izvode

// Koren stabla hijerarhije izuzetaka - klasa izuzetak (exception)
// Mozemo u catch grani pojedinacno da obradjujemo tipove u listu,
// grupno za klase u cvorovima
// ili sve zajedno u catch grani ciji je tip exception (obradjuje bilo koji tip u hijerarhiji)

// Catch grane za listove - za prvi nivo iznad listova - drugi nivo ... - koren pa
// Univerzalni hendler (drugo od toga - njega svakako na kraju)

class exception {
public:
    exception() noexcept;
    exception(const exception &) noexcept;
    exception &operator=(const exception &) noexcept;
    virtual ~exception() noexcept;
    virtual const char *what() const noexcept;
};

// what() vraca pokazivac na tekstualni opis izuzetka (std. ne propisuje tekst poruka za standardne izuzetke - propisuje prevodioc)
// what() implementiramo kao opis izuzetka

// Ne smeju bacati izuzetke nijedne funkcije
// Ne sme ni nasa funkcija bacati izuzetak redefinisana (sme da suzi listu izuzetaka - ne sme da prosiri - ne sme da baci izuzetak nadjacanje)

