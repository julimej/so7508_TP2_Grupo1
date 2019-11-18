#include  "../Sem-sv/sv_sem.h"
#include  "../Sem-sv/sv_shm.h"
#include  "Mensaje.h"
#include "Constantes.h"
using namespace std;

int main ()
{
    sv_shm area(AREA);
    sv_sem sem_llamado(SEM_LLAMADO);
    
    sem_llamado.del();    
    area.del();

    return 0;
}