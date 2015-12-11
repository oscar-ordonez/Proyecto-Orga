#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "borrarcampos.h"
#include "campo.h"
#include <QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNuevo_Archivo_triggered();

    void on_actionSalir_triggered();

    void on_actionCrear_Campos_triggered();

    void on_pushButton_clicked();

    void on_abrirArchivo_clicked();

    void on_crearCampo_clicked();

    void on_addRows_clicked();

    void on_actionBorrar_Campos_triggered();

    void on_actionSalvar_Archivo_triggered();

    void on_actionCerrar_Archivo_triggered();

    void on_actionListar_Campos_triggered();

    void on_actionModificar_Campos_triggered();

    void on_actionIntroducir_Registros_triggered();

private:

    QList<Campo> listaCampos;
    Ui::MainWindow *ui;
    BorrarCampos *borrarCampos;
};

#endif // MAINWINDOW_H
