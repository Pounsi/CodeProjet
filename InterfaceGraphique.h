#ifndef DEF_DEF
#define DEF_DEF

#include "Fonctions.h"
#include "CryptageVigenere.h"
#include "CryptageSubstitution.h"
#include "DecryptageSubstitution.h"
#include "DecryptageVigenere.h"
#include "AnalyseFrequentielle.h"


#endif

typedef struct doublechar{
	gchar texte[TAILLETEXTE];
	gchar cle[TAILLECLE];
}DOUBLEC;


//dans un autre fichier
void Enregistrer (GtkWidget *p_widget, GtkWidget *text );
void RecupererChemin(GtkWidget *bouton, GtkWidget *file_selection);
void ChoisirFichier();
//interface
void ViderContenaire(GtkContainer * container);
void MenuResultatSubstitution(GtkWidget *Fenetre, gchar* Text_crypt);
void MenuResultatVigenere(GtkWidget *Fenetre, gchar* Text_crypt, gchar* cle);
void MenuResultatAnalyse(GtkWidget *Fenetre, gchar* Texte);
void MenuResultatDecryptageSubstitution(GtkWidget *Fenetre, gchar* Cle_et_text_clair);
void MenuResultatDecryptageVigenere(GtkWidget *Fenetre, gchar* Text_crypt , gchar* cle);
void BoiteDialogueSubstitution(GtkWidget *Fenetre);
void BoiteDialogueVigenere(GtkWidget *Fenetre);
void BoiteDialogueAnalyse(GtkWidget *Fenetre);
void BoiteDialogueDecryptageSubstitution(GtkWidget *Fenetre);
void BoiteDialogueDecryptageVigenere(GtkWidget *Fenetre);
void MenuDecryptageVigenere(GtkWidget *Fenetre);
void MenuDecryptageSubstitution(GtkWidget *Fenetre);
void MenuCryptageVigenere(GtkWidget *Fenetre);
void MenuCryptageSubstitution(GtkWidget *Fenetre);
void MenuAnalyseFrequentielle(GtkWidget *Fenetre);
void MenuDecryptage(GtkWidget *Fenetre);
void MenuCryptage(GtkWidget *Fenetre);
void MenuPrincipal(GtkWidget *Fenetre);
void MenuResultatDecryptagePartiel(GtkWidget *Fenetre,DOUBLEC* ch);
