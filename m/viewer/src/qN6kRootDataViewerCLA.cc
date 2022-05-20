/*
*
*/

#include <cstdlib>
#include "qN6kRootDataViewerCLA.hh"

qN6kRootDataViewerCLA::qN6kRootDataViewerCLA(int ArgCount, char** ArgVector){

	AddProgramDescription("QuarkNet 6000 DAQ ROOT data viewer");

	AddGlobalArgument( "InFile", "File with ROOT data from QuarkNet 6000");
	AddOption("Event",'e',"Event number to show",optArgType::integer);

	if( !Parse( ArgCount, ArgVector ) ){
		PrintUsageMessage( ArgVector[0] );
		std::exit(1);
	}
}
