#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "taulell.h"

using namespace std;

nat demana_coord(string text) {
// Mostra el text a la pantalla i llegeix un natural del teclat
  cout<<text;
  nat x;
  cin>>x;
  return x;
}


coord demana_moviment(taulell t, int color, nat limit) {
// Retorna una coordenada (fila i columna entre 1 i límit)
// que sigui vàlida  per col·locar el color dins del taulell t.
// Comprova que la coordenada estigui dins dels límits, la
// casella estigui lliure i el moviment sigui possible.
//Pre: el color es pot posar al taulell t
//Post: retorna una coordenada que es pot posar al taulell t
  bool es_possible=false;
  coord p;
  while(not es_possible){
	  nat x,y;
	  stringstream z;
	  z<<"Fila (1-"<<limit<<"): ";
	  x=demana_coord(z.str());
	  stringstream z2;
	  z2<<"Columna (1-"<<limit<<"): ";
	  y=demana_coord(z2.str());
	  p.x=x-1;
	  p.y=y-1;
	  if(not t.dins_limits(p))
		es_possible=true;
	  if(not es_possible){
		  if(t.mov_possible(p,color)){		
			if(not t(p).es_visitada())
				es_possible=true;
			else
				 cout<<"Error: Posició ja ocupada o moviment no vàlid."<<endl;
		  }
		  else
			cout<<"Error: Posició ja ocupada o moviment no vàlid."<<endl;
	  }
  }

  
	return p;
}
	  

coord moviment_aleatori(taulell t, int color, nat limit) {
// Retorna una coordenada (fila i columna entre 1 i límit) aleatòria
// que sigui vàlida per col·locar el color dins del taulell t.
// Comprova que la coordenada estigui dins dels límits, la
// casella estigui lliure i el moviment sigui possible.
  srand (time(NULL));
  coord k;
  bool es_s=false;
  while(not es_s){
  	int x= rand() % limit + 1;
	int y= rand() % limit + 1;
	k.x=x-1;
	k.y=y-1;
	if(t.mov_possible(k,color)){
		if(not t(k).es_visitada())
			es_s=true;
	}
  }
 
  return k;
}
nat debug=0;

int minimax(taulell &t, int color, nat prof, nat metode, coord &cmillor) {
// Avalua segons un algorisme minimax el taulell "t" pel color "color"
// fins a una profunditat "prof" i segons el mètode "metode" la millor
// coordenada per tirar "cmillor" i retorna el valor avaluat.
// pre: color = BLANCA o NEGRA, prof >= 1, metode = 0 o 1
  int valorcrida;
  int millorvalor;
  if(debug==1){
    char auxout1;
    if(color==casella::BLANCA)
	auxout1='B';
    else
	auxout1='N';
    cout<<"PROF: "<<prof<<" COLOR: " << auxout1 <<endl;
    t.mostra();
  }

  if(prof==0){
    if(metode==0)
        millorvalor=t.avalua();
    
    else if(metode==1)
        millorvalor=t.avalua_posicio();
    
  }
   else if(not t.pot_jugar(-color) and not t.pot_jugar(color)){
      millorvalor=t.avalua();
      if(millorvalor>0) 
        millorvalor=1000;
      
      else if(millorvalor<0) 
        millorvalor=-1000;
      
    }

  else{
    queue<coord> cua_coord=t.coord_pot_jugar(color);
    if(not cua_coord.empty()){
        int size=cua_coord.size();
        int cont=0;
	cmillor=cua_coord.front();
        while(not cua_coord.empty()){						//Inv cua.coord:"anem cridem recursivament fins que arribem a 0, despres el bucle es fa fins que es .empty()"
             taulell copia(t);							//    prof:"anem decreixen prof fins que es el cas inicial"
	     coord auxfront=cua_coord.front();					//    valorcrida:"conté el que retorna la funcio recursiva"
             copia.posa_fitxa(auxfront,color);					//    millorvalor:"actualitzem aquest valor si es compleixen les condicions"
             coord auxcoordcrida;
	     int aux=-color;
             valorcrida=minimax(copia,aux,prof-1,metode,auxcoordcrida);
	     bool es_primer= size==cua_coord.size();
             coord auxoperant=cua_coord.front();
	     cua_coord.pop();
             if(es_primer){
                millorvalor=valorcrida;
		++cont;
             }
             if(cont==1){
		     bool es_blanca_i_pot= color==casella::BLANCA and valorcrida>millorvalor;
		     if(es_blanca_i_pot){
		          cmillor=auxoperant;
		          millorvalor=valorcrida;
		        }
		     bool es_negra_i_pot= color==casella::NEGRA and valorcrida<millorvalor;
		     if(es_negra_i_pot){
		          cmillor=auxoperant;
		          millorvalor=valorcrida;
		        }
            }
        }
    }

    else{
             taulell copia(t);
             millorvalor=minimax(copia,-color,prof-1,metode,cmillor);
    }
  }
  if(debug==2){
    char auxout2;
    if(casella::BLANCA)
	auxout2='B';
    else
	auxout2='N';
    cout<<"PROF: "<<prof<<" COLOR: " <<auxout2<<" VMILLOR: "<<millorvalor<<endl;
  }
  return millorvalor;
} 

int main(int argc, char *argv[]) {
  nat mida = 8; // Mida taulell
  nat mode = 0;	 // Mode de jugar les blanques: 0: Per teclat, 1: Aleatori, 2: Cerca minimax
  nat prof = 1; // Profunditat cerca minimax
  nat metode = 0; // Mètode avaluació taulell en la cerca minimax:
                  // 0: Per número_fitxes_nostres - número_fitxes_contrari
                  // 1: Per número de coordenades a on podem jugar
  if (argc > 1)
    mida = atoi(argv[1]);
  if (argc > 2)
    mode = atoi(argv[2]);
  if (mode == 2) {
    if (argc > 3)
      prof = atoi(argv[3]);
    if (argc > 4)
      metode = atoi(argv[4]);
   if (argc > 5)
      debug = atoi(argv[5]);
  }

  // Inicialitzacions del joc
  bool jug1=true;
  bool jug2=true;
  int tornnegres=1;
  int color;  

  // Creem un taulell mida x mida
  taulell t(mida);	

  // Mentres el joc no s'acabi, cada iteració és una jugada
 
  while (jug1 or jug2) {							//Inv jug1:"bool que ens diu si un jugador pot jugar"
	    if(tornnegres%2==1)							//    jug2:"bool que ens diu si l'altre jugador pot jugar"
		color=casella::NEGRA;
	    else
		color=casella::BLANCA;
	    // color no pot jugar i ha de passar
	    if(t.pot_jugar(color)){
	    // Mostra capçalera, taulell i llegeix/calcula moviment
		    if(color==casella::NEGRA)
	            	cout<<"========== Jugador N =========="<<endl;
		    else
			cout<<"========== Jugador B =========="<<endl;
		    t.mostra(color);
		    coord c;
		    if(mode==0)
		    c=demana_moviment(t,color,mida);
		    if(mode==1){
			if(color==casella::BLANCA)
		    		c=moviment_aleatori(t,color, mida);
			else
				c=demana_moviment(t,color,mida);
		    }
		    if(mode==2){
			if(color==casella::BLANCA){
				c.x=debug;
				int valorminimax=minimax(t,color,prof,metode,c);
				}
			else
				c=demana_moviment(t,color,mida);
		   }

		    // Si la jugada és vàlida
		    if(t.dins_limits(c)){
			      // Col·loquem la nova fitxa i girem fitxes
			      t.posa_fitxa(c,color);
			      

			      // Informem estat de la partida
				int val = t.avalua();
			 	if (val > 0)
			    	cout<<"Està guanyant el jugador B."<<endl;
			  	else if (val < 0)
			   	cout<<"Està guanyant el jugador N."<<endl;
			  	else
			   	cout<<"Esteu empatant."<<endl;
	    
			       // Canviem el torn del jugador
				++tornnegres;
		    }

	      	    else {   
				jug1=false;
		 		jug2=false;
		    }
	  }
	    else{
		     if(color==casella::BLANCA)
			jug1=false;
		     if(color==casella::NEGRA)
			jug2=false;
		     ++tornnegres;
		}
  }

  // Visualització final de la partida
 cout<<"========== Fi partida =========="<<endl;
 t.mostra();
 int valfinal=t.avalua();
 if(valfinal>0)
	cout<<"Ha guanyat el jugador B"<<endl;
 else if(valfinal<0)
	cout<<"Ha guanyat el jugador N"<<endl;
 else
	cout<<"Heu empatat"<<endl;
}

