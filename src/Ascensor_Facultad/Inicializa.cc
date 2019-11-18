#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include <iostream>
#include <sstream>
#include "Mensaje.h"
#include "Constantes.h"
#include "Utils.h"

int main (){
    imprimir_padrones();
    sv_sem sem_llamado(SEM_LLAMADO,0);    
    cout<<"Semaforos inicializados"<<endl;
    Edificio* edificio;
    sv_shm area(AREA);
    edificio= reinterpret_cast<Edificio*>(area.map(sizeof(Edificio)));
    cout<<"Area inicializada"<<endl;

    return 0;
} 

