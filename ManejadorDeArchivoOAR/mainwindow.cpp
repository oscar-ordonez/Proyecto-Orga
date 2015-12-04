#include "mainwindow.h"
#include "borrarcampos.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QInputDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

//algunas variables necearias
int row = 1;
int columns = 1;
QStringList campos;
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->panelCampos->setVisible(false);
    ui->tablaCampos->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionNuevo_Archivo_triggered()
{
    QMessageBox::StandardButton msgbox;
      msgbox = QMessageBox::question(this, "Nuevo archivo", "Desea crear un nuevo archivo?",
                                     QMessageBox::Yes|QMessageBox::No);
      if (msgbox == QMessageBox::Yes) {
        qDebug() << "Yes was clicked Nuevo Archivo";
        //verifica si existe la carpeta archivos. Si no existe la crea
        if(!QDir("Archivos").exists()){
            qDebug() << "Archivos carpet was create";
            QDir().mkdir("Archivos");
        }
        //pedir el nombre para el archivo
        bool ok;
        QString nombreArchivo = QInputDialog::getText(this, tr("Nuevo archivo"),
                                                 tr("Nombre del archivo:"), QLineEdit::Normal,
                                                 QDir::home().dirName(), &ok);
        if (ok && !nombreArchivo.isEmpty()) {
            qDebug() << "Nombre del archivo: " << nombreArchivo;
        }
        //crear archivo
        QFile archivo("./Archivos/" + nombreArchivo + ".ncr");
        archivo.open(QIODevice::WriteOnly | QIODevice::Truncate);
        archivo.close();
        QMessageBox::information(this,"Archivo nuevo","El archivo fue creado");
        qDebug() << "El archivo fue creado con exito";
      } else {
        qDebug() << "Yes was *not* clicked Nuevo Archivo";
      }
}

void MainWindow::on_actionSalir_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCrear_Campos_triggered()
{
    ui->panelCampos->setVisible(true);
}

void MainWindow::on_abrirArchivo_clicked()
{
    QString direccion = QFileDialog::getOpenFileName(this,tr("Abrir archivo"),"./Archivos/", "All files (*.*);;Text File (*.*)");
    qDebug() << "Direccion del archivo para abrir" + direccion;
    QFile archivo (direccion);
    archivo.open(QIODevice::ReadOnly);
    QTextStream tsreading (&archivo);
    //verificar si hay cosas escritas en el archivo
    QString contenido = tsreading.readAll();
    int caracteres = contenido.length();
    qDebug() << "El archivo contine " << caracteres << " caracteres";
    ui->tablaCampos->setVisible(true);
    if(caracteres > 0){

    }else{

    }
}

QStringList titulos;//titulos de los campos

void MainWindow::on_crearCampo_clicked()
{
    campos.append(ui->nombreCampo->text());
    ui->tablaCampos->setRowCount(row);
    ui->tablaCampos->setColumnCount(columns);
    titulos.append(ui->nombreCampo->text());
    ui->tablaCampos->setHorizontalHeaderLabels(titulos);
    ui->tablaCampos->show();
    columns++;
    ui->addRows->setEnabled(true);

    //reset campos
    ui->nombreCampo->setText("");
    ui->comboBoxTipoCampo->setCurrentIndex(0);
    ui->tamanoCampo->setValue(1);

}

void MainWindow::on_pushButton_clicked()//action no utilizada
{

}

void MainWindow::on_addRows_clicked()
{
    row++;
    ui->tablaCampos->insertRow(ui->tablaCampos->rowCount());
    ui->tablaCampos->show();
}

void MainWindow::on_actionBorrar_Campos_triggered()
{   //es menos eficiente
    //BorrarCampos borrarCampos;
    //borrarCampos.setModal(true);
    //borrarCampos.exec();
    borrarCampos = new BorrarCampos(this);
    borrarCampos->show();
    borrarCampos->llenarComboBox(campos);

}
