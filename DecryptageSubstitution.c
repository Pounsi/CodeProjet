#include "DecryptageSubstitution.h"

void RemplacerCara(gchar* texte,gchar C1,gchar C2) // Fonction qui vas remplacer le caractere C1 du texte ou de la clef par le caractere C2
{
	
	int i;
	for ( i = 0; i < strlen(texte); i++) // on parcourt le texte ou la clef
	{
		if (texte[i]==C1) // si on trouve le caractere C1 on le remplace avec C2
		{
			texte[i]=C2;
		}
	}
	
}

ANALYSE Remplace(ANALYSE a,gchar car,gchar nvx){ //cette fonction remplace le caractere crypté 'car' par le caractere décrypté 'nvx' dans la structure analyse afin de peremettre aux fonctions RechercheAnalyse et RechercheTri de ne pas utiliser les digrammes et trigrammes dejà utilisé pour le décryptage.
	int i;
	for (i = 0; i < a.nbdi; i++)  //remplace dans les digrammes
	{
		if(a.di[i].nom[0] == car) a.di[i].nom[0] = nvx;
		if(a.di[i].nom[1] == car) a.di[i].nom[1] = nvx;
	}
	for (i = 0; i < a.nbtr; i++) // remplace dansles trigrammes
	{
		if(a.tr[i].nom[0] == car) a.tr[i].nom[0] = nvx;
		if(a.tr[i].nom[1] == car) a.tr[i].nom[1] = nvx;
		if(a.tr[i].nom[2] == car) a.tr[i].nom[2] = nvx;
	}
	return a; // retourne l'analyse modifié
}

gchar RechercheAnalyse(ANALYSE a,gchar car,gchar* fait){ //Permet de conjecturer quel caractère nous allons remplacer dans le texte en utilisant les digrammes de l'analyse 'a', un tableau de caractère 'fait[]' permettant de savoir quelle caractères ont été déja conjecturé et le caractère 'car': l'autre caractère du digramme.
	int i,j;
	int ok;
	for (i = 0; i < a.nbdi; i++)  // on parcourt la liste des digrammes de 'a' 
	{
		ok=0;
		if(a.di[i].nom[0] == car){ //si 'car' est le premiere caractère d'un digramme et que le deuxieme caractère n'appartient pas au tableau 'fait[]] alors on retourne ce deuxieme caractère'
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.di[i].nom[1] == fait[j])
					ok = 1;
			}
			if(ok == 0)
				return a.di[i].nom[1];
		}
		ok=0;
		if(a.di[i].nom[1] == car){ //si 'car' est le deuxieme caractère d'un digramme et que le premier caractère n'appartient pas au tableau 'fait[]] alors on retourne ce premier caractère'
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.di[i].nom[0] == fait[j])
					ok = 1;
			}
			if(ok == 0)
				return a.di[i].nom[0];
		}	
	}
	return '0'; // on retourne le caractère '0' si on ne trouve aucun caractère correspondant au critère de séléction.
}

gchar RechercheTri(gchar* TexteCrypte,gchar* cle,ANALYSE a,RESSOURCESLANGUE a2, gchar car,gchar car2,gchar* fait){ // Fonction qui permet de conjecturer quel caractère nous allons remplacer dans le texte en utilisant les trigrammes de l'analyse 'a', le tableau 'fait[]' permettant de savoir quelle caractères ont été déja conjecturé et les caractères 'car' et 'car2' : les autres caractères du trigramme.
	int i,j;																											// Elle permet egalement de conjecturer avec quel caractère nous allons remplacer le caractère crypté dans le texte en utilisant les trigrammes de la ressource 'a2', le tableau 'fait[]' permettant de savoir quelle caractères ont été déja conjecturé et les caractères 'car' et 'car2' : les autres caractères du trigramme.
	int ok;
	char monc1,monc2='0';
	int map1;
	int quit=0;
	for (i = 0; i < a.nbtr; i++) //pour les trigrammes de l'analyse
	{
		ok=0;
		if(a.tr[i].nom[0] == car && a.tr[i].nom[1] == car2){ //test la premiere lettre = car et seconde lettre = car2 pour renvoyer troisieme lettre si elle n'appartient pas à 'fait[]'
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.tr[i].nom[2] == fait[j])
					ok = 1;
			}
			if(ok == 0){
				monc1= a.tr[i].nom[2]; map1=2;quit=1;}
		}
		ok=0;
		if(a.tr[i].nom[0] == car2 && a.tr[i].nom[2] == car){ //test premiere lettre = car2 et troisieme lettre = car pour renvoyer seconde lettre si elle n'appartient pas à 'fait[]'
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.tr[i].nom[1] == fait[j])
					ok = 1;
			}
			if(ok == 0){
				monc1= a.tr[i].nom[1];map1=1;quit=1;}
		}	
		ok=0;
		if(a.tr[i].nom[0] == car2 && a.tr[i].nom[1] == car){ //test premiere lettre = char2 et seconde lettre = car pour renvoyer troisieme lettre si elle n'appartient pas à 'fait[]'
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.tr[i].nom[2] == fait[j])
					ok = 1;
			}
			if(ok == 0){
				monc1= a.tr[i].nom[2];map1=2;quit=1;}
		}	
		ok=0;
		if(a.tr[i].nom[0] == car && a.tr[i].nom[2] == car2){ //test premiere lettre = char et troisieme lettre = car2 pour renvoyer seconde lettre si elle n'appartient pas à 'fait[]'
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.tr[i].nom[1] == fait[j])
					ok = 1;
			}
			if(ok == 0){
				monc1=a.tr[i].nom[1];map1=1;quit=1;}
		}	
		ok=0;
		if(a.tr[i].nom[1] == car && a.tr[i].nom[2] == car2){ //test seconde lettre = char et troisieme lettre = car2 pour renvoyer premiere lettre si elle n'appartient pas à 'fait[]'
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.tr[i].nom[0] == fait[j])
					ok = 1;
			}
			if(ok == 0){
				monc1= a.tr[i].nom[0];map1=0;quit=1;}
		}	
		ok=0;
		if(a.tr[i].nom[1] == car2 && a.tr[i].nom[2] == car){ //test seconde lettre = char2 et troisieme lettre = char pour renvoyer premiere lettre si elle n'appartient pas à 'fait[]'
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.tr[i].nom[0] == fait[j])
					ok = 1;
			}
			if(ok == 0){
				monc1= a.tr[i].nom[0];map1=0;quit=1;}
		}
	if(quit == 1) break;
	}
	for (i = 0; i < 25; i++) //pour les trigrammes de la ressource
	{
		ok=0;					
		if(a2.tr[i].nom[0] == car && a2.tr[i].nom[1] == car2){ //test premiere lettre = car et seconde lettre = car2 pour renvoyer troisieme lettre si elle n'appartient pas à 'fait[]'
			for (j = 0; j < ALPHABET; j++)
			{
				if((a2.tr[i].nom[2] == fait[j]) || (map1 != 2))
					ok = 1;
			}
			if(ok == 0){
				monc2= a2.tr[i].nom[2];}
		}
		ok=0;
		if(a2.tr[i].nom[0] == car && a2.tr[i].nom[2] == car2){ //test premiere lettre = car et troisieme lettre = car2 pour renvoyer seconde lettre si elle n'appartient pas à 'fait[]'
			for (j = 0; j < ALPHABET; j++)
			{
				if((a2.tr[i].nom[1] == fait[j]) || (map1 != 1))
					ok = 1;
			}
			if(ok == 0){
				monc2= a2.tr[i].nom[1];}
		}	
		ok=0;
		if(a2.tr[i].nom[0] == car2 && a2.tr[i].nom[1] == car){ //test premiere lettre = char2 et seconde lettre = car pour renvoyer troisieme lettre si elle n'appartient pas à 'fait[]'
			for (j = 0; j < ALPHABET; j++)
			{
				if((a2.tr[i].nom[2] == fait[j])|| (map1 != 2))
					ok = 1;
			}
			if(ok == 0){
				monc2= a2.tr[i].nom[2];}
		}	
		ok=0;
		if(a2.tr[i].nom[0] == car && a2.tr[i].nom[2] == car2){ //test premiere lettre = char et troisieme lettre = car2 pour renvoyer seconde lettre si elle n'appartient pas à 'fait[]'
			for (j = 0; j < ALPHABET; j++)
			{
				if((a2.tr[i].nom[1] == fait[j])|| (map1 != 1))
					ok = 1;
			}
			if(ok == 0){
				monc2=a2.tr[i].nom[1];}
		}	
		ok=0;
		if(a2.tr[i].nom[1] == car && a2.tr[i].nom[2] == car2){ //test seconde lettre = char et troisieme lettre = car2 pour renvoyer premiere lettre si elle n'appartient pas à 'fait[]'
			for (j = 0; j < ALPHABET; j++)
			{
				if((a2.tr[i].nom[0] == fait[j]) || (map1 != 0))
					ok = 1;
			}
			if(ok == 0){
				monc2= a2.tr[i].nom[0];}
		}	
		ok=0;
		if(a2.tr[i].nom[1] == car && a2.tr[i].nom[2] == car2){ //test seconde lettre = char et troisieme lettre = char2 pour renvoyer premiere lettre si elle n'appartient pas à 'fait[]'
			for (j = 0; j < ALPHABET; j++)
			{
				if((a2.tr[i].nom[0] == fait[j]) || (map1 != 0))
					ok = 1;
			}
			if(ok == 0){
				monc2= a2.tr[i].nom[0];}
		}
	}
	if (monc2 != '0'){
		a = Remplace(a,monc1,monc2); // on remplace le caractère conjecturé grace à l'analyse par celui conjecturer par la ressource
		RemplacerCara(cle,monc1,monc2);
		RemplacerCara(TexteCrypte,monc1,monc2);
		return monc2;
	}
	return '0';
}

gchar RechercheRessources(RESSOURCESLANGUE a,gchar car,gchar* fait){ //Permet de conjecturer avec quel caractère nous allons remplacer le caractère crypté dans le texte en utilisant les digrammes de la ressource 'a', un tableau de caractère 'fait[]' permettant de savoir quelle caractères ont été déja conjecturé et le caractère 'car': l'autre caractère du digramme.
	int i,j;
	int ok;
	for (i = 0; i < 25; i++) // on parcourt la liste des digrammes de la ressource
	{
		ok=0;
		if(a.di[i].nom[0] == car){ //si 'car' est le premiere caractère d'un digramme et que le deuxieme caractère n'appartient pas au tableau 'fait[]] alors on retourne ce deuxieme caractère'
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.di[i].nom[1] == fait[j])
					ok = 1;
			}
			if(ok == 0)
				return a.di[i].nom[1];
		}
		ok=0;
		if(a.di[i].nom[1] == car){ //si 'car' est le deuxieme caractère d'un digramme et que le premier caractère n'appartient pas au tableau 'fait[]] alors on retourne ce premier caractère'
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.di[i].nom[0] == fait[j])
					ok = 1;
			}
			if(ok == 0)
				return a.di[i].nom[0];
		}	
	}
	return '0';  // on retourne le caractère '0' si on ne trouve aucun caractère correspondant au critère de séléction.
}

void InitTableau(gchar* TexteClair,gchar TabOccA[],gchar TabOccRL[],gchar clef[]){// La fonction qui permet de conjecturer le premier caractère du décryptage et donc le carctère quiapparait le plus dans le texte 
	int i;
	for(i=0;i<strlen(TexteClair);i++) // on parcourt le texte et si un caractère est le même que le caractère le plus frequent dans le texte on le remplace par le caractere le plus frequent dans la langue choisit
	{	
		if (TexteClair[i]==TabOccA[0])
			{
				TexteClair[i]=TabOccRL[0];
			}
	}
	
	for(i=0;i<ALPHABET;i++) // même procédé avec le clef de substitution
	{
		if(clef[i]==TabOccA[0])
			{
				clef[i]=TabOccRL[0];
			}
	}
}

void CreeTabOccA(gchar TabOcc[],ANALYSE analyseTexte) // remplit le tableau 'TabOcc' avec la liste des caractère du texte (et donc de l'analyse 'analyseTexte') trié par ordre de fréquence décroissante 
{
	float max=-1;
	int i,n,ret;
	for (i = 0; i < ALPHABET; i++)
	{
		for (n = 0; n < ALPHABET; n++)
		{
			
			if (analyseTexte.occ[0][n]>max)
			{
				ret=n;
				max=analyseTexte.occ[0][n];
			}
		}
		max=-1;
		TabOcc[i]=ret+97;
		analyseTexte.occ[0][ret]=0;
	}
	TabOcc[i]='\0';
}

void CreeTabOccRL(gchar TabOcc[],RESSOURCESLANGUE ressourceLangue) // remplit le tableau 'TabOcc' avec la liste des caractère de la ressource 'ressourceLangue' trié par ordre de fréquence décroissante 
{
	float max=0;
	int i,n,ret;
	for (i = 0; i < ALPHABET; i++)
	{
		for (n = 0; n < ALPHABET; n++)
		{
			
			if (ressourceLangue.occ[n]>max)
			{
				ret=n;
				max=ressourceLangue.occ[n];
			}
		}
		max=0;
		TabOcc[i]=ret+65;
		ressourceLangue.occ[ret]=0;
	}
	TabOcc[i]='\0';
}

void DecryptageSubstitution(gchar TexteDecrypte[],gchar TexteCrypte[],gchar cle[])
{
	ANALYSE a;
	RESSOURCESLANGUE res;
	int i,j;
	int taille;
	gchar tabA[ALPHABET+1];//vas contenir la liste des caractères de l'analyse trié par ordre de frequence décroissant
	gchar tabRes[ALPHABET+1];//vas contenir la liste des caractères de la ressource trié par ordre de frequence décroissant
	gchar fait[ALPHABET];//vas contenir les caracteres deja conjecturé
	res=ChargerRessources();
	ConvertisseurTableau(TexteCrypte,&taille,TexteCrypte);
	a=AnalyseFrequentielle(TexteCrypte);

	a=tri(a);// tri les digrammes et trigrammes de l'analyse frequentielle par ordre de frequence decroissant
	
	CreeTabOccA(tabA,a); // tri les caractères de l'analyse
	CreeTabOccRL(tabRes,res);
	
	InitTableau(TexteCrypte,tabA,tabRes,cle); 
	
	a=Remplace(a,tabA[0],tabRes[0]); 
	RemplacerCara(cle,tabA[0],tabRes[0]);
	RemplacerCara(TexteCrypte,tabA[0],tabRes[0]);
	fait[0]= tabRes[0];
	
	gchar ch = '0';
	gchar ch2 = '0';
	
	int n=0;
	
	for(i=0;i<4;i++){ // premier teste : caractères formant un digramme avec tabRes[0]
		ch = RechercheAnalyse(a,tabRes[0],fait);
		ch2 = RechercheRessources(res,tabRes[0],fait);
		if(ch != '0' && ch2 != '0'){ // si l'on trouve des caractère respectant les critères de selection
			a=Remplace(a,ch,ch2);
			RemplacerCara(cle,ch,ch2);
			RemplacerCara(TexteCrypte,ch,ch2);
			for(n=0;fait[n] >64 && fait[n] <91;n++){} //pour trouver la première case vide de 'fait[]'
			fait[n]=ch2;
		}
	}
	
	for(j=1;j<13;j++){ //second teste : caractères formant un digramme avec les caractères entré dans 'fait[]'
		for(i=0;i<3;i++){ 
			ch = RechercheAnalyse(a,fait[j],fait);
			ch2 = RechercheRessources(res,fait[j],fait);
		
			if(ch != '0' && ch2 != '0'){
				a=Remplace(a,ch,ch2);
				RemplacerCara(cle,ch,ch2);
				RemplacerCara(TexteCrypte,ch,ch2);
				for(n=0;fait[n] >64 && fait[n] <91;n++){}
				fait[n]=ch2;
			}
		}
	}
	
	for(i=0;i<10;i++){ // troisieme teste : caractères formant un trigramme avec tabRes[0] et les caractères entré dans 'fait[]'
		ch2=fait[i+1];
		ch2 = RechercheTri(TexteCrypte,cle,a,res,fait[0],ch2,fait);
		if(ch2 != '0'){
			for(n=0;fait[n] >64 && fait[n] <91;n++){}
			fait[n]=ch2;
		}
	}
	
	for(j=0;j<10;j++){// teste : caractères formant un trigramme avec deux caractères entré dans 'fait[]'
		for(i=0;i<10;i++){
			ch2=fait[i+1];
			ch2 = RechercheTri(TexteCrypte,cle,a,res,fait[j+1],ch2,fait);
			if(ch2 != '0'){
				for(n=0;fait[n] >64 && fait[n] <91;n++){}
				fait[n]=ch2;
			}
		}
	}
}
