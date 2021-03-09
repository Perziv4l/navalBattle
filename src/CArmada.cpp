#include "CArmada.h"

void CArmada :: ajouterBateau(CBateau& unBat){

    this-> m_listeBateaux.push_back(unBat);

}

CBateau* CArmada :: getBateau(int i){

    return &this-> m_listeBateaux[i];

}

int CArmada :: getEffectifTotal(){

    return sizeof(this-> m_listeBateaux);

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

    for(int i=0;i<sizeof(this-> m_listeBateaux);i++){

        if(!this-> m_listeBateaux[i].estCoule()){
            ret++;
        }
    }

    return ret;
}

void CArmada :: getArmadaFromFile(){

    const char* nomFich= "flotille.txt";
    ifstream fluxIn(nomFich, ios::in);
    string maChaine;
    pair<int,int> base(0,0);

    while(!fluxIn.eof()){
        getline(fluxIn, maChaine,'\n');
        if(maChaine.at(0)!='#'){
            istringstream tmp(maChaine);
            string nomBateau;
            int nbrGrille;
            int taille;
            tmp>> nomBateau >> nbrGrille >> taille;
            for(int i=0;i<nbrGrille;i++){
                CBateau nouv(nomBateau,base,taille);
                ajouterBateau(nouv);
            }
        }
    }
    
    fluxIn.close();
}


bool CArmada :: placerAleatoirement(){

    bool ret = false;

    for(int i=0;i<getEffectifTotal();i++){
        
    }

    return ret;
}