#include "nodo.h"

nodo::nodo()
{
    QList<int> sons;

    for(int i=0;i<64;i++){
        sons.append(-1);
    }
    listSon=sons;
    QList<Index> index;

    for(int i=0;i<63;i++){
        index.append(Index("",""));
    }
    listData = index;
}


QList <Index> nodo::getData(){
    return listData;
}

QList<int > nodo:: getSons(){

    return listSon;
}

void nodo::setListData(QList < Index> data){
    listData = data;
}

void nodo::setListSon(QList<int> sons){
    listSon=sons;
}

void nodo::setIndex(Index indice,int posicion){
   if(posicion!=-1){
       listData.replace(posicion,indice);
   }
}

void nodo::setSon(int son, int posicion){
    if(posicion!=-1){
        listSon.replace(posicion,son);
    }
}

bool nodo::sonExist(){
    bool encontro = false;
    for(int i=0;i<listSon.count();i++){
        if(listSon[i]!=-1){
            encontro = true;
            break;
         }
    }
    return encontro;
}

int  nodo::getLeftSon(int posicion){
    return listSon[posicion];
}

int nodo::getRightSon(int posicion){
    return listSon[posicion+1];
}
int nodo::disponible(Index list,int tipo){
    int num=0;
    if(tipo==1){
    for(int i=0;i<listData.count();i++){
        if(listData[i].getKey()!=""){
            if(list.getKey()<listData[i].getKey()){
                num=i;
                break;
            }
        }else if(listData[i].getKey()==""){
            num=i;
            break;
        }
    }
    }else{
        for(int i=0;i<listData.count();i++){
            if(listData[i].getKey() !=""){
                if(list.getKey().toInt()<listData[i].getKey().toInt()){
                    num=i;
                    break;
                }
            }else if(listData[i].getKey()==""){
                num=i;
                break;
            }

        }
    }
    return num;
}
int nodo::lugar(){
    int disponible = -1;
    for(int i=0;i<62;i++){
        if(listData[i].getKey()==""){
            int disponible=i;
            break;
         }
    }

    return disponible;
}

int nodo::datosTemp(Index index,int tipo){
    int temp = 63;
    if(tipo==1){
    for(int i=0;i<listData.count();i++){
        if(index.getKey()<listData[i].getKey()){
            temp=i;
            break;
         }
    }
    listData.insert(temp,index);
    }else{
        for(int i=0;i<listData.count();i++){
            if(index.getKey().toInt()<listData[i].getKey().toInt()){
                temp=i;
                break;
             }
        }
    }
    return temp;
}

void nodo::insertSonTemp(int posicion,int son){
    listSon.insert(posicion+1,son);
}

Index nodo::removeHalf(){
    int half = (listData.count()/2)-2;
    Index temp = listData[half];
    listData.removeAt(half);
    return temp;
}

void nodo::insertIndex(Index indice,int posicion){
    listData.insert(posicion,indice);
    listData.removeAt(63);
}

void nodo::insertSon(int son,int posicion){
    listSon.insert(posicion,son);
    listSon.removeAt(64);
}
