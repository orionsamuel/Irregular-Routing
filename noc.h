#include "systemc.h"
#include <iostream>
#include "router.h"
#include "parameters.h"


SC_MODULE(NoC){

	sc_in<bool> clk;

	int coreNumbers;

	trafego_rede trafego;

	router *rt[25];

	int mount_flits;

	int count_flit;

	flits dados[40];



	void chaveamento_externo();

	void calcula_flits();

	void set_packets();


	SC_CTOR(NoC){
		cout << mount_flits << endl;
		//dados = new flits[mount_flits];
		for(int i = 0; i < 25; i++){
			rt[i] = new router("rt");
			rt[i]->clk(clk);
		}

		SC_METHOD(chaveamento_externo);
		sensitive << clk.pos();
		SC_METHOD(calcula_flits);
		sensitive << clk.pos();
		SC_CTHREAD(set_packets, clk.pos());
	}
};