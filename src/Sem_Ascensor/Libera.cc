#include  "../Sem-sv/sv_sem.h"
#include  "../Sem-sv/sv_shm.h"
#include  "Mensaje.h"
using namespace std;

int main(){
    sv_shm area("Area");
    sv_sem sem_llamado("semLlamado");
    sv_sem sem_ocupado("semOcupado");
    sv_sem sem_leer("semLectura");
    sv_sem sem_escribir("semEscritura");
    sem_llamado.del();
    sem_ocupado.del();
    sem_leer.del();
    sem_escribir.del();
    area.del();
    return 0;
}