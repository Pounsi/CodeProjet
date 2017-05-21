#include "DecryptageSubstitution.h"

void DecryptageSubstitution(gchar* TexteClair,gchar* text,gchar* cle)
{

}

//~ RESSOURCESLANGUE TabRessource(){ //changer de module
	//~ RESSOURCESLANGUE Ressource;
	//~ FILE* fichier=NULL;
	//~ int nbr;
	
	//~ if(langue == 0){  //en Francais
		//~ fichier = fopen("TabRessourceFrancais.txt", "r");
		//~ while(nbr<26){
			//~ fscanf(fichier,"%f", Ressource.occ[nbr]);	
			//~ nbr++;
		//~ }
		//~ nbr=0;
		//~ while(nbr<26){
			//~ fscanf(fichier,"%c %d",Ressource.di[nbr].nom,Ressource.di[nbr].frequence);		//fonction pou gchar?
			//~ nbr++;
		//~ }
		
		//~ nbr=0;
		//~ while(nbr<26){
			//~ fscanf(fichier,"%c %d",Ressource.tr[nbr].nom,Ressource.tr[nbr].frequence);		//fonction pou gchar?
			//~ nbr++;
		//~ }
		
		//~ fclose(fichier);
	//~ }
	
	//~ if(langue == 1){  //en Anglais
		//~ fichier = fopen("TabRessourceAnglais.txt", "r");
				//~ while(nbr<26){
			//~ fsanf(fichier,"%f" Ressource.occ[nbr]);	
			//~ nbr++;
		//~ }
		//~ nbr=0;
		//~ while(nbr<26){
			//~ fsanf(fichier,"%c %d",Ressource.di[nbr].nom,Ressource.di[nbr].frequence);		//fonction pou gchar?
			//~ nbr++;
		//~ }
		//~ nbr=0;
		//~ while(nbr<26){
			//~ fsanf(fichier,"%c %d",Ressource.tr[nbr].nom,Ressource.tr[nbr].frequence);		//fonction pou gchar?
			//~ nbr++;
		//~ }
		//~ fclose(fichier);
	//~ }
	//~ return Ressource;
//~ }
	

//~ void VerificationCoherenceDigrammeTrigramme(gchar T[], int TailleTexte, gchar clef[], int TailleAlphabet, RESSOURCESLANGUE Ressource){
	//~ int parcoureTexte=0; //entier parcourant le texte
	//~ int anomalie=0; //entier verifiant si un digramme est anormal (1 si anormal 0 si normal)
	//~ int testDigramme=0; //compteur qui vas tester les 25 digrammes les plus connu de la langue
	//~ gchar* digrammeTeste; //initialisation d'une chaine de caractère pour stocker le digramme testé
	
	//~ while(parcoureTexte < TailleTexte){
		
		//~ //verification si digramme en texte clair (boucle, si crypté parcoureTexte++sinon sortir de la boucle , si pas de digramme disponible passer se qui suit)
		
		//~ anomalie=1; //anomalie fixé à 1 puis on regarde si le digramme est répértorier dans la liste des digramme utilisée.
		
		//~ while(testDigramme<25){
		
			//~ //fonction prenant Deux caractère du tableau et les met sous forme de chaine de caractère
		
			//~ if(digrammeTeste == Ressource.di[testDigramme].nom){					//teste de normalité
			//~ anomalie=0;
			//~ testDigramme=26; //test valide on met fin a la boucle
			//~ }
			
			//~ testDigramme++;
		//~ }
		
		//~ if(anomalie==1){
			
			//~ // fonction de correction (while(anomlie==1))
			
			//~ //MenuResultatDecyptagePartiel(???????????????????????)
			//~ }
			
		//~ parcoureTexte++;
	//~ }
//~ }

//~ void DecryptageSub(gchar* texteCrypte){
	//~ RESSOURCESLANGUE langue; // structure qui vas contenir les frequences de la langue choisi
	//~ ANALYSE texte;	// structure qui vas contenir les frequences du texte
	
	//~ langue = TabRessource();  // remplie la structure 
	//~ texte = AnalyseFrequentielle(texteCrypte); //remplie la structure 
	
	//~ gchar TCRYPT[texte.nb];
	//~ ConvertisseurTableau(TCRYPT[], texte.nb, texteCrypte);
	
	//~ char TCLEF[25];	//Tableau qui vas contenir la clef de substitution
	//~ int nbrChangement=0; //nbr de lettres qui on était modifié par la fonction et qui vons servir de compteur pour la boucle
	//~ while(nbrChangement < 26){
		
		//~ //ici fonction de comparaison des deux structures
		
		
		//~ VerificationCoherenceDigrammeTrigramme(TCRYPT[],texte.nb,TCLEF[],25,langue);
		//~ nbrChangement++;	
	//~ }
	
//~ }
	
