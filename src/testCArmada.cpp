#include "CArmada.h"

void testAjouterNormal();
void testGetEffectifTotalNormal();
void testGetBateauNormal();
void testGetBateauErreur();
void testGetEffectifNormal();

int main(){

    testAjouterNormal();
    testGetEffectifTotalNormal();
    testGetBateauNormal();
    testGetBateauErreur();
    //testGetEffectifTotalErreur();
    testGetEffectifNormal();
    //testGetEffectifErreur();
}

void testAjouterNormal(){

    cout<<"Test Ajouter Normal"<<endl;
    CArmada test;
    CBateau teste;
    test.ajouterBateau(teste);
    if(test.getEffectifTotal()==1){
        cout<<"Test Ok!"<<endl;
    }else{
        cout<<"Test Non Ok"<<endl;
    }
    
}

void testGetEffectifTotalNormal(){

    cout<<"Test Get Effectif Total Normal"<<endl;
    CArmada test;
    CBateau teste;
    test.ajouterBateau(teste);
    if(test.getEffectifTotal()==1){
        cout<<"Test Ok!"<<endl;
    }else{
        cout<<"Test Non Ok"<<endl;
    }
}

void testGetBateauNormal(){
    cout<<"Test Get Bateau Normal"<<endl;
    CArmada test;
    CBateau teste;
    test.ajouterBateau(teste);
    try{
        test.getBateau(0);
        cout<<"Test OK"<<endl;
    }catch(range_error& c){
        cout<<"Test Non OK"<<endl;
    }

}

void testGetBateauErreur(){
    cout<<"Test Get Bateau Erreur"<<endl;
    CArmada test;
    CBateau teste;
    test.ajouterBateau(teste);
    try{
        test.getBateau(1);
        cout<<"Test Non OK"<<endl;
    }catch(range_error& c){
        cout<<"Test OK"<<endl;
    }

}

void testGetEffectifNormal(){
    cout<<"Test Get Effectif"<<endl;
    CArmada test;
    CBateau teste;
    test.ajouterBateau(teste);
    pair<int,int> tir(0,0);
    teste.tirAdverse(tir);
    if(test.getEffectif() == 0){
        cout<<"Test Ok!"<<endl;
    }else{
        cout<<"Test Non Ok"<<endl;
    }

}