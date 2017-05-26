#ifndef DEF_DEF
#define DEF_DEF

#include "Fonctions.h"
#include "AnalyseFrequentielle.h"

#endif

void CreeTabOccA(gchar TabOcc[],ANALYSE analyse);
void CreeTabOccRL(gchar TabOcc[],RESSOURCESLANGUE ressourcelangue);
void DecryptageSubstitution(gchar TexteClair[],gchar text[],gchar cle[]);
gchar Recherche(ANALYSE a,gchar car,gchar* ch);
gchar Recherche2(RESSOURCESLANGUE a,gchar car,gchar* ch);
ANALYSE remplace(ANALYSE a,gchar car,gchar nvx);
void InitTableau(gchar* TexteClair,gchar TabOccA[],gchar TabOccRL[],gchar cle[]);

gchar RechercheTri(gchar* TexteCrypte,gchar* cle,ANALYSE a,RESSOURCESLANGUE a2, gchar car,gchar car2,gchar* fait); /////////////////////////////
