#include "CJoueurServ.h"
#include "CJoueurCli.h"
#include "CArmada.h"
#include "CGui.h"
#include "BiblioStd.h"

// Simple signature de la fonction dialogueChoix � d�clarer ici
int dialogueChoix ();

int main() {

	CGui* pGuiServ = NULL;
	CGui* pGuiCli = NULL;
	bool okPlcmt;

	// Nombre de cases de bateaux adverses touch�es par des tirs.
	// Si ce nombre = nbre total de cases de la flottille alors la flottille adverse est coul�e.
	int nbToucheAdverse = 0;

	// Pour d�marrer : choix client ou serveur
	int choix = dialogueChoix ();
	
	// Initialisation al�atoire
	srand(time(NULL));

	switch (choix) {
		
		// choix serveur
		case 0: {
			cout << "Mode serveur demarre..." << endl;

			// Construction de l'interface utilisateur c�t� serveur
			pGuiServ = new CGui();

			// Cr�ation du joueur de type serveur
			CJoueurServ jouServ ( pGuiServ );

			// Ouvrir la socket sur le port PORTCOM
			// Le serveur se met � l'�coute d'une connexion client sur ce port
			// Si cela se passe mal, une exception logic_error est lanc�e (et pas captur�e...)
			jouServ.openSocket( PORTCOM );

			// Attendre le client
			// Le message "... en attente du client" doit appara�tre
			jouServ.attenteClient();

			// R�cup�rer les donn�es du jeu � partir du fichier "flotille.txt" qui se trouve dans /ws.
			// L'armada est construite dynamiquement : on cr�e un pointeur sur cette armada.
			CArmada* pArmServ  = new CArmada();
			pArmServ->getArmadaFromFile();

			// Envoyer les donn�es du jeu au client.
			// L'armada "pArmServ" est envoy�e par r�seau au client.
			jouServ.envoisArmadaVersClient ( *pArmServ );

			// Le serveur attend que le client ait positionn� ses bateaux.
			// attendre() est m�thode de CJoueur.
			jouServ.attendre();
			
			// Structure de donn�es des tirs pour le serveur cr��e.
			CCoups* pCoupsServ = new CCoups();

			// Mise � jour de la GUI du serveur.
			// A noter : les structures point�es par pArmServ et pCoupsServ seront d�truites dans le destructeur de CGui.
			pGuiServ->setArmadaCoups ( pArmServ, pCoupsServ );
			
			// Finalement, le serveur place ses bateaux sur sa grille.
			okPlcmt = pGuiServ->positionnerBateaux();
			if (okPlcmt) cout << endl << "Placement armada reussi..." << endl << endl;
			else cout << endl << "*** PLACEMENT armada IMPOSSIBLE ! ***" << endl << endl;			

			/*** DEBUT DU JEU ***/
			// ancienne version du while(...) plus n�cessaire, la sortie se faisant avec 2 break
			// while ( (pArmServ->getEffectif() > 0) && (pArmServ->getNbreTotCases() != nbToucheAdverse) && okPlcmt ) {
			while ( okPlcmt ) {

				// C'est le serveur qui tire en premier
				pair<int,int> coup = pGuiServ->choisirAttaque ();
				
				// envoie d'un tir au client par r�seau
				// ET r�cup�ration de sa r�ponse (coul�, touch� ou plouf) pour mettre � jour pCoupsServ
				jouServ.attaque ( coup, *pCoupsServ );
				
				// Afficher les deux grilles pour le serveur
				cout << *pGuiServ;

				// mise � jour de nbToucheAdverse
				
				nbToucheAdverse = pCoupsServ->getCoupsBut();
				// Si toutes les cases de l'adversaire sont touch�es alors le serveur a gagn�	
				if (pArmServ->getNbreTotCases() == nbToucheAdverse) {
					// le serveur a gagn�
					cout << "LE SERVEUR" << endl;
					pGuiServ->afficheGagne();
					break;
				}

				// ATTENTE d'une attaque client par r�seau
				// D�s que le client tire, on lui envoie une r�ponse : coul�, touch� ou plouf
				jouServ.attaqueAdverse (pArmServ, pCoupsServ);
				
				// suite � l'attaque, le serveur peut perdre
				// Si il ne reste plus aucun bateau alors le serveur a perdu								              
				if (pArmServ->getEffectif() == 0) {
					// le serveur a perdu
					cout << "LE SERVEUR" << endl;
					pGuiServ->affichePerdu();
					break;
				}
                
				// Afficher les deux grilles pour le serveur
				cout << *pGuiServ;
			}

			// Obligatoire sinon "case 1" ex�cut�
			break;
		}

		// choix client
		case 1: {

			cout << "Mode client demarre..." << endl;

			// Construction de l'interface utilisateur c�t� client
			pGuiCli = new CGui();

			// Se connecter au serveur sur le port PORTCOM
			CJoueurCli jouCli ( pGuiCli );
			// Si cela se passe mal, une exception logic_error est lanc�e (et pas captur�e...)
			jouCli.connectServer ( "localhost", PORTCOM );	// "localhost" ou "127.0.0.1"

			cout << "Connexion au serveur Ok" << endl;

			// R�cup�rer les donn�es du jeu.
			// C'est le serveur qui cr�e l'armada client et le lui envoie par r�seau.
			CArmada* pArmCli  = jouCli.getArmadaCli();
			
			// Structure de donn�es des tirs pour le client cr��e.
			CCoups* pCoupsCli = new CCoups();

			// Mise � jour de la GUI du client.
			// A noter : les structures point�es par pArmCli et pCoupsCli seront d�truites dans le destructeur de CGui.
			pGuiCli->setArmadaCoups ( pArmCli, pCoupsCli );
			
			// Le client place ses bateaux sur sa grille.
			okPlcmt = pGuiCli->positionnerBateaux();
			if (okPlcmt) {
				cout << endl << "Placement armada reussi..." << endl << endl;
				// Le client informe le serveur qu'il a plac� ses bateaux
				jouCli.ok();
			}				
			else cout << endl << "*** PLACEMENT armada IMPOSSIBLE ! ***" << endl << endl;						
			

			/*** DEBUT DE PARTIE (pour le client) ***/
			// ancienne version du while(...) plus n�cessaire, la sortie se faisant avec 2 break
			// while ( (pArmCli->getEffectif() > 0) && ( pArmCli->getNbreTotCases() != nbToucheAdverse ) && okPlcmt ) {
			while ( okPlcmt ) {

				// ATTENTE d'une attaque du serveur par r�seau
				// D�s que le serveur tire, on lui envoie une r�ponse : coul�, touch� ou plouf
				jouCli.attaqueAdverse (pArmCli, pCoupsCli);

				// Afficher les deux grilles pour le client
				cout << *pGuiCli;

				// suite � l'attaque, le client peut perdre
				// Si il ne reste plus aucun bateau alors le client a perdu			               
				if (pArmCli->getEffectif() == 0) {
					// le client a perdu
					cout << "LE CLIENT" << endl;
					pGuiCli->affichePerdu();
					break;
				}

				// au client � choisir un tir
				pair<int,int> coup = pGuiCli->choisirAttaque ();

				// envoie d'un tir au serveur par le r�seau
				// ET r�cup�ration de sa r�ponse (coul�, touch� ou plouf) pour mettre � jour pCoupsCli
				jouCli.attaque ( coup, *pCoupsCli );
				
				// Afficher les deux grilles pour le client
				cout << *pGuiCli;
			
				// mise � jour de nbToucheAdverse
				nbToucheAdverse = pCoupsCli->getCoupsBut();
				
				// Si toutes les cases de l'adversaire sont touch�es alors le client a gagn�
				if (pArmCli->getNbreTotCases() == nbToucheAdverse) {
					// le client a gagn�
					cout << "LE CLIENT" << endl;
					pGuiCli->afficheGagne();
					break;
				}
			}

			// Obligatoire
			break;
		}

	}

	// Destruction des zones dynamiques
	if ( pGuiServ != NULL ) delete pGuiServ;
	if ( pGuiCli != NULL ) delete pGuiCli;

	return 0;
}

/**********************************************/

// Simple dialogue avec l'utilisateur : renvoie 0 pour un choix serveur, 1 pour un choix client
int dialogueChoix () {

	string str;
	int ret;

	cout << "Demarrer le client ou le serveur : tapez 0 pour le serveur / 1 pour le client" << endl;
	cout << "!! Le serveur doit etre demarre avant le client..." << endl;

	getline ( cin, str, '\n' );
	istringstream tmp (str);
	tmp >> ret;

	return ( ret );	
}

