#include <iostream>
#include "casella.h"

///////////////////////////////////////////
//// Implementació de la classe casella ///

//---- Crea una casella amb valor inicial LLIURE.
casella::casella() {  
//Pre:cert
//Post: crea una nova casella lliure sense visitar
   color=0;
   visitada=false;
}

//---- Modifica el color de la casella.
void casella::omple(int x) {
//Pre:x ha de ser 1,-1 o 0
//Post: omple la casella amb el valor x
  color=x;
}

//---- Marcar la casella com a visitada.
void casella::marca() {
//Pre: cert
//Post: la casella esta marcada
  visitada=true;
}

//---- Desmarca la casella (no visitada). 
void casella::desmarca() {
//Pre:cert
//Post: la casella passa a estar desmarcada
  visitada=false;
}

//---- Obté el contingut de la casella.
int casella::valor() const {
//Pre: cert
//Post: retorna el color de la casella
  return color;
}

//---- Obté el el caràcter de la casella a dibuxar:
//---- BLANCA -> B, NEGRA -> N, LLIURE -> -
char casella::mostra() const {
//Pre: cert
//Post: retorna el caracter corresponent al color
  char x;
  if(color==BLANCA)
	x='B';
  if(color==LLIURE)
	x='-';
  if(color==NEGRA)
	x='N';
  return x;
}

//---- Consulta si la casella esta marcada com visitada.
bool casella::es_visitada() const {
//Pre:cert
//Post: retorna true si esta visitada, false si no ho esta
   return visitada;
}
