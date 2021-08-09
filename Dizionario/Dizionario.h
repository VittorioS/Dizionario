#pragma once

#define MAX_LUNGHEZZA_SIGNIFICATO 500
#define MAX_CONTRARI 5
#define MAX_DIZIONARIO 100
#define MAX_PAROLE 6
#define MAX_LUNGHEZZA_TERMINE 50
struct base_parola
{
	char *termine;
	char *significato;
};
typedef base_parola tipo_base_parola;
struct parola {
	tipo_base_parola parola_base;
	int count_contrari;
	tipo_base_parola contrari[MAX_CONTRARI];
};
typedef parola tipo_parola;

struct dizionario {
	int indice;
	tipo_parola parole[MAX_DIZIONARIO];
};
typedef dizionario tipo_dizionario;

tipo_parola crea_parola(char termine[], char significato[]);

void clear_dizionario();

void collega_contrario(tipo_parola & parola, tipo_parola & contrario);

bool cerca_parola(char termine[], tipo_parola & parola_trovata);

void split_frase(char * frase, int & lunghezza, char * risultato[]);

void scelta_contrari(char frase[], char risultato[]);

void write_parola(tipo_parola parola);
