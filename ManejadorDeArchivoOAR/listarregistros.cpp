#include "listarregistros.h"
#include "ui_listarregistros.h"

listarRegistros::listarRegistros(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listarRegistros)
{
    ui->setupUi(this);
}

listarRegistros::~listarRegistros()
{
    delete ui;
}

void listarRegistros::on_cerrarListarRegistros_clicked()
{
    this->close();
}
