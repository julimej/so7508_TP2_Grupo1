#include <iostream>
#include <vector>
#include "../Sem-sv/sv_sem.h"
#include "../Sem-sv/sv_shm.h"
#include "Mensaje.h"
#include "Constantes.h"
using namespace std;

class Ascensor
{
    private:
    sv_sem sem_llamado;
    sv_shm area;
    Edificio* edificio;
    int pisoActual = 1;
    int pisoDestino = 1;
    int capacidad = 4;
    vector<Pasajero> pasajeros;
    public:
    Ascensor();
    void EsperarLlamada();
    bool LlegoADestino();
    void MoverAscensor();
    void BajarPasajeros();
    void SubirPasajeros();
    int CapacidadActual();
    bool HayLugar();
    bool EstaSubiendo();
    int ObtenerCantidadPasajerosPisoActual();
    Pasajero* ObtenerPasajerosPisoActual();
    void BuscarProximoDestino();
    void BuscarProximoDestinoEnPiso(int piso);
    void BuscarProximoDestinoEnPisoSuperior();
    void BuscarProximoDestinoEnPisoInferior();
};

Ascensor::Ascensor() : sem_llamado(SEM_LLAMADO), area(AREA)
{
    edificio = reinterpret_cast<Edificio*>(area.map(BUFSIZ));
};

void Ascensor::EsperarLlamada()
{
    edificio->ascensorFuncionando = false;
    sem_llamado.wait();
    cout << "Se llamo al ascensor desde el piso " << edificio->pisoPrimerPasajero << endl;
    pisoDestino = edificio->pisoPrimerPasajero;
    edificio->ascensorFuncionando = true;
}

bool Ascensor::LlegoADestino()
{
    return pisoActual == pisoDestino && pisoDestino != edificio->pisoPrimerPasajero;
}

void Ascensor::MoverAscensor()
{
    if (pisoDestino > pisoActual)
        pisoActual++;
    else if (pisoDestino < pisoActual)
        pisoActual--;

    cout << "================ PISO: " << pisoActual << "  ================" << endl;
}

void Ascensor::BajarPasajeros()
{
    if (pasajeros.empty())
    {
        cout << "Ningun pasajero se baja en este piso" << endl;
        return;
    }

    vector<Pasajero> pasajerosQueSeQuedan;

    for (int i=0; i < pasajeros.size(); i++)
    {
        Pasajero pasajero = pasajeros.at(i);

        if (pasajero.pisoDestino == pisoActual)
        {
            cout << "El pasajero " << pasajero.pisoDestino << " se baja en este piso." << endl;
        }
        else
        {
            pasajerosQueSeQuedan.push_back(pasajero);
        }        
    }

    pasajeros = pasajerosQueSeQuedan;
}

void Ascensor::SubirPasajeros()
{
    if (!HayLugar())
    {
        cout << "No hay más lugar en el ascensor." << endl;
        return;
    }
    else
    {
        cout << "Hay lugar en el ascensor." << endl;
    }

    int cantidadPasajerosPisoActual = ObtenerCantidadPasajerosPisoActual();

    if (cantidadPasajerosPisoActual == 0)
    {
        cout << "No hay pasajeros esperando a subir en este piso." << endl;
        return;
    }
    else
    {
        cout << "Hay " << cantidadPasajerosPisoActual << " pasajero/s en este piso" << endl;
    }

    Pasajero* pasajerosPisoActual = ObtenerPasajerosPisoActual();

    vector<Pasajero> proximosPasajeros;
    Pasajero pasajerosQueSeQuedan[4];
    int cantPasajerosQueSeQuedan = 0;

    for (int i=0; i < cantidadPasajerosPisoActual; i++)
    {
        Pasajero pasajeroActual = *(pasajerosPisoActual + i);

        if (pisoActual == edificio->pisoPrimerPasajero)
        {
            if (pasajeros.size() > 0)
                sem_llamado.wait();

            pasajeros.push_back(pasajeroActual);

            cout << "Se sube un pasajero." << endl;

            pisoDestino = pasajeroActual.pisoDestino;
        }
        else if (EstaSubiendo() && (pasajeroActual.pisoDestino > pisoActual) && HayLugar())
        {
            sem_llamado.wait();
            pasajeros.push_back(pasajeroActual);

            cout << "Se sube un pasajero." << endl;
            
            if (pasajeroActual.pisoDestino > pisoDestino)
                pisoDestino = pasajeroActual.pisoDestino;
        }
        else if (!EstaSubiendo() && (pasajeroActual.pisoDestino < pisoActual) && HayLugar())
        {
            sem_llamado.wait();
            pasajeros.push_back(pasajeroActual);

            cout << "Se sube un pasajero." << endl;
            
            if (pasajeroActual.pisoDestino < pisoDestino)
                pisoDestino = pasajeroActual.pisoDestino;
        }
        else
        {
            cout << "El pasajero no se sube." << endl;

            pasajerosQueSeQuedan[cantPasajerosQueSeQuedan] = pasajeroActual;
            cantPasajerosQueSeQuedan++;
        }
    }

    cout << "Ya subieron todos los pasajeros posibles." << endl;
    
    switch (pisoActual)
    {
        case 1:
            copy(begin(pasajerosQueSeQuedan), end(pasajerosQueSeQuedan), begin(edificio->pasajerosPiso1));
            edificio->cantPasajerosPiso1 = cantPasajerosQueSeQuedan;
            break;

        case 2:
            copy(begin(pasajerosQueSeQuedan), end(pasajerosQueSeQuedan), begin(edificio->pasajerosPiso2));
            edificio->cantPasajerosPiso2 = cantPasajerosQueSeQuedan;
            break;

        case 3:
            copy(begin(pasajerosQueSeQuedan), end(pasajerosQueSeQuedan), begin(edificio->pasajerosPiso3));
            edificio->cantPasajerosPiso3 = cantPasajerosQueSeQuedan;
            break;

        case 4:
            copy(begin(pasajerosQueSeQuedan), end(pasajerosQueSeQuedan), begin(edificio->pasajerosPiso4));
            edificio->cantPasajerosPiso4 = cantPasajerosQueSeQuedan;
            break;

        case 5:
            copy(begin(pasajerosQueSeQuedan), end(pasajerosQueSeQuedan), begin(edificio->pasajerosPiso5));
            edificio->cantPasajerosPiso5 = cantPasajerosQueSeQuedan;
            break;
        
        default:
            break;
    }
}

int Ascensor::CapacidadActual()
{
    return capacidad - pasajeros.size();
}

bool Ascensor::HayLugar()
{
    return capacidad > pasajeros.size();
}

bool Ascensor::EstaSubiendo()
{
    return pisoActual == 1 || pisoDestino > pisoActual;
}

Pasajero* Ascensor::ObtenerPasajerosPisoActual()
{
    switch (pisoActual)
    {
        case 1:
            return edificio->pasajerosPiso1;            

        case 2:
            return edificio->pasajerosPiso2;            

        case 3:
            return edificio->pasajerosPiso3;            

        case 4:
            return edificio->pasajerosPiso4;            

        case 5:
            return edificio->pasajerosPiso5;            
    
        default:            
            return nullptr;
    }
}

int Ascensor::ObtenerCantidadPasajerosPisoActual()
{
    switch (pisoActual)
    {
        case 1:
            return edificio->cantPasajerosPiso1;

        case 2:
            return edificio->cantPasajerosPiso2;        

        case 3:
            return edificio->cantPasajerosPiso3;

        case 4:
            return edificio->cantPasajerosPiso4;

        case 5:
            return edificio->cantPasajerosPiso5;        
    
        default:            
            return 0;
    }
}

void Ascensor::BuscarProximoDestino()
{
    cout << "Buscando próximo destino" << endl;

    BuscarProximoDestinoEnPiso(pisoActual);

    if (EstaSubiendo() && LlegoADestino())
        BuscarProximoDestinoEnPisoSuperior();

    if (!EstaSubiendo() && LlegoADestino())
        BuscarProximoDestinoEnPisoInferior();

    if (LlegoADestino())
        cout << "No hay más pasajeros esperando el ascensor." << endl;
    else
        cout << "Hay un pasajero esperando en el piso " << pisoDestino << endl;
}

void Ascensor::BuscarProximoDestinoEnPiso(int piso)
{
    if (!LlegoADestino())
        return;

    switch (piso)
    {
        case 1:
            if (edificio->cantPasajerosPiso1 > 0)
            {
                pisoDestino = edificio->pasajerosPiso1[0].pisoDestino;
            }
            break;

        case 2:
            if (edificio->cantPasajerosPiso2 > 0)
            {
                pisoDestino = edificio->pasajerosPiso2[0].pisoDestino;
            }
            break;

        case 3:
            if (edificio->cantPasajerosPiso3 > 0)
            {
                pisoDestino = edificio->pasajerosPiso3[0].pisoDestino;
            }
            break;

        case 4:
            if (edificio->cantPasajerosPiso4 > 0)
            {
                pisoDestino = edificio->pasajerosPiso4[0].pisoDestino;
            }
            break;

        case 5:
            if (edificio->cantPasajerosPiso5 > 0)
            {
                pisoDestino = edificio->pasajerosPiso5[0].pisoDestino;
            }
            break;
        
        default:
            break;
    }
}
void Ascensor::BuscarProximoDestinoEnPisoSuperior()
{
    switch (pisoActual)
    {
        case 1:
            BuscarProximoDestinoEnPiso(2);
            BuscarProximoDestinoEnPiso(3);
            BuscarProximoDestinoEnPiso(4);
            BuscarProximoDestinoEnPiso(5);
            break;

        case 2:
            BuscarProximoDestinoEnPiso(3);
            BuscarProximoDestinoEnPiso(4);
            BuscarProximoDestinoEnPiso(5);
            break;

        case 3:
            BuscarProximoDestinoEnPiso(4);
            BuscarProximoDestinoEnPiso(5);
            break;

        case 4:
            BuscarProximoDestinoEnPiso(5);
            break;

        default:
            break;
    }
}
void Ascensor::BuscarProximoDestinoEnPisoInferior()
{
    switch (pisoActual)
    {
        case 5:
            BuscarProximoDestinoEnPiso(4);
            BuscarProximoDestinoEnPiso(3);
            BuscarProximoDestinoEnPiso(2);
            BuscarProximoDestinoEnPiso(1);
            break;

        case 4:
            BuscarProximoDestinoEnPiso(3);
            BuscarProximoDestinoEnPiso(2);
            BuscarProximoDestinoEnPiso(1);
            break;

        case 3:
            BuscarProximoDestinoEnPiso(2);
            BuscarProximoDestinoEnPiso(1);
            break;

        case 2:
            BuscarProximoDestinoEnPiso(1);
            break;

        default:
            break;
    }
}

int main(int argc, char * argv[])
{    
    Ascensor ascensor;

    while (true)
    {
        ascensor.EsperarLlamada();

        while (!ascensor.LlegoADestino())
        {
            ascensor.MoverAscensor();
            ascensor.BajarPasajeros();
            ascensor.SubirPasajeros();
            sleep(2);

            if (ascensor.LlegoADestino())
                ascensor.BuscarProximoDestino();
        }
    }

    return 0;
}