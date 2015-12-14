#include "index.h"

Index::Index() {

}

Index::Index(QString key,QString RRN){
    this->key = key;
    this->RRN = RRN;
}

void Index::setKey(QString key){
    this->key = key;
}

QString Index::getKey(){
    return key;
}

void Index::setRRN(QString RRN){
    this->RRN = RRN;
}

QString Index::getRRN(char letra){
    if(letra == 'I'){
        QString RRN2 = "      ";
        for(int i=0;i<RRN.length();i++){
            RRN2[i]=RRN[i];
        }
        return RRN2;
    }else{
        QString RRN2 = "          ";
        for(int i=0;i<RRN.length();i++){
            RRN2[i]=RRN[i];
        }
        return RRN2;
    }
}

int Index::getLlave(int n){
    return key.toInt();
}
