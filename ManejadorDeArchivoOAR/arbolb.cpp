#include "arbolb.h"

ArbolB::ArbolB(){

}

QList<nodo> ArbolB::getNodos(){
    return nodos;
}

void ArbolB::setNodos(QList<nodo> nodo){
    this->nodos=  nodo;
}

void ArbolB::insertNode(nodo nodo){
    nodos.append(nodo);
}

int ArbolB::insertIndex(Index index,int posicion,int tipo){
    int retrn = posicion;
    if(tipo==1){
        if(nodos.count()>0){
            if(!(nodos[posicion].getSons()[0]==-1)){
                for(int i=0;i<nodos[posicion].getData().count();i++){
                    if(nodos[posicion].getData()[i].getKey()!=""){
                        if(nodos[posicion].getLeftSon(i)!=-1 && index.getKey()<nodos[posicion].getData()[i].getKey()){
                            insertIndex(index,nodos[posicion].getLeftSon(i),1);
                        }else if(i==nodos[posicion].getData().count()-1){
                            insertIndex(index,nodos[posicion].getRightSon(i),1);
                        }
                    }else{
                        insertIndex(index,nodos[posicion].getLeftSon(i),1);
                        break;
                    }
                }
            }else if(nodos[posicion].getData()[61].getKey()==""){
                nodos[posicion].insertIndex(index,nodos[posicion].disponible(index,1));
            }else{
                int sonPlace = nodos[posicion].datosTemp(index,1);
                nodos[posicion].insertSonTemp(sonPlace,-1);
                retrn = divide(posicion,1);
            }
        }else{
            nodos.append(nodo());
            nodos[posicion].setIndex(index,0);
        }
    }else{
        if(nodos.count()>0){
            if(!(nodos[posicion].getSons()[0]==-1)){
                for(int i=0;i<nodos[posicion].getData().count();i++){
                    if(nodos[posicion].getData()[i].getKey()!=""){
                        if(nodos[posicion].getLeftSon(i)!=-1 && index.getKey().toInt()<nodos[posicion].getData()[i].getKey().toInt()){
                            insertIndex(index,nodos[posicion].getLeftSon(i),2);
                        }else if(i==nodos[posicion].getData().count()-1){
                            insertIndex(index,nodos[posicion].getRightSon(i),2);
                        }
                    }else{
                        insertIndex(index,nodos[posicion].getLeftSon(i),2);
                        break;
                    }
                }
            }else if(nodos[posicion].getData()[61].getKey()==""){
                nodos[posicion].insertIndex(index,nodos[posicion].disponible(index,2));
            }else{
                int sonPlace = nodos[posicion].datosTemp(index,2);
                nodos[posicion].insertSonTemp(sonPlace,-1);
                retrn = divide(posicion,2);
            }
        }else{
            nodos.append(nodo());
            nodos[posicion].setIndex(index,0);
        }
    }
    return retrn;
}


int ArbolB::divide(int pos,int tipo){
    int pa=pos;
 if(tipo==1){
    Index temp = nodos[pos].removeHalf();
    nodo tempiz;
    nodo tempder;
    for(int i=0;i<31;i++){
        if(i<30){
            tempiz.setIndex(nodos[pos].getData()[i],i);
            tempiz.setSon(nodos[pos].getSons()[i],i);
        }else{
            tempiz.setSon(nodos[pos].getSons()[i],i);
        }
    }
    int j =30;
    for(int i=0;i<32;i++){
        if(i<31){
            tempder.setIndex(nodos[pos].getData()[j],i);
            tempder.setSon(nodos[pos].getSons()[j],i);
        }else{
            tempder.setSon(nodos[pos].getSons()[j],i);
        }
        j++;
    }
    nodos.removeAt(pos);
    nodos.insert(pos,tempiz);
    nodos.append(tempder);
    int nuevaconeccion = nodos.count()-1;
    int pospadre=-1;
    for(int i=0;i<nodos.count();i++){
        for(int j=0;j<nodos[i].getSons().count();j++){
            if(nodos[i].getSons()[j]==pos){
                pospadre=i;
            }
        }
    }

    if(pospadre==-1){
        nodos.append(nodo());
        nodos[nodos.count()-1].setIndex(temp,0);
        nodos[nodos.count()-1].setSon(pos,0);
        nodos[nodos.count()-1].setSon(nuevaconeccion,1);
        pa=nodos.count()-1;
    }else{

        if(nodos[pospadre].getData()[62].getKey()==""){
            int lugar = nodos[pospadre].disponible(temp,1);
            nodos[pospadre].insertIndex(temp,lugar);
            nodos[pospadre].insertSon(nuevaconeccion,lugar+1);
            pa=pospadre;

        }

       else{
            int sonPlace = nodos[pospadre].datosTemp(temp,1);
            nodos[pospadre].insertSonTemp(sonPlace,nuevaconeccion);
            divide(pospadre,1);
        }

    }
 }else{
     Index temp = nodos[pos].removeHalf();
     nodo tempiz;
     nodo tempder;
     for(int i=0;i<31;i++){
         if(i<30){
             tempiz.setIndex(nodos[pos].getData()[i],i);
             tempiz.setSon(nodos[pos].getSons()[i],i);
         }else{
             tempiz.setSon(nodos[pos].getSons()[i],i);
         }
     }
     int j =30;
     for(int i=0;i<32;i++){
         if(i<31){
             tempder.setIndex(nodos[pos].getData()[j],i);
             tempder.setSon(nodos[pos].getSons()[j],i);
         }else{
             tempder.setSon(nodos[pos].getSons()[j],i);
         }
         j++;
     }
     nodos.removeAt(pos);
     nodos.insert(pos,tempiz);
     nodos.append(tempder);
     int nuevaconeccion = nodos.count()-1;
     int pospadre=-1;
     for(int i=0;i<nodos.count();i++){
         for(int j=0;j<nodos[i].getSons().count();j++){
             if(nodos[i].getSons()[j]==pos){
                 pospadre=i;
             }
         }
     }

     if(pospadre==-1){
         nodos.append(nodo());
         nodos[nodos.count()-1].setIndex(temp,0);
         nodos[nodos.count()-1].setSon(pos,0);
         nodos[nodos.count()-1].setSon(nuevaconeccion,1);
         pa=nodos.count()-1;
     }else{

         if(nodos[pospadre].getData()[62].getKey()==""){
             int lugar = nodos[pospadre].disponible(temp,2);
             nodos[pospadre].insertIndex(temp,lugar);
             nodos[pospadre].insertSon(nuevaconeccion,lugar+1);
             pa=pospadre;

         }

        else{
             int sonPlace = nodos[pospadre].datosTemp(temp,2);
             nodos[pospadre].insertSonTemp(sonPlace,nuevaconeccion);
             divide(pospadre,2);
         }

     }
 }
    return pa;

}

QList<int> ArbolB::searchIndex(QString in,int pos,int tipo){
    int posnodo=-1;
    int posdata = -1;
    if(nodos.count()>0){
    if(tipo==1){
    if(!(nodos[pos].getSons()[0]==-1)){
        for(int i=0;i<nodos[pos].getData().count();i++){
            if(nodos[pos].getData()[i].getKey()!=""){
                if(nodos[pos].getData()[i].getKey()!=in){
                if(nodos[pos].getLeftSon(i)!=-1 && in<nodos[pos].getData()[i].getKey()){
                   searchIndex(in,nodos[pos].getLeftSon(i),1);
                 }else if(i==nodos[pos].getData().count()-1){
                    searchIndex(in,nodos[pos].getRightSon(i),1);
                }
                }else{
                    posnodo=pos;
                    posdata=i;
                    break;
                }
            }else{
                searchIndex(in,nodos[pos].getLeftSon(i),1);
                break;
            }
       }
    }else{
        for(int i=0;i<nodos[pos].getData().count();i++){
            if(nodos[pos].getData()[i].getKey()==in){
                posnodo=pos;
                posdata=i;
                break;
            }
        }
    }

    }else{
        if(!(nodos[pos].getSons()[0]==-1)){
            for(int i=0;i<nodos[pos].getData().count();i++){
                if(nodos[pos].getData()[i].getKey()!=""){
                    if(nodos[pos].getData()[i].getKey()!=in){
                    if(nodos[pos].getLeftSon(i)!=-1 && in.toInt()<nodos[pos].getData()[i].getKey().toInt()){
                       searchIndex(in,nodos[pos].getLeftSon(i),2);
                     }else if(i==nodos[pos].getData().count()-1){
                        searchIndex(in,nodos[pos].getRightSon(i),2);
                    }
                    }else{
                        posnodo=pos;
                        posdata=i;
                        break;
                    }
                }else{
                    searchIndex(in,nodos[pos].getLeftSon(i),2);
                    break;
                }
            }
        }else{
            for(int i=0;i<nodos[pos].getData().count();i++){
                if(nodos[pos].getData()[i].getKey().toInt()==in.toInt()){
                    posnodo=pos;
                    posdata=i;
                    break;
                }
            }
        }
    }
    }//fin primer if
    QList<int> mandar;
    mandar.append(posnodo);
    mandar.append(posdata);

    return mandar;
}
