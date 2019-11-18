LOADLIBES=-pthread #-lrt
CXXFLAGS=-std=c++11

all: src/Ascensor_Facultad/Inicializa src/Ascensor_Facultad/Libera src/Ascensor_Facultad/Pasajero src/Ascensor_Facultad/Ascensor src/Ascensor_Facultad/Finaliza src/Ascensor_Facultad/Inicializa src/Ascensor_Facultad/Libera src/Ascensor_Facultad/Pasajero src/Ascensor_Facultad/Ascensor src/Ascensor_Facultad/Finaliza

clean:
	rm -f *~ src/Ascensor_Facultad/Inicializa src/Ascensor_Facultad/Libera src/Ascensor_Facultad/Pasajero src/Ascensor_Facultad/Ascensor src/Ascensor_Facultad/Finaliza src/Ascensor_Facultad/Inicializa src/Ascensor_Facultad/Libera src/Ascensor_Facultad/Pasajero src/Ascensor_Facultad/Ascensor src/Ascensor_Facultad/Finaliza
