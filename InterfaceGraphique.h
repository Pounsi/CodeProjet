#ifndef DEF_DEF
#define DEF_DEF

#include "Fonctions.h"
#include "CryptageVigenere.h"
#include "CryptageSubstitution.h"
#include "DecryptageSubstitution.h"
#include "DecryptageVigenere.h"
#include "AnalyseFrequentielle.h"


#endif




//dans un autre fichier
void Enregistrer (GtkWidget *p_widget, GtkWidget *text );
void RecupererChemin(GtkWidget *bouton, GtkWidget *selection);
void ChoisirFichier();
//interface
void ViderContenaire(GtkContainer * container);
void MenuResultatSubstitution(GtkWidget *Fenetre, DOUBLEC *Donnees);
void MenuResultatVigenere(GtkWidget *Fenetre, gchar* Text_crypt, gchar* cle);
void MenuResultatAnalyse(GtkWidget *Fenetre, ANALYSE analyse);
void MenuResultatDecryptageSubstitution(GtkWidget *Fenetre, DOUBLEC* Donnees);
void MenuResultatDecryptageVigenere(GtkWidget *Fenetre, gchar* Text_crypt , gchar* cle);
void BoiteDialogueSubstitution(GtkWidget *Fenetre);
void BoiteDialogueVigenereCle(GtkWidget *Fenetre);
void BoiteDialogueVigenereTexte(GtkWidget *Fenetre, DOUBLEC *Donnees);
void BoiteDialogueAnalyse(GtkWidget *Fenetre);
void BoiteDialogueDecryptageSubstitution(GtkWidget *Fenetre);
void BoiteDialogueDecryptageVigenere(GtkWidget *Fenetre);
void MenuDecryptageVigenere(GtkWidget *Fenetre);
void MenuDecryptageSubstitution(GtkWidget *Fenetre);
void MenuCryptageVigenere(GtkWidget *Fenetre,DOUBLEC *Donnees);
void MenuCryptageSubstitution(GtkWidget *Fenetre);
void MenuAnalyseFrequentielle(GtkWidget *Fenetre);
void MenuDecryptage(GtkWidget *Fenetre);
void MenuCryptage(GtkWidget *Fenetre);
void MenuPrincipal(GtkWidget *Fenetre);
void MenuResultatDecryptagePartiel(GtkWidget *Fenetre,DOUBLEC* Donnees);
void BoiteDialogueChangerLaCleSubstitution(GtkWidget *Fenetre,DOUBLEC *Donnees);
