# Makefile du projet "Bataille navale" A PLACER DANS /ws

# Chaque classe du projet doit être testée séparément.
# Il y aura donc un lanceur (main) par classe à tester.

# Ce makefile doit permettre de faire :
#	- la compilation du lanceur associé à chaque classe à tester
#	- la compilation du projet final (c-à-d main.cpp)

# Déclaration de quelques variables utiles au makefile
GPP = g++ -Wall
SRC = ../src
BIN = ../bin

# La cible "deleteAll" est exécutée en tapant la commande "make deleteAll"
deleteAll :
	@# Précéder chaque commande d'une TABULATION
	@echo suppression du contenu du répertoire ../bin
	rm -f $(BIN)/*.o $(BIN)/*.bin

# Test de la classe CBateau
# Compilation du lanceur testCBateau, pour cela (l'ordre de compilation est important en C++) :
#	- supprimer le contenu du répertoire "../bin" et
#	- d'abord compiler CBateau
#	- ensuite compiler testCBateau

# La cible "testCBateau" est exécutée en tapant la commande "make testCBateau"
testCBateau : deleteAll compilCBateau compilTestCBateau

# La cible "compilCBateau" est exécutée en tapant la commande "make compilCBateau"
compilCBateau :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CBateau
	$(GPP) $(SRC)/CBateau.cpp -o $(BIN)/CBateau.o -c

# La cible "compilTestCBateau" est exécutée en tapant la commande "make compilTestCBateau"
compilTestCBateau :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation testCBateau
	$(GPP) $(SRC)/testCBateau.cpp $(BIN)/CBateau.o -o $(BIN)/testCBateau.bin


# La cible "testArmada" est exécutée en tapant la commande "make testCArmada"
testCArmada : deleteAll compilCBateau compilCArmada compilTestCArmada

# La cible "compilCBateau" est exécutée en tapant la commande "make compilCArmada"
compilCArmada :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CArmada
	$(GPP) $(SRC)/CArmada.cpp -o $(BIN)/CArmada.o -c

# La cible "compilTestCArmada" est exécutée en tapant la commande "make compilTestCAramada"
compilTestCArmada :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation testCArmada
	$(GPP) $(SRC)/testCArmada.cpp $(BIN)/CBateau.o $(BIN)/CArmada.o -o $(BIN)/testCArmada.bin

# La cible "testGui" est exécutée en tapant la commande "make testCGui"
testCGui : deleteAll compilCGui compilCGui compilTestCGui

# La cible "compilCGui" est exécutée en tapant la commande "make compilCGui"
compilCGui :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CGui
	$(GPP) $(SRC)/CGui.cpp -o $(BIN)/CGui.o -c

# La cible "compilTestCGui" est exécutée en tapant la commande "make compilTestCGui"
compilTestCGui :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation testCGui
	$(GPP) $(SRC)/testCGui.cpp -o $(BIN)/testCGui.bin

# La cible "compilCCoups" est exécutée en tapant la commande "make compilCCoups"
compilCCoups :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CCoups
	$(GPP) $(SRC)/CCoups.cpp -o $(BIN)/CCoups.o -c

# La cible "compilCSocket" est exécutée en tapant la commande "make compilCSocket"
compilCSocket :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CSocket
	$(GPP) $(SRC)/CSocket.cpp -o $(BIN)/CSocket.o -c

# La cible "compilCClienSocket" est exécutée en tapant la commande "make compilCClientSocket"
compilCClientSocket :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CClientSocket
	$(GPP) $(SRC)/CClientSocket.cpp -o $(BIN)/CClientSocket.o -c

# La cible "compilCServeurSocket" est exécutée en tapant la commande "make compilCServerSocket"
compilCServerSocket :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CServeurSocket
	$(GPP) $(SRC)/CServerSocket.cpp -o $(BIN)/CServerSocket.o -c

# La cible "compilCJoueur" est exécutée en tapant la commande "make compilCJoueur"
compilCJoueur :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CJoueur
	$(GPP) $(SRC)/CJoueur.cpp -o $(BIN)/CJoueur.o -c

# La cible "compilCJoueurCli" est exécutée en tapant la commande "make compilCJoueurCli"
compilCJoueurCli :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CJoueurCli
	$(GPP) $(SRC)/CJoueurCli.cpp -o $(BIN)/CJoueurCli.o -c

# La cible "compilCJoueurServ" est exécutée en tapant la commande "make compilCJoueurServ"
compilCJoueurServ :
	@# Précéder chaque commande d'une TABULATION
	@echo Compilation CJoueurServ
	$(GPP) $(SRC)/CJoueurServ.cpp -o $(BIN)/CJoueurServ.o -c


# ICI, la cible de compilation finale pour obtenir main.bin
# A executer A LA FIN du projet en s'assurant que toutes les classes du projet compilent et s'exécutent sans erreurs !
# La cible "lanceurFinal"
lanceurFinal : deleteAll compilCBateau compilCArmada compilCCoups compilCGui compilCSocket compilCClientSocket compilCServerSocket compilCJoueur compilCJoueurCli compilCJoueurServ
	@echo Compilation lanceurFinal
	$(GPP) $(SRC)/main.cpp $(BIN)/CBateau.o $(BIN)/CArmada.o $(BIN)/CCoups.o $(BIN)/CGui.o $(BIN)/CSocket.o $(BIN)/CClientSocket.o $(BIN)/CServerSocket.o $(BIN)/CJoueur.o $(BIN)/CJoueurCli.o $(BIN)/CJoueurServ.o -o $(BIN)/main.bin


