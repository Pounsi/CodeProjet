#include "CryptageSubstitution.h"

int Ascii0_25(int nbr){ //prend le code ascii d'une lettre en caractere et la renvoyer dans [0;25]
	if(nbr >= 97 && nbr <= 122)	
		return nbr-97;
	else
		return nbr;
}

int *tirage(int nombre, int min, int max)
{
    int *tabelems, *ret, i, indice, maxi = max - min;
    if(min >= max || nombre > maxi + 1 || nombre < 1)
        return NULL;
    tabelems = malloc((maxi + 1) * sizeof(int));
    ret = malloc(nombre * sizeof(int));
    for(i = 0; i < maxi + 1; i++)
        tabelems[i] = i + min;
    for(i = 0; i < nombre; i++){
        indice = rand() % (maxi + 1);
        ret[i] = tabelems[indice];
        tabelems[indice] = tabelems[maxi];
        maxi--;
    }
    free(tabelems);
    return ret;
}
 
void GenereCle(gchar T[]){
	int i,*tab;
    srand(time(NULL));
	tab = tirage(25, 0, 25); //25 : nbr delement a tiré, intervalle [0;25]
	
	for(i = 0; i < ALPHABET; i++){
		T[i]=tab[i];
		
	}
	free(tab);
   
}

void CryptageSubstitution(gchar* TexteCrypte, gchar* TexteClair)
{ 
	int taille, i, x;
	
	gchar T[ALPHABET];
	GenereCle(T);
	
	gchar TextePourCryptage[strlen(TexteClair)];
	ConvertisseurTableau(TextePourCryptage,&taille,TexteClair);
	
	for (i = 0; i < strlen(TextePourCryptage); i++)
	{
		x = Ascii0_25(TextePourCryptage[i]);

		if(x < 0 || x > 25){
			TexteCrypte[i]= x;
		}
		else{
			TexteCrypte[i] = T[x]+97;
		}
	}
}
