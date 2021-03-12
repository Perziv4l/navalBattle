/*
 * Cette classe caractérise le tableau qui est affiché à chaque joueur, elle possède plusieurs attributs:
 *      - la grille du joueur 1
 *      - la grille du joueur 2
 *      - pointeur sur l'armada du joueur
 *      - pointeur sur les tirs du joueurs
 */

#ifndef CGUI_H
#define CGUI_H

#include "BiblioStd.h"
#include "CArmada.h"
#include "CCoups.h"
#include "CBateau.h"
#include "CBaseJeu.h"

class CGui : public CBaseJeu{

    private:
        char m_grilleJou[TAILLE_GRILLE-1][TAILLE_GRILLE-1];
        char m_grilleAdv[TAILLE_GRILLE-1][TAILLE_GRILLE-1];
        CArmada* m_pArmada;
        CCoups* m_pCoup; 
    
    public:
        CGui();
        CGui(CArmada* pArmada,CCoups* pCoup);
        virtual ~CGui();
        void setArmadaCoups(CArmada* pArmada, CCoups* pCoup);
        bool positionnerBateaux();
        pair<int,int> choisirAttaque();
        void afficheGagne();
        void affichePerdu();
        friend ostream& operator<< ( ostream&os, CGui& theG );
        void remplirDeuxGrilles(ostream& os);
        void afficherLaGrille(ostream&   os,string jouOuAdv );
        
};
#endif // CGUI_H