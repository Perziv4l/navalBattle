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

    for(int i =0; i< (int)this-> m_listeBateaux.size();i++){

        bool save = false;
        int positionYmax;
        int positionXmin;
        int positionYmin;
        while(!save){

            save = true;
            positionXmin = rand()%(TAILLE_GRILLE - 1);
            positionYmin = rand()%(TAILLE_GRILLE - 1);
            positionYmax = positionYmin + this-> m_listeBateaux[i].getTaille()-1;
            if(positionYmax>TAILLE_GRILLE-1){
                save = false;
            }
            for(int j =0; j< (int)this-> m_listeBateaux.size();j++){
                for(int y =0; y< (int)this-> m_listeBateaux[j].getTaille();y++){
                    for(int z=positionYmin; z<=positionYmax; z++){
                        if(this-> m_listeBateaux[j].getPosition().first == positionXmin && this-> m_listeBateaux[j].getPosition().second + y == z){
                            save = false;
                        }
                    }
                }
            }
        }
        this-> m_listeBateaux[i].setPosition(positionXmin,positionYmin);
        save = false;
    }

    for(int i=0;i<(int)this -> m_listeBateaux.size();i++){
        string prems = to_string(this ->m_listeBateaux[i].getPosition().first);
        string deuz = to_string(this -> m_listeBateaux[i].getPosition().second);

        cout<<prems<<deuz<<endl;
    }
    return true;

}