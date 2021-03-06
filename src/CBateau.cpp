#include "CBateau.h"

/**
 * constructeur de CBateau sans aucun paramètre
 */
CBateau :: CBateau(){

    this-> m_taille = 0;
    this-> m_nom = "Neant";
    this-> m_position = make_pair(0,0);
    this-> m_pDegats = NULL;

}

/**
 * constructeur de CBateau avec paramètre
 * @param n string, nom du bateau
 * @param p pair<int,int>, position de départ du bateau
 * @param t int, taille du bateau
 */
CBateau :: CBateau(string n, pair<int,int> p, int t){

    if(p.first <0 || p.first >TAILLE_GRILLE-2 || p.second <0 || p.second >TAILLE_GRILLE-2 || t<1 || t>10 || p.second + t-1 >TAILLE_GRILLE-2){
        range_error e("Placement incorrect");
        throw e;
    }else{
        this-> m_nom = n;
        this-> m_position = p;
        this-> m_taille = t;
        this-> m_pDegats = new bool[this-> m_taille];
        for(int i=0;i<this -> m_taille;i++){
            this-> m_pDegats[i] = false;
        }
    }

}

/**
 * getter des dégats d'une position du bateau
 * @param i int, la position demandé
 * @return bool, vrai si touché a cet endroit, faux sinon
 */
bool CBateau :: getDegats(int i){

    bool ret = false;

    if(i>-1 && i<this-> m_taille){
        if(this-> m_pDegats[i] == true){
            ret = true;
        }
    }
    
    return ret;
}

/**
 * getter du nom du bateau
 * @return string, nom du bateau
 */
string CBateau :: getNom(){

    return this->m_nom;

}

/**
 * getter de la taille du bateau
 * @return int, taille du bateau
 */
int CBateau :: getTaille(){

    return this->m_taille;
    
}

/**
 * getter de la position de départ du bateau
 * @return pair<int,int>, position du bateau
 */
pair<int,int> CBateau :: getPosition(){

    return this->m_position;

}

/**
 * setter de la position du bateau
 * @param i int, position x
 * @param j int, position y
 */
void CBateau :: setPosition(int i,int j){

    if(i>-1 && i<10 && j<10 && j>-1){
        this->m_position.first = i;
        this->m_position.second = j; 
    }else{
        range_error s("Mauvais placement du bateau");
        throw s;
    }

}

/**
 * demande si le bateau est coulé
 * @return bool, vrai si le bateau est coule, faux sinon
 */
bool CBateau :: estCoule(){

    bool ret = true;

    for(int i= 0; i<this-> m_taille; i++){
        if(getDegats(i) == false){
            ret = false;
        }
    }

    return ret;
}

/**
 * reçois le tir de l'adversaire et regarde ce que ce tir fait, si il touche ou non
 * Si oui, alors le tir passe la position en touché et mets vrai sur le tableau correspondant aux dégats sur la position exact
 * Si non, il ne se passe rien
 * @param p pair<int,int>, la coordonné du tir
 * @return bool, vrai si le bateau est touché, faux sinon
 */
bool CBateau :: tirAdverse(pair<int,int> p){

    bool touche = false;
    if(p.first <0 || p.second<0 || p.first >TAILLE_GRILLE-2 || p.second >TAILLE_GRILLE-2){
        range_error t("Tir avec de mauvaise coordonnés");
        throw t;
    }else{
        for(int i=0; i< this-> m_taille;i++){
            if(p.first == this-> m_position.first && p.second == this-> m_position.second + i && !getDegats(i)){
                touche = true;
                this-> m_pDegats[i] = true;
            }
        }
    }
    return touche;
}

/**
 * permet de cout<< la classe bateau
 * @param os ostream&
 * @param theB CBateau&
 * @return ostream&
 */
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

/**
 * destructeur de la classe, détruis le tableau de dégat
 */
CBateau :: ~CBateau(){

    delete[] this->m_pDegats;

}

/**
 * 
 * @param bateau const CBateau&
 */
void CBateau:: operator=(const CBateau& bateau){

    if(this-> m_pDegats != NULL){
        delete[] this-> m_pDegats;
    }
    this-> m_taille = bateau.m_taille;
    this-> m_nom = bateau.m_nom;
    this-> m_position = bateau.m_position;
    this-> m_pDegats = bateau.m_pDegats;
}


CBateau :: CBateau(const CBateau &bateau){

    if (bateau.m_pDegats != NULL) {
        m_pDegats = new bool[bateau.m_taille];
        for (int i = 0; i < bateau.m_taille; i++) {
            m_pDegats[i] = bateau.m_pDegats[i];
        }
    } else {
        m_pDegats = NULL;
    }

    m_taille = bateau.m_taille;
    m_position = bateau.m_position;
    m_nom = bateau.m_nom;
}

