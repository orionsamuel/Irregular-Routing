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



	int tableAcess(){
		if((this->destiny > this->position) && (this->position == 1)){
				this->portDestiny = NORTH;
			}else if((this->destiny > this->position) && ((this->position % 2) == 1)){
				this->portDestiny = NORTH;
			}else if((this->destiny > this->position) && ((this->position % 2) == 0)){
				this->portDestiny = EAST;
			}else if((this->destiny < this->position) && ((this->position % 2) == 1)){
				this->portDestiny = SOUTH;
			}else if((this->destiny < this->position) && ((this->position % 2) == 0)){
				this->portDestiny = WEST;
			}
		return this->portDestiny;
	}


	routing(){

    }
};


#endif // ROUTING_H_INCLUDED
