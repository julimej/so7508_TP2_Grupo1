#include <iostream>
#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include "Mensaje.h"
#include "Constantes.h"

void log_tiempo() {
    auto tiempo_actual = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(tiempo_actual);
    cout << "Tiempo actual: " <<std::ctime(&t)<<endl;
}

void log_mensaje(string mensaje) {
    log_tiempo();
    cout<<mensaje<<endl;
    cout<<"###############################"<<endl;
}