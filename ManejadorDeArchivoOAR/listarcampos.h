#ifndef LISTARCAMPOS_H
#define LISTARCAMPOS_H

#include <QDialog>
#include "campo.h"
namespace Ui {
class ListarCampos;
}

class ListarCampos : public QDialog
{
    Q_OBJECT

public:
    explicit ListarCampos(QWidget *parent = 0);
    void llenarTabla(QList <Campo>);
    ~ListarCampos();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ListarCampos *ui;
};

#endif // LISTARCAMPOS_H
