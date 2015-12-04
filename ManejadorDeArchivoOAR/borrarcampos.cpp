#include "borrarcampos.h"
#include "ui_borrarcampos.h"

BorrarCampos::BorrarCampos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BorrarCampos)
{
    ui->setupUi(this);
}

BorrarCampos::~BorrarCampos()
{
    delete ui;
}

void BorrarCampos::llenarComboBox(QStringList campos){
    ui->cb_borrarCampo->addItems(campos);
}

void BorrarCampos::on_buttonBox_accepted()
{
    //ui->tablaCampos->removeColumn(ui->cb_borrarCampo->currentIndex());
}
