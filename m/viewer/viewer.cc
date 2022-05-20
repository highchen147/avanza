/*
 * viewer.cc
 * Programa para visualizar los datos provenientes de la 
 * tarjet QuarkNet 6000 almacenados en archvios de ROOT.
 * 
 * Héctor Pérez - hector@ecfm.usac.edu.gt
 * 
 * Abril, 2022
 * 
 */

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>


#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

#include "qN6kRootDataViewerCLA.hh"

/*
 * El programa toma como argumentos el nombre del archivo de ROOT
 * donde se encuentran los datos y muestra cuantos eventos contiene
 * el archivo. Si se especifica la opción -e N se muestra la 
 * información del evento N del archivo.
 */
int main(int argc, char **argv){

  /* Se toman los argumentos de linea de comando y se verifican.
   * Si algo no es correcto se muestra el mensaje de usage y se
   * aborta el programa */
	qN6kRootDataViewerCLA *CommandLine = new qN6kRootDataViewerCLA(argc, argv);

	std::string InputFileName;

  /* Se obtiene el nombre del archivo proporcionado en la linea
   * de comandos */
	CommandLine->GetGlobalArgumentValue("InFile", InputFileName);

	/* Se abre el archivo de datos */
	TFile *InputFile = new TFile(InputFileName.c_str());

  if( InputFile->IsZombie() )
  {
    std::cout << "Invalid input file name\n";
    return 1;
  }

  TTree *dataTree = new TTree("dataTree","dataTree");

	/* Se asocia un arbol para leer los datos del archivo */

  InputFile->GetObject("dataTree;1", dataTree);

  if( !dataTree )
  {
    std::cout << "No QuarkNet 6000 data found on file " << InputFileName << std::endl;
    return 1;
  }


  std::cout << "data tree found..\n";

  /* Se marcan como activas las ramas del arbol de datos */

  dataTree->SetBranchStatus("*",0);
  dataTree->SetBranchStatus("TSDate",1);
  dataTree->SetBranchStatus("TSTime",1);
  dataTree->SetBranchStatus("TSNs",1);
  dataTree->SetBranchStatus("RE0",1);
  dataTree->SetBranchStatus("FE0",1);
  dataTree->SetBranchStatus("RE1",1);
  dataTree->SetBranchStatus("FE1",1);
  dataTree->SetBranchStatus("RE2",1);
  dataTree->SetBranchStatus("FE2",1);
  dataTree->SetBranchStatus("RE3",1);
  dataTree->SetBranchStatus("FE3",1);


  std::cout << "brances activated..\n";
  
  /* Variables para cargar los datos del archivo
   *
   * TSDateData: Cadena de caracteres que aloja la fecha de captura de datos */
	char TSDateData[7];
  /* TSTimeData: Cadena de caracteres que aloja la hora de captura de datos
   * con presición de segundos */
	char TSTimeData[7];
  /* TSNsData: Entero que indica los nanosegundos transcurridos desde 
   * TSTimeData hasta el inicio del evento capturado */
	uint32_t TSNsData;

  /* RE<ch>: Vectores que contienen los tiempos en los cuales el voltaje 
   * de la señal de los pulsos excedieron el umbral predefinido para el canal ch.
   * Los tiempos son los nanosegundos que transcurrieron desde TSNsData.
   * 
   * FE<ch>: Vectores que contienen los tiempos en los cuales el voltaje
   * de la señal de los pulsos dejaron de exceder el umbral predefinido 
   * para el canal ch. Tambien están medidos en nanosegundos desde
   * TSNsData. */
  std::vector<float> *RE0 = 0;
  std::vector<float> *FE0 = 0;
  std::vector<float> *RE1 = 0;
  std::vector<float> *FE1 = 0;
  std::vector<float> *RE2 = 0;
  std::vector<float> *FE2 = 0;
  std::vector<float> *RE3 = 0;
  std::vector<float> *FE3 = 0;

  /* Se asocian las ramas del arbol con las variables respectivas */
  dataTree->SetBranchAddress("TSDate",TSDateData);
  dataTree->SetBranchAddress("TSTime",TSTimeData);
  dataTree->SetBranchAddress("TSNs",&TSNsData);
  dataTree->SetBranchAddress("RE0",&RE0);
  dataTree->SetBranchAddress("FE0",&FE0);  
  dataTree->SetBranchAddress("RE1",&RE1);
  dataTree->SetBranchAddress("FE1",&FE1);  
  dataTree->SetBranchAddress("RE2",&RE2);
  dataTree->SetBranchAddress("FE2",&FE2);  
  dataTree->SetBranchAddress("RE3",&RE3);
  dataTree->SetBranchAddress("FE3",&FE3);  
  
  
  std::cout << "brances asociated..\n";
      
  /* Se obtiene el número de eventos en el archivo .root */
  int n_events = (int) dataTree->GetEntries();

  std::cout << n_events << " events found\n";

  /* Si se proporciona la opcion -e N se muestran los datos
   * del evento N */
  int Event=0;
  if( CommandLine->GetOptionValue("Event",Event) == 0 )
  {
    if( (Event < 0) || (Event >= n_events ) )
    {
      std::cout << "Invalid event number\n";
      return 1;
    }

    /* Se cargan los datos del especificado evento*/
    dataTree->GetEntry(Event);

    std::cout << "Event " << Event << std::endl;
    std::cout << "\tTSDate: " << TSDateData << std::endl;
    std::cout << "\tTSTime: " << TSTimeData << std::endl;
    std::cout << "\tTSNs: " << TSNsData << std::endl;
    
    std::cout << "\tRE0 size: " << RE0->size() << std::endl;
    for(int i = 0; i< RE0->size(); i++ )
      std::cout << "\t\t" << RE0->at(i) << std::endl;

    std::cout << "\tFE0 size: " << FE0->size() << std::endl;
    for(int i = 0; i< FE0->size(); i++ )
      std::cout << "\t\t" << FE0->at(i) << std::endl;
    
    std::cout << "\tRE1 size: " << RE1->size() << std::endl;
    for(int i = 0; i< RE1->size(); i++ )
      std::cout << "\t\t" << RE1->at(i) << std::endl;
    
    std::cout << "\tFE1 size: " << FE1->size() << std::endl;
    for(int i = 0; i< FE1->size(); i++ )
      std::cout << "\t\t" << FE1->at(i) << std::endl;
    
    std::cout << "\tRE2 size: " << RE2->size() << std::endl;
    for(int i = 0; i< RE2->size(); i++ )
      std::cout << "\t\t" << RE2->at(i) << std::endl;

    std::cout << "\tFE2 size: " << FE2->size() << std::endl;
    for(int i = 0; i< FE2->size(); i++ )
      std::cout << "\t\t" << FE2->at(i) << std::endl;
    
    std::cout << "\tRE3 size: " << RE3->size() << std::endl;
    for(int i = 0; i< RE3->size(); i++ )
      std::cout << "\t\t" << RE3->at(i) << std::endl;
    
    std::cout << "\tFE3 size: " << FE3->size() << std::endl;
    for(int i = 0; i< FE3->size(); i++ )
      std::cout << "\t\t" << FE3->at(i) << std::endl;
      
  }
  
  InputFile->Close();
  return 0;
}
