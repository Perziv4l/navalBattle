#include "CBateau.h"

int main(){

    cout<<"Test constructeur CBateau()"<<endl;
    CBateau test;

    if(test.getTaille()==0 && test.getNom() == "Neant" && test.getPosition().first == 0 && test.getPosition().second == 0){
        cout<<"Test Ok"<<endl;            
    }else{
        cout<<"Test Non Ok"<<endl;
    }

    cout<<"Test constructeur CBateau(string,pair,int) cas normal"<<endl;
    
    pair<int,int> testConstrct(1,2);
    CBateau testConstructNormal("Cuirasser",testConstrct,5);
    if(testConstructNormal.getTaille() ==5 && testConstructNormal.getNom() == "Cuirasser" && testConstructNormal.getPosition().first==1 && testConstructNormal.getPosition().second ==2){
        cout<<"Test Ok"<<endl;            
    }else{
        cout<<"Test Non Ok"<<endl;
    }

    cout<<"Test constructeur CBateau(string,pair,int) cas d'erreur"<<endl;
    pair<int,int> testConstrctErr(15,2);
    try{
        CBateau testConstructErreur("Cuirasser",testConstrctErr,5);
        cout<<"Test Non Ok"<<endl;
    }catch(range_error& c){
        cout<<"Test Ok"<<endl;
    }

    cout<<"Test getter"<<endl;
    pair<int,int> testGetter(2,3);
    try{
        CBateau testGet("Cuirasser",testGetter,4);
        if(testGet.getNom() == "Cuirasser"){
            cout<<"Test Ok"<<endl;
        }else{
            cout<<"Test Non Ok"<<endl;
        }
        pair<int,int> compare(2,3);
        if(testGet.getPosition()== compare){
            cout<<"Test Ok"<<endl;
        }else{
            cout<<"Test Non Ok"<<endl;
        }
        if(testGet.getTaille()==4){
            cout<<"Test Ok"<<endl;
        }else{
            cout<<"Test Non Ok"<<endl;
        }
    }catch(range_error& c){
        cout<<"Erreur de placement du bateau"<<endl;
    }

    cout<<"Test du setter de position cas normal"<<endl;
    pair<int,int> testSetter(3,3);
    try{
        CBateau testSet("Sous-Marin",testSetter,1);
        testSet.setPosition(1,1);
        try{
            if(testSet.getPosition().first == 1 && testSet.getPosition().second == 1){
                cout<<"Test Ok"<<endl;
            }else{
                cout<<"Test Non Ok"<<endl;
            }
        }catch(range_error& s){
            cout<<"Test Non Ok"<<endl;
        }
    }catch(range_error& c){
        cout<<"Test Non Ok"<<endl;
    }

    cout<<"Test du setter de position cas erreur"<<endl;
    try{
        CBateau testSetErreur("Sous-Marin",testSetter,1);
        try{
            testSetErreur.setPosition(15,1);
            if(testSetErreur.getPosition().first == 1 && testSetErreur.getPosition().second == 1){
                cout<<"Test Non Ok"<<endl;
            }else{
                cout<<"Test Non Ok"<<endl;
            }
        }catch(range_error& s){
            cout<<"Test Ok"<<endl;
        }
    }catch(range_error& c){
        cout<<"Test Non Ok"<<endl;
    }

    cout<<"Test Degat sur Bateau normal"<<endl;
    pair<int,int> degat(2,3);
    try{
        CBateau testDegat("Sous Marin",degat,1);
        pair<int,int> tirAdversaire(2,3);
        try{
            testDegat.tirAdverse(tirAdversaire);
            if(testDegat.getDegats(0)){
                cout<<"Test Ok"<<endl;
            }else{
                cout<<"Test Non Ok"<<endl;
            }
            cout<<"Test Coulé"<<endl;
            if(testDegat.estCoule()){
                cout<<"Test Ok"<<endl;
            }else{
                cout<<"Test Non Ok"<<endl;
            }
        }catch(range_error& t){
            cout<<"Test Non Ok"<<endl;
        }
        
    }catch(range_error& c){
        cout<<"Test Non Ok"<<endl;
    }

    cout<<"Test Degat Erreur"<<endl;
    pair<int,int> degatErr(2,3);
    try{
        CBateau testDegatErreur("Sous Marin",degatErr,1);
        pair<int,int> tirAdversaireErr(15,2);
        try{
            testDegatErreur.tirAdverse(tirAdversaireErr);
            cout<<"Test Non Ok"<<endl;
        }catch(range_error& t){
            cout<<"Test Ok"<<endl;
        }
    }catch(range_error& c){
        cout<<"Test Non Ok"<<endl;
    }

    cout<<"Test Degat sur Bateau grand"<<endl;
    pair<int,int> degats(2,3);
    try{
        CBateau testDegat("Sous Marin",degats,2);
        pair<int,int> tirAdversaire(2,3);
        try{
            testDegat.tirAdverse(tirAdversaire);
            if(testDegat.getDegats(0)){
                cout<<"Test Ok"<<endl;
            }else{
                cout<<"Test Non Ok"<<endl;
            }
            cout<<"Test Coulé"<<endl;
            if(!testDegat.estCoule()){
                cout<<"Test Ok"<<endl;
            }else{
                cout<<"Test Non Ok"<<endl;
            }
        }catch(range_error& t){
            cout<<"Test Non Ok"<<endl;
        }
        
    }catch(range_error& c){
        cout<<"Test Non Ok"<<endl;
    }
    return 0;
}