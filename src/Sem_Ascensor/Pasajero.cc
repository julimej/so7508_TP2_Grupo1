#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include <iostream>
#include <sstream>
#include "Mensaje.h"

int validar_parametro(char* str) {
    stringstream strValue;
    strValue << str;    
    unsigned int intValue;
    strValue >> intValue;
    return intValue;
}

int main (int argc, char* argv[]){
    if (argc != 4) {
        cout<<"Uso: "<<argv[0]<<" <nombre> <piso_actual> <prox_piso>"<<endl;
        return 1;
    }
    sv_sem sem_llamado("semLlamado");
    sv_sem sem_ocupado("semOcupado");
    sv_sem sem_leer("semLectura");
    sv_sem sem_escribir("semEscritura");
    Mensaje * msj;
    sv_shm area("area");
    msj=reinterpret_cast<Mensaje *> (area.map(BUFSIZ));
    sem_ocupado.wait();
    cout<< "El ascensor fue llamado"<<endl;
    sem_escribir.wait();
    int piso_pasajero = validar_parametro(argv[2]);
    int prox_piso = validar_parametro(argv[3]);
    msj->setPisoPasajero(piso_pasajero);
    msj->setProxPiso(prox_piso);
    sem_leer.post();
    sem_leer.wait();
    int piso_ascensor=msj->getPisoAscensor();
    for (int i= abs(piso_pasajero-piso_ascensor); i>0; i--) {
        sem_leer.wait();
        piso_ascensor = msj->getPisoAscensor();
        cout<<"El ascensor esta en el piso: "<<piso_ascensor<<endl;
        sem_escribir.post();
        usleep(500);
    }
    cout<< "El ascensor llego al piso del pasajero"<<endl;
    for (int i=abs(piso_pasajero-prox_piso); i>0; i--) {
        sem_leer.wait();
        piso_ascensor = msj->getPisoAscensor();
        cout<<"El ascensor esta en el piso: "<<piso_ascensor<<endl;
        sem_escribir.post();
        usleep(500);
    }
    cout<< "El ascensor dejo al pasajero en el piso: "<<prox_piso<<endl;
    return 0;
} 