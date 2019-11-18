#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "Mensaje.h"
#include "Constantes.h"

int validar_parametro(char* str) {
    stringstream strValue;
    strValue << str;    
    unsigned int intValue;
    strValue >> intValue;
    return intValue;
}

int main (int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "Uso: " << argv[0] << " <nombre> <piso_actual> <prox_piso>" << endl;
        return 1;
    }

    sv_sem sem_llamado(SEM_LLAMADO);    
    Edificio* edificio;
    sv_shm area(AREA);
    edificio = reinterpret_cast<Edificio*>(area.map(BUFSIZ));

    Pasajero pasajero;
    //pasajero.nombre = argv[1];
    pasajero.pisoActual = validar_parametro(argv[2]);
    pasajero.pisoDestino = validar_parametro(argv[3]);

    cout << "El pasajero se llama " << argv[1] << endl;
    cout << "Quiero ir desde el piso " << pasajero.pisoActual << endl;
    cout << "Al piso " << pasajero.pisoDestino << endl;

    switch (pasajero.pisoActual)
    {
        case 1:
            edificio->pasajerosPiso1[edificio->cantPasajerosPiso1] = pasajero;
            edificio->cantPasajerosPiso1++;
            break;

        case 2:            
            edificio->pasajerosPiso2[edificio->cantPasajerosPiso2] = pasajero;            
            edificio->cantPasajerosPiso2++;
            break;

        case 3:
            edificio->pasajerosPiso3[edificio->cantPasajerosPiso3] = pasajero;
            edificio->cantPasajerosPiso3++;
            break;

        case 4:
            edificio->pasajerosPiso4[edificio->cantPasajerosPiso4] = pasajero;
            edificio->cantPasajerosPiso4++;
            break;

        case 5:
            edificio->pasajerosPiso5[edificio->cantPasajerosPiso5] = pasajero;
            edificio->cantPasajerosPiso5++;
            break;
        
        default:
            break;
    }

    if (!edificio->ascensorFuncionando)
        edificio->pisoPrimerPasajero = pasajero.pisoActual;

    // Lo llamo
    sem_llamado.post();
    cout << "El ascensor fue llamado" << endl;
    
    return 0;
} 