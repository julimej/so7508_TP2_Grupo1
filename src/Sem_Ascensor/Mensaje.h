#ifndef MENSAJE_H
#define MENSAJE_H

/*Clase encargada de contener los mensajes que se
transmiten entre el ascensor y los pasajeros*/

struct Mensaje {
    int piso_ascensor;
    int piso_pasajero;
    int prox_piso;
    bool continua_corriendo;
};

#endif