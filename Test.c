#include <CUnit/Basic.h>
#include "InterfaceGraphique.h"

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
	tmp = 3/10;
	
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
/* void TestAnalyseFreq()
{
	ANALYSE a;
	int kas, taille;
	float tmp;
	gchar TexteCrypte[]	= "abcdefghijklmnopqrstuvwxyz"; 
	gchar TexteC[strlen(TexteCrypte)];
	kas = 3;
	ConvertisseurTableau(TexteC,&taille,TexteCrypte);
	RetirerToutCarSpec(TexteC,TexteC);
	a = AnalyseFreq(a,TexteC,kas); 	
	printf("\n %f", a.occ[0][0]);
	//CU_ASSERT_EQUAL(a.occ[0][0], 0.047337);	
} */
void TestKasiski()
{
	ANALYSE a;
	int kas, taille;
	gchar TexteCrypte[]	= "FTHKPVFCSIMEICEPOMVOEPDPGBYCCXKPVFPCQASWRSPDMEZKKLEDTHLLRKWIUEPGQMNDHWYIOAPQJIFPFCYUWPIVOYPPHCNXAWSKWUWTXVPPCNSVPHKGSKCICWEIPHGNMPBEPDIPWSTDUWPWCQEOTPNPPGYZQTIGYJTLREPSWGMVDSPZREWIOTGJPPIZFCBYKPBGCGGWIOPXKPVFPJQZXDLPNPYTAVQQIUDMQYRGWEWDXCOIDCIUESKDHWCEPEXTZMULRUWIPQEPEWWTXUZRQYGNPHGGMNWIGYZKWPGLYHTPFPWGDXTLRUQITEWCWEULRIZYNPQGAYKDENFWNOYPVITBYGXEKDWQYXKEVGOIUPNQFVPPWVAEUCIPZYXPPGPXKWHQTXTPXQFVPPVCLFKONCYPCYRGPWWTZCYXGDIUOIWITCCIPEWRPVFPRVWIWCIOAPQTIVWIEZRHTIPEHGYSWGICFEUZRQYGNPUWTETPWKRRGLPWDPFFRMPVSFI"; 
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
	gchar TexteCrypte[]	= "FTHKPVFCSIMEICEPOMVOEPDPGBYCCXKPVFPCQASWRSPDMEZKKLEDTHLLRKWIUEPGQMNDHWYIOAPQJIFPFCYUWPIVOYPPHCNXAWSKWUWTXVPPCNSVPHKGSKCICWEIPHGNMPBEPDIPWSTDUWPWCQEOTPNPPGYZQTIGYJTLREPSWGMVDSPZREWIOTGJPPIZFCBYKPBGCGGWIOPXKPVFPJQZXDLPNPYTAVQQIUDMQYRGWEWDXCOIDCIUESKDHWCEPEXTZMULRUWIPQEPEWWTXUZRQYGNPHGGMNWIGYZKWPGLYHTPFPWGDXTLRUQITEWCWEULRIZYNPQGAYKDENFWNOYPVITBYGXEKDWQYXKEVGOIUPNQFVPPWVAEUCIPZYXPPGPXKWHQTXTPXQFVPPVCLFKONCYPCYRGPWWTZCYXGDIUOIWITCCIPEWRPVFPRVWIWCIOAPQTIVWIEZRHTIPEHGYSWGICFEUZRQYGNPUWTETPWKRRGLPWDPFFRMPVSFI"; 
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

	
	CU_ASSERT_EQUAL(cle[0], 2);
	CU_ASSERT_EQUAL(cle[1], 11);
	CU_ASSERT_EQUAL(cle[2], 4);	
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
int main(int argc, char **argv)
{
	
	CU_initialize_registry();
	//TestCryptageVigenere();	
		
	CU_pSuite suite = CU_add_suite("Suitecontenantlestest", 0,0);

    CU_add_test(suite, "CryptageVigenere", TestCryptageVigenere);
	CU_add_test(suite, "CryptageSubsitution", TestCryptageSubstitution);
	//CU_add_test(suite, "AnalyseFreq", TestAnalyseFreq);
	CU_add_test(suite, "AnalyseFrequentielle", TestAnalyseFrequentielle	);
	CU_add_test(suite, "PGCD", TestPGCD);
	CU_add_test(suite, "Kasiski", TestKasiski);
	CU_add_test(suite, "IndiceMutuelle", TestIndiceMutuelle);
	CU_add_test(suite, "DecryptageVigenere", TestDecrypteVigenere);

	//	if (CUE_SUCCESS != CU_initialize_registry())
	//return CU_get_error();
	
	//=> rajouter test valeur du registre
	
	// fin  
	CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}	

