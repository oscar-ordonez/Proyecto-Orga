#ifndef NODO_H
#define NODO_H
#include <QString>
#include <index.h>
#include <QList>

class nodo
{
    QList<Index> listData;
    QList<int> listSon;

public:
    nodo();
    QList < Index> getData();
    QList<int> getSons();

    void setListData(QList <Index>);
    void setListSon(QList<int>);

    void setIndex(Index,int);
    void setSon(int, int);

    bool sonExist();

    int  getLeftSon(int);
    int getRightSon(int);
    int disponible(Index,int);
    int lugar();
    int datosTemp(Index,int);

    void insertSonTemp(int,int);
    Index removeHalf();
    void insertIndex(Index,int);
    void insertSon(int,int);
};

#endif // NODO_H
