#ifndef BORRARCAMPOS_H
#define BORRARCAMPOS_H

#include <QDialog>

namespace Ui {
class BorrarCampos;
}

class BorrarCampos : public QDialog
{
    Q_OBJECT

public:
    explicit BorrarCampos(QWidget *parent = 0);
    void llenarComboBox(QStringList);
    ~BorrarCampos();

public:
    Ui::BorrarCampos *ui;

private slots:
    void on_buttonBox_accepted();
};

#endif // BORRARCAMPOS_H
