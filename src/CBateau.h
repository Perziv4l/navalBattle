/*
 * Cette classe caractérise les Bateaux de la bataille navale avec
 *      - La taille
 *      - Le nom    
 *      - La position
 *      - Les dégats
 */

#ifndef CBATEAU_H
#define CBATEAU_H

#include "BiblioStd.h"

class CBateau {

    private:
        int m_taille;
        string m_nom;
        pair<int,int> m_position;
        bool* m_pDegats;
    
    public:
        CBateau();
        CBateau(string n,pair<int,int> p,int t);
        bool getDegats(int i);
        string getNom();
        int getTaille();
        pair<int,int> getPosition();
        void setPosition(int i,int j);
        bool estCoule();
        bool tirAdverse(pair<int,int> p);
        friend ostream& operator<<(ostream& os,CBateau& theB);
        CBateau(const CBateau &bateau);
        ~CBateau();
        void operator=(const CBateau& bateau);

};
#endif // CBATEAU_H