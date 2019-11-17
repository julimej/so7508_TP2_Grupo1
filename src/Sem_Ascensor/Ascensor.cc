#include <iostream>
#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include "Mensaje.h"
#include "Constantes.h"
#include "Utils.h"
using namespace std;

int main(int argc, char * argv[]){
    sv_sem sem_llamado(SEM_LLAMADO);
    sv_sem sem_ocupado(SEM_OCUPADO);
    sv_sem sem_leer_ascensor(SEM_LECTURA_ASCENSOR);
    sv_sem sem_leer_pasajero(SEM_LECTURA_PASAJERO);
    Mensaje * msj;
    sv_shm area(AREA);
    msj=reinterpret_cast<Mensaje *> (area.map(BUFSIZ));

    while (true) {
        sem_llamado.wait();
        if (!msj->continua_corriendo) break;
        log_mensaje("El ascensor fue llamado");
        sem_leer_ascensor.wait();
        int piso_pasajero = msj->piso_pasajero;
        int piso_ascensor = msj->piso_ascensor;
        int incremento = (piso_pasajero>=piso_ascensor) ? 1 : -1; 

        for(int i= abs(piso_ascensor-piso_pasajero); i>0; i--) {            
            piso_ascensor+=incremento;
            msj->piso_ascensor = piso_ascensor;
            log_mensaje("El ascensor esta en el piso: " + to_string(piso_ascensor));
            sem_leer_pasajero.post();
            usleep(ESPERA);
        }

        log_mensaje("El ascensor llego al piso del pasajero");

        int prox_piso = msj->prox_piso;
        incremento = (prox_piso>=piso_ascensor) ? 1 : -1;

        for(int i= abs(prox_piso-piso_ascensor); i>0; i--) {
            piso_ascensor+=incremento;
            msj->piso_ascensor = piso_ascensor;
            log_mensaje("El ascensor esta en el piso: "+ to_string(piso_ascensor));
            sem_leer_pasajero.post();
            usleep(ESPERA);
        }

        log_mensaje("El ascensor dejo al pasajero en el piso: " + to_string(piso_ascensor));
        sem_ocupado.post();
    }

    log_mensaje("Ascensor terminado.");

    return 0;
}