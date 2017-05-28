#ifndef DEF_DEF
#define DEF_DEF

#include "Fonctions.h"
#include "AnalyseFrequentielle.h"

#endif

void CreeTabOccA(gchar TabOcc[],ANALYSE analyseTexte);
void CreeTabOccRL(gchar TabOcc[],RESSOURCESLANGUE ressourceLangue);
void DecryptageSubstitution(gchar TexteDecrypte[],gchar TexteCrypte[],gchar cle[]);
gchar RechercheAnalyse(ANALYSE a,gchar car,gchar* fait);
gchar RechercheRessources(RESSOURCESLANGUE a,gchar car,gchar* fait);
ANALYSE Remplace(ANALYSE a,gchar car,gchar nvx);
void InitTableau(gchar* TexteClair,gchar TabOccA[],gchar TabOccRL[],gchar cle[]);

gchar RechercheTri(gchar* TexteCrypte,gchar* cle,ANALYSE a,RESSOURCESLANGUE a2, gchar car,gchar car2,gchar* fait);
