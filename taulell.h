#include <string>
#include <vector>
#include <queue>

#include "direccio.h"
#include "casella.h"
#include "util.h"

using namespace std;

//----  La classe "taulell" és l'estructura de dades principal de la
//----  pràctica. Guarda la taula n x n amb la informació de les caselles.

class taulell {
 private:
   //---- Taula per guardar les caselles del taulell.
   std::vector<std::vector<casella> > taula;

   /// casella lliure extra, per si estem fora dels límits.
   casella lliure;

 public: 
   //---- Constructora. Serveix per declarar una variable
   //---- de tipus "taulell" de mida n x n inicialitzada
   //---- amb les fitxes inicials d'una partida de Reversi.
   //---- Pre: n >=2
   taulell(nat n);
   //Pre:cert
   //Post:crea una taula n x n amb les 4 caselles centrals amb els valors b n
							     //	          n b

   //---- Diu si les coord p estan dins dels limits del taulell.
   bool dins_limits(coord p) const;
   //Pre:cert
   //Post:retorna true si esta dins de la taula la coordenada p,fals altrament

   //---- Accedeix a la casella de la coord p del taulell.
   casella& operator()(coord);
   //Pre:cert
   //Post:retorna la casella corresponent a la coordenada en el taulell

   //---- Escriu a la pantalla el contingut del taulell.
   void mostra() const;
   //Pre:cert
   //Post:mostra per pantalla el contigut del taulell

   //---- Escriu a la pantalla el contingut del taulell marcant amb 'x'
   //---- les caselles on es poden posar fitxes del color donat.
   void mostra(int color) const; 
   //Pre:cert
   //Post:mostra per pantalla el contigut del taulell marcant amb "?" les caselles on pot posar fitxes el color passat per copia

   //---- Avalua les fitxes del taulell:
   //---- num_caselles_blanques - num_caselles_negres.
   int avalua() const;
   //Pre:cert
   //Post:retorna el valor de num_caselles_blanques-num_caselles_negres
      //---- Avalua les fitxes del taulell ponderat segons posicio
   //---- num_caselles_blanques - num_caselles_negres.
   //---- Les caselles blanques de la primera/última fila/columna les *5
   //---- Les caselles blanques de les 4 cantonades les *10
   //---- Les caselles negres de la primera/última fila/columna les * -5
   //---- Les caselles negres de les 4 cantonades les * -10
   int avalua_posicio() const;
   //Pre:cert
   //Post:retorna valor segons el protocol de puntuament del taulell de la practica
   //---- Comprova si es pot girar desde la coordenada cini en la direcció d
   //---- varies fitxes de l'adversari (al final hem de trobar un color 'nostre').
   //---- Retorna: girar (si es pot girar o no), c (coordenada final on s'ha trobat el color donat)
   void es_pot_girar(coord cini, direccio d, int color, bool &girar, coord &c) const;
   //Pre:cert
   //Post:girar passa a ser true si es poden girar les fitxes de l'adversari, en cas de ser true la coordenada c passa a ser on s'ha trobat la coordenada final, si no es pot girar es fals i c no varia     el valor

   //---- Comprova si es pot posar una fitxa de color a la coordena c:
   //---- Cal comprovar si en una de les 8 direccions es poden girar fitxes
   //---- de l'adversari (de color diferent al color donat).
   bool mov_possible(coord c, int color) const;
   //Pre:la c ha de estar dintre del taulell,color ha de ser un valor correcte(1,-1,0)
   //Post:retorna true si es pot possar fitxa a la coordenada i si es necessari girar les fitxes de l'adversari(el color contrari)

   //---- Comprova si el color pot jugar (la fitxa de color es pot col·locar en algun lloc).
   bool pot_jugar(int color) const;
   //Pre:color ha de ser un valor correcte(1,-1,0)
   //Post:retorna true si el color pot posar fitxes

   //---- Retorna una cua amb les coordenades a on el color pot jugar.
   //---- S'encuen per fila creixent, i per la mateixa fila per columna creixent.
   queue<coord> coord_pot_jugar(int color) const;
   //Pre:color ha de ser un valor correcte(1,-1,0)
   //Post:retorna una cua amb els valors on es poden posar les fitxes

   //---- Canvia el color de les caselles des de la casella ci
   //---- fins a la casella cf en la direcció d.
   void gira_fitxes(coord ci, coord cf, direccio d);
   //Pre:direccio ha de ser diferent a STOP
   //Post:gira les fitxes començcant en la coordenada ci en la direccio d fins la coordenada cf

   //---- Col·loca la fitxa de color a la coordena c i gira les fitxes necessàries segons regles d'Otelo
   void posa_fitxa(coord c, int color);
   //Pre:color es un valor correcte (1,-1,0)
   //Post:el color de la casella que esta a la coordenada c del taulell passa a ser el color passat per copia
};
