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

int Kasiski(gchar* pgor, gchar* texteCrypte){

	int i,j,kas,taillepgor;
	
	taillepgor = strlen(pgor);
	int nbrpgor = 0;
	int distance[TAILLECLE];
	
	for (i = 0; i < strlen(texteCrypte); i++)
	{
		for (j = 0; j < taillepgor; j++)
		{
			if(pgor[j] == texteCrypte[i]){
				if(j == taillepgor-1){
					distance[nbrpgor] = i-(taillepgor-1);
					nbrpgor++;
				}
				i++;
			}
			else if(texteCrypte[i] == pgor[0]){
	
				j=0;
				i++;
			}
			else break;
		}
		
	}
	kas = distance[0];
	j=0;
	for (i = 0; i < nbrpgor; i++)
	{
		kas = pgcd(kas,distance[i]);
		j++;
	}
	for (i = 0; i < nbrpgor; i++)
	{
				printf("\ndistance[%d] = %d",i,distance[i]);
	}
	
	printf("\nkasiski = %d\n",kas);
	return kas;
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
			if(fabs(mg[j][i] - 0.065) < VraiIndice){
				VraiIndice = fabs(mg[j][i] - 0.065);
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
	int cle[TAILLECLE];

	gchar* pgor = "rfap"; //il faut la fonction qui determine la PGOR
	gchar TexteC[strlen(TexteCrypte)];
	
	ConvertisseurTableau(TexteC,&taille,TexteCrypte);
	RetirerToutCarSpec(TexteC,TexteC);
	
	don = ChargerRessources();  // remplie la structure avec les proba de la langue choisi.
	kasiski = Kasiski(pgor, TexteC); //recupere le PGOR (ou tri) et le texte clair, retourne taille cle	
	
	req = AnalyseFreq(TexteC,kasiski); //remplie la structure avec les fréquences du texte

	indiceMutuelle(cle, kasiski, req, don, savecle);  
	
	Decrypte(TexteDecrypte, TexteC, savecle, kasiski);
		
}
