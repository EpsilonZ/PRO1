#include "direccio.h"


///////////////////////////////////////////
//// Implementació de la classe direcció ///

///--- Crear una direcció nova, amb el primer valor de la llista.
direccio::direccio() {
//Pre:cert
//Post: crea una nova direccio amb el primer valor de la llista(nord)
	init();
}

///--- Veure si el valor de la direcció és el del final de la llista.
bool direccio::is_stop() const {
//Pre:cert
//Post:retorna true si està a la direccio stop

 return d==STOP;
  
}

///--- canviar el valor de la direccio, posant-li el primer de la llista
void direccio::init() {
//Pre:cert
//Post:la direccio passa a estar a nord
  d=N;
}

///--- Canviar el valor de la direcció pel següent de la llista.
///--- Permet usar instruccions "++d" (on d és de tipus direcció).
direccio& direccio::operator++() {
//Pre:cert
//Post: retorna la següent direccio de la llista
 if (not is_stop()) d=dirs(d+1);
  return (*this);
}  

///--- Obtenir les components x,y que representen un moviment 
///--- en aquesta direcció. P.ex  N -> (-1,0), NE -> (-1,1)
coord direccio::despl() const {
//Pre:cert
//Post:retorna una coordenada corresponent al desplaçament de la direccio
  coord x;
  if(d==N){
     x.x=-1;
     x.y=0;
  }
  if(d==NE){
    x.x=-1;
    x.y=1; 
  }    
  if(d==S){
    x.x=1;
    x.y=0;
  }
  if(d==SE){
    x.x=1;
    x.y=1;
  }
  if(d==SO){
    x.x=1;
    x.y=-1;
  }
  if(d==NO){   
    x.x=-1;
    x.y=-1;
  }
  if(d==O){
    x.x=0;
    x.y=-1;
  }
  if(d==E){
    x.x=0;
    x.y=1;
  }
  return x;
}


///--- Obtenir un string amb el nom de la direcció.
///--- Aquest mètode és útil per fer debugging.
string direccio::mostra() const {
//Pre:cert
//Post:retorna un string que marca en quina direccio estem

 string rt;
 if(d==N)
   rt="NORD";
 if(d==NE)
   rt="NORD-EST";
 if(d==S)
   rt="SUD";
 if(d==SE)
  rt="SUD-EST";
 if(d==SO)
  rt="SUD-OEST";
 if(d==NO)
  rt="NORD-OEST";
 if(d==O)
  rt="OEST";
 if(d==E)	
  rt="EST";

 return rt;
}
