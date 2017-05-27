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
	return '0';
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
				monc1= a.tr[i].nom[2]; map1=2;quit=1;}
		}
		ok=0;
		if(a.tr[i].nom[0] == car2 && a.tr[i].nom[2] == car){ //test premierelettre = car et troisiemelettre = car2 pour renvoyer secondelettre
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.tr[i].nom[1] == fait[j])
					ok = 1;
			}
			if(ok == 0){
				monc1= a.tr[i].nom[1];map1=1;quit=1;}
		}	
		ok=0;
		if(a.tr[i].nom[0] == car2 && a.tr[i].nom[1] == car){ //test premierelettre = char2 et secondelettre = car pour renvoyer troisiemelettre
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.tr[i].nom[2] == fait[j])
					ok = 1;
			}
			if(ok == 0){
				monc1= a.tr[i].nom[2];map1=2;quit=1;}
		}	
		ok=0;
		if(a.tr[i].nom[0] == car && a.tr[i].nom[2] == car2){ //test premierelettre = char2 et troisiemelettre = car pour renvoyer secondelettre
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.tr[i].nom[1] == fait[j])
					ok = 1;
			}
			if(ok == 0){
				monc1=a.tr[i].nom[1];map1=1;quit=1;}
		}	
		ok=0;
		if(a.tr[i].nom[1] == car && a.tr[i].nom[2] == car2){ //test secondelettre = char2 et troisiemelettre = car pour renvoyer premierelettre
			for (j = 0; j < ALPHABET; j++)
			{
				if(a.tr[i].nom[0] == fait[j])
					ok = 1;
			}
			if(ok == 0){
				monc1= a.tr[i].nom[0];map1=0;quit=1;}
		}	
		ok=0;
		if(a.tr[i].nom[1] == car2 && a.tr[i].nom[2] == car){ //test secondelettre = char et troisiemelettre = char2 pour renvoyer premierelettre
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
	return '0';
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
	return '0';
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
	int i,j;
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
	
	gchar ch = '0';
	gchar ch2 = '0';
	
	int n=0;
	
	for(i=0;i<4;i++){ // premier teste (avec E)
		ch = Recherche(a,tabRes[0],fait);
		ch2 = Recherche2(res,tabRes[0],fait);
		if(ch != '0' && ch2 != '0'){
			a=remplace(a,ch,ch2);
			RemplacerCle(cle,ch,ch2);
			RemplacerCle(TexteCrypte,ch,ch2);
			for(n=0;fait[n] >64 && fait[n] <91;n++){}
			fait[n]=ch2;
			printf("\n%s\n",cle);
		}
	}
	
	for(j=1;j<13;j++){
		for(i=0;i<3;i++){ 
			ch = Recherche(a,fait[j],fait);
			ch2 = Recherche2(res,fait[j],fait);
		
			if(ch != '0' && ch2 != '0'){
				a=remplace(a,ch,ch2);
				RemplacerCle(cle,ch,ch2);
				RemplacerCle(TexteCrypte,ch,ch2);
				for(n=0;fait[n] >64 && fait[n] <91;n++){}
				fait[n]=ch2;
			}
		}
	}
	
	for(i=0;i<10;i++){
		ch2=fait[i+1];
		ch2 = RechercheTri(TexteCrypte,cle,a,res,fait[0],ch2,fait);
		if(ch2 != '0'){
			for(n=0;fait[n] >64 && fait[n] <91;n++){}
			fait[n]=ch2;
		}
	}
	
	for(i=0;i<10;i++){
		ch2=fait[i+1];
		ch2 = RechercheTri(TexteCrypte,cle,a,res,fait[1],ch2,fait);
		if(ch2 != '0'){
			for(n=0;fait[n] >64 && fait[n] <91;n++){}
			fait[n]=ch2;
		}
	}
}

/*
DT LGWIAOMTN XGWL ST ZGFPGWK GW EGFLMAMTN XGWL JWT E'TLM WFT ZGFFT PGWKFTT, JWT PT ST XTWOSST GW FGF GW JWT XGWL XGWL LTFMTN ZOTF ET DAMOF GW 
TFEGKT JWT E TLM WFT PGWKFTT GW OS YAWM TMKT ZGF TM XGOSA WF TVTDHST RT STWK EIAFM LO MAFM TLM JWT ETSA HWOLLT B KTLLTDZSTK TF S AZLTFET RT STWK
 DWLOJWT SGOF AW RTSA RTL DGFMAUFTL YKGORTL TM TDZKWDTTL XTKL RTL EAEIGML HKGYGFRL TM R AFMOJWTL EAXTKFTL OS FGWL YAWM ASSTK AXAFM ST STXTK 
RW PGWK TF JWTMT RT S'GK HAST TM TFEIAFMT STL FAOFL RT PAROL PTMAOTFM RT HWOLLAFML EIAKDTL JWAFR STL DAKMTAWV MGDZAOTFM EGDDT RTL ESGEITL 
LGFFAFMTL TF RTL SOTWV HKGYGFRL GW RGKDTFM STL EIGLTL MTFTZKTWLTL RAFL STL LASSTL EAXTKFTWLTL LGWL STL DGFMAUFTL HGWK WF AFMOJWT KGO TM WF
 LTOUFTWK SWMOF SA DAOFML ADAL RGKTL TM DOKGOMAFML OSL YAEGFFTKTFM TM YGKUTKTFM TM SA SWDO?KT OSL AMMKAHTKTFM HGWK SA EAEITK RAFL STL 
UTDDTL LWK SA UAKRT RT S THTT. LWK RTL EGSSOTKL R AKUTFM OSL TFYOSTKTFM STL ?MGOSTL TF YSTWK LWK RTL EGWKGFFTL OSL AEEKGEI?KTFM ST YTW-RKAUGF
 TF YOSL MGKLARTL OSL DAOSSTKTFM SA SWDOTKT RT SA SWFT TM RW LGSTOS. SGOF AW RTSA RTL DGFMAUFTL YKGORTL TM TDZKWDTTL XTKL RTL EAEIGML HKGYGFRL
 TM R AFMOJWTL EAXTKFTL OS FGWL YAWM ASSTK AXAFM ST STXTK RW PGWK HGWK KTESADTK FGMKT GK SGFUMTDHL GWZSOT. RTL UGZTSTML OSL EOLTSTKTFM SA
 HGWK TWV DTDTL TM RTL IAKHTL R GK GW FWS IGDDT FT EKTWLT SGFUMTDHL OSL LGFM KTLMTL TM DAOFMTL EIAFLGFL YWKTFM EIAFMTTL OFTFMTFRWTL RTL IGDDTL 
GW RTL TSYTL STL HOFL KWUOLLAOTFM LWK STL EODTL STL XTFML UTDOLLAOTFM RAFL SA FWOM ST YTW TMAOM KGWUT OS L'TMTFRAOM YSADZGBAFM STL AKZKTL 
EGDDT RTL MGKEITL TMOFETSAOTFM RT SWDOTKT STL ESGEITL LGFFAOTFM RAFL SA XASSTT 
*/
