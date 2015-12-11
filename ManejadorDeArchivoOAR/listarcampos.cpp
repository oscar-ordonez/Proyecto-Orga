#include "listarcampos.h"
#include "ui_listarcampos.h"
#include "campo.h"
ListarCampos::ListarCampos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListarCampos)
{
    ui->setupUi(this);
}

ListarCampos::~ListarCampos()
{
    delete ui;
}
 void ListarCampos::llenarTabla(QList <Campo> listaCampos){
    /*for(int i = 0; i < listaCampos.size(); i++){
        int row = ui->tablaListar->rowCount();
        ui->tablaListar->insertRow(row);
        ui->tablaListar->setItem(row,0,new QTableWidgetItem(listaCampos.at(i).getNombreCampo()));
        ui->tablaListar->setItem(row,1,new QTableWidgetItem(listaCampos.at(i).getTipoCampo()));
        ui->tablaListar->setItem(row,2,new QTableWidgetItem(QString::listaCampos.at(i).getTamanoCampo()));
        if(listaCampos.at(i).getEsLlave()){
            ui->tablaCampos->setItem(row,3,new QTableWidgetItem("Si"));
        }else{
            ui->tablaCampos->setItem(row,3,new QTableWidgetItem("No"));
        }
    }*/
 }
