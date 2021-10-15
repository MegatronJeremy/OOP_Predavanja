#include <iostream>
using namespace std;

int a = 1; //staticka globalna promenljiva
void h() {
    int b = 1;  // inicijalizuje se samo jednom (automatski objekat na steku) -> svaki put kad se ulazi u f-ju
    static int c = 1; // inicijalizuje se samo jednom u memoriji za stat. alokaciju
    cout << "a=" << a++ << " b=" << b++ << " c=" << c++ << endl;
}

/**/
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
/**/

/**/
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

/**/
int main() {
    while(a<3) h(); // za prvi primer

    int i = 0; // i je l vrednost (u kasnijim izrazima)
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