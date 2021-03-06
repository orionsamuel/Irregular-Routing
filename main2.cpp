#include "noc.h"
#include "parameters.h"
#include <iostream>

using namespace std;

int sc_main (int argc, char* argv[]){

	sc_clock clock("Clock", 10, SC_NS);

	NoC rede("NoC");
	rede.clk(clock);

	int coreNumbers;
	char linha[100];
	string temp0;
	string temp1;
	string temp2;
	string temp3;
	int temp00;
	int temp01;
	int temp02;
	int temp03;
	int count;
	int count_flit;

	int mount_flits;

	trafego_rede trafego;

	float deadline_parcial, deadline;
	int total_packets;
	sc_time latencia_parcial, latencia_media;

	ifstream arquivoTrafego, leitura;
	ofstream saidaDados;


	//Instanciamento do arquivo de trafego
	arquivoTrafego.open("teste01.txt", ios_base::in);
	if (arquivoTrafego.is_open()){
		arquivoTrafego.getline(linha, 100);
		coreNumbers = atoi(linha);
		while(arquivoTrafego.getline(linha, 100)){
			temp0 = "";
			temp1 = "";
			temp2 = "";
			temp3 = "";
			for(count = 0; count < 100; count++){
				if(linha[count] != ' '){
					temp0 = temp0 + linha[count];
				}else{
					break;
				}
			}
			temp00 = atoi(temp0.c_str());
			count = count + 1;

			for(; count < 100; count ++){
				if(linha[count] != ' '){
					temp1 = temp1 + linha[count];
				}else{
					break;
				}
			}
			temp01 = atoi(temp1.c_str());
			count = count + 1;

			for(; count < 100; count ++){
				if(linha[count] != ' '){
					temp2 = temp2 + linha[count];
				}else{
					break;
				}
			}
			temp02 = atoi(temp2.c_str());
			count = count + 1;

			for(; count < 100; count ++){
				if(linha[count] != ' '){
					temp3 = temp3 + linha[count];
				}else{
					break;
				}
			}
			temp03 = atoi(temp3.c_str());

			trafego.push_back({temp00, temp01, temp02, temp03});
		}
	}

	arquivoTrafego.close();



	rede.coreNumbers = coreNumbers;
	rede.trafego = trafego;


	for(int i = 0; i < coreNumbers; i++){
		rede.rt[i]->position = i + 1;
	}


	for(int i = 0; i < trafego.size(); i++){
		mount_flits = mount_flits + (trafego[i].pacotes * 5);
	}

	flits dados[mount_flits];

	rede.mount_flits = mount_flits;

	for(int i = 0; i < trafego.size(); i++){
		for(int j = 0; j < trafego[i].pacotes; j++){
			for(int k = 0; k < 5; k++){
				int diferenca = trafego[i].destino - trafego[i].origem;
				if((diferenca > 0) && (trafego[i].origem < trafego[i].destino)){
					for(int m = 0; m < (diferenca + 1); m++){
						dados[count_flit].caminho.push(trafego[i].origem + m);
					}
				}if((diferenca < 0) && (trafego[i].origem > trafego[i].destino)){
					diferenca = diferenca * (-1);
					int sub = 0;
					for(int m = (diferenca + 1); m > 0; m--){
						dados[count_flit].caminho.push(trafego[i].origem + sub);
						sub--;
					}
				}
				count_flit++;
			}
		}
	}

	//rede.dados = dados;
	for(int i = 0; i < mount_flits; i++){
		rede.dados[i] = dados[i];
	}
	

	sc_start(trafego[1].deadline, SC_NS);

	//Calculo dos pacotes que chegaram ao destino
	for(int i = 0; i < trafego.size(); i++){
		total_packets = total_packets + trafego[i].pacotes;
	}

	for(int i = 0; i < coreNumbers; i++){
		deadline_parcial = deadline_parcial + rede.rt[i]->count;
	}
	
	for(int i = 0; i < coreNumbers; i++){
		latencia_parcial = latencia_parcial + rede.rt[i]->latencia_rt;
	}

	deadline = (deadline_parcial * 100) / total_packets;
	latencia_media = (latencia_parcial / total_packets) * 1000;

	saidaDados.open("saida_simulacao.txt");
	saidaDados << deadline << endl;
	saidaDados << latencia_media;
	saidaDados.close();

	cout << rede.rt[0]->out_port[4].payload << endl;
	cout << rede.rt[1]->out_port[4].payload << endl;
	cout << rede.rt[2]->out_port[4].payload << endl;
	cout << rede.rt[3]->out_port[4].payload << endl;
}