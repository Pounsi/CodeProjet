LIBS=`pkg-config --libs gtk+-2.0`

run: all clean
	./dcrypt
		
test: Ctest clean
	./test

all: main.o InterfaceGraphique.o Fonctions.o  CryptageVigenere.o CryptageSubstitution.o DecryptageVigenere.o DecryptageSubstitution.o AnalyseFrequentielle.o
	gcc main.o InterfaceGraphique.o Fonctions.o CryptageVigenere.o CryptageSubstitution.o DecryptageVigenere.o DecryptageSubstitution.o AnalyseFrequentielle.o -o dcrypt $(LIBS)

Ctest: Test.o InterfaceGraphique.o Fonctions.o  CryptageVigenere.o CryptageSubstitution.o DecryptageVigenere.o DecryptageSubstitution.o AnalyseFrequentielle.o
	gcc Test.o InterfaceGraphique.o Fonctions.o CryptageVigenere.o CryptageSubstitution.o DecryptageVigenere.o DecryptageSubstitution.o AnalyseFrequentielle.o -o test  -lcunit $(LIBS)

Fonctions.o: Fonctions.c Fonctions.h
	gcc -c Fonctions.c `pkg-config --cflags gtk+-2.0` -o Fonctions.o

CryptageVigenere.o: CryptageVigenere.c Fonctions.o
	gcc -Wall `pkg-config --cflags gtk+-2.0` -c CryptageVigenere.c

DecryptageVigenere.o: DecryptageVigenere.c Fonctions.o AnalyseFrequentielle.o
	gcc -Wall `pkg-config --cflags gtk+-2.0` -c DecryptageVigenere.c

DecryptageSubstitution.o : DecryptageSubstitution.c Fonctions.o
	gcc -Wall `pkg-config --cflags gtk+-2.0` -c DecryptageSubstitution.c

CryptageSubstitution.o : CryptageSubstitution.c Fonctions.o
	gcc -Wall `pkg-config --cflags gtk+-2.0` -c CryptageSubstitution.c

AnalyseFrequentielle.o : AnalyseFrequentielle.c Fonctions.o
	gcc -Wall `pkg-config --cflags gtk+-2.0` -c AnalyseFrequentielle.c

InterfaceGraphique.o: InterfaceGraphique.c CryptageVigenere.o CryptageSubstitution.o DecryptageSubstitution.o DecryptageVigenere.o AnalyseFrequentielle.o
	gcc -Wall `pkg-config --cflags gtk+-2.0` -c InterfaceGraphique.c

main.o: main.c InterfaceGraphique.o
	gcc -c main.c  `pkg-config --cflags gtk+-2.0` -o main.o

Test.o: Test.c InterfaceGraphique.o
	gcc -c Test.c  -lcunit `pkg-config --cflags gtk+-2.0` -o Test.o

clean:
	rm -f *core
	rm -f *.o
	rm -f police.h
	rm -f *.tar
	rm -f *.tgz