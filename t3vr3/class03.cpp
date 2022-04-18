/* 
 * class03.cpp: Programa para mostrar el uso de la
 * clase VecInt2R.
 * 
 * Ejemplo para la parte III del curso introductorio
 * de ROOT.
 * 
 * Hector Perez, abril 2020
 * 
 */

#include <cstdlib>
#include <iostream>

#include "VecR3.hpp"

using namespace std;

/* Inicio del programa, se crean instancias de VecR2
 * y se llaman los metodos. */
int main()
{
    VecR3 v1(1,0,0);
    VecR3 v2(0,1,0);

    cout<<  "v1 = " <<  v1 << endl;
    cout<<  "Magnitud de v1: " << v1.Magnitud() << endl;

    cout<<  "v2 = " <<  v2 << endl;

    VecR3 v3;

    v3 = v1 + v2;

    cout << "v3 = v1 + v2 = " << v3 << endl;

    VecR3 v4;

    v4 = v1 + v2/2;

    cout << "v4 = v1 + v2/2 = " << v4 << endl;

    cout << "Producto punto" << endl;
    cout << "v1*v2 = " << v1*v2 << endl;
    cout << "v3*v4 = " << v3*v4 << endl;

    VecR3 v5;

    v5 = v1 % v4;
    cout << "Producto cruz" << endl;
    cout << "v1%v4 = " << v5 << endl;
    VecR3::Mostar_Polar(true);
    cout<< "Mostar en notacion polar activado" << endl;
    cout<<  "v1 = " <<  v1 << endl;
    cout<<  "v2 = " <<  v2 << endl;
    cout << "v3 = " <<  v3 << endl;
    cout << "v4 = " <<  v4 << endl;


    return 0;
}