#include  "../Sem-sv/sv_sem.h"
#include  "../Sem-sv/sv_shm.h"
#include  "Mensaje.h"
using namespace std;

int main(){
    sv_sem capacidad("Capacidad",0);
    sv_sem mutex("Mutex",1);
    sv_sem entra("Entra",1);
    sv_shm area("Area");
    capacidad.del();
    mutex.del();
    entra.del();
    area.del();
    return 0;
}