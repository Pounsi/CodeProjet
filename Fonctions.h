#ifndef DEF_DEF
#define DEF_DEF
	

#endif

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <time.h>
#include <tgmath.h>

#define TAILLEFICHIER 1000
#define TAILLETEXTE 20000
#define TAILLECLE 26
#define ALPHABET 26
#define hauteur 500
#define largeur 500

int langue;
int choix;

GtkWidget *Fenetre;

typedef struct phoneme{
	int frequence;
	gchar nom[5];
}PHONEME;
typedef struct analyse{ //fréquence
	int nb; 
	float occ[TAILLECLE][ALPHABET];
	PHONEME di[TAILLETEXTE-1]; 
	PHONEME tr[TAILLETEXTE-2];
	int nbdi;
	int nbtr;
	gchar pgor[3];
}ANALYSE;
typedef struct ressourceslangue{ //probabilité
	float occ[ALPHABET];
	PHONEME di[25];
	PHONEME tr[25];
}RESSOURCESLANGUE;
typedef struct doublechar{
	gchar texte[TAILLETEXTE];
	gchar cle[TAILLECLE];
}DOUBLEC;


void RetirerToutCarSpec(gchar chaine[], gchar copy[]);
void RetirerCarSpecMajuscule(gchar chaine[], gchar copy[]);
void LireFichier(gchar TexteClaire[] ,int TailleMax ,const gchar* chemin);
void ConvertisseurTableau(gchar T[],int *TailleTexte,gchar* Texte);
RESSOURCESLANGUE ChargerRessources();
void RemplacerCleSubstitution(DOUBLEC *Donnees,gchar C1,gchar C2);
ANALYSE tri(ANALYSE a);	
