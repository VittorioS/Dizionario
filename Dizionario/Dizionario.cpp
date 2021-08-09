// Dizionario.cpp : definisce il punto di ingresso dell'applicazione console.
//
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "Dizionario.h"
#include <stdbool.h>
#include <string.h>


tipo_parola parole[MAX_DIZIONARIO];
tipo_dizionario Dizionario;

//void init_parola(tipo_parola parola) {
//	parola.significato = (char*) malloc(MAX_LUNGHEZZA_SIGNIFICATO * sizeof(parola.significato));
//	parola.contrari = (tipo_parola*) malloc(MAX_CONTRARI * sizeof(parola.contrari));
//}

tipo_parola crea_parola(char termine[], char significato[]) {
	tipo_parola parola;
	parola.parola_base.significato = significato;
	parola.parola_base.termine = termine;
	for (int i = 0; i < MAX_CONTRARI; i++)
	{
		parola.contrari[i].termine = "";
		parola.contrari[i].significato = "";
	}	
	parola.count_contrari = 0;
	return parola;
}

void clear_dizionario() {
	
	for (int i = 0; i < MAX_DIZIONARIO; i++)
	{
		//Dizionario.parole[i].parola_base.termine = "";
		//Dizionario.parole[i].parola_base.significato = "";
	}
}

void collega_contrario(tipo_parola &parola, tipo_parola &contrario) {
	parola.contrari[parola.count_contrari] = contrario.parola_base;
	contrario.contrari[contrario.count_contrari] = parola.parola_base;
	parola.count_contrari++;
	contrario.count_contrari++;
}

void aggiungi_parola(tipo_parola parola) {
	Dizionario.parole[Dizionario.indice] = parola;
	Dizionario.indice++;
}

bool cerca_parola(char termine[], tipo_parola &parola_trovata) {
	bool risultato = false;
	for (int i = 0; i < Dizionario.indice; i++)
	{	
		if (strcmp(Dizionario.parole[i].parola_base.termine, termine) == 0) {
			risultato = true;
			parola_trovata = Dizionario.parole[i];
		}
	}
	return risultato;
}

void split_frase(char *frase, int &lunghezza, char *risultato[]) {
	char *token;
	token = strtok(frase, " ");
	do
	{
		risultato[lunghezza] = token;
		lunghezza++;
		token = strtok(NULL, " ");
	} while (token != NULL);
}

void scelta_contrari(char frase[], char risultato[]) {
	tipo_parola parola_trovata;
	int lunghezza = 0;
	char *frase_divisa[123];
	
	split_frase(frase, lunghezza, frase_divisa);

	strcpy(risultato, "");

	for (int i = 0; i < lunghezza; i++)
	{
		if (cerca_parola(frase_divisa[i], parola_trovata) == true) {
			strcat(risultato, parola_trovata.contrari[0].termine);
		}
		else {
			strcat(risultato, frase_divisa[i]);
		}

		
		strcat(risultato, " ");
	}
}


//using namespace std;

void write_parola(tipo_parola parola) {
	printf("Termine: %s\n", parola.parola_base.termine);
	printf("Significato: %s\n", parola.parola_base.significato);
}


int main()
{	
	clear_dizionario();

	parole[0] = crea_parola("bello", "Significato Bello");
	parole[1] = crea_parola("brutto", "Significato Brutto");
	parole[2] = crea_parola("buono", "Significato Buono");
	parole[3] = crea_parola("cattivo", "Significato Cattivo");
	parole[4] = crea_parola("basso", "Significato Basso");
	parole[5] = crea_parola("alto", "Significato Alto");

	collega_contrario(parole[0], parole[1]);
	collega_contrario(parole[2], parole[3]);
	collega_contrario(parole[4], parole[5]);

	for (int i = 0; i < MAX_PAROLE; i++)
	{
		aggiungi_parola(parole[i]);
	}

	char opzione[2];
	char input[1000];
	do
	{
		system("CLS");
		printf("/////////////////////////////////////////\n");
		printf("/////////////////////////////////////////\n");
		printf("//////////////DIZIONARIO/////////////////\n");
		printf("/////////////////////////////////////////\n");
		printf("/////////////////////////////////////////\n");
		printf("Scegli una operazione\n");
		printf("1. Cerca il contrario di una parola\n");
		printf("2. Sostituisci i contrari in una frase\n");
		printf("Scegli una operazione: ");
		fflush(stdin);
		gets_s(opzione);
		char vettore[100];
		//opzione[0] = '2';
		switch (opzione[0])
		{
			case '1':
				tipo_parola parola_trovata;
				printf("Inserire termine: ");
				fflush(stdin);
				gets_s(input);
				if (cerca_parola(input, parola_trovata) == true) {
					write_parola(parola_trovata);
				}
				else {
					printf("Errore");
				}
				break;
			case '2':
				printf("Inserire una frase: ");
				fflush(stdin);
				gets_s(input);
				//strcpy(input, "ciao ciao bello ciao ciao");
				scelta_contrari(input, vettore);
				printf("%s", vettore);

				break;
			default:	
				printf("Errore");
				break;
		}

		printf("\n");
		system("PAUSE");
	} while (opzione[0] != '3');
    return 0;
}

