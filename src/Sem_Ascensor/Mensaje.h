#ifndef MENSAJE_H
#define MENSAJE_H

/*Clase encargada de contener los mensajes que se
transmiten entre el ascensor y los pasajeros*/

class Mensaje {
private:
    int piso_actual=0;
    bool esta_lleno=false;
    bool finalizo=false; 
public:
    Mensaje()=default;
    ~Mensaje()=default;

    int getPiso() { 
        return this->piso_actual;
    };

    void setPiso(int piso) {
        this->piso_actual = piso;
    };

    bool getEstaLleno() { 
        return this->esta_lleno;
    };

    void setEstaLleno(bool esta_lleno) {
        this->esta_lleno=esta_lleno;
    };
    void finalizar() {
        this->finalizo=true;
    }
};

#endif