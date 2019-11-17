#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include <iostream>
#include <sstream>
#include "Mensaje.h"

int main (int argc, char* argv[]){
    sv_sem sem_llamado("semLlamado",0);
    sv_sem sem_ocupado("semOcupado",1);
    sv_sem sem_leer("semLectura",0);
    sv_sem sem_escribir("semEscritura",1);
    cout<<"Semaforos inicializados"<<endl;
    Mensaje* msj;
    sv_shm area("Area");
    cout<<"Area inicializada"<<endl;
    msj= reinterpret_cast<Mensaje *> (area.map(sizeof (Mensaje)));
    return 0;
} 

