LOADLIBES=-pthread #-lrt
CXXFLAGS=-std=c++11

all: src/Sem_Ascensor/Inicializa src/Sem_Ascensor/Libera src/Sem_Ascensor/Pasajero src/Sem_Ascensor/Ascensor src/Sem_Ascensor/Finaliza src/Ascensor_Facultad/Inicializa src/Ascensor_Facultad/Libera src/Ascensor_Facultad/Pasajero src/Ascensor_Facultad/Ascensor src/Ascensor_Facultad/Finaliza

clean:
	rm -f *~ src/Sem_Ascensor/Inicializa src/Sem_Ascensor/Libera src/Sem_Ascensor/Pasajero src/Sem_Ascensor/Ascensor src/Sem_Ascensor/Finaliza src/Ascensor_Facultad/Inicializa src/Ascensor_Facultad/Libera src/Ascensor_Facultad/Pasajero src/Ascensor_Facultad/Ascensor src/Ascensor_Facultad/Finaliza
