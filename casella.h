//----  La classe "casella" guarda la informació de les caselles del taulell
//----  És una classe privada a la que no es pot accedir (ni cal) des del
//----  programa. La informació sobre les caselles d'un taulell s'obté 
//----  a través de les operacions de la classe "taulell".

class casella {
  private:
    // Atribut on guardar el contingut de la casella 
    int color;
    // Atribut per saber si la casella esta marcada com a visitada
    bool visitada;

  public:
    // Possibles continguts de les caselles
    static const int BLANCA=1;
    static const int NEGRA=-1;
    static const int LLIURE=0;

    //---- Crea una casella amb valor inicial LLIURE.
    casella();
    //Pre:cert
    //Post: crea una nova casella lliure sense visitar

    //---- Modifica el color de la casella.
    void omple(int x);
    //Pre:x ha de ser 1,-1 o 0
    //Post: omple la casella amb el valor x
    //---- Marca la casella com a visitada.
    void marca();
    //Pre: cert
    //Post: la casella esta marcada
    //---- Desmarca la casella (no visitada). 
    void desmarca();
    //Pre:cert
    //Post: la casella passa a estar desmarcada

    //---- Obté el contingut (valor) de la casella.
    int valor() const;
    //Pre: cert
    //Post: retorna el color de la casella
    //---- Obté el caràcter de la casella a dibuxar:
    //---- BLANCA -> B, NEGRA -> N, LLIURE -> -
    char mostra() const;
    //Pre: cert
    //Post: retorna el caracter corresponent al color
    //---- Consulta si la casella esta marcada com visitada.
    bool es_visitada() const;
    //Pre:cert
    //Post: retorna true si esta visitada, false si no ho esta
};

