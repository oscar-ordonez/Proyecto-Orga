#ifndef CAMPO_H
#define CAMPO_H
#include <QString>
class Campo
{

public:
    QString nombreCampo;
    QString tipoCampo;
    int tamanoCampo;
    bool esLlave;

public:

    Campo();
    Campo(QString, QString, int, bool);

    void setNombreCampo (QString);
    QString getNombreCampo() const;

    void setTipoCampo (QString);
    QString getTipoCampo() const;

    void setTamanoCampo (int);
    int getTamanoCampo() const;

    void setEsLlave (bool);
    bool getEsLlave() const;

};

#endif // CAMPO_H
