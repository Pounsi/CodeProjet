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
        if(chaine[i]>=97 && chaine[i]<=122) 
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
	RetirerToutCarSpec(T,T);
	T[j] = '\0';

	 
}


void LireFichier(gchar TexteClaire[] ,int TailleMax ,const gchar* chemin)
{	//TailleMax=1000; //La cest a la baise mais vos mieux faire une variable dynamique

	
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

ANALYSE tri(ANALYSE a)
{ 
int i, min, j , tmp;
char tmp_di[2];
char tmp_di2[3];

for (i =0; i <a.nbdi; i++)
{
	min = i; 
	for (j = i+1; j < a.nbdi ; j++) 
	if(a.di[j].frequence > a.di[min].frequence)
	min = j; 
	
	
	if (min != i){
		//echanger occurences digrammes(l'entier de frequence)
tmp = a.di[i].frequence;
a.di[i].frequence = a.di[min].frequence;
a.di[min].frequence = tmp;

//echanger nom digrammes(le char*)
strcpy(tmp_di,a.di[i].nom);
strcpy(a.di[i].nom,a.di[min].nom);
strcpy(a.di[min].nom, tmp_di);
				}
}

/////////////////////////////////// trigrammes tri
for (i =0; i <a.nbtr; i++)
{
	min = i; 
	for (j = i+1; j < a.nbtr ; j++) {
	if(a.tr[j].frequence > a.tr[min].frequence){
	printf("%d > %d \n",a.tr[j].frequence , a.tr[min].frequence);
	min = j; }
	}
	
	
	if (min != i){
		//echanger occurences digrammes(l'entier de frequence)
tmp = a.tr[i].frequence;
a.tr[i].frequence = a.tr[min].frequence;
a.tr[min].frequence = tmp;

//echanger nom digrammes(le char*)
printf("on inverse %s et %s\n",a.tr[min].nom,a.tr[i].nom);
//strcpy(tmp_di2,a.tr[i].nom);
//strcpy(a.tr[i].nom,a.tr[min].nom);
//strcpy(a.tr[min].nom, tmp_di2);
char c;
int k;
for (k = 0; k < 3; k++)
{
	c=a.tr[i].nom[k];
	a.tr[i].nom[k] = a.tr[min].nom[k];
	a.tr[min].nom[k]=c;
}



printf("on inverse %s et %s\n",a.tr[min].nom,a.tr[i].nom);
				}
				printf("on a %s\n",a.tr[0].nom);
printf("on a %s\n",a.tr[1].nom);
printf("on a %s\n",a.tr[2].nom);
printf("on a %s\n",a.tr[3].nom);
}


return a;
}


void RetourALaLigne(gchar output[],gchar input[])
{
	int i,j,ligne;
	char info[100]="Pour lire le contenu en entier veuilliez enregistrer votre document";
	i=0;
	j=0;
	ligne=0;
	while(input[i-j]!='\0' && ligne<7)
	{
		if (i%40==0 && i!=0 && output[i]!='\n')
		{
			
			output[i]='\n';
			j++;
			ligne++;
			
		}
		else
		{
			output[i]=input[i-j];
		}

		i++;
		
	}
	
	output[i]='\n';
	i++;
	output[i]='\n';
	i++;
	output[i]='\0';
	if (ligne==7)
	{
		strcat(output,info);
	}

}

void DechiffreSubstitution(gchar text[],gchar cle[])
{
	int i,j;
	gchar tmp[TAILLETEXTE];
	strcpy(tmp,text);
	for (i = 0; i < strlen(cle); ++i)
	{
		for (j = 0; j < strlen(text); ++j)
		{
			if (tmp[j]-97==i)
			{
				text[j]=cle[i];
				
			}
		}
	}
}
