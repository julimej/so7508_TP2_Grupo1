#include  "../Sem-sv/sv_sem.h"
#include  "../Sem-sv/sv_shm.h"
#include  "Mensaje.h"
using namespace std;

int main(){
  sv_sem mutex("Ascensor",0);
  sv_shm area("area");
  mutex.del();
  area.del();
}