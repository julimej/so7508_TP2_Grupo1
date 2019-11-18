#ifndef MENSAJE_H
#define MENSAJE_H

struct Pasajero {
    int pisoActual;
    int pisoDestino;
    //string nombre;
};

struct Edificio {
    int cantPasajerosPiso1;
    int cantPasajerosPiso2;
    int cantPasajerosPiso3;
    int cantPasajerosPiso4;
    Pasajero pasajerosPiso1[4];
    Pasajero pasajerosPiso2[4];
    Pasajero pasajerosPiso3[4];
    Pasajero pasajerosPiso4[4];
    Pasajero pasajerosPiso5[4];
    int cantPasajerosPiso5;
    bool ascensorFuncionando;
    int pisoPrimerPasajero;
};


#endif