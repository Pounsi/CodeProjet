LIBS=`pkg-config --libs gtk+-2.0`
SRC=Code

install:
	sudo apt-get install libgtk2.0-dev
	sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev
	
run: all clean
	./dcrypt
		
test: Ctest clean
	./test

all: main.o InterfaceGraphique.o Fonctions.o  CryptageVigenere.o CryptageSubstitution.o DecryptageVigenere.o DecryptageSubstitution.o AnalyseFrequentielle.o
	gcc main.o InterfaceGraphique.o Fonctions.o CryptageVigenere.o CryptageSubstitution.o DecryptageVigenere.o DecryptageSubstitution.o AnalyseFrequentielle.o -o dcrypt $(LIBS)

Ctest: Test.o InterfaceGraphique.o Fonctions.o  CryptageVigenere.o CryptageSubstitution.o DecryptageVigenere.o DecryptageSubstitution.o AnalyseFrequentielle.o
	gcc Test.o InterfaceGraphique.o Fonctions.o CryptageVigenere.o CryptageSubstitution.o DecryptageVigenere.o DecryptageSubstitution.o AnalyseFrequentielle.o -o test  -lcunit $(LIBS)

Fonctions.o: $(SRC)/Fonctions.c Headers/Fonctions.h
	gcc -c $(SRC)/Fonctions.c `pkg-config --cflags gtk+-2.0` -o Fonctions.o

CryptageVigenere.o: $(SRC)/CryptageVigenere.c Fonctions.o
	gcc -Wall `pkg-config --cflags gtk+-2.0` -c $(SRC)/CryptageVigenere.c

DecryptageVigenere.o: $(SRC)/DecryptageVigenere.c Fonctions.o AnalyseFrequentielle.o
	gcc -Wall `pkg-config --cflags gtk+-2.0` -c $(SRC)/DecryptageVigenere.c

DecryptageSubstitution.o : $(SRC)/DecryptageSubstitution.c Fonctions.o
	gcc -Wall `pkg-config --cflags gtk+-2.0` -c $(SRC)/DecryptageSubstitution.c

CryptageSubstitution.o : $(SRC)/CryptageSubstitution.c Fonctions.o
	gcc -Wall `pkg-config --cflags gtk+-2.0` -c $(SRC)/CryptageSubstitution.c

AnalyseFrequentielle.o : $(SRC)/AnalyseFrequentielle.c Fonctions.o
	gcc -Wall `pkg-config --cflags gtk+-2.0` -c $(SRC)/AnalyseFrequentielle.c

InterfaceGraphique.o: $(SRC)/InterfaceGraphique.c CryptageVigenere.o CryptageSubstitution.o DecryptageSubstitution.o DecryptageVigenere.o AnalyseFrequentielle.o
	gcc -Wall `pkg-config --cflags gtk+-2.0` -c $(SRC)/InterfaceGraphique.c

main.o: $(SRC)/main.c InterfaceGraphique.o
	gcc -c $(SRC)/main.c  `pkg-config --cflags gtk+-2.0` -o main.o

Test.o: Tests/Test.c InterfaceGraphique.o
	gcc -c Tests/Test.c  -lcunit `pkg-config --cflags gtk+-2.0` -o Test.o

clean:
	rm -f *core
	rm -f *.o
	rm -f police.h
	rm -f *.tar
	rm -f *.tgz
