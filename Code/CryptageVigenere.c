#include "../Headers/CryptageVigenere.h"

void CryptageVigenere(gchar* resultat,gchar* Texte,gchar* Cle)
{
   int i;
   gchar a,b,c;
   gchar texteClair[strlen(Texte)];
   int length = strlen(Cle);
   int x;
   ConvertisseurTableau(texteClair,&x,Texte);
		for ( i = 0; i < strlen(texteClair); i++)
		{
			a= texteClair[i] - 97;
			b= Cle[i%length] - 97;
			c = (a+b) ;
			if(c >= ALPHABET)
				c=c-ALPHABET;
			resultat[i] = c + 97;
		}
		resultat[i]= '\0';
}
