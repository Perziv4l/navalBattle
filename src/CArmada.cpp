#include "CArmada.h"


void CArmada :: ajouterBateau(CBateau& unBat){

    if (&m_listeBateaux == NULL){
        throw range_error("Can't add a ship into a null armada array.");
    }else{
        this -> m_listeBateaux.push_back(unBat);
    }
}

CBateau* CArmada :: getBateau(int i){

    if((i >= (int)this -> m_listeBateaux.size()) | (i < 0)){
        range_error e("out of range");
        throw e;
    }
    return &this-> m_listeBateaux[i];
}

int CArmada :: getEffectifTotal(){

    return (int)(this-> m_listeBateaux).size();

}

int CArmada :: getNbreTotCases(){

    int ret =0;

    for(int i=0; i<getEffectifTotal();i++){
         ret += this-> m_listeBateaux[i].getTaille();
    }

    return ret;
}

int CArmada :: getEffectif(){

    int ret =0;

    for(int i=0;i<(int)(this-> m_listeBateaux).size();i++){

        if(!this-> m_listeBateaux[i].estCoule()){
            ret++;
        }
    }

    return ret;
}

void CArmada :: getArmadaFromFile(){

    const char* nomFich= "/home/perzival/Desktop/IUT/C++/ProjetNavalBattleEtud/navalBattle/ws/flotille.txt";
    ifstream input;
    input.open(nomFich, ios::in);
    string maChaine;
    pair<int,int> base(0,0);

    while(maChaine != ";"){
        getline(input, maChaine,'\n');
        if((maChaine.at(0)!='#') & (maChaine != ";")){
            istringstream tmp(maChaine);
            string nomBateau;
            int nbBateauInt;
            int taille;
            tmp>> nomBateau >> nbBateauInt >> taille;
            if (nbBateauInt >= 1) {
                for (int i = 0; i < nbBateauInt; i++) {
                    CBateau b(nomBateau, make_pair(0, 0), taille);
                    ajouterBateau(b);
                }
            }
        }        
    }   
    input.close();
}


bool CArmada :: placerAleatoirement(){

    srand( (unsigned)time(NULL));
    int borneSup = TAILLE_GRILLE - 2;

    if (this->getNbreTotCases() > borneSup*borneSup) {
        return false;
    }

    vector<pair<int, int>> busy_cases;
    int error = 0;

    for (int i = 0; i < (int)m_listeBateaux.size(); i++) {

        int x = rand()%(borneSup + 1);
        int y = rand()%(borneSup + 1);

        int j = 0;
        bool found = true;

        if (x + this->m_listeBateaux[i].getTaille() > borneSup) {
            found = false;
        } else if (i > 0) {

            while (found and j <= (int)busy_cases.size()) {

                for (int k = 0; k < this->m_listeBateaux[i].getTaille(); k++) {

                    if (&busy_cases[j] != NULL and busy_cases[j].first == x+k and busy_cases[j].second == y) {
                        found = false;
                    }

                }

                j++;

            }
        }

        if (found) {

            for (int j = 0; j < this->m_listeBateaux[i].getTaille(); j++) {
                busy_cases.push_back(make_pair(x+j,y));
            }

            this->m_listeBateaux[i].setPosition(x,y);

            i++;

        } else {

            error++;

            if (error >= MAXESSAIS) {
                return false;
            }

        }

    }

    return true;

}