#include  "../Sem-sv/sv_sem.h"
#include  "../Sem-sv/sv_shm.h"
#include  "Mensaje.h"
#include "Constantes.h"
using namespace std;

int main (){
    sv_shm area(AREA);
    sv_sem sem_llamado(SEM_LLAMADO);
    sv_sem sem_ocupado(SEM_OCUPADO);
    sv_sem sem_leer_ascensor(SEM_LECTURA_ASCENSOR);
    sv_sem sem_leer_pasajero(SEM_LECTURA_PASAJERO);
    sem_llamado.del();
    sem_ocupado.del();
    sem_leer_ascensor.del();
    sem_leer_pasajero.del();
    area.del();
    return 0;
}