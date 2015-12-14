#ifndef ARBOLB_H
#define ARBOLB_H

#include <QString>
#include "index.h"
#include "nodo.h"
#include <QList>

class ArbolB
{
    QList<nodo> nodos;
public:
    ArbolB();
    QList <nodo> getNodos();
    void setNodos(QList<nodo>);
    int insertIndex(Index,int,int);
    int divide(int,int);
    void insertNode(nodo);
    QList<int> searchIndex(QString,int,int);
};

#endif // ARBOLB_H
