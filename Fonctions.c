#include "Fonctions.h"


void RetirerCarSpecMajuscule(gchar chaine[], gchar copy[])
{
    int i,j = 0, lg;
    lg = strlen(chaine);
    
    for(i=0; i<lg; i++)
    {	
        if(chaine[i] != ' ' && chaine[i] != '\t' && chaine[i] != '\'') // Si c'ets pas un des ces caractere
        {
            copy[j] = chaine[i];
            
            if(copy[j] > 64 && copy[j] < 91) // Si C'est une majuscule
			{
				copy[j] = chaine[i] + 32;
			}
			
            j++;
        }
    }
    copy[j] = '\0';
}

void RetirerToutCarSpec(gchar chaine[], gchar copy[])
{
    int i,j = 0, lg;
    lg = strlen(chaine);
    
    for(i=0; i<lg; i++)
    {	
        if(chaine[i]>=48 && chaine[i]<=57 || chaine[i]>=97 && chaine[i]<=122) 
        {
            copy[j] = chaine[i];
			
            j++;
        }
    }
    copy[j] = '\0';
}

void ConvertisseurTableau(gchar T[],int *TailleTexte,gchar* Texte){
	
	int i,j=0,doute = 0;
	gchar Tab[strlen(Texte)];
	RetirerCarSpecMajuscule(Texte,Tab);
	int taille = strlen(Tab);
	*TailleTexte = taille;
	
	for(i=0;i<taille;i++){
		gchar c = Tab[i];
		
		if(doute){
			doute = 0;
			if(c == -85 || c == -86 || c == -87 || c == -88){
				T[j] = 'e';
				j++;
			}
			else if(c == -92 || c == -94 || c == -96){
				T[j] = 'a';
				j++;
			}
			else if(c == -68 || c == -69 || c == -71){
				T[j] = 'u';
				j++;
			}
			else if(c == -81 || c == -82){
				T[j] = 'i';
				j++;
			}
			else if(c == -76 || c == -74){
				T[j] = 'o';
				j++;
			}
			else if(c == -89){
				T[j] = 'c';
				j++;
			}
		}
		else{
			doute = c == -61;
			if(doute) continue;
			T[j] = c;
			j++;
		}
	}
	T[j] = '\0';
	 
}


void LireFichier(gchar TexteClaire[] ,int TailleMax ,const gchar* chemin)
{	//TailleMax=1000; //La cest a la baise mais vos mieux faire une variable dynamique
	
	printf("\n%s\n",chemin);
	
	gchar str[TailleMax];
	FILE *charger = fopen(chemin,"r");
	if(charger == NULL) 
   {
      perror("Error opening file");
  
   }
   
   fgets(str, TailleMax, charger);
   strcpy(TexteClaire,str);
 
   while(fgets(str, TailleMax, charger) != NULL){
	   strcat(TexteClaire,str);
  }
  
}


RESSOURCESLANGUE ChargerRessources(){
	

	int i, taille_max=TAILLEFICHIER; //La cest a la baise mais vos mieux faire une variable dynamique
	RESSOURCESLANGUE res;
	gchar str[taille_max];
	
	FILE *charger;
	
	if(langue == 0)
		charger = fopen("RessourceFrancais.txt","r");
	if(langue == 1)
		charger = fopen("RessourceAnglais.txt","r");
		
	if(charger == NULL) 
   {
      perror("Error opening file");
  
   }
	
	//de A à Z
	for(i=0;i<ALPHABET;i++){
		fgets(str, taille_max, charger);
		res.occ[i] = atof(str);
	}

	//Les Digrammes
	for(i=0;i<25;i++){
		fgets(str, taille_max, charger);
		strncpy(res.di[i].nom,str,2);		
		res.di[i].frequence = atoi(strpbrk(str,"0123456789"));
	}
	
	//Les Trigrammes
	for(i=0;i<20;i++){
		fgets(str, taille_max, charger);
		strncpy(res.tr[i].nom,str,3);
		res.tr[i].frequence = atoi(strpbrk(str,"0123456789"));
	}
	
	fclose(charger);
	return res;
}

void RemplacerCleSubstitution(DOUBLEC *Donnees,gchar C1,gchar C2)
{
	
	int i;
	for ( i = 0; i < strlen(Donnees->cle); ++i)
	{
		if (Donnees->cle[i]==C1)
		{
			Donnees->cle[i]=C2;
		}
		else if (Donnees->cle[i]==C2)
		{
			Donnees->cle[i]=C1;
		}
		
		
	}
	
}
