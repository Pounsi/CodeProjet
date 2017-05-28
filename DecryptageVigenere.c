#include "DecryptageVigenere.h"

int pgcd(int a, int b)
{
  int r;
  while (b != 0)
    {
      r = a%b;
      a = b;
      b = r;
    }
  return a;
}

int Kasiski(ANALYSE a, gchar* texteCrypte){

	int i,j,x,taillepgor;
	int kas[TR_A_TESTER];
	int nbrpgor;
	int distance[10];
	static int numeroessai = 0;
	int kasiski=0;
	
	if(numeroessai == 0){
	for(x=0;x<TR_A_TESTER;x++){//nbr de pgor
		//printf("\n tri[%d] = %s freq = %d",x,a.tr[x].nom,a.tr[x].frequence);
		
		taillepgor = strlen(a.tr[x].nom);
		nbrpgor = 0;
		
		for (i = 0; i < strlen(texteCrypte); i++)
		{
			for (j = 0; j < taillepgor; j++)
			{
				if(a.tr[x].nom[j] == texteCrypte[i]){
					if(j == taillepgor-1){
						distance[nbrpgor] = (i-(taillepgor-1)); // numeroessai est itéré a chaque appel de la fonction (premier appel il vaut 0, deuxieme appel il vaut 1)
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
		
		//printf("\n decalage %d\n",decalage);
		
		kas[x] = distance[0];
		for (i = 0; i < nbrpgor; i++)
		{
			kas[x] = pgcd(kas[x],distance[i]);
		}
		
		for (i = 0; i < nbrpgor; i++)
		{
			//printf("\ndistance[%d] = %d",i,distance[i]);
		}
	}
	
	int kasiski=0;
	for (i = 0; i < TR_A_TESTER; i++)
	{
		if(kas[i] != 1){
			kasiski = kas[i];
			break;
		}
	}
	
	for (i = 0; i < TR_A_TESTER; i++)
	{
		if(kas[i]>kasiski)
			kasiski = kas[i];
	}
		
			
	if(!kasiski) return 2;
	if(kasiski > 12) return 2;
	for (i = 0; i < TR_A_TESTER; i++)
	{
			//printf("\nkas[%d] = %d",i,kas[i]);
	}
	numeroessai++;
	return kasiski;
	
}
else{
	//printf(" \n numero essai vallait = %d pendant execution \n ", numeroessai-1);
	
	
	if(numeroessai > 12){
	numeroessai=numeroessai%12;
	}
	kasiski = numeroessai;
	numeroessai++;
	return kasiski;
}
}
	
void indiceMutuelle(int cle[], int kasiski, ANALYSE freq, RESSOURCESLANGUE prob, gchar safecle[])
{ 
	float mg[kasiski][ALPHABET];
	
	int w; // w = n/m
	int i,j,g;
	
	for (j = 0; j < kasiski; j++)
	{
		for (i = 0; i < ALPHABET; i++)
		{
			mg[j][i]=0;
		}	
	}
	
	double VraiIndice;
	w = freq.nb/kasiski;
	for (j = 0; j < kasiski; j++)	//Ici, remplissage tableau Mg avec les indices de coincidences 
	{
		for (g = 0; g < ALPHABET; g++)
		{
			for (i = 0; i < ALPHABET; i++)
			{	
				mg[j][g] = mg[j][g] + ((prob.occ[i] * freq.occ[j][(i+g)%26])/w);
			}
			
		}
	}

	for(j=0;j<kasiski;j++){   //ici on selectionne la valeurs de chaque ligne la plus proche de 0.065 
		VraiIndice	= 2;//on initialise a une grande valeur pour être sur que la premiere valeur du tableau soit affecter a Vraiindice(a modifier si on a temps)
		for (i = 0; i < ALPHABET; i++)
		{
			if(fabs(mg[j][i] - 1) < VraiIndice){
				VraiIndice = fabs(mg[j][i] - 1);
					cle[j] = i; 		
			}
		}
			
	}				
//affecter la valeur de fin a safecle

	for (i = 0; i <kasiski ; i++)
	{
		safecle[i] = cle[i] + 97;
		
	}
		
	safecle[i] = '\0';
	for (i = 0; i < 5; ++i)
	{
		for ( j = 0; j < 26; ++j)
		{
			//printf("mg[%d][%d] = %f et car = %c \n",i,j,mg[i][j],j+97);
		}
	}
	
}

void Decrypte(char resultat[],char* texteCrypte,gchar cle[], int kasiski)
{
   int i;
   int a,b,c;
   int taille;
   taille = strlen(texteCrypte);
   
	for ( i = 0; i < taille ; i++)
	{
		a= texteCrypte[i] - 97;
		b= cle[i%kasiski] - 97;
		c = a-b ;
		if(c < 0)
			c=c+26;
		resultat[i] = c + 97;
	}
	resultat[i] = '\0';
}

void DecryptageVigenere(gchar* TexteDecrypte, gchar* TexteCrypte, gchar savecle[]){
	RESSOURCESLANGUE don;
	ANALYSE req;
	int kasiski,taille;
	gchar TexteC[strlen(TexteCrypte)];
	gchar SauvegradeCle[TAILLECLE];
	
	
	ConvertisseurTableau(TexteC,&taille,TexteCrypte);
	RetirerToutCarSpec(TexteC,TexteC);
	
	don = ChargerRessources();  // remplie la structure avec les proba de la langue choisi.
	
	req = AnalyseFrequentielle(TexteC); //remplie la structure avec les fréquences du texte
	req = tri(req);
		
	kasiski = Kasiski(req, TexteC); //recupere le PGOR (ou tri) et le texte clair, retourne taille cle	
	
	req = AnalyseFreq(req,TexteC,kasiski); //remplie la structure avec les fréquences du texte

	int cle[kasiski];

	indiceMutuelle(cle, kasiski, req, don, SauvegradeCle); 

	strcpy(savecle,SauvegradeCle);


	
	Decrypte(TexteDecrypte, TexteC, SauvegradeCle, kasiski);
	
}

