#include <bits/stdc++.h>
#include "Klase.h"

using namespace std;


int main() {
    Complex c, c1, c2;
    c = c1.zbir(c2);

    X x; const X cx{};
    x.citaj();  // u redu: inspektor promenljivog objekta
    x.pisi();   // u redu: mutator promenljivog objekta
    cx.citaj(); // u redu: mutator promenljivog objekta
//    cx.pisi(); // ! GRESKA: mutator nepromenljivog objekta
    return 0;
}