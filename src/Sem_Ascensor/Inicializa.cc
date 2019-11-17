#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include <iostream>
#include <sstream>

int main (int argc, char* argv[]){
    if (argc != 2) {
        cout<<"Ingrese una capacidad valida para el ascensor";
        return 0;
    }

    stringstream strValue;
    strValue << argv[1];

    unsigned int intValue;
    strValue >> intValue;

    sv_sem mutex("Ascensor",intValue);
    cout<< "Semaforo inicializado con capacidad: "<< intValue <<endl;
} 

