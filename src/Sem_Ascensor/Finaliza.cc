#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include "Mensaje.h"
#include "Constantes.h"
#include "Utils.h"
using namespace std;

int main(){
    imprimir_padrones();
    sv_sem sem_llamado(SEM_LLAMADO);
    Mensaje * msj;
    sv_shm area(AREA);
    msj=reinterpret_cast<Mensaje *> (area.map(BUFSIZ));
    msj->continua_corriendo = false;
    sem_llamado.post();
    return 0;
}