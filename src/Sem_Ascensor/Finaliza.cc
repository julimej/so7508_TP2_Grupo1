#include  "../Sem-sv/sv_sem.h"
#include  "../Sem-sv/sv_shm.h"
#include  "Mensaje.h"
using namespace std;

int main(){
    sv_sem sem_llamado("semLlamado");
    sv_sem sem_ocupado("semOcupado");
    sv_sem sem_leer("semLectura");
    sv_sem sem_escribir("semEscritura");
    Mensaje * msj;
    sv_shm area("area");
    msj->finalizar();
    sem_llamado.post();
    return 0;
}