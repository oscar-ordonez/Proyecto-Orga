#ifndef INDEX_H
#define INDEX_H
#include <QString>

class Index
{
    QString key;
    QString RRN;
public:
    Index();
    Index(QString,QString);

    void setKey(QString);
    QString getKey();

    void setRRN(QString);
    QString getRRN(char);

    int getLlave(int);
};

#endif // INDEX_H
