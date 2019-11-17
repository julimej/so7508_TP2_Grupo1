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

// class Mensaje {
// private:
//     int piso_ascensor=0;
//     int piso_pasajero=0;
//     int prox_piso=0;
//     bool continua_corriendo=true; 
// public:
//     Mensaje()=default;
//     ~Mensaje()=default;

//     int getPisoPasajero() { 
//         return this->piso_pasajero;
//     };

//     void setPisoPasajero(int piso) {
//         this->piso_pasajero = piso;
//     };

//     int getProxPiso() { 
//         return this->prox_piso;
//     };

//     void setProxPiso(int piso) {
//         this->prox_piso = piso;
//     };

//     int getPisoAscensor() { 
//         return this->piso_ascensor;
//     };

//     void setPisoAscensor(int piso) {
//         this->piso_ascensor = piso;
//     };
    
//     bool estaCorriendo() {        
//         return this->continua_corriendo;
//     }

//     void finalizar() {
//         this->continua_corriendo=false;
//     }
// };