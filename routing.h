#ifndef ROUTING_H_INCLUDED
#define ROUTING_H_INCLUDED
#include "parameters.h"
#include <iostream>

using namespace std;

class routing{
public:
	int position;
	int destiny; //Entra o endereço do roteador destino
	int portDestiny; //Retorna a porta por onde o pacote deve passar



	int saida_routing(){
		if((destiny > position) && (position == 1)){
				this->portDestiny = NORTH;
			}else if((destiny > position) && ((position % 2) == 1)){
				this->portDestiny = NORTH;
			}else if((destiny > position) && ((position % 2) == 0)){
				this->portDestiny = EAST;
			}else if((destiny < position) && ((position % 2) == 1)){
				this->portDestiny = WEST;
			}else if((destiny < position) && ((position % 2) == 0)){
				this->portDestiny = SOUTH;
			}
		return this->portDestiny;
	}


	routing(){

    }
};


#endif // ROUTING_H_INCLUDED
