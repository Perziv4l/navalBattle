#include "CBateau.h"

CBateau :: CBateau(){

    this-> m_taille = 0;
    this-> m_nom = "Neant";
    this-> m_position = make_pair(0,0);
    this-> m_pDegats = NULL;

}

CBateau :: CBateau(string n, pair<int,int> p, int t){

    if(p.first <0 || p.first >9 || p.second <0 || p.second >9 || t<1 || t>10 || p.second + t-1 >9){
        range_error e("Placement incorrect");
        throw e;
    }else{
        this-> m_nom = n;
        this-> m_position = p;
        this-> m_taille = t;
        this-> m_pDegats = new bool[this-> m_taille];
    }

}

bool CBateau :: getDegats(int i){

    bool ret = false;

    if(i>-1 && i<this-> m_taille){
        if(this-> m_pDegats[i] == true){
            ret = true;
        }
    }
    
    return ret;
}

string CBateau :: getNom(){

    return this->m_nom;

}

int CBateau :: getTaille(){

    return this->m_taille;
    
}

pair<int,int> CBateau :: getPosition(){

    return this->m_position;

}

void CBateau :: setPosition(int i,int j){

    if(i>-1 && i<10 && j<10 && j>-1){
        this->m_position.first = i;
        this->m_position.second = j; 
    }else{
        range_error s("Mauvais placement du bateau");
        throw s;
    }

}

bool CBateau :: estCoule(){

    bool ret = true;

    for(int i=0; i<this-> m_taille; i++){
        if(this-> getDegats(i) == false){
            ret = false;
        }
    }

    return ret;
}

bool CBateau :: tirAdverse(pair<int,int> p){

    bool ret = false;
    if(p.first <0 || p.second<0 || p.first >9 || p.second >9){
        range_error t("Tir avec de mauvaise coordonnés");
        throw t;
    }else{
        if(p.first == this-> m_position.first){
            for(int i=this-> m_position.second;i<this-> m_taille+this-> m_position.second;i++){
                if(p.second == this-> m_position.second && this->m_pDegats[i-this-> m_position.second]==false){
                    ret = true;
                    this-> m_pDegats[i-this-> m_position.second]=true;
                }
            }
        }
    }
    return ret;

}

ostream& operator<<(ostream& os,CBateau& theB){

    os<<"Le nom du bateau est: "<<theB.getNom()<<"\nIl est de taille: "<<theB.getTaille()<<"\n Sa position de départ est: "<<theB.getPosition().first<<","<<theB.getPosition().second<<endl;
    if(theB.estCoule() == true){
        os<<"Le Bateau est coule"<<endl;
    }else{
        for(int i=0;i<theB.getTaille();i++){
            if(theB.getDegats(i) == true){
                os<<"Il a été touché à la case num "<<i+1<<endl;
            }
        }
    } 
    return os;

}

CBateau :: ~CBateau(){

    delete[] this->m_pDegats;

}

void CBateau:: operator=(const CBateau& bateau){

    if(this-> m_pDegats != NULL){
        delete[] this-> m_pDegats;
    }
    this-> m_taille = bateau.m_taille;
    this-> m_nom = bateau.m_nom;
    this-> m_position = bateau.m_position;
    this-> m_pDegats = bateau.m_pDegats;
}

