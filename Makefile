LOADLIBES=-pthread #-lrt
CXXFLAGS=-std=c++11

all: src/Sem_Ascensor/Inicializa src/Sem_Ascensor/Libera

clean:
	rm -f *~ src/Sem_Ascensor/Inicializa src/Sem_Ascensor/Libera
