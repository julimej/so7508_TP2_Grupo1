#include "../includes.hpp"


class Pasajero {
private:
  int pisoSubida;
  int pisoBajada;
  std::string nombre;
  bool subio;
  bool bajo;
public:
  Pasajero(std::string nombre, int pisoSubida, int pisoBajada);
  ~Pasajero();
  int getPisoBajada() { return pisoBajada; }
  int getPisoSubida() { return pisoSubida; }
  void subir() {subio = true;}
  void bajar() {bajo = true;}
};
