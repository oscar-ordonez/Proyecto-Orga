#ifndef LISTARREGISTROS_H
#define LISTARREGISTROS_H

#include <QDialog>

namespace Ui {
class listarRegistros;
}

class listarRegistros : public QDialog
{
    Q_OBJECT

public:
    explicit listarRegistros(QWidget *parent = 0);
    ~listarRegistros();

private:
    Ui::listarRegistros *ui;
};

#endif // LISTARREGISTROS_H
