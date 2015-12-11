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
#include <fstream>
#include <cstring>


//algunas variables necearias
QString archivoAbierto = "";
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
    archivoAbierto = direccion;
    QFile archivo (direccion);
    archivo.open(QIODevice::ReadOnly);
    QTextStream tsreading (&archivo);
    //verificar si hay cosas escritas en el archivo
    QString contenido = tsreading.readAll();
    int caracteres = contenido.length();
    qDebug() << "El archivo contine " << caracteres << " caracteres";
    qDebug() << contenido;

    ui->tablaCampos->setVisible(true);
    if(caracteres > 0){
        QString registro, nombreCampo, tipoCampo, tamanoCampo, esLlave, sp="hola\\";
        int ubicacion = 0, row = ui->tablaCampos->rowCount();
        ui->tablaCampos->insertRow(row);
        for(int i = 0; i < caracteres; i++){
            if (contenido.at(i) == '|'){
                break;
            } else if(contenido.at(i) == ' '){
                switch (ubicacion){
                case 0:
                    ui->tablaCampos->setItem(row,ubicacion,new QTableWidgetItem(registro));
                    ubicacion++;
                    registro = "";
                    break;
                case 1:
                    ui->tablaCampos->setItem(row,ubicacion,new QTableWidgetItem(registro));
                    ubicacion++;
                    registro = "";
                    break;
                case 2:
                    ui->tablaCampos->setItem(row,ubicacion,new QTableWidgetItem(registro));
                    ubicacion++;
                    registro = "";
                    break;
                case 3:
                    ui->tablaCampos->setItem(row,ubicacion,new QTableWidgetItem(registro));
                    row = ui->tablaCampos->rowCount();
                    ui->tablaCampos->insertRow(row);
                    ubicacion = 0;
                    registro = "";
                    break;
                }
                //ui->tablaCampos->setItem(row,ubicacion,new QTableWidgetItem(registro));
            } else if(contenido.at(i) == sp.at(sp.size()-1)){
                qDebug() << "entro";
            } else if (contenido.at(i) != ' '){
                registro.append(contenido.at(i));
            }
        }
        QMessageBox::information(this,"Abrir archivo","El archivo que usted selecciono ya contiene campos");
    }else{

        QMessageBox::information(this,"Abrir archivo","El archivo que usted selecciono no contiene campos");
    }
}

QStringList titulos;//titulos de los campos

void MainWindow::on_crearCampo_clicked()
{

}

void MainWindow::on_pushButton_clicked()//accion no utilizada
{

}

void MainWindow::on_addRows_clicked()//accion no utilizada
{

}

void MainWindow::on_actionBorrar_Campos_triggered()
{

}

void MainWindow::on_actionSalvar_Archivo_triggered()
{

}
