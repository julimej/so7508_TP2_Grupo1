#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include <iostream>
#include <sstream>
#include "Mensaje.h"

int main (int argc, char* argv[]){
    if (argc != 2) {
        cout<<"Ingrese una capacidad valida para el ascensor";
        return 0;
    }

    stringstream strValue;
    strValue << argv[1];

    unsigned int intValue;
    strValue >> intValue;

    sv_sem capacidad("Capacidad",intValue);
    sv_sem mutex("Mutex",1);
    sv_sem entra("Entra",1);
    cout<<"Semaforos inicializados"<<endl;
    Mensaje* msj;
    sv_shm area("Area");
    msj= reinterpret_cast<Mensaje *> (area.map(sizeof (Mensaje)));
    return 0;
} 

