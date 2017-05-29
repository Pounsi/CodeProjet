#include <CUnit/Basic.h>
#include "../Headers/InterfaceGraphique.h"

void TestCryptageVigenere()
{
	
	gchar texte[]	= "testcryptagevigenere"; 
	gchar cle[] 	= "cle";
	gchar resultat[strlen(texte)];
	CryptageVigenere(resultat,texte,cle);
	CU_ASSERT_STRING_EQUAL(resultat,"vpwvnvaaxcrixtkgyitp");
		
}
void TestCryptageSubstitution()
{
	gchar texte[] = "abc";
	gchar cle[26] ; 
	gchar resultat[strlen(texte)];
	CryptageSubstitution(resultat,texte,cle);
	CU_ASSERT_EQUAL(resultat[0],cle[0]);
	CU_ASSERT_EQUAL(resultat[2],cle[2]);
}
void TestAnalyseFrequentielle()
{		
	ANALYSE a;
	gchar* ch = "bainfinfaa";
	a = AnalyseFrequentielle(ch);
	a = tri(a);
	float tmp;
	tmp = 3;
	
	CU_ASSERT_EQUAL(a.occ[0][0],tmp);
	CU_ASSERT_STRING_EQUAL(a.di[0].nom,"in");
	CU_ASSERT_STRING_EQUAL(a.tr[0].nom,"inf");
	CU_ASSERT_EQUAL(a.nb,10);	    
}
void TestDecrypteVigenere()
{	
	gchar texte[]	= "vpwvnvaaxcrixtkgyitp"; 
	gchar cle[] 	= "cle";
	gchar resultat[strlen(texte)];
	Decrypte(resultat,texte,cle,3);
	CU_ASSERT_STRING_EQUAL(resultat,"testcryptagevigenere");
		
}
void TestKasiski()
{
	ANALYSE a;
	int kas, taille;
	gchar TexteCrypte[]	= "AMCIORESTIOHAJVVFPISFRPIBBCUDNUCGNBXAOVDFVRFTENRLBEEQCRKQSFCNJIOBWPPUTFFEOVRBKNFWREGLPOLBVTBSUBPTZRATUEVPETCITQNQGNECNUNARWEMNEJNSFTEWGLFEONOEMWNEGSQNUTIRBPDTCTUCQVCNUUEVTOQGEOUDVOONGNUKLJPSDTIUDUUUEOEHBOPJQNOCTEQNUWNFTEQTITGDFXOMGERWITGLPIEECNTNAMWCBTNFHADGANQNUREMNIFTEMWEQNUTDEBWBVVDFNAOPEFNOSUDFNADGRFOOOKEEGSUTOQJEFUUOHPFVOOBECWTTGNMKGVGDFUCICMQKOOUPVKSFPCPWPFFEMWEGCLFELVDAUVEJPTMCFJPAMGDFEEUVEEGROKESGDJUPVVEFGNNCIFVPFTDVGFBEEBWVBNEOEEDHAQTOQQSEGSBUAJUOOCLPNYNRIRWEEGMBTSFKLMGVJPCFPTMCBSWNFFEWGNVGNTWIUGPSGSJFEOVDVELVDDFELBTE"; 
	gchar TexteC[strlen(TexteCrypte)];
	
	ConvertisseurTableau(TexteC,&taille,TexteCrypte);
	RetirerToutCarSpec(TexteC,TexteC);
	a = AnalyseFrequentielle(TexteC); 
	a = tri(a);	
	kas = Kasiski(a, TexteC);

	CU_ASSERT_EQUAL(kas, 3);	
}
void TestIndiceMutuelle()
{
	ANALYSE req;
	int kas, taille;
	RESSOURCESLANGUE pro;
	gchar TexteCrypte[]	= "AMCIORESTIOHAJVVFPISFRPIBBCUDNUCGNBXAOVDFVRFTENRLBEEQCRKQSFCNJIOBWPPUTFFEOVRBKNFWREGLPOLBVTBSUBPTZRATUEVPETCITQNQGNECNUNARWEMNEJNSFTEWGLFEONOEMWNEGSQNUTIRBPDTCTUCQVCNUUEVTOQGEOUDVOONGNUKLJPSDTIUDUUUEOEHBOPJQNOCTEQNUWNFTEQTITGDFXOMGERWITGLPIEECNTNAMWCBTNFHADGANQNUREMNIFTEMWEQNUTDEBWBVVDFNAOPEFNOSUDFNADGRFOOOKEEGSUTOQJEFUUOHPFVOOBECWTTGNMKGVGDFUCICMQKOOUPVKSFPCPWPFFEMWEGCLFELVDAUVEJPTMCFJPAMGDFEEUVEEGROKESGDJUPVVEFGNNCIFVPFTDVGFBEEBWVBNEOEEDHAQTOQQSEGSBUAJUOOCLPNYNRIRWEEGMBTSFKLMGVJPCFPTMCBSWNFFEWGNVGNTWIUGPSGSJFEOVDVELVDDFELBTE"; 
	gchar TexteC[strlen(TexteCrypte)];
	kas = 3;
	int cle[kas]; 
	gchar safecle[kas];
	
	ConvertisseurTableau(TexteC,&taille,TexteCrypte);
	RetirerToutCarSpec(TexteC,TexteC);
	pro = ChargerRessources();
	req = AnalyseFreq(req,TexteC,kas); 
	req = tri(req);	
	indiceMutuelle(cle,kas,req,pro,safecle);

	
	CU_ASSERT_EQUAL(cle[0], 0);
	CU_ASSERT_EQUAL(cle[1], 1);
	CU_ASSERT_EQUAL(cle[2], 2);	
}
void TestPGCD()
{
	int a,b,c;
	a = 4; b = 12; 
	c = pgcd(a,b);
	CU_ASSERT_EQUAL(c,4);	
	a = 140; b = 295;
	c = pgcd(a,b);
	CU_ASSERT_EQUAL(c,5);
	a = 2876; b = 2432;
	c = pgcd(a,b);
	CU_ASSERT_EQUAL(c,4);
}
void TestRemplacercle()
{
	gchar cle[] ="sacle";
	gchar c[] = "s";
	gchar b[] = "m";
	RemplacerCara(cle,c[0],b[0]);
	CU_ASSERT_STRING_EQUAL(cle,"macle");
}
void TestRemplace()
{
	ANALYSE a;
	a.nbdi = 1;
	a.nbtr = 1;
	gchar* di = "sd";
	gchar* tri = "asi";
	strcpy(a.di[0].nom,di);
	strcpy(a.tr[0].nom,tri);
	gchar c = 's';
	gchar b = 'm';
	a = Remplace(a,c,b);

	CU_ASSERT_STRING_EQUAL(a.di[0].nom,"md");
	CU_ASSERT_STRING_EQUAL(a.tr[0].nom,"ami");
}
void TestRecherche()
{
	ANALYSE a;
	gchar res = '0';
	a.nbdi = 1;
	gchar* di = "cd";
	gchar fait[2];
	fait[0] = 'c';
	strcpy(a.di[0].nom,di);
	gchar c[ALPHABET] = "c";
	res = RechercheAnalyse(a,c[0],fait);
	CU_ASSERT_EQUAL(res,'d');
	a.nbdi = 2;
	fait[1] = 'd';
	gchar* di2 = "ce";
	strcpy(a.di[1].nom,di2);
	res = RechercheAnalyse(a,c[0],fait);
	CU_ASSERT_EQUAL(res,'e');
	
}
void TestRecherche2()
{
	RESSOURCESLANGUE r	;
	gchar res = '0';
	gchar* di = "cd";
	gchar fait[26];
	fait[0] = 'c';
	strcpy(r.di[0].nom,di);
	gchar c[ALPHABET] = "c";
	res = RechercheRessources(r,c[0],fait);
	CU_ASSERT_EQUAL(res,'d');

	fait[1] = 'd';
	gchar* di2 = "ce";
	strcpy(r.di[1].nom,di2);
	res = RechercheRessources(r,c[0],fait);
	CU_ASSERT_EQUAL(res,'e');
	
}
int setup(void)  { return 0; }
int teardown(void) { return 0; }

int main(int argc, char **argv)
{
	
	CU_initialize_registry();
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();	
	
	CU_pSuite suite = CU_add_suite("Suitecontenantlestest", setup,teardown);

    CU_add_test(suite, "CryptageVigenere", TestCryptageVigenere);
	CU_add_test(suite, "CryptageSubsitution", TestCryptageSubstitution);
	CU_add_test(suite, "AnalyseFrequentielle", TestAnalyseFrequentielle	);
	CU_add_test(suite, "PGCD", TestPGCD);
	CU_add_test(suite, "Kasiski", TestKasiski);
	CU_add_test(suite, "IndiceMutuelle", TestIndiceMutuelle);
	CU_add_test(suite, "DecryptageVigenere", TestDecrypteVigenere);
	CU_add_test(suite, "RemplacerCle", TestRemplacercle);
	CU_add_test(suite, "Remplace", TestRemplace);
	CU_add_test(suite, "Recherche", TestRecherche);
	CU_add_test(suite, "Recherche2", TestRecherche2);
	
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

    return 0;
}	

