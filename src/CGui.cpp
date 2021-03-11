#include "CGui.h"

CGui :: CGui(){

    this -> m_pArmada = NULL;
    this -> m_pCoup = NULL;
}

CGui :: CGui(CArmada* pArmada,CCoups* pCoup){

    this -> m_pArmada = pArmada;
    this -> m_pCoup = pCoup;
}

CGui :: ~CGui(){

    delete[] this -> m_pArmada;
    delete[] this -> m_pCoup;
}

void CGui :: setArmadaCoup(CArmada* pArmada,CCoups* pCoup){
    this -> m_pArmada = pArmada;
    this -> m_pCoup = pCoup;

}

bool CGui :: positionnerBateaux(){
    bool reussite = this -> m_pArmada -> placerAleatoirement();
    return reussite;
}

pair<int,int> CGui :: choisirAttaque(){
    cout<<"***Vous Allez tiré votre missile"<<endl;
    bool aya = false;
    int x;
    while(!aya){
        cout<<"Veuillez saisir la coordonné Horizontale."<<endl;
        string in;
        cin>>in;
        try{
            x = stoi(in);
            if(x<TAILLE_GRILLE-1 && x > -1){
                aya = true;
            }   
        }catch(invalid_argument& e){
            cout<<"Coordonné invalide"<<endl;
        }
    }
    aya = false;
    int y;
    while(!aya){
        cout<<"Veuillez saisir la coordonné Vertical."<<endl;
        string in;
        cin>>in;
        try{
            y = stoi(in);
            if(y<TAILLE_GRILLE-1 && y > -1){
                aya = true;
            }   
        }catch(invalid_argument& e){
            cout<<"Coordonné invalide"<<endl;
        }
    }
    pair<int,int> ret(x,y);
    return ret;
}

void CGui :: afficheGagne(){

    cout<<"***************VOUS AVEZ GAGNE !!!!!***************"<<endl;
}

void CGui :: affichePerdue(){

    cout<<"***************VOUS AVEZ PERDUE ;( ***************"<<endl;
}

ostream& operator<<(ostream& os,CGui& theG){

    theG.remplirDeuxGrilles(os);
    return os;
}

void CGui :: remplirDeuxGrilles(ostream& os){
    for(int i =0; i<this -> m_pArmada -> getEffectifTotal(); i++){
        for(int y =0; y< this -> m_pArmada -> getBateau(i) -> getTaille();y++){
           pair<int,int> position = this -> m_pArmada -> getBateau(i) -> getPosition();
           int positionX = position.first;
           int positionY = position.second + y;
           char lettre = 'B';
           bool touch = this -> m_pArmada -> getBateau(i) -> getDegats(y);
           if(touch == true){
               lettre = 'X';
           }
           this -> m_grilleJou[positionX][positionY] = lettre;     
        }
    }
    for(int i=0; i< this -> m_pCoup -> getTaille("ploufAdverse");i++){

        pair<int,int> position = this -> m_pCoup -> getPair("ploufAdverse",i);
        int positionX = position.first;
        int positionY = position.second;
        char lettre = 'O';
        this -> m_grilleJou[positionX][positionY] = lettre;
    }
    afficherLaGrille(os,"joueur");

    for(int i=0; i< this -> m_pCoup -> getTaille("dansLEau");i++){

        pair<int,int> position = this -> m_pCoup -> getPair("dansLEau",i);
        int positionX = position.first;
        int positionY = position.second;
        char lettre = 'O';
        this -> m_grilleAdv[positionX][positionY] = lettre;
    }

    for(int i=0; i< this -> m_pCoup -> getTaille("touche");i++){

        pair<int,int> position = this -> m_pCoup -> getPair("touche",i);
        int positionX = position.first;
        int positionY = position.second;
        char lettre = 'X';
        this -> m_grilleAdv[positionX][positionY] = lettre;
    }
    afficherLaGrille(os,"adversaire");
}

void CGui :: afficherLaGrille(ostream& os,string jouOuAdv){
    
    string grille = "Grille"+jouOuAdv+"\n";
    for(int i=0; i<TAILLE_GRILLE;i++){
        if(i==0){
            grille += "        ";
        }else{
            grille += to_string(i-1) + "      ";
        }
    }
    for(int i=0;i<TAILLE_GRILLE;i++){
        grille += "\n \n"+to_string(i)+"      ";
        for(int y=0;y<TAILLE_GRILLE;y++){
            if(this -> m_grilleJou[i][y]!= 'O' || this -> m_grilleJou[i][y]!= 'X' || this -> m_grilleJou[i][y]!= 'B'){
                grille += "       ";
            }else{
                grille += this -> m_grilleJou[i][y]+"      ";
            }
        }
    }
}