#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include <iostream>
#include <sstream>
#include "Mensaje.h"
#include "Utils.h"
#include "Constantes.h"

int validar_parametro(char* str) {
    stringstream strValue;
    strValue << str;    
    unsigned int intValue;
    strValue >> intValue;
    return intValue;
}

int main (int argc, char* argv[])
{
    if (argc != 4)
    {
        cout<<"Uso: "<<argv[0]<<" <nombre> <piso_actual> <prox_piso>"<<endl;
        return 1;
    }

    sv_sem sem_llamado(SEM_LLAMADO);
    sv_sem sem_ocupado(SEM_OCUPADO);
    sv_sem sem_leer_ascensor(SEM_LECTURA_ASCENSOR);
    sv_sem sem_leer_pasajero(SEM_LECTURA_PASAJERO);
    Mensaje * msj;
    sv_shm area(AREA);
    msj = reinterpret_cast<Mensaje *>(area.map(BUFSIZ));

    // Espero a que desocupe para llamarlo
    sem_ocupado.wait();

    // Ingreso los datos del viaje en el area compartida
    int piso_pasajero = validar_parametro(argv[2]);
    int prox_piso = validar_parametro(argv[3]);
    msj->piso_pasajero = piso_pasajero;
    msj->prox_piso = prox_piso;

    //Verifico que no quiera ir a su mismo piso
    if (piso_pasajero == prox_piso) {
        log_mensaje("Ya se encuentra en ese piso");
        return 1;
    }

    sem_leer_ascensor.post();

    // Lo llamo
    sem_llamado.post();
    log_mensaje("El ascensor fue llamado");

    // Ascensor llegando al piso que fue llamado
    sem_leer_pasajero.wait();
    int piso_ascensor=msj->piso_ascensor;

    while (piso_ascensor != piso_pasajero)
    {
        log_mensaje("El ascensor esta en el piso: "+ to_string(piso_ascensor));
        sem_leer_ascensor.post();
        sem_leer_pasajero.wait();
        piso_ascensor=msj->piso_ascensor;
        usleep(ESPERA);
    }

    log_mensaje("El ascensor llego al piso del pasajero");
    sem_leer_ascensor.post();

    // Ascensor llegando al piso destino
    for (int i=abs(piso_pasajero-prox_piso); i>0; i--) {
        sem_leer_pasajero.wait();
        piso_ascensor = msj->piso_ascensor;
        log_mensaje("El ascensor esta en el piso: " + to_string(piso_ascensor));
        sem_leer_ascensor.post();
        usleep(ESPERA);
    }
    log_mensaje("El ascensor dejo al pasajero en el piso: " + to_string(prox_piso));
    
    return 0;
} 