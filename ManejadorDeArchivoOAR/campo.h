#ifndef CAMPO_H
#define CAMPO_H
#include <QString>
class Campo
{

private:
    QString nombreCampo;
    QString tipoCampo;
    int tamanoCampo;
    bool esLlave;

public:

    Campo();
    Campo(QString, QString, int, bool);

    void setNombreCampo (QString);
    QString getNombreCampo();

    void setTipoCampo (QString);
    QString getTipoCampo();

    void setTamanoCampo (int);
    int getTamanoCampo();

    void setEsLlave (bool);
    bool getEsLlave();

};

#endif // CAMPO_H
