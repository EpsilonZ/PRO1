#include <iostream>
#include "taulell.h"

///////////////////////////////////////////
//// Implementació de la classe taulell ///

//---- Constructora. Serveix per declarar una variable
//---- de tipus "taulell" de mida n x n inicialitzada
//---- amb les fitxes inicials d'una partida de Reversi.
//---- Pre: n >=2
taulell::taulell(nat n) {
//Pre:cert
//Post:crea una taula n x n amb les 4 caselles centrals amb els valors b n
							//	       n b
  // crea taula de mida n x n
  taula = vector<vector<casella> >(n,vector<casella>(n,casella()));

  // inicialitza les 4 caselles centrals del taulell
  // si n és senar, les 4 caselles centrals queden una mica desplaçades amunt i a l'esquerra
	taula[n/2-1][n/2-1].omple(casella::BLANCA);
	taula[n/2-1][n/2-1].marca();
	taula[n/2-1][n/2].omple(casella::NEGRA);
	taula[n/2-1][n/2].marca();
	taula[n/2][n/2-1].omple(casella::NEGRA) ;
	taula[n/2][n/2-1].marca();
	taula[n/2][n/2].omple(casella::BLANCA);
	taula[n/2][n/2].marca();
}
	


//---- Diu si les coord p estan dins dels limits del taulell.
bool taulell::dins_limits(coord p) const {
//Pre:cert
//Post:retorna true si esta dins de la taula la coordenada p,fals altrament

	  bool i=false;
	  bool j=false;
	  if(p.x>=0 and p.x<taula.size())
	 	i=true;
	  if(p.y>=0 and p.y<taula.size())
		j=true;

	  return i&&j;
}


//---- Accedeix a la casella de la coord p del taulell.
casella& taulell::operator()(coord p) {
//Pre:cert
//Post:retorna la casella corresponent a la coordenada p en el taulell
  	return taula[p.x][p.y];
}


//---- Escriu a la pantalla el contingut del taulell.
void taulell::mostra() const {
//Pre:cert
//Post:mostra per pantalla el contigut del taulell
  	// escriu capçalera per enumerar columnes
	  cout<<"  ";
	  for(unsigned int k=1; k<=taula.size();++k){		//Inv: k:"es el valor que anem augmentan i mostrarem per pantalla fins a k==taula.size()"
		cout<<k;	
		if(k!=taula.size())
			cout<<" ";
	  }
	  cout<<endl;
	  for(unsigned int i=0;i<taula.size();++i){		//Inv: i"valor que augmentem a cada iteracio fins a i<taula.size()"
		cout<<i+1<<" ";                  
		for(unsigned int j=0;j<taula.size();++j){	//Inv: j"valor que augmentem a cada iteracio fins a j<taula.size()"	     
			cout<<taula[i][j].mostra();
			if(j!=taula.size()-1)
				cout<<" ";
		}
	  cout<<endl;
		}
	  // escriu contingut amb la numeració de fila al principi
}


//---- Escriu a la pantalla el contingut del taulell marcant amb '?'
//---- les caselles on es poden posar fitxes del color donat.
void taulell::mostra(int color) const {
//Pre:cert
//Post:mostra per pantalla el contigut del taulell marcant amb "?" les caselles on pot posar fitxes el color passat per copia
  // escriu capçalera per enumerar columnes
 	 cout<<"  ";
	 for(unsigned int k=1; k<=taula.size() ; ++k){         //Inv: k:"es el valor que anem augmentan i mostrarem per pantalla fins a k==taula.size()"
	   cout<<k<<" ";
	 }
	 cout<<endl;
	 queue<coord> auxcoord= coord_pot_jugar(color);
		//Inv: auxcoord:"es la cua que conte les coordenades on podem possar fitxes"
		 for(unsigned int i=0;i<taula.size();++i){		//     i"valor que augmentem a cada iteracio fins a i<taula.size()"
			cout<<i+1<<" ";
			for(unsigned int j=0;j<taula.size();++j){       //Inv: j"valor que augmentem a cada iteracio fins a j<taula.size()"
				coord auxtaul;
				auxtaul.x=i;
				auxtaul.y=j;
				if(not auxcoord.empty() and auxcoord.front()==auxtaul){
						cout<<"?";
						if(j!=taula.size()-1)
							cout<<" ";
						auxcoord.pop();
				}
				
				else 
					cout<<taula[i][j].mostra()<<" ";
			}
		 	cout<<endl;
		}
	
	
	  
}


//---- Avalua les fitxes del taulell:
//---- num_caselles_blanques - num_caselles_negres.
int taulell::avalua() const {
//Pre:cert
//Post:retorna el valor de num_caselles_blanques-num_caselles_negres
  int x=0;
  int y=0;
  for(unsigned int i=0;i<taula.size();++i){			//Inv: i"valor que augmentem a cada iteracio fins a i<taula.size()"
	for(unsigned int j=0;j<taula.size();++j){               //Inv: j"valor que augmentem a cada iteracio fins a j<taula.size()"
		if(taula[i][j].valor()==casella::BLANCA)
		++x;
		if(taula[i][j].valor()==casella::NEGRA)
 		++y;
 	}
  }
  
return x-y;
}


//---- Comprova si es pot girar desde la coordenada cini en la direcció d
//---- varies fitxes de l'adversari (al final hem de trobar el color donat).
//---- Retorna: girar (si es pot girar o no), c (coordenada final on s'ha trobat el color donat)

void taulell::es_pot_girar(coord cini, direccio d, int color, bool &girar, coord &c) const {
//Pre:cert
//Post:girar passa a ser true si es poden girar les fitxes de l'adversari, en cas de ser true la coordenada c passa a ser on s'ha trobat la coordenada final, si no es pot girar es fals i c no varia el valor
			
	girar=false;
	coord auxcini=cini;
	auxcini=auxcini+d.despl();
	if(dins_limits(auxcini)){
		if(taula[auxcini.x][auxcini.y].valor()!=casella::LLIURE){
			if(taula[auxcini.x][auxcini.y].valor()!=color) {
				while(not girar){						//Inv: girar:"el bool girar passara a ser true si troba una casella lliure/color o si esta fora de 
					auxcini=auxcini+d.despl();				        // la taula la coordenada auxcini
					if(dins_limits(auxcini)){				//     auxcini:"a cada iteracio augmentarem el seu valor amb el desplaçament corresponent"	   
						if(taula[auxcini.x][auxcini.y].valor()==color){
							girar=true;
							c=auxcini;
						}
						else if(taula[auxcini.x][auxcini.y].valor()==casella::LLIURE)
							girar=true;	
					}
					else
						girar=true;
				}
			}
		}
		if(not dins_limits(auxcini))
			girar=false;
		if(girar){
			if(taula[auxcini.x][auxcini.y].valor()==casella::LLIURE)
				girar=false;
		}
	}			
			
}


//---- Comprova si es pot posar una fitxa de color a la coordena c:
//---- Cal comprovar si en una de les 8 direccions es poden girar fitxes
//---- de l'adversari (de color diferent al color donat).
bool taulell::mov_possible(coord c, int color) const {
//Pre:la c ha de estar dintre del taulell,color ha de ser un valor correcte(1,-1,0)
//Post:retorna true si es pot possar fitxa a la coordenada i si es necessari girar les fitxes de l'adversari(el color contrari)
        
       
	if(taula[c.x][c.y].valor()==casella::LLIURE){
		direccio auxil;
		auxil.init();
		while(not auxil.is_stop()){
			if(dins_limits(c)){
				bool es_pot;
				coord q;
				es_pot_girar(c,auxil,color,es_pot,q);
				if(es_pot)
					return true;
			}
		++auxil;
		}
	}
	return false;
}


//---- Comprova si el color pot jugar (la fitxa de color es pot col·locar en algun lloc).
bool taulell::pot_jugar(int color) const {
//Pre:color ha de ser un valor correcte(1,-1,0) 	
//Post:retorna true si el color pot posar fitxes
  
  direccio cc;
  cc.init();
  bool b=false;
  for(int i=0;i<taula.size();++i){
	for(int j=0;j<taula.size();++j){
		coord p(i,j);
		if(mov_possible(p,color))
			return true;

  	}
  }
  return false;
 

  
}

int taulell::avalua_posicio() const{
//Pre:cert
//Post:retorna valor segons el protocol de puntuament de la practica

	int puntuacion=0;
	for(int i=0;i<taula.size();++i){						//Inv: i"valor que augmentem a cada iteracio fins a i<taula.size()"	
		for(int j=0;j<taula.size();++j){					//Inv: j"valor que augmentem a cada iteracio fins a j<taula.size()"
			coord auxil(i,j);
			if(i==0){
				
				if(j==0 or j==taula.size()-1){
					puntuacion+=(10*taula[i][j].valor());		
					}
				
				else{	
					puntuacion+=(5*taula[i][j].valor());
				}
				
			}
			else if(i==taula.size()-1){
				if(j==0 or j==taula.size()-1){
					puntuacion+=(10*taula[i][j].valor());
				}
					
				else{
					puntuacion+=(5*taula[i][j].valor());
				}
					
			}
			else if (i!=0 and i!=taula.size()-1){
				if(j==0 or j==taula.size()-1){	
					puntuacion+=(5*taula[i][j].valor());
				}
					
				else{	
					puntuacion+=(1*taula[i][j].valor());
				}
			
			}
					
		}
	}
	return puntuacion;
}
//---- Retorna una cua amb les coordenades a on el color pot jugar.
//---- S'encuen per fila creixent, i per la mateixa fila per columna creixent.
queue<coord> taulell::coord_pot_jugar(int color) const {
//Pre:color ha de ser un valor correcte(1,-1,0)
//Post:retorna una cua amb els valors on es poden posar les fitxes
       
	queue<coord>coords;
	for(unsigned int i=0; i<taula.size(); ++i){			//Inv: j"valor que augmentem a cada iteracio fins a j<taula.size()"
		for(unsigned int j=0; j<taula.size(); ++j){		//Inv: i"valor que augmentem a cada iteracio fins a i<taula.size()"
			coord auxtaula(i,j);
			if(mov_possible(auxtaula,color)){
				coords.push(auxtaula);
			}
			
		}
					
	}
	return coords;
}
	

//---- Canvia el color de les caselles des de la casella ci
//---- fins a la casella cf en+ la direcció d.
void taulell::gira_fitxes(coord ci, coord cf, direccio d) {
//Pre:direccio ha de ser diferent a STOP
//Post:gira les fitxes començcant en la coordenada ci en la direccio d fins la coordenada cf
	  ci=ci+d.despl();
	  int color=taula[ci.x][ci.y].valor();
	  if(dins_limits(ci) and dins_limits(cf)){	
		  while(ci.x!=cf.x or ci.y!=cf.y){		
			taula[ci.x][ci.y].omple(-color);        
			ci=ci+d.despl();
		 }
	 }


}

//---- Col·loca la fitxa de color a la coordena c i gira les fitxes necessàries segons regles d'Otelo
void taulell::posa_fitxa(coord c, int color){
//Pre:color es un valor correcte (1,-1,0)
//Post:el color de la casella que esta a la coordenada c del taulell passa a ser el color passat per copia
	taula[c.x][c.y].omple(color);
	taula[c.x][c.y].marca();
	direccio d;
	d.init();
	bool k;
	coord aux;
	while(not d.is_stop()){
		es_pot_girar(c,d,color,k,aux);
		if(k)
			gira_fitxes(c,aux,d);
		++d;
	}

}
		
