#include "campo.h"

Campo::Campo(){
}

Campo::Campo(QString nombreCampo, QString tipoCampo, int tamanoCampo, bool esLlave){
    this->nombreCampo = nombreCampo;
    this->tipoCampo = tipoCampo;
    this->tamanoCampo = tamanoCampo;
    this->esLlave = esLlave;
}

void Campo::setNombreCampo (const QString nombreCampo){
    this->nombreCampo = nombreCampo;
}

QString Campo::getNombreCampo() const{
    return nombreCampo;
}

void Campo::setTipoCampo (QString tipoCampo){
    this->tipoCampo = tipoCampo;
}

QString Campo::getTipoCampo() const{
    return tipoCampo;
}

void Campo::setTamanoCampo (int tamanoCampo){
    this->tamanoCampo = tamanoCampo;
}

int Campo::getTamanoCampo() const{
    return tamanoCampo;
}

void Campo::setEsLlave (bool esLlave){
    this->esLlave = esLlave;
}

bool Campo::getEsLlave() const{
    return esLlave;
}
