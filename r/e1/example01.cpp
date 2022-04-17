/*
 * example01.cpp: Ejemplo de uso de librerías de
 * ROOT en codigo de C++
 * 
 * Ejemplo para el curso introductorio de ROOT.
 * Laboratorio Avanzado
 * 
 * Héctor Pérez, febrero 2020.
 * 
 */

#include <cstdlib>

/* Includes de las librerías de ROOT.
 * Generalmente es mejor incluirlas despues
 * de las librería propias de C++ */

#include "TROOT.h"
#include "TH1D.h"
#include "TApplication.h"

/* Ahora si se debe incluir la función main en el
 * código, ya ques se generará un ejecutable independient
 * del CLING de ROOT. */
int main(int argc, char* argv[])
{
    
    /* Esta clase abre una aplicación de root 
     * que se encarga de manejar la interfaze
     * gráfica. */
    TApplication theApp("RootExample01", &argc, argv);
    if (gROOT->IsBatch())
    {
        fprintf(stderr, "%s: cannot run in batch mode\n", argv[0]);
        return 0;
    }

    /* Se puede instanciar los objetos de ROOT y manipularlos como se
     * hace en el CLING o con los scripts. */       
    TH1D *RanHisto = new TH1D("rh","Histograma de numeros aleatorios",200,-3,3);
    RanHisto->FillRandom("gaus",10000);
    RanHisto->Draw();

    /* Este método corre la aplicación de ROOT que muestra la
     * gráfica. Para salir, hay que ir a "File->Quit ROOT" en la
     * ventana que aparece. */
    theApp.Run();
}