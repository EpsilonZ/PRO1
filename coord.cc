#include <sstream>
#include "coord.h"

using namespace std;

///////////////////////////////////////////
//// Implementació de la classe coord ///

//---- Crear un parell de coordenades sense valor inicial
coord::coord() { }

//---- Crear un nou parell de coordenades, amb valor (a,b)
coord::coord(int a, int b) { 
  x=a;
  y=b;
}

//---- Suma a la coordenada actual el parell de coordenades donat.
//---- Per exemple:  t=(3,4) i z=(-1,2),  tindrem t+z = (2,6)
coord coord::operator+(const coord& c) const {
  coord c2;
  c2.x=c.x+x;
  c2.y=c.y+y;
  return c2;
}

//---- Compara la coordenada actual el parell de coordenades donat.
bool coord::operator==(const coord &c) const {
  
  return x==c.x and y==c.y; 
}

//---- Retorna un string amb el contingut de la coordenada entre paréntesis.
//---- Aquest mètode és útil per fer debugging.
//---- Per exemple si x=3 i y=-1, mostra retornaria "(3,-1)"
string coord::mostra() const {
  stringstream k;
  k<<'('<<x<<','<<y<<')';
  return k.str();
  
}

//---- Retorna un string amb el contingut de la coordenada entre paréntesis
//---- sumant 1 a cada component. Aquest mètode és útil per fer debugging.
//---- Per exemple si x=3 i y=-1, mostra1 retornaria "(4,0)"
string coord::mostra1() const {
  int m=x+1;
  int n=y+1;
  stringstream z;
  z<<'('<<m<<','<<n<<')';
  return z.str();
  
}
