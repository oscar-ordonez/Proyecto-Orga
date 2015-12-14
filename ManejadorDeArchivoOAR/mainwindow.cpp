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
#include <QTextStream>


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
    ui->panelRegistros->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionNuevo_Archivo_triggered()
{
    //panels
    ui->panelRegistros->setVisible(false);
    ui->panelCampos->setVisible(false);

    //nuevo archivo
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
    //panels
    ui->panelRegistros->setVisible(false);
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
        QMessageBox::information(this,"Abrir archivo","El archivo que usted selecciono ya contiene campos");
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
    qDebug() << "le dio click a crear campo";
    ui->tablaCampos->setEditTriggers(false);
    QString nombreCampo = ui->nombreCampo->text();
    QString tipoCampo = ui->comboBoxTipoCampo->currentText();
    int tamanoCampo = ui->tamanoCampo->text().toInt();
    bool llave = false;

    qDebug() << "Campo: " << nombreCampo;
    qDebug() << "Tipo: " << tipoCampo;
    qDebug() << "Tamaño: " << tamanoCampo;

    if(ui->comboBoxEsLlave->currentText()=="Si"){
        llave = true;
        ui->comboBoxEsLlave->setVisible(false);
        ui->labelEsLlave->setVisible(false);
        ui->comboBoxEsLlave->removeItem(0);
    }

    qDebug() << "Llave: " << llave;

    if (nombreCampo != ""){
        bool campoDisponible = true;
        foreach (Campo temp, listaCampos) {
            if(temp.getNombreCampo() == nombreCampo){
                campoDisponible = false;
            }
        }

        if(campoDisponible){
            listaCampos.append(Campo(nombreCampo,tipoCampo,tamanoCampo,llave));
            int row = ui->tablaCampos->rowCount();
            ui->tablaCampos->insertRow(row);
            ui->tablaCampos->setItem(row,0,new QTableWidgetItem(nombreCampo));
            ui->tablaCampos->setItem(row,1,new QTableWidgetItem(tipoCampo));
            ui->tablaCampos->setItem(row,2,new QTableWidgetItem(QString::number(tamanoCampo)));
            if(llave){
                ui->tablaCampos->setItem(row,3,new QTableWidgetItem("Si"));
            }else{
                ui->tablaCampos->setItem(row,3,new QTableWidgetItem("No"));
            }
        }
    }

    ui->nombreCampo->setText("");
    ui->comboBoxTipoCampo->setCurrentIndex(0);
    ui->tamanoCampo->setValue(1);
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
    if(archivoAbierto != "" && listaCampos.count() > 0){
        string nombreArchivo = (archivoAbierto + "Dato").toStdString();
        QString nombreIndice = (archivoAbierto + "Indx");
        QString nombreIndiceArbol = (archivoAbierto + "IAbl");

        ifstream archivo ("./Archivos/todosArchivos.ncr");
        bool existe = false;

        //verificar que el archivo que se creo no existe
        while(archivo.good()){
            string temp;
            archivo >> temp;
            if(temp == nombreArchivo){
                existe = true;
            }
        }
        archivo.close();

        if(existe == false){
            char nombre [nombreArchivo.length()];
            int tamano = nombreArchivo.length();
            for (int i = 0; i < tamano; i++){
                nombre[i] = nombreArchivo[i];
            }
            if(tamano < nombreArchivo.length()){
                nombre[tamano] = '\0';
            }

            //agregar a archivos creados
            ofstream archivo ("./Archivos/todosArchivos.ncr");
            archivo << nombreArchivo << endl;
            archivo.close();

            //escribir estructura al archivo
            QString data;
            bool llave = false;
            foreach(Campo campo, listaCampos){
                data += campo.getNombreCampo() + " " + campo.getTipoCampo() + " " + QString::number(campo.getTamanoCampo())+" ";
                if(campo.getEsLlave()){
                    data += "Si\n";
                    llave = true;
                }else{
                    data += "No\n";
                }
            }
            data += "|\n";
            data += "-1    \n";
            data += "$\n";

            ofstream file(nombre);
            file << data.toStdString();
            file.close();

            //indices
            if(llave){
                //indice normal
                QFile fileIndice(nombreIndice);
                fileIndice.open(QIODevice::ReadWrite | QIODevice::Text);
                fileIndice.close();
                //indice con arbol b
                QFile fileIndiceArbol(nombreIndiceArbol);
                fileIndiceArbol.open(QIODevice::ReadWrite | QIODevice::Text);
                fileIndiceArbol.close();
            }

            //borrar tabla
            foreach(Campo campo, listaCampos){
                ui->tablaCampos->removeRow(0);
                listaCampos.removeAt(0);
            }

            if(ui->comboBoxEsLlave->isVisible() == false){
                ui->comboBoxEsLlave->setVisible(true);
                ui->comboBoxEsLlave->addItem("Si");
            }

        }else{
            //mesnaje error que el archivo ya existe
        }
        ui->comboBoxEsLlave->setEnabled(true);
        ui->comboBoxEsLlave->setItemText(0,"Si");
    }else{
        if(listaCampos.count() == 0){
            //mandar mensajes q no hay campos
        }else{
            //mandar mensajes q no hay archivo abierto
        }
    }

    //panels
    ui->panelRegistros->setVisible(false);
    ui->panelCampos->setVisible(false);

}

void MainWindow::on_actionCerrar_Archivo_triggered()
{
    //panels
    ui->panelRegistros->setVisible(false);
    ui->panelCampos->setVisible(false);
}

void MainWindow::on_actionListar_Campos_triggered()
{
    //panels
    ui->panelRegistros->setVisible(false);
    ui->panelCampos->setVisible(true);


}

void MainWindow::on_actionModificar_Campos_triggered()
{
    //panels
    ui->panelRegistros->setVisible(false);
    ui->panelCampos->setVisible(true);
}

void MainWindow::on_actionIntroducir_Registros_triggered()
{
    //panels
    ui->panelRegistros->setVisible(true);
    ui->panelCampos->setVisible(false);

    ui->datoRegistro->setVisible(true);
    ui->datoRegistroDec->setVisible(false);
    ui->datoRegistroDec2->setVisible(false);
    ui->labelRegistroPunto->setVisible(false);

    qDebug() << "Click en crear registros\nCargando Archivos a comboBox";
    numHead = 0;
    numEOSE = 0;
    ifstream archivo("./Archivos/todosArchivos.ncr");
    while(archivo.good()){
        string dato;
        archivo >> dato;
        qDebug() << "archivo lee:" + QString::fromStdString(dato);
        ui->comboBoxArchivosRegistros->addItem(QString::fromStdString(dato).replace("_"," "));
    }
    listaCamposAbiertos.clear();
    listaCamposLlenados.clear();
    ui->comboBoxArchivosRegistros->removeItem(ui->comboBoxArchivosRegistros->count()-1);
}

void MainWindow::on_abrirArchivoRegistro_clicked()//Metodo no utilizado
{

}

void MainWindow::on_comboBoxArchivosRegistros_activated(const QString &arg1)
{
    qDebug() << "Entra metodo combo box";
    fileArchivo.close();
    fileIndice.close();

    qDebug() << "cierra Archivos";
    ui->labelRegistoNumero->setText("N/A");
    ui->labelRegistoNombre->setText("N/A");
    ui->labelRegistoTipo->setText("N/A");
    ui->labelRegistoTamano->setText("N/A");
    ui->labelRegistoLlave->setText("N/A");

    listaLlaves.clear();
    listaCamposAbiertos.clear();

    qDebug() << "vacia listas";
    numHead = 0;
    numEOSE = 0;
    numCampoLlave = -1;
    numOSH = 0;

    fileArchivo.setFileName(ui->comboBoxArchivosRegistros->currentText());
    if(!fileArchivo.open(QIODevice::ReadWrite | QIODevice::Text)){
        return;
    }
    qDebug() << "Asigna nombre de archivo";
    QTextStream textStream (&fileArchivo);
    QString linea;
    qDebug() << "antes de while";
    while (!textStream.atEnd()) {
        linea = textStream.readLine();
        numEOSE += linea.toUtf8().length()+1;
        if(linea =="|")
            break;
        QStringList stringList = linea.split(" ");
        bool llave =false;
        if(stringList[3]=="Si"){
           llave = true;
           numCampoLlave = listaCamposAbiertos.count();
        }
        listaCamposAbiertos.append(Campo(stringList[0],stringList[1],stringList[2].toInt(),llave));
    }
    qDebug() << "DEspus de while";

    numOSH = numEOSE;
    linea = textStream.readLine();
    numEOSE += linea.length()+1;
    numHead = linea.toInt();
    numEOSE +=1;

    ui->labelRegistoNumero->setText("1");
    ui->labelRegistoNombre->setText(listaCamposAbiertos[0].getNombreCampo());
    ui->labelRegistoTipo->setText(listaCamposAbiertos[0].getTipoCampo());
    ui->labelRegistoTamano->setText(QString::number(listaCamposAbiertos[0].getTamanoCampo()));
    if(listaCamposAbiertos[0].getEsLlave())
        ui->labelRegistoLlave->setText("Si");
    else
        ui->labelRegistoLlave->setText("No");

    QString mask;
    if(listaCamposAbiertos[0].getTipoCampo() == "DEC"){
        ui->datoRegistro->setVisible(false);
        ui->datoRegistroDec->setVisible(true);
        ui->datoRegistroDec2->setVisible(true);
        ui->labelRegistroPunto->setVisible(true);
        for (int i = 0; i < listaCamposAbiertos[0].getTamanoCampo();i++){
            mask += "0";
        }
        ui->datoRegistroDec2->setInputMask(mask + "\0");
    }else if(listaCamposAbiertos[0].getTipoCampo() == "INTF"){
      for(int i=0;i<listaCamposAbiertos[0].getTamanoCampo();i++)
           mask += "0";
      ui->datoRegistro->setInputMask(mask + "\0");
    }else{
      ui->datoRegistro->setInputMask("");
      ui->datoRegistro->setMaxLength(listaCamposAbiertos[0].getTamanoCampo());
    }

    loadKeys();
    if(numCampoLlave != -1){
        QString nombreindice = ui->comboBoxArchivosRegistros->currentText();
        nombreindice[nombreindice.length()-4] = 'I',nombreindice[nombreindice.length()-3] = 'n';
        nombreindice[nombreindice.length()-2] = 'd',nombreindice[nombreindice.length()-1] = 'x';
        fileIndice.setFileName(nombreindice);
        if (!fileIndice.open(QIODevice::ReadWrite | QIODevice::Text))
             return;
     }
}

void MainWindow::loadKeys(){
    int recorrido = 0;
    for(int i=0;i < numCampoLlave;i ++){
         recorrido += listaCamposAbiertos[i].getTamanoCampo();
    }

    if(numCampoLlave != -1){
        fileArchivo.seek(0);
        QTextStream textStream (&fileArchivo);
        QString linea = textStream.readLine();
        bool comienzo = false;
        while (!linea.isNull()) {
            linea = textStream.readLine();
            if(comienzo){
               if(linea[0]!='*'){
                    listaLlaves.append(linea.mid(recorrido,listaCamposAbiertos[numCampoLlave].getTamanoCampo()));
               }
            }
            if(linea=="$"){
                comienzo = false;
            }
        }
    }
}

void MainWindow::on_siguienteRegistro_clicked()
{
    if((ui->datoRegistro->text()== "" && ui->labelRegistoLlave->text() == "Si")){
        //mandar mensaje de que llene campos
    }else{
        bool disponible = true;
        QString nombreCampo = ui->datoRegistro->text();
        for(int i = nombreCampo.length(); i < listaCamposAbiertos[ui->labelRegistoNumero->text().toInt()-1].getTamanoCampo(); i++){
                      nombreCampo+=' ';
        }
        if(ui->labelRegistoLlave->text()=="Si"){
            for(int i = 0; i < listaLlaves.count(); i++){
                if(listaLlaves[i]==nombreCampo){
                    QMessageBox::information(this,"Introducir Registro","El Registro ya existe");
                    disponible = false;
                }
            }

        }
        if(disponible){
            int numeroCampo = ui->labelRegistoNumero->text().toInt();
            listaCamposLlenados.append(nombreCampo);
            if (ui->labelRegistoNumero->text().toInt() < listaCamposAbiertos.count()) {
                ui->labelRegistoNumero->setText(QString::number(numeroCampo+1));
            }else{
                ui->labelRegistoNumero->setText("1");
                numeroCampo=0;
                ui->labelNumeroRegistro->setText(QString::number(ui->labelNumeroRegistro->text().toInt()+1));
                QString dato;
                for(int i=0 ; i<listaCamposLlenados.count();i++){
                    dato += listaCamposLlenados[i];
                }
                dato += '\n';
                int offSet=0;
                for(int i=0; i < listaCamposAbiertos.count();i++){
                    offSet += listaCamposAbiertos[i].getTamanoCampo();
                }
                offSet++;
                if(numCampoLlave != -1){
                    int tamano = listaCamposAbiertos[numCampoLlave].getTamanoCampo();
                    QList<Index> listaIndices;
                    QTextStream input(&fileIndice);
                    int posicion = 0;
                    bool next = false;
                    int recorrido =0;
                    if(fileIndice.size() >0 ){
                        fileIndice.seek(0);
                        QString linea;
                        while(!input.atEnd()){
                            linea =  input.readLine();
                            listaIndices.append(Index(linea.mid(0,tamano).toUpper(),linea.mid(tamano,linea.length())));
                            if(listaCamposAbiertos[numCampoLlave].getTipoCampo()=="CHAR") {
                                if(listaCamposLlenados[numCampoLlave].toUpper()< listaIndices[listaIndices.count()-1].getKey() && next ==false){
                                    posicion = recorrido;
                                    next = true;
                                }
                            }else{
                                if(listaCamposLlenados[numCampoLlave].toInt() < listaIndices[listaIndices.count()-1].getKey().toInt() && next ==false){
                                        posicion=recorrido;
                                        next = true;
                                }
                            }
                            recorrido++;
                        }
                    }
                    if(next==false){
                        posicion=listaIndices.count();
                        if(numHead!=-1){
                            listaIndices.insert(posicion,Index (listaCamposLlenados[numCampoLlave].toUpper(),QString::number(numHead)));
                        }else{
                            int R = ((fileArchivo.size()-(numEOSE+1))/offSet)+1;
                            listaIndices.insert(posicion,Index (listaCamposLlenados[numCampoLlave].toUpper(),QString::number(R)));
                        }
                        fileIndice.seek(0);
                        QString datos;
                        for(int i=0;i<listaIndices.count();i++){
                            datos+=(listaIndices[i].getKey()+listaIndices[i].getRRN('I'))+'\n';
                        }
                        QTextStream output (&fileIndice);
                        output<<datos;
                        output.flush();
                    }
                    input.flush();
                }
                if(numHead==-1){
                    QTextStream output(&fileArchivo);
                    fileArchivo.seek(fileArchivo.size());
                    output << dato;
                    output.flush();
                }else{
                    int OSH = numOSH;
                    fileArchivo.seek(0);
                    QTextStream input(&fileArchivo);
                    QString linea2;
                    offSet=0;
                    bool start = false;
                    int RRN=0;
                    while (!input.atEnd()){
                        linea2 = input.readLine();
                        if(start){
                            RRN++;
                        if(RRN == numHead)
                            break;
                        else
                            offSet+= linea2.toUtf8().length()+1;
                        }
                        if(linea2=="$")
                            start=true;
                    }
                    offSet += numEOSE+1;
                    ////////////Escribir en archivo
                    QTextStream inputArchivo(&fileArchivo);
                    QString linea3;
                    fileArchivo.seek(offSet);
                    linea3 = inputArchivo.readLine();
                    fileArchivo.seek(offSet);
                    inputArchivo << dato;
                    inputArchivo.flush();
                    QStringList nuevohead = linea3.split("*");
                    numHead = nuevohead[1].toInt();
                    QString sendHead = "      ";
                    for(int i=0;i<nuevohead[1].length();i++)
                        sendHead[i]=nuevohead[1][i];
                    fileArchivo.seek(offSet);
                    inputArchivo<<sendHead;
                    inputArchivo.flush();
                }
                listaCamposLlenados.clear();
                listaLlaves.clear();
                loadKeys();
            }
            ui->labelRegistoNombre->setText(listaCamposAbiertos[numeroCampo].getNombreCampo());
            ui->labelRegistoTipo->setText(listaCamposAbiertos[numeroCampo].getTipoCampo());
            ui->labelRegistoTamano->setText(QString::number(listaCamposAbiertos[numeroCampo].getTamanoCampo()));
            if(listaCamposAbiertos[numeroCampo].getEsLlave())
                ui->labelRegistoLlave->setText("Si");
            else
                ui->labelRegistoLlave->setText("No");
            QString mask;
            ui->datoRegistro->setText("");
            if(listaCamposAbiertos[numeroCampo].getTipoCampo()=="INTF"){
                for(int i=0;i<listaCamposAbiertos[numeroCampo].getTamanoCampo();i++)
                    mask+="0";
                    ui->datoRegistro->setInputMask(mask+"\0");
            }else{
                ui->datoRegistro->setInputMask("");
                ui->datoRegistro->setMaxLength(listaCamposAbiertos[numeroCampo].getTamanoCampo());
            }
        }
    }
}
