#include <iostream>
#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include "Mensaje.h"
using namespace std;

int main(int argc, char * argv[]){
    sv_sem sem_llamado("semLlamado");
    sv_sem sem_ocupado("semOcupado");
    sv_sem sem_leer("semLectura");
    sv_sem sem_escribir("semEscritura");
    Mensaje * msj;
    sv_shm area("area");
    msj=reinterpret_cast<Mensaje *> (area.map(BUFSIZ));
    while (true) {
        sem_llamado.wait();
        if (!msj->estaCorriendo()) break;
        cout<< "El ascensor fue llamado" << endl;
        sem_leer.wait();
        int piso_pasajero = msj->getPisoPasajero();
        int piso_ascensor = msj->getPisoAscensor();
        int incremento = (piso_pasajero>=piso_ascensor) ? 1 : -1; 
        for(int i= abs(piso_ascensor-piso_pasajero); i>0; i--) {
            sem_escribir.wait();
            piso_ascensor+=incremento;
            msj->setPisoAscensor(piso_ascensor);
            cout<< "El ascensor esta en el piso: "<<piso_ascensor<<endl;
            sem_leer.post();
            usleep(500);
        }
        cout<< "El ascensor llego al piso del pasajero"<<endl;
        int prox_piso = msj->getProxPiso();
        incremento = (prox_piso>=piso_ascensor) ? 1 : -1;
        for(int i= abs(prox_piso-piso_ascensor); i>0; i--) {
            piso_ascensor+=incremento;
            msj->setPisoAscensor(piso_ascensor);
            cout<< "El ascensor esta en el piso: "<<piso_ascensor<<endl;
            usleep(500);
        }
        cout<<"El ascensor dejo al pasajero en el piso: "<<piso_ascensor<<endl;
        sem_ocupado.post();
    }
    cout<<"Ascensor terminado."<<endl;
    return 0;
}