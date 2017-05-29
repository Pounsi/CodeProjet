#include "../Headers/DecryptageVigenere.h"

int pgcd(int a, int b)
{
  int r;
  while (b != 0){
      r = a%b;
      a = b;
      b = r;
    }
  return a;
}

//Estimation de la taille de la clé
int Kasiski(ANALYSE a, gchar* texteCrypte){

	int i,j,x,taillepgor,nbrpgor;
	int kas[TR_A_TESTER];
	int distance[10];
	static int numeroessai = 0;
	int kasiski=0;
	
	if(numeroessai == 0){ //correspond au premier clic de l'utilisateur (estimation automatique de la clé)
		for(x=0;x<TR_A_TESTER;x++){//nbr de pgor		
			taillepgor = strlen(a.tr[x].nom);
			nbrpgor = 0;
			for (i = 0; i < strlen(texteCrypte); i++)
			{
				for (j = 0; j < taillepgor; j++)
				{
					if(a.tr[x].nom[j] == texteCrypte[i]){ //On cherche les trigrammes 
						if(j == taillepgor-1){
							distance[nbrpgor] = (i-(taillepgor-1)); 
							nbrpgor++;
						}
					i++;
					}
					else if(texteCrypte[i] == a.tr[x].nom[0]){
						j=0;
						i++;
					}
					else break;
				}	
			}
			kas[x] = distance[0];
				for (i = 0; i < nbrpgor; i++){
					kas[x] = pgcd(kas[x],distance[i]);	// PGCD(a,b,c) =  PGCD(PGCD(a,b),c)
				}
		}
		
	int kasiski=0;
		for (i = 0; i < TR_A_TESTER; i++)
		{
			if(kas[i] != 1){ //si kasiski vaut 1 on ne le sauvegarde pas
				kasiski = kas[i]; //on stocke les différentes hypothèses de la clé dans kas[i]
				break;
			}
		}
		for (i = 0; i < TR_A_TESTER; i++){ //On retient la plus grande estimation (améliorable avec un test statistique sur les indices de coincidences de chaque caractères du mot clé)
		if(kas[i]>kasiski)
			kasiski = kas[i];
		}
	if(!kasiski) return 2;  //Permet de borner la recherche de clé de 2 a 24
	if(kasiski > 24) return 2; //Permet de borner la recherche de clé de 2 a 24
	numeroessai++;//compteur de clic
	return kasiski;
}
	else{	//correspond au 2eme ou plus clics de l'utilisateur (estimation manuel :taille de la clé)
		if(numeroessai > 24){
			numeroessai=numeroessai%24;
		}
		kasiski = numeroessai;
		numeroessai++;//compteur de clic
	return kasiski;
	}
}

//Estimation des caractères composant le mot clé	
void indiceMutuelle(int cle[], int kasiski, ANALYSE freq, RESSOURCESLANGUE prob, gchar safecle[]){ 
	
	float mg[kasiski][ALPHABET];
	int w; // w = n/m
	int i,j,g;
	double VraiIndice;
	
	for (j = 0; j < kasiski; j++){	//initialisations du tableau a double entrée
		for (i = 0; i < ALPHABET; i++){
			mg[j][i]=0;
		}	
	}
	
	w = freq.nb/kasiski;
	for (j = 0; j < kasiski; j++){ //Ici, remplissage tableau double entrée avec les indices de coincidences
		for (g = 0; g < ALPHABET; g++){
			for (i = 0; i < ALPHABET; i++){	
				mg[j][g] = mg[j][g] + ((prob.occ[i] * freq.occ[j][(i+g)%26])/w);
			}	
		}
	}
	for(j=0;j<kasiski;j++){   //ici on selectionne la valeurs de chaque ligne la plus proche de 0.065 (Peut être remplacer par 1 pour debug)
		
		VraiIndice	= 2;//on initialise a une grande valeur pour être sur que la premiere valeur du tableau soit affecter a Vraiindice
		for (i = 0; i < ALPHABET; i++){
			if(fabs(mg[j][i] - 1) < VraiIndice){
				VraiIndice = fabs(mg[j][i] - 1);
					cle[j] = i; 		
			}
		}		
	}		
	for (i = 0; i <kasiski ; i++){
		safecle[i] = cle[i] + 97;	
	}
	safecle[i] = '\0';
}

//Utilisation cyclique de la clé pour décrypter le texte 
void Decrypte(char resultat[],char* texteCrypte,gchar cle[], int kasiski){
	
   int a,b,c,i,taille;
   taille = strlen(texteCrypte); //affectation du nombre de caractère du texte a taille
   
	for ( i = 0; i < taille ; i++){
		a= texteCrypte[i] - 97;
		b= cle[i%kasiski] - 97; // %kasiski pour pouvoir itérer de facon cyclique
		c = a-b ;				//on soustrait la valeur du caractère du mot clé a la valeur du caractère du texte crypté
		if(c < 0)
			c=c+26;
		resultat[i] = c + 97;
	}
	resultat[i] = '\0';
}

//Fonction principale du module
void DecryptageVigenere(gchar* TexteDecrypte, gchar* TexteCrypte, gchar savecle[]){
	
	RESSOURCESLANGUE don;
	ANALYSE req;
	int kasiski,taille;
	gchar TexteC[strlen(TexteCrypte)];
	gchar SauvegardeCle[TAILLECLE];
	
	ConvertisseurTableau(TexteC,&taille,TexteCrypte);
	RetirerToutCarSpec(TexteC,TexteC);
	don = ChargerRessources();  // remplie la structure avec les proba de la langue choisi.
	req = AnalyseFrequentielle(TexteC); //remplie la structure avec les fréquences du texte
	req = tri(req);
	
	kasiski = Kasiski(req, TexteC); //recupere le PGOR (ou tri) et le texte clair, retourne taille cle	
	req = AnalyseFreq(req,TexteC,kasiski); //remplie la structure avec les fréquences du texte

	int cle[kasiski]; //declaration d'une tableau d'entier de la taille la clé
	indiceMutuelle(cle, kasiski, req, don, SauvegardeCle); 
	strcpy(savecle,SauvegardeCle);
	
	Decrypte(TexteDecrypte, TexteC, SauvegardeCle, kasiski);

}
