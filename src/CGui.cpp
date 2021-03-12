#include "CGui.h"

/**
 * constructeur sans parametre de CGui
 */
CGui :: CGui(){

    this -> m_pArmada = NULL;
    this -> m_pCoup = NULL;
    for(int i=0; i<TAILLE_GRILLE-1;i++){
        for(int y=0; y<TAILLE_GRILLE-1;y++){
            this-> m_grilleAdv[i][y]='-';
            this-> m_grilleJou[i][y]='-';
        }
    }
}

/**
 * constructeur avec l'armada et les coups joués
 * @param pArmada pArmada, l'armada du joueur
 * @param pCoup pCoup, pointeur sur le tableau de coup
 */
CGui :: CGui(CArmada* pArmada,CCoups* pCoup){

    this -> m_pArmada = pArmada;
    this -> m_pCoup = pCoup;
    for(int i=0; i<TAILLE_GRILLE-1;i++){
        for(int y=0; y<TAILLE_GRILLE-1;y++){
            this-> m_grilleAdv[i][y]='-';
            this-> m_grilleJou[i][y]='-';
        }
    }
}

/**
 * destructeur de CGui
 */
CGui :: ~CGui(){

    if(m_pArmada!= NULL){
        delete[] this -> m_pArmada;
    }
    if(m_pCoup!=NULL){
        delete[] this -> m_pCoup;
    }   
}

/**
 * setter des attributs de CGui
 * @param pArmada pArmada, l'armada du joueur
 * @param pCoup pCoup, pointeur sur le tableau de coup
 */
void CGui :: setArmadaCoups(CArmada* pArmada,CCoups* pCoup){
    this -> m_pArmada = pArmada;
    this -> m_pCoup = pCoup;

}

/**
 * positionne les bateaux en appelant le placement aléatoire de l'armada du joueur
 * @return bool, vrai si le placement aléatoire a été effectué, faux sinon
 */
bool CGui :: positionnerBateaux(){
    bool reussite = this -> m_pArmada -> placerAleatoirement();
    return reussite;
}

/**
 * choisir la position du missille envoyé
 * @return pair<int,int>, pair entier des position x,y
 */
pair<int,int> CGui :: choisirAttaque(){

    cout<<"***Vous Allez tiré votre missile"<<endl;

    bool aya = false;
    int x;

    while(!aya){ //Boucle tant que la coordonné saisie n'est pas valide
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
    
    while(!aya){ //Boucle tant que la coordonné saisie n'est pas valide
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

/**
 * Affiche à l'écran du vainceur qu'il a gagné
 */
void CGui :: afficheGagne(){

    cout<<"***************VOUS AVEZ GAGNE !!!!!***************"<<endl;
}

/**
 * affiche au perdant qu'il a perdue
 */
void CGui :: affichePerdu(){

    cout<<"***************VOUS AVEZ PERDUE ;( ***************"<<endl;
}

/**
 *
 */
ostream& operator<<(ostream& os,CGui& theG){

    theG.remplirDeuxGrilles(os);
    return os;
}

/**
 * Remplis les 2 grilles(joueur et adversaire) du joueurs
 * @param os ostream&
 */
void CGui :: remplirDeuxGrilles(ostream& os){

    for(int i =0; i<this -> m_pArmada -> getEffectifTotal(); i++){ //boucle sur tout les bateaux de l'armada

        for(int y =0; y< this -> m_pArmada -> getBateau(i) -> getTaille();y++){ //boucle sur toutes les positions pour marquer X ou B en fonction se si c'est touché ou non

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
    for(int i=0; i< this -> m_pCoup -> getTaille("ploufAdverse");i++){ // boucle sur le tableau de coup de l'adversaire qui ont été dans l'eau

        pair<int,int> position = this -> m_pCoup -> getPair("ploufAdverse",i);
        int positionX = position.first;
        int positionY = position.second;
        char lettre = 'O';
        this -> m_grilleJou[positionX][positionY] = lettre;
    }
    afficherLaGrille(os,"joueur");

    for(int i=0; i< this -> m_pCoup -> getTaille("dansLEau");i++){// boucle sur le tableau de coup du joueur qui ont été dans l'eau

        pair<int,int> position = this -> m_pCoup -> getPair("dansLEau",i);
        int positionX = position.first;
        int positionY = position.second;
        char lettre = 'O';
        this -> m_grilleAdv[positionX][positionY] = lettre;
    }

    for(int i=0; i< this -> m_pCoup -> getTaille("touche");i++){// boucle sur le tableau de coup du joueur qui ont touché

        pair<int,int> position = this -> m_pCoup -> getPair("touche",i);
        int positionX = position.first;
        int positionY = position.second;
        char lettre = 'X';
        this -> m_grilleAdv[positionX][positionY] = lettre;
    }
    afficherLaGrille(os,"adversaire");
}

/**
 * Affiche les grilles du joueur dans la console
 * @param jouOuAdv string, savoir si c'est la grille joueur ou adversaire
 * @param os ostream&
 */
void CGui::afficherLaGrille(ostream &os, string jouOuAdv)
{
  if (jouOuAdv.compare("joueur") == 0)
  {
    os << "========== Your grid ==========" << endl;
    for (int i = 0; i < TAILLE_GRILLE; i++) // boucle sur le nombre de ligne
    {
      if (i == 0) // premiere ligne
      {
        for(int j =0; j<TAILLE_GRILLE-1;j++){ // boucle pour donner la premiere ligne qui donne le numero des colonnes
            os << "   "<<j;
        }
      }
      else // toutes les autres lignes
      {
        os << i - 1 << "  "; // Numero des lignes

        for (int j = 0; j < TAILLE_GRILLE - 1; j++) // boucle qui affiche les lettres des différentes grilles
        {
          string theCase(1, m_grilleJou[i - 1][j]);
          os << theCase << "   ";
        }
      }

      os << endl;
    }
  }
  else if (jouOuAdv.compare("adversaire") == 0)
  {
    os << "======= Opponent's grid =======" << endl;
    for (int i = 0; i < TAILLE_GRILLE; i++) // boucle sur le nombre de ligne
    {
      if (i == 0) //première ligne
      {
        for(int j =0; j<TAILLE_GRILLE-1;j++){ // boucle pour donner la premiere ligne qui donne le numero des colonnes
            os << "   "<<j;
        }
      }
      else //toutes les autres lignes
      {
        os << i - 1 << "  ";

        for (int j = 0; j < TAILLE_GRILLE - 1; j++) // boucle pour donner la premiere ligne qui donne le numero des colonnes
        {
          char currentCase = m_grilleAdv[i - 1][j];
          os << currentCase << "   ";
        }
      }
      os << endl;
    }
  }
  os << endl;
}