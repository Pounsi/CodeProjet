#include "DecryptageSubstitution.h"

void RemplacerCle(gchar* cle,gchar C1,gchar C2)
{
	
	int i;
	for ( i = 0; i < strlen(cle); i++)
	{
		if (cle[i]==C1)
		{
			cle[i]=C2;
		}
	}
	
}

ANALYSE remplace(ANALYSE a,gchar car,gchar nvx){
	int i;
	for (i = 0; i < a.nbdi; i++)
	{
		if(a.di[i].nom[0] == car) a.di[i].nom[0] = nvx;
		if(a.di[i].nom[1] == car) a.di[i].nom[1] = nvx;
	}
	for (i = 0; i < a.nbtr; i++)
	{
		if(a.tr[i].nom[0] == car) a.tr[i].nom[0] = nvx;
		if(a.tr[i].nom[1] == car) a.tr[i].nom[1] = nvx;
		if(a.tr[i].nom[2] == car) a.tr[i].nom[2] = nvx;
	}
	return a;
}

gchar Recherche(ANALYSE a,gchar car,gchar* fait){
	int i,j;
	int ok;
	for (i = 0; i < a.nbdi; i++)
	{
		ok=0;
		if(a.di[i].nom[0] == car){
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.di[i].nom[1] == fait[j])
					ok = 1;
			}
			if(ok == 0)
				return a.di[i].nom[1];
		}
		ok=0;
		if(a.di[i].nom[1] == car){
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.di[i].nom[0] == fait[j])
					ok = 1;
			}
			if(ok == 0)
				return a.di[i].nom[0];
		}	
	}
	return 'A';//a modifier
}

gchar RechercheTri(gchar* TexteCrypte,gchar* cle,ANALYSE a,RESSOURCESLANGUE a2, gchar car,gchar car2,gchar* fait){ // pour Analyse, remplace ANALYSE par RESSOURCESLANGUE pour RechercheTri2
	int i,j;
	int ok;
	char monc1,monc2='0';
	int map1;
	int quit=0;
	for (i = 0; i < a.nbtr; i++)
	{
		ok=0;
		if(a.tr[i].nom[0] == car && a.tr[i].nom[1] == car2){ //test premierelettre = car et secondelettre = car2 pour renvoyer troisiemelettre
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.tr[i].nom[2] == fait[j])
					ok = 1;
			}
			if(ok == 0){
				monc1= a.tr[i].nom[2]; map1=2;quit=1;printf("ici1");}
		}
		ok=0;
		if(a.tr[i].nom[0] == car2 && a.tr[i].nom[2] == car){ //test premierelettre = car et troisiemelettre = car2 pour renvoyer secondelettre
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.tr[i].nom[1] == fait[j])
					ok = 1;
			}
			if(ok == 0){
				monc1= a.tr[i].nom[1];map1=1;quit=1;printf("ici2") ;}
		}	
		ok=0;
		if(a.tr[i].nom[0] == car2 && a.tr[i].nom[1] == car){ //test premierelettre = char2 et secondelettre = car pour renvoyer troisiemelettre
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.tr[i].nom[2] == fait[j])
					ok = 1;
			}
			if(ok == 0){
				monc1= a.tr[i].nom[2];map1=2;quit=1;printf("ici3");}
		}	
		ok=0;
		if(a.tr[i].nom[0] == car && a.tr[i].nom[2] == car2){ //test premierelettre = char2 et troisiemelettre = car pour renvoyer secondelettre
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.tr[i].nom[1] == fait[j])
					ok = 1;
			}
			if(ok == 0){
				monc1=a.tr[i].nom[1];map1=1;quit=1;printf("ici4");}
		}	
		ok=0;
		if(a.tr[i].nom[1] == car && a.tr[i].nom[2] == car2){ //test secondelettre = char2 et troisiemelettre = car pour renvoyer premierelettre
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.tr[i].nom[0] == fait[j])
					ok = 1;
			}
			if(ok == 0){
				monc1= a.tr[i].nom[0];map1=0;quit=1;printf("ici5");}
		}	
		ok=0;
		if(a.tr[i].nom[1] == car2 && a.tr[i].nom[2] == car){ //test secondelettre = char et troisiemelettre = char2 pour renvoyer premierelettre
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.tr[i].nom[0] == fait[j])
					ok = 1;
			}
			if(ok == 0){
				monc1= a.tr[i].nom[0];map1=0;quit=1;printf("ici6");}
		}
	if(quit == 1) break;
	}
	for (i = 0; i < 25; i++)
	{
		ok=0;
		if(a2.tr[i].nom[0] == car && a2.tr[i].nom[1] == car2){ //test premierelettre = car et secondelettre = car2 pour renvoyer troisiemelettre
			for (j = 0; j < ALPHABET; j++)
			{
				if((a2.tr[i].nom[2] == fait[j]) || (map1 != 2))
					ok = 1;
			}
			if(ok == 0){
				monc2= a2.tr[i].nom[2];}
		}
		ok=0;
		if(a2.tr[i].nom[0] == car && a2.tr[i].nom[2] == car2){ //test premierelettre = car et troisiemelettre = car2 pour renvoyer secondelettre
			for (j = 0; j < ALPHABET; j++)
			{
				if((a2.tr[i].nom[1] == fait[j]) || (map1 != 1))
					ok = 1;
			}
			if(ok == 0){
				monc2= a2.tr[i].nom[1];}
		}	
		ok=0;
		if(a2.tr[i].nom[0] == car2 && a2.tr[i].nom[1] == car){ //test premierelettre = char2 et secondelettre = car pour renvoyer troisiemelettre
			for (j = 0; j < ALPHABET; j++)
			{
				if((a2.tr[i].nom[2] == fait[j])|| (map1 != 2))
					ok = 1;
			}
			if(ok == 0){
				monc2= a2.tr[i].nom[2];}
		}	
		ok=0;
		if(a2.tr[i].nom[0] == car && a2.tr[i].nom[2] == car2){ //test premierelettre = char2 et troisiemelettre = car pour renvoyer secondelettre
			for (j = 0; j < ALPHABET; j++)
			{
				if((a2.tr[i].nom[1] == fait[j])|| (map1 != 1))
					ok = 1;
			}
			if(ok == 0){
				monc2=a2.tr[i].nom[1];}
		}	
		ok=0;
		if(a2.tr[i].nom[1] == car && a2.tr[i].nom[2] == car2){ //test secondelettre = char2 et troisiemelettre = car pour renvoyer premierelettre
			for (j = 0; j < ALPHABET; j++)
			{
				if((a2.tr[i].nom[0] == fait[j]) || (map1 != 0))
					ok = 1;
			}
			if(ok == 0){
				monc2= a2.tr[i].nom[0];}
		}	
		ok=0;
		if(a2.tr[i].nom[1] == car && a2.tr[i].nom[2] == car2){ //test secondelettre = char et troisiemelettre = char2 pour renvoyer premierelettre
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
		a = remplace(a,monc1,monc2);
		RemplacerCle(cle,monc1,monc2);
		RemplacerCle(TexteCrypte,monc1,monc2);
		return monc2;
	}
	return 'A';
}

gchar Recherche2(RESSOURCESLANGUE a,gchar car,gchar* fait){
	int i,j;
	int ok;
	for (i = 0; i < 25; i++)
	{
		ok=0;
		if(a.di[i].nom[0] == car){
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.di[i].nom[1] == fait[j])
					ok = 1;
			}
			if(ok == 0)
				return a.di[i].nom[1];
		}
		ok=0;
		if(a.di[i].nom[1] == car){
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.di[i].nom[0] == fait[j])
					ok = 1;
			}
			if(ok == 0)
				return a.di[i].nom[0];
		}	
	}
	return 'A';//a modifier faut pas avoir ee par exemple
}

void InitTableau(gchar* TexteClair,gchar TabOccA[],gchar TabOccRL[],gchar cle[]){
	int i;
	for(i=0;i<strlen(TexteClair);i++)
	{	
		if (TexteClair[i]==TabOccA[0]) 
			{
				TexteClair[i]=TabOccRL[0];
			}
	}
	
	for(i=0;i<ALPHABET;i++)
	{
		if(cle[i]==TabOccA[0])
			{
				cle[i]=TabOccRL[0];
			}
	}
}

void CreeTabOccA(gchar TabOcc[],ANALYSE analysetexte)
{
	float max=-1;
	int i,n,ret;
	for (i = 0; i < ALPHABET; i++)
	{
		for (n = 0; n < ALPHABET; n++)
		{
			
			if (analysetexte.occ[0][n]>max)
			{
				ret=n;
				max=analysetexte.occ[0][n];
			}
		}
		max=-1;
		TabOcc[i]=ret+97;
		analysetexte.occ[0][ret]=0;
	}
	TabOcc[i]='\0';
}

void CreeTabOccRL(gchar TabOcc[],RESSOURCESLANGUE ressourcelangue)
{
	float max=0;
	int i,n,ret;
	for (i = 0; i < ALPHABET; i++)
	{
		for (n = 0; n < ALPHABET; n++)
		{
			
			if (ressourcelangue.occ[n]>max)
			{
				ret=n;
				max=ressourcelangue.occ[n];
			}
		}
		max=0;
		TabOcc[i]=ret+65;
		ressourcelangue.occ[ret]=0;
	}
	TabOcc[i]='\0';
}


void DecryptageSubstitution(gchar TexteDecrypte[],gchar TexteCrypte[],gchar cle[])
{
	ANALYSE a;
	RESSOURCESLANGUE res;
	int i,j,x;
	int taille;
	gchar tabA[ALPHABET+1];
	gchar tabRes[ALPHABET+1];
	gchar fait[ALPHABET];
	res=ChargerRessources();
	ConvertisseurTableau(TexteCrypte,&taille,TexteCrypte);
	a=AnalyseFrequentielle(TexteCrypte);
		for (i = 0; i < a.nbtr ; i++)
	{
		printf("%s \n",a.tr[i].nom);
	}
	a=tri(a);
	printf("apres le tri \n");
			for (i = 0; i < a.nbtr ; i++)
	{
		printf("%s \n",a.tr[i].nom);
	}
	CreeTabOccA(tabA,a);
	CreeTabOccRL(tabRes,res);
	
	
	InitTableau(TexteCrypte,tabA,tabRes,cle);
	
	a=remplace(a,tabA[0],tabRes[0]);
	RemplacerCle(cle,tabA[0],tabRes[0]);
	RemplacerCle(TexteCrypte,tabA[0],tabRes[0]);
	fait[0]= 'E';

	gchar ch = Recherche(a,tabRes[0],fait);
	gchar ch2 = Recherche2(res,tabRes[0],fait);
	a=remplace(a,ch,ch2);
	RemplacerCle(cle,ch,ch2);
	RemplacerCle(TexteCrypte,ch,ch2);
	fait[1]=ch2;
	printf("\n%s\n",cle);

/*
	ch = Recherche(a,tabRes[0],fait);
	ch2 = Recherche2(res,tabRes[0],fait);
	a=remplace(a,ch,ch2);
	RemplacerCle(cle,ch,ch2);
	RemplacerCle(TexteCrypte,ch,ch2);
	fait[2]=ch2;
	printf("\n%s\n",cle);



	ch = Recherche(a,tabRes[0],fait);
	ch2 = Recherche2(res,tabRes[0],fait);
	a=remplace(a,ch,ch2);
	RemplacerCle(cle,ch,ch2);
	RemplacerCle(TexteCrypte,ch,ch2);
	fait[3]=ch2;
	printf("\n%s\n",cle);*/

	
	ch2 = RechercheTri(TexteCrypte,cle,a,res,tabRes[0],ch2,fait);
	fait[2] = ch2;
	printf("\n%s\n",cle);
	
}
