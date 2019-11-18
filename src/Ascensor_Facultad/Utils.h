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

void imprimir_padrones() {
    cout<<"Integrantes del grupo:"<<endl;
    cout<<"\tLautaro Ituarte, 93639.\n\tJulian Mejliker, 100866.\n\tJoel Saidman, 99730."<<endl;
    cout<<"================================"<<endl;
}