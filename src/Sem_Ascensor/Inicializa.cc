#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include <iostream>
#include <sstream>
#include "Mensaje.h"
#include "Constantes.h"

int main (){
    sv_sem sem_llamado(SEM_LLAMADO,0);
    sv_sem sem_ocupado(SEM_OCUPADO,1);
    sv_sem sem_leer_ascensor(SEM_LECTURA_ASCENSOR,0);
    sv_sem sem_leer_pasajero(SEM_LECTURA_PASAJERO,0);
    cout<<"Semaforos inicializados"<<endl;
    Mensaje* msj;
    sv_shm area(AREA);
    msj= reinterpret_cast<Mensaje*>(area.map(sizeof(Mensaje)));
    msj -> continua_corriendo = true;    
    cout<<"Area inicializada"<<endl;

    return 0;
} 

