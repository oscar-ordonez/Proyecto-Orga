#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "borrarcampos.h"
#include "campo.h"
#include <QList>
#include <QFile>
#include "index.h"
#include "arbolb.h"

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

    void on_abrirArchivoRegistro_clicked();

    void on_comboBoxArchivosRegistros_activated(const QString &arg1);

    void loadKeys();

    void on_siguienteRegistro_clicked();
    void on_modificarCampo_clicked();

    void on_comboBoxModificarCampo_currentIndexChanged(int index);

    void on_modificarCampo_2_clicked();

    void on_eliminarCampo_clicked();

    void on_comboBoxModificarCampo_activated(const QString &arg1);

    void exportXml();

    void exportJson();

    void exportExcel();

    void on_actionExportar_Excel_triggered();

    void on_actionCrear_Indices_triggered();

    void on_actionReindexar_Archivos_triggered();

private:

    QList<Campo> listaCampos;
    QList<QString> listaLlaves;
    QList<Campo> listaCamposAbiertos;
    QList<QString> listaCamposLlenados;
    int numCampoLlave;
    int numHead;
    int numEOSE;//endoffsetestructure
    int numOSH; //offsethead
    QFile fileArchivo;
    QFile fileIndice;
    QList<Index> indexList;
    ArbolB arbolB;
    Ui::MainWindow *ui;
    BorrarCampos *borrarCampos;
};

#endif // MAINWINDOW_H
