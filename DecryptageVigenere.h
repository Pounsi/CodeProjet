#ifndef DEF_DEF
#define DEF_DEF

#include "Fonctions.h"
#include "AnalyseFrequentielle.h"

#endif

int pgcd(int a, int b);
int Kasiski(ANALYSE a, gchar* texteCrypte);
void indiceMutuelle(int cle[], int kasiski, ANALYSE freq, RESSOURCESLANGUE prob, gchar safecle[]);
void Decrypte(char resultat[],char* texteCrypte,gchar cle[], int kasiski);
void DecryptageVigenere(gchar* TexteDecrypte, gchar* TexteCrypte,gchar savecle[]);
