#include "mainwindow.h"
#include "borrarcampos.h"
#include "listarcampos.h"
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
    ui->panelModificar->setVisible(false);
    ui->panelCruzar->setVisible(false);
    ui->panelIndexar->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionNuevo_Archivo_triggered()
{
    //panels
    ui->panelCampos->setVisible(false);
    ui->tablaCampos->setVisible(false);
    ui->panelRegistros->setVisible(false);
    ui->panelModificar->setVisible(false);
    ui->panelCruzar->setVisible(false);
    ui->panelIndexar->setVisible(false);

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
    ui->panelCampos->setEnabled(true);
    ui->panelModificar->setEnabled(false);
    ui->tablaCampos->setVisible(false);
    ui->panelRegistros->setVisible(false);
    ui->panelModificar->setVisible(false);
    ui->panelCruzar->setVisible(false);
    ui->panelIndexar->setVisible(false);

}

void MainWindow::on_abrirArchivo_clicked()
{
    QString direccion = QFileDialog::getOpenFileName(this,tr("Abrir archivo"),"./Archivos/", "All files (*.*);;Text File (*.*)");
    qDebug() << "Direccion del archivo para abrir" + direccion;
    archivoAbierto = direccion;
    QFile archivo (direccion);
    archivo.open(QIODevice::ReadOnly);
    QTextStream tsreading (&archivo);
    Campo temporalCampo;
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
            } else if(contenido.at(i) == ' ' || contenido.at(i) == '\n'){
                switch (ubicacion){
                case 0:
                    ui->tablaCampos->setItem(row,ubicacion,new QTableWidgetItem(registro));
                    ubicacion++;
                    nombreCampo = registro;
                    registro = "";
                    break;
                case 1:
                    ui->tablaCampos->setItem(row,ubicacion,new QTableWidgetItem(registro));
                    ubicacion++;
                    tipoCampo = registro;
                    registro = "";
                    break;
                case 2:
                    ui->tablaCampos->setItem(row,ubicacion,new QTableWidgetItem(registro));
                    ubicacion++;
                    tamanoCampo = registro;
                    registro = "";
                    break;
                case 3:
                    ui->tablaCampos->setItem(row,ubicacion,new QTableWidgetItem(registro));
                    row = ui->tablaCampos->rowCount();
                    ui->tablaCampos->insertRow(row);
                    ubicacion = 0;
                    esLlave = registro;
                    registro = "";
                    temporalCampo.setNombreCampo(nombreCampo);
                    temporalCampo.setTipoCampo(tipoCampo);
                    temporalCampo.setTamanoCampo(tamanoCampo.toInt());
                    if(esLlave == "Si"){
                        temporalCampo.setEsLlave(true);
                        ui->labelEsLlave->setVisible(false);
                        ui->comboBoxEsLlave->setVisible(false);
                        ui->comboBoxEsLlave->setCurrentIndex(1);
                    }else{
                        temporalCampo.setEsLlave(false);
                    }
                    listaCampos.append(temporalCampo);
                    break;
                }
                //ui->tablaCampos->setItem(row,ubicacion,new QTableWidgetItem(registro));
            }else if (contenido.at(i) != ' '){
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
    //panels
    ui->panelRegistros->setVisible(false);
    ui->panelCampos->setEnabled(false);
    ui->panelModificar->setEnabled(true);
    ui->panelModificar->setVisible(true);
    ui->modificarCampo->setEnabled(false);
    ui->eliminarCampo->setEnabled(true);
    ui->comboBoxModificarCampo->clear();

    ui->panelCruzar->setVisible(false);
    ui->panelIndexar->setVisible(false);

    /*for(int i = 0; i < ui->comboBoxModificarCampo->count(); i++){
        ui->comboBoxModificarCampo->removeItem(i);
    }*/
    //llenar comboBox
    for(int i = 0; i < listaCampos.size(); i++){
        ui->comboBoxModificarCampo->addItem(listaCampos.at(i).getNombreCampo());
    }

    //reset all fields
    ui->comboBoxModificarCampo->setCurrentIndex(0);
    ui->comboBoxModificarEsLlave->setCurrentIndex(0);
    //ui->comboBoxModificarEsLlave->setEnabled(false);
    ui->comboBoxTipoModificarCampo->setCurrentIndex(0);
    //ui->comboBoxTipoModificarCampo->setEnabled(false);
    ui->tamanoModificarCampo->setValue(1);
    //ui->tamanoModificarCampo->setEnabled(false);
    ui->nombreModificarCampo->setText("");
    //ui->nombreModificarCampo->setEnabled(false);

}

void MainWindow::on_actionSalvar_Archivo_triggered()
{
    if(archivoAbierto != "" && listaCampos.count() > 0){
    string nombreArchivo = (archivoAbierto + "Dato").toStdString();
    QString nombreIndice = (archivoAbierto + "Indx");
    QString nombreIndiceArbol = (archivoAbierto + "InAbl");

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
    ui->panelCampos->setVisible(false);
    ui->tablaCampos->setVisible(false);
    ui->panelRegistros->setVisible(false);
    ui->panelModificar->setVisible(false);
    ui->panelCruzar->setVisible(false);
    ui->panelIndexar->setVisible(false);

}

void MainWindow::on_actionCerrar_Archivo_triggered()
{
    //panels
    ui->panelRegistros->setVisible(false);
    ui->panelCampos->setVisible(false);
    ui->panelCampos->setVisible(false);
    ui->tablaCampos->setVisible(false);
    ui->panelRegistros->setVisible(false);
    ui->panelModificar->setVisible(false);
    ui->panelCruzar->setVisible(false);
    ui->panelIndexar->setVisible(false);

}

void MainWindow::on_actionListar_Campos_triggered()
{
    //panels
    ui->panelRegistros->setVisible(false);
    ui->panelCampos->setVisible(true);

    ui->panelRegistros->setVisible(false);
    ui->panelModificar->setVisible(false);
    ui->panelCruzar->setVisible(false);
    ui->panelIndexar->setVisible(false);

    ListarCampos listarCampos;
    listarCampos.llenarTabla(listaCampos);
    listarCampos.setModal(true);
    listarCampos.exec();

}

void MainWindow::on_actionModificar_Campos_triggered()
{
    //panels
    ui->panelRegistros->setVisible(false);
    ui->panelCampos->setEnabled(false);

    ui->panelModificar->setVisible(true);
    ui->panelModificar->setEnabled(true);
    ui->modificarCampo->setEnabled(true);
    ui->eliminarCampo->setEnabled(false);
    ui->comboBoxModificarCampo->clear();

    ui->panelCruzar->setVisible(false);
    ui->panelIndexar->setVisible(false);

    /*for(int i = 0; i < ui->comboBoxModificarCampo->count(); i++){
        ui->comboBoxModificarCampo->removeItem(i);
    }*/
    //llenar comboBox
    for(int i = 0; i < listaCampos.size(); i++){
        ui->comboBoxModificarCampo->addItem(listaCampos.at(i).getNombreCampo());
    }

    //reset all fields
    ui->comboBoxModificarCampo->setCurrentIndex(0);
    ui->comboBoxModificarEsLlave->setCurrentIndex(0);
    ui->comboBoxModificarEsLlave->setEnabled(true);
    ui->comboBoxTipoModificarCampo->setCurrentIndex(0);
    ui->comboBoxTipoModificarCampo->setEnabled(true);
    ui->tamanoModificarCampo->setValue(1);
    ui->tamanoModificarCampo->setEnabled(true);
    ui->nombreModificarCampo->setText("");
    ui->nombreModificarCampo->setEnabled(true);
}

void MainWindow::on_actionIntroducir_Registros_triggered()
{
    //panels
    ui->panelRegistros->setVisible(true);
    ui->panelCampos->setVisible(false);

    ui->panelCampos->setVisible(false);
    ui->tablaCampos->setVisible(false);
    ui->panelModificar->setVisible(false);
    ui->panelCruzar->setVisible(false);
    ui->panelIndexar->setVisible(false);

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
void MainWindow::on_modificarCampo_clicked() {
    ui->panelRegistros->setVisible(false);
    ui->panelCruzar->setVisible(false);
    ui->panelIndexar->setVisible(false);


    bool verificar = false;
    for(int i = 0; i < listaCampos.size(); i++){
        if(listaCampos.at(i).getEsLlave()){
            verificar = true;
            break;
        }
    }
    if(verificar && ui->comboBoxModificarEsLlave->currentIndex() == 0){
        QMessageBox error;
         error.setText("Ya existe una llave");
         error.exec();
    }else{
         int posicion = ui->comboBoxModificarCampo->currentIndex();
         QString nombre = ui->nombreModificarCampo->text(), tipo = ui->comboBoxTipoModificarCampo->currentText();
         int tamano = ui->tamanoModificarCampo->value();
         bool llave = false;
         if  (ui->comboBoxModificarEsLlave->currentIndex() == 0){
             llave = true;
         }else{
             llave = false;
         }
         listaCampos.replace(posicion, Campo(nombre, tipo, tamano, llave));
         ui->panelModificar->setEnabled(false);
    }
}

void MainWindow::on_eliminarCampo_clicked()
{
    ui->panelRegistros->setVisible(false);
    ui->panelCruzar->setVisible(false);
    ui->panelIndexar->setVisible(false);


    listaCampos.removeAt(ui->comboBoxModificarCampo->currentIndex());
    ui->panelModificar->setEnabled(false);
}

void MainWindow::on_comboBoxModificarCampo_activated(const QString &arg1){ //accion no se usa

}

void MainWindow::on_comboBoxModificarCampo_currentIndexChanged(int index)
{

    ui->nombreModificarCampo->setText(listaCampos.at(index).getNombreCampo());
    ui->tamanoModificarCampo->setValue(listaCampos.at(index).getTamanoCampo());
    if(listaCampos.at(index).esLlave){
        ui->comboBoxModificarEsLlave->setCurrentIndex(0);
    }else{
        ui->comboBoxModificarEsLlave->setCurrentIndex(1);
    }
    if(listaCampos.at(index).getTipoCampo() == "CHAR"){
        ui->comboBoxTipoModificarCampo->setCurrentIndex(0);
    } else if(listaCampos.at(index).getTipoCampo() == "INTF"){
        ui->comboBoxTipoModificarCampo->setCurrentIndex(1);
    } else{
        ui->comboBoxTipoModificarCampo->setCurrentIndex(2);
    }
}

void MainWindow::exportXml() {
    //si no hay campos o no hay registros entonces no se crea el archivo
    if (this->current_open_file.listFields().size() == 0 || this->current_open_file.getAllIndexes().size() == 0) {
        this->lbl_status_bar->setText("There are no fields or records");
        return;
    }

    //se despliega un dialogo para seleccionar la carpeta en donde se desea guardar
    //el archivo XML
    QString file_path = QFileDialog::getExistingDirectory(this, "Export to XML file", "");

    //si el usuario no presionó cancelar
    if (!file_path.isEmpty()) {
        //se concatena el nombre del archivo XML a la carpeta seleccionada
        file_path += "/outputXML.xml";

        //se crea un archivo lógico
        QFile file(file_path);

        // se abre el archivo en modo escritura
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::warning(this, "Error", "Can not export file");
        } else {
            //Se crea un stream para escribir el archivo XML
            QXmlStreamWriter xml_writer;
            //se enlaza el stream con el archivo
            xml_writer.setDevice(&file);
            // se inicia el documento
            xml_writer.writeStartDocument();

            //Se agrega el elemento raíz
            xml_writer.writeStartElement("database");
            vector<PrimaryIndex*> indexes = this->current_open_file.getAllIndexes();

            // se añaden todos los registros con su información correspondiente
            // del campo donde están almacenados
            for (int i = 0; i < indexes.size(); i++) {
                PrimaryIndex* curr_i = indexes[i];
                Record* curr_r = this->current_open_file.readRecord(curr_i);
                vector<Field*> fields = curr_r->getFields();
                vector<string> record = curr_r->getRecord();

                xml_writer.writeStartElement("record");

                for (int j = 0; j < fields.size(); j++) {
                    Field* curr_f = fields[j];

                    xml_writer.writeStartElement(QString::fromStdString(curr_f->getName()));

                    if (curr_f->isKey()) {
                        xml_writer.writeAttribute(QString::fromStdString(string("key")), QString::fromStdString(string("true")));
                    } else {
                        xml_writer.writeAttribute(QString::fromStdString(string("key")), QString::fromStdString(string("false")));
                    }

                    if (curr_f->getDatatype() == INT_DT) {
                        xml_writer.writeAttribute(QString::fromStdString(string("type")), QString::fromStdString(string("INT")));
                        xml_writer.writeAttribute(QString::fromStdString(string("length")), QString::number(curr_f->getLength()));
                    } else if (curr_f->getDatatype() == STRING_DT) {
                        xml_writer.writeAttribute(QString::fromStdString(string("type")), QString::fromStdString(string("STRING")));
                        xml_writer.writeAttribute(QString::fromStdString(string("length")), QString::number(curr_f->getLength()));
                    } else {
                        xml_writer.writeAttribute(QString::fromStdString(string("type")), QString::fromStdString(string("REAL")));
                        xml_writer.writeAttribute(QString::fromStdString(string("length")), QString::number(curr_f->getLength()));
                        xml_writer.writeAttribute(QString::fromStdString(string("dplaces")), QString::number(curr_f->getDecimalPlaces()));
                    }

                    xml_writer.writeCharacters(QString::fromStdString(record[j]));
                    xml_writer.writeEndElement();
                }
                xml_writer.writeEndElement();

            }
            //se cierra el tag principal y el documento
            xml_writer.writeEndElement();
            xml_writer.writeEndDocument();

        }
    }
}
void MainWindow::exportJson() {
    //verifica si existen campos y registros
    if (this->current_open_file.listFields().size() == 0 || this->current_open_file.getAllIndexes().size() == 0) {
        this->lbl_status_bar->setText("There are no fields or records");
        return;
    }

    //levanta un dialogo para seleccionar la carpeta donde se va a guardar el archivo JSON
    QString file_path = QFileDialog::getExistingDirectory(this, "Export JSON file", "");

    if (!file_path.isEmpty()) {
        //se concatena el nuevo nombre del archivo a la carpeta seleccionada
        file_path += "/outputJSON.json";

        //se crea un archivo lógico
        QFile file(file_path);
        //se abre para escritura y en modo texto
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Can not export the file");
        } else {
            //se crea un documento JSON
            QJsonDocument doc;
            QJsonObject root;

            vector<Field*> fields1 = this->current_open_file.listFields();

            //se agregan todos los campos como objetos JSON dentro del objeto raíz
            for (int i = 0; i < fields1.size(); i++) {
                Field* curr_f = fields1[i];

                QJsonObject curr_o;
                curr_o.insert(QString::fromStdString(string("name")), QJsonValue(QString::fromStdString(curr_f->getName())));

                if (curr_f->getDatatype() == INT_DT) {
                    curr_o.insert(QString::fromStdString(string("datatype")), QJsonValue(QString::fromStdString(string("INT"))));
                } else if (curr_f->getDatatype() == REAL_DT) {
                    curr_o.insert(QString::fromStdString(string("datatype")), QJsonValue(QString::fromStdString(string("REAL"))));
                } else {
                    curr_o.insert(QString::fromStdString(string("datatype")), QJsonValue(QString::fromStdString(string("STRING"))));
                }

                curr_o.insert(QString::fromStdString(string("length")), QJsonValue(QString::number(curr_f->getLength())));

                if (curr_f->getDatatype() == REAL_DT) {
                    curr_o.insert(QString::fromStdString(string("dplaces")), QJsonValue(QString::number(curr_f->getDecimalPlaces())));
                } else {
                    curr_o.insert(QString::fromStdString(string("dplaces")), QJsonValue(QString::number(0)));
                }

                curr_o.insert(QString::fromStdString(string("key")), QJsonValue(curr_f->isKey()));

                root.insert(QString::fromStdString(string("Field")) + QString::number(i), QJsonValue(curr_o));
            }


            vector<PrimaryIndex*> indexes = this->current_open_file.getAllIndexes();

            //se agregan los registros como objetos JSON a la raíz
            for (int i = 0; i < indexes.size(); i++) {
                QJsonObject curr_o;
                PrimaryIndex* curr_i = indexes[i];
                Record* curr_r = this->current_open_file.readRecord(curr_i);
                vector<Field*> fields = curr_r->getFields();
                vector<string> record = curr_r->getRecord();

                for (int j = 0; j < fields.size(); j++) {
                    Field* curr_f = fields[j];
                    curr_o.insert(QString::fromStdString(curr_f->getName()), QJsonValue(QString::fromStdString(record[j])));
                }
                root.insert(QString::fromStdString(string("Record")) + QString::number(i), QJsonValue(curr_o));
            }

            doc.setObject(root);
            // se transfiere el contenido del documento JSON a un Qstring
            QString result(doc.toJson());

            //se crea un stream que enlaza el archivo lógico con el stream de texto
            QTextStream out(&file);

            //se envia al archivo
            out << result;
        }
    }
}
void MainWindow::exportExcel(){
    /*
    ofstream MyExcelFile;
    MyExcelFile.open("./Archivos/TablaExcel.csv");
    for(int i = 0; i < listaCampos.size(); i++){
        MyExcelFile << listaCampos.at(i).getNombreCampo();
    }
    MyExcelFile << endl;
    MyExcelFile.close();
    */
}

void MainWindow::on_actionExportar_Excel_triggered()
{
    exportExcel();
}

void MainWindow::on_actionCrear_Indices_triggered()//no existe
{

}

void MainWindow::on_actionReindexar_Archivos_triggered()
{

    ui->panelIndexar->setVisible(true);
    ui->panelCampos->setVisible(false);
    ui->tablaCampos->setVisible(false);
    ui->panelRegistros->setVisible(false);
    ui->panelModificar->setVisible(false);
    ui->panelCruzar->setVisible(false);


    qDebug()<<"Entra a indexar";
    numCampoLlave = -1;
    listaCamposAbiertos.clear();
    indexList.clear();
    arbolB.getNodos().clear();

    ui->panelIndexar->setVisible(true);
    ui->comboBoxIndexar->clear();
    ui->comboBoxIndexar->clear();
    QList<QString> archivos;

    qDebug()<<"Abre donde estan todos los archivos";
    QFile file("./Archivos/todosArchivos.ncr");
    qDebug()<<"Pasa Abrir archivo";
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Entra al if";
        QTextStream in(&file);
        while (!in.atEnd()) {
            qDebug()<<"Entra al while";
            QString archivo;
            archivo=in.readLine();
            archivos.append(archivo);
            qDebug()<<"Archivo: " << archivo;
        }
    }

    //solo cargara archivos con registros
    for(int i=0;i<archivos.count();i++){
        qDebug()<<"Entra al for";
        QFile file (archivos[i].replace("_"," "));
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
            return;
        QTextStream in(&file);
        QString line ;
        int mas = 0;
        bool tienellave = false;
        bool activar = false;
        while (!in.atEnd()){
            qDebug()<<"Entra al segundo while";
            line = in.readLine();
            if(line.contains("Si"))
                tienellave = true;
            if(mas==1){
                mas++;
                break;
            }
            if(activar)
                if(line!="\n")
                    mas++;
            if(line=="$")
                activar = true;
        }
        if(mas>=1 && tienellave){
            qDebug()<<"Se supone q escribe";
            ui->comboBoxIndexar->addItem(archivos[i]);
        }
        file.close();
    }
}

void MainWindow::on_comboBoxIndexar_activated(const QString &arg1)
{
    numCampoLlave = -1;
    listaCamposAbiertos.clear();
    indexList.clear();
    QList<Index> indicesar;
    ArbolB arboll;
    arbolB = arboll;
    QFile file(arg1);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString line ;
    bool parar = false;
    bool empezar  = false;
    int offllave =0;
    int RRN=0;
    int offsetarbol=0;
    int pa=0;
    while (!in.atEnd()){
         line = in.readLine();
          if(line=="|")
              parar = true;
          //////////leer estructura
          if(parar==false){
              QStringList divisiones = line.split(" ");
              bool lla =false;
              if(divisiones[3]=="Si"){
                    lla=true;
                    numCampoLlave = listaCamposAbiertos.count();
              }
              listaCamposAbiertos.append(Campo(divisiones[0],divisiones[1],divisiones[2].toInt(),lla));
          }//fin leer estructura
           /////////////////leer registros
          if(empezar)
            RRN++;
          if(empezar && line[0]!='*'){
                QString llave  = line.mid(offllave,listaCamposAbiertos[numCampoLlave].getTamanoCampo());
                indexList.append(Index(llave.toUpper(),QString::number(RRN)));
                indicesar.append(Index(llave.toUpper(),QString::number(offsetarbol)));
                if(listaCamposAbiertos[numCampoLlave].getTipoCampo()=="CHAR"){
                    pa= arbolB.insertIndex(indicesar[indicesar.count()-1],pa,1);
                }else{
                    pa= arbolB.insertIndex(indicesar[indicesar.count()-1],pa,2);
                }
           }
           if(line=="$"){
                empezar = true;
                for(int i=0;i<numCampoLlave;i++){
                    offllave+=listaCamposAbiertos[i].getTamanoCampo();
                }
           }
           offsetarbol+=line.toUtf8().length()+1;
    }
    file.close();
}

void MainWindow::on_botonIndexar_clicked()
{
    if(ui->comboBoxIndexar->currentText()!=""){
        //ordenar los indices
        if(listaCamposAbiertos[numCampoLlave].getTipoCampo()=="INTF")
            InsercionE();
        else
            Insercion();

        QString nombreindicea = ui->comboBoxIndexar->currentText()+"l";
        nombreindicea[nombreindicea.length()-5] = 'I',nombreindicea[nombreindicea.length()-4] = 'n';
        nombreindicea[nombreindicea.length()-3] = 'A',nombreindicea[nombreindicea.length()-2] = 'b';
        QFile filea(nombreindicea);
        if (!filea.open(QIODevice::ReadWrite | QIODevice::Text))
         return;
        QTextStream outa(&filea);
        QString mandara;
        for(int i=0;i<arbolB.getNodos().count();i++){
            for(int j=0;j<arbolB.getNodos()[i].getData().count();j++){
                mandara+=arbolB.getNodos()[i].getData()[j].getKey()+arbolB.getNodos()[i].getData()[j].getRRN('a');
            }

            for(int j=0;j<arbolB.getNodos()[i].getSons().count();j++){
                QString hijo ="    ";
                QString hi=QString::number(arbolB.getNodos()[i].getSons()[j]);
                for(int o=0;o<hi.length();o++){
                    hijo[o]=hi[o];
                }
               mandara+=hijo;
            }
            mandara+='\n';

        }

         outa<<mandara;
         filea.resize(filea.pos());
         filea.close();
        QString nombreindice = ui->comboBoxIndexar->currentText();
        nombreindice[nombreindice.length()-4] = 'I',nombreindice[nombreindice.length()-3] = 'n';
        nombreindice[nombreindice.length()-2] = 'd',nombreindice[nombreindice.length()-1] = 'x';
        QFile file(nombreindice);
            if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
             return;
         QTextStream out(&file);
         QString mandar1;

            for(int i=0;i<indexList.count();i++){
               mandar1+=(indexList[i].getKey()+indexList[i].getRRN('l'))+'\n';
            }
            out<<mandar1;
            file.resize(file.pos());
         file.close();
        ui->comboBoxIndexar->clear();
        }
}

void MainWindow::InsercionE(){
    int i, j;
    Index temp;
    for (i = 1; i < indexList.count(); i++){
        temp = indexList[i];
        j = i-1;
    while ( ((j >= 0 &&indexList[j].getKey().toInt()> temp.getKey().toInt()) ) ){
        indexList[j+1]=indexList[j];
        j--;
    }
        indexList[j+1]=temp;
    }
}//fin metodo ordenar

void MainWindow::Insercion(){
    int i, j;
    Index temp;
    for (i = 1; i < indexList.count(); i++){
        temp = indexList[i];
        j = i-1;
    while ( ((j >= 0 &&indexList[j].getKey()> temp.getKey()) ) ){
        indexList[j+1]=indexList[j];
        j--;
    }
    indexList[j+1]=temp;
    }
}//fin metodo ordenar

void MainWindow::on_actionCruzar_Arbol_B_triggered()
{
    ui->panelCampos->setVisible(false);
    ui->tablaCampos->setVisible(false);
    ui->panelRegistros->setVisible(false);
    ui->panelModificar->setVisible(false);
    ui->panelCruzar->setVisible(true);
    ui->panelIndexar->setVisible(false);


    file1.close();
    file2.close();
    campo1.clear();
    campo2.clear();
    ui->comboBoxCruzar1->clear();
    ui->comboBoxCruzar2->clear();
    for(int i=ui->cruzarTabla->rowCount()-1;i>=0;i--)
        ui->cruzarTabla->removeRow(i);
    for(int i=ui->cruzarTabla->columnCount();i>=0;i--)
        ui->cruzarTabla->removeColumn(i);
    ifstream verificar("./Archivos/todosArchivos.ncr");
    while(verificar.good()){
        string archivo;
        verificar >> archivo;
        ui->comboBoxCruzar1->addItem(QString::fromStdString(archivo).replace("_"," "));
        ui->comboBoxCruzar2->addItem(QString::fromStdString(archivo).replace("_"," "));
    }//fin del while
    verificar.close();

    ui->comboBoxCruzar1->removeItem(ui->comboBoxCruzar1->count()-1);
    ui->comboBoxCruzar2->removeItem(ui->comboBoxCruzar2->count()-1);
}


void MainWindow::on_comboBoxCruzar1_activated(const QString &arg1)
{
    campo1.clear();
    for(int i=ui->cruzarTabla->rowCount()-1;i>=0;i--)
        ui->cruzarTabla->removeRow(i);
    for(int i=ui->cruzarTabla->columnCount();i>=0;i--)
        ui->cruzarTabla->removeColumn(i);
    ui->comboBoxCampoComun->clear();
    file1.close();
    file1.setFileName(arg1);
    if(!file1.open(QIODevice::ReadWrite | QIODevice::Text))
        return;
    QTextStream in(&file1);
    QString line;
    while (!in.atEnd()) {
        line = in.readLine();
        if(line=="|")
            break;
        QStringList divisiones = line.split(" ");
        bool lla =false;
        if(divisiones[3]=="Si"){
           lla=true;
        }//fin del if
        campo1.append(Campo(divisiones[0],divisiones[1],divisiones[2].toInt(),lla));
    }//fin del while
}

void MainWindow::on_comboBoxCruzar2_activated(const QString &arg1)
{
    campo2.clear();
    for(int i=ui->cruzarTabla->rowCount()-1;i>=0;i--)
        ui->cruzarTabla->removeRow(i);
    for(int i=ui->cruzarTabla->columnCount();i>=0;i--)
        ui->cruzarTabla->removeColumn(i);
    ui->comboBoxCampoComun->clear();
    file2.close();
    file2.setFileName(arg1);
    if (!file2.open(QIODevice::ReadWrite | QIODevice::Text))
        return;
    QTextStream in(&file2);
    QString line;
    while (!in.atEnd()) {
        line = in.readLine();
        if(line=="|")
            break;
        QStringList divisiones = line.split(" ");
        bool lla =false;
        if(divisiones[3]=="Sí"){
            lla=true;
        }//fin del if
        campo2.append(Campo(divisiones[0],divisiones[1],divisiones[2].toInt(),lla));
     }//fin del while
}

void MainWindow::on_botonCruzar_clicked()
{
    for(int i=ui->cruzarTabla->rowCount()-1;i>=0;i--)
        ui->cruzarTabla->removeRow(i);
    for(int i=ui->cruzarTabla->columnCount();i>=0;i--)
        ui->cruzarTabla->removeColumn(i);
    ui->comboBoxCampoComun->clear();

    if(ui->comboBoxCruzar1->currentText()!=ui->comboBoxCruzar2->currentText()){
          for(int i=0;i<campo1.count();i++){
              for(int j=0;j<campo2.count();j++){
                  if(campo1[i].getNombreCampo()==campo2[j].getNombreCampo() && campo1[i].getTamanoCampo()==campo2[j].getTamanoCampo()
                      && campo1[i].getTipoCampo()== campo2[j].getTipoCampo()){
                      if(campo1[i].getEsLlave() || campo2[j].getEsLlave())
                      ui->comboBoxCampoComun->addItem(campo1[i].getNombreCampo());
                      j=campo2.count();
                  }//fin del if
              }//fin del for
          }//fin del for
    }//fin del if
}



void MainWindow::on_comboBoxCampoComun_activated(const QString &arg1)
{
    for(int i=ui->cruzarTabla->rowCount()-1;i>=0;i--)
            ui->cruzarTabla->removeRow(i);
        for(int i=ui->cruzarTabla->columnCount();i>=0;i--)
            ui->cruzarTabla->removeColumn(i);

        bool campo1=true;
        for(int i=0;i<this->campo2.count();i++){
            if(this->campo2[i].getNombreCampo()==ui->comboBoxCampoComun->currentText() && this->campo2[i].getEsLlave()==true)
                campo1=false;
        }//fin del for
        int columnaeliminar=0;
        int campollave=0;
        int tamano=0;
        if(campo1==false){
        for(int i=0;i<this->campo1.count();i++){
            ui->cruzarTabla->insertColumn(i);
           if(this->campo1[i].getNombreCampo().length()>this->campo1[i].getTamanoCampo())
                ui->cruzarTabla->setColumnWidth(i,this->campo1[i].getNombreCampo().length()*10);
            else
                ui->cruzarTabla->setColumnWidth(i,this->campo1[i].getTamanoCampo()*15);
            ui->cruzarTabla->setHorizontalHeaderItem(i,new QTableWidgetItem(this->campo1[i].getNombreCampo()));
            if(this->campo1[i].getNombreCampo()==ui->comboBoxCampoComun->currentText() && this->campo1[i].getEsLlave()==false)
                campollave = i;

        }//fin del for

        for(int i=0;i<this->campo2.count();i++){
            tamano+=this->campo2[i].getTamanoCampo();
            int col =this->campo1.count()+i;
            ui->cruzarTabla->insertColumn(col);
            if(this->campo2[i].getNombreCampo().length()>this->campo2[i].getTamanoCampo())
                ui->cruzarTabla->setColumnWidth(col,this->campo2[i].getNombreCampo().length()*10);
            else
                ui->cruzarTabla->setColumnWidth(col,this->campo2[i].getTamanoCampo()*15);
             ui->cruzarTabla->setHorizontalHeaderItem(col,new QTableWidgetItem(this->campo2[i].getNombreCampo()));
             if(this->campo2[i].getNombreCampo()==ui->comboBoxCampoComun->currentText() && this->campo2[i].getEsLlave()==true)
                 columnaeliminar=col;
        }//fin del for
        }else{
            for(int i=0;i<this->campo2.count();i++){
                ui->cruzarTabla->insertColumn(i);
               if(this->campo2[i].getNombreCampo().length()>this->campo2[i].getTamanoCampo())
                    ui->cruzarTabla->setColumnWidth(i,this->campo2[i].getNombreCampo().length()*10);
                else
                    ui->cruzarTabla->setColumnWidth(i,this->campo2[i].getTamanoCampo()*15);
                ui->cruzarTabla->setHorizontalHeaderItem(i,new QTableWidgetItem(this->campo2[i].getNombreCampo()));
                if(this->campo2[i].getNombreCampo()==ui->comboBoxCampoComun->currentText() && this->campo2[i].getEsLlave()==false)
                    campollave = i;
            }//fin del for

            for(int i=0;i<this->campo1.count();i++){
                tamano+=this->campo1[i].getTamanoCampo();
                int col =this->campo2.count()+i;
                ui->cruzarTabla->insertColumn(col);
                if(this->campo1[i].getNombreCampo().length()>this->campo1[i].getTamanoCampo())
                    ui->cruzarTabla->setColumnWidth(col,this->campo1[i].getNombreCampo().length()*10);
                else
                    ui->cruzarTabla->setColumnWidth(col,this->campo1[i].getTamanoCampo()*15);
                 ui->cruzarTabla->setHorizontalHeaderItem(col,new QTableWidgetItem(this->campo1[i].getNombreCampo()));
                 if(this->campo1[i].getNombreCampo()==ui->comboBoxCampoComun->currentText() && this->campo1[i].getEsLlave()==true)
                     columnaeliminar=col;
            }//fin del for
        }//fin del else
         ui->cruzarTabla->removeColumn(columnaeliminar);
         ArbolB arbol;
         QString nombreindicea;
         int cantr=0;

         if(campo1==false){
             nombreindicea = file2.fileName()+"l";
             qDebug() << "File name: " << nombreindicea;
             cantr=this->campo2[columnaeliminar-this->campo1.count()].getTamanoCampo();
         }else{
             nombreindicea = file1.fileName()+"l";
             cantr=this->campo1[columnaeliminar-this->campo2.count()].getTamanoCampo();
         }//fin del else
         nombreindicea[nombreindicea.length()-5] = 'I',nombreindicea[nombreindicea.length()-4] = 'n';
         nombreindicea[nombreindicea.length()-3] = 'A',nombreindicea[nombreindicea.length()-2] = 'b';
         QFile filea(nombreindicea);
         if (!filea.open(QIODevice::ReadWrite | QIODevice::Text))
          return;
         QTextStream in(&filea);
         QString line;
         while(!in.atEnd()){
             line=in.readLine();
             nodo temp;
             QList<Index> indices;
             QList<int> hijos;
             int camino=0;
             for(int i=0;i<63;i++){
                 indices.append(Index(line.mid(camino,cantr),line.mid(cantr+camino,10)));
                 camino+=cantr+10;
             }//fin del for
             camino-=cantr+6;
             for(int i=0;i<64;i++){
                 hijos.append(line.mid(camino,4).toInt());
                 camino+=4;
             }//fin del for
             temp.setListData(indices);
             temp.setListSon(hijos);
             arbol.insertNode(temp);
         }//fin del while
         filea.close();
         int padre=arbol.getNodos().count()-1;


         ui->comboBoxCruzar1->addItem(QString::number(padre));

         file1.seek(0);
         file2.seek(0);
         if(campo1==false){
             QTextStream in(&file1);
             QString line;
             bool empezar = false;
             while(!in.atEnd()){
                 line = in.readLine();
                 if(empezar){
                     if(line[0]!='*'){
                         int rowc = ui->cruzarTabla->rowCount();
                         int camino=0;
                         ui->cruzarTabla->insertRow(rowc);
                         QString data;
                         for(int o=0;o<this->campo1.count();o++){
                             data= line.mid(camino,this->campo1[o].getTamanoCampo());
                            ui->cruzarTabla->setItem(rowc,o,new QTableWidgetItem(data));
                          camino+=this->campo1[o].getTamanoCampo();
                       }//fin del for
                     }//fin del if
                 }//fin del if
                 if(line=="$")
                     empezar=true;

             }//fin del while

           QTextStream in2(&file2);
           QString line2;
            for(int i=0;i<ui->cruzarTabla->rowCount();i++){
                QTableWidgetItem* item = ui->cruzarTabla->item(i,campollave);
                QString llave = item->text();
                QList<int> partes;
                if(this->campo2[columnaeliminar-this->campo1.count()].getTipoCampo()=="CHAR"){
                    partes = arbol.searchIndex(llave,padre,1);
                 }else{
                    partes = arbol.searchIndex(llave,padre,2);
                }//fin del else
                if(partes[0]!=-1){
                    file2.seek(arbol.getNodos()[partes[0]].getData()[partes[1]].getRRN('a').toInt());
                    line2=in2.readLine();
                    int camino=0;
                    for(int k=0;k<this->campo2.count();k++){
                        if(k!=columnaeliminar-this->campo1.count()){
                            ui->cruzarTabla->setItem(i,k+(this->campo1.count()-1),new QTableWidgetItem(line2.mid(camino,this->campo2[k].getTamanoCampo())));
                        }//fin del if
                        camino+=this->campo2[k].getTamanoCampo();
                    }//fin del for
                }//fin del if
            }//fin del for

           }else{
             QTextStream in(&file2);
             QString line;
             bool empezar = false;
             while(!in.atEnd()){
                 line = in.readLine();
                 if(empezar){
                     if(line[0]!='*'){
                         int rowc = ui->cruzarTabla->rowCount();
                         int camino=0;
                         ui->cruzarTabla->insertRow(rowc);
                         QString data;
                         for(int o=0;o<this->campo2.count();o++){
                             data= line.mid(camino,this->campo2[o].getTamanoCampo());
                             ui->cruzarTabla->setItem(rowc,o,new QTableWidgetItem(data));
                          camino+=this->campo2[o].getTamanoCampo();
                       }//fin del for
                    }//fin del if
                  }//fin del if
                 if(line=="$")
                     empezar=true;

             }//fin del while

             QTextStream in2(&file1);
             QString line2;
              for(int i=0;i<ui->cruzarTabla->rowCount();i++){
                  QTableWidgetItem* item = ui->cruzarTabla->item(i,campollave);
                  QString llave = item->text();
                  QList<int> partes;
                  if(this->campo1[columnaeliminar-this->campo2.count()].getTipoCampo()=="CHAR"){
                      partes = arbol.searchIndex(llave,padre,1);
                   }else{
                      partes = arbol.searchIndex(llave,padre,2);
                  }//fin del else
                  if(partes[0]!=-1){
                      file1.seek(arbol.getNodos()[partes[0]].getData()[partes[1]].getRRN('a').toInt());
                      line2=in2.readLine();
                      int camino=0;
                      for(int k=0;k<this->campo1.count();k++){
                          if(k!=columnaeliminar-this->campo2.count()){
                              ui->cruzarTabla->setItem(i,k+(this->campo2.count()-1),new QTableWidgetItem(line2.mid(camino,this->campo1[k].getTamanoCampo())));
                          }//fin del if
                          camino+=this->campo1[k].getTamanoCampo();
                      }//fin del for
                  }//fin del if
              }//fin del for


         }//fin del else


         ui->comboBoxCampoComun->addItem(QString::number(ui->cruzarTabla->columnCount()));
         int rowcount = ui->cruzarTabla->rowCount();
         int i=0;
          while(i<rowcount){
             QTableWidgetItem* item = ui->cruzarTabla->item(i,ui->cruzarTabla->columnCount()-1);
             if(item==NULL){
                 ui->cruzarTabla->removeRow(i);
                 rowcount--;
             }else{
                 i++;
            }//fin del else
          }//fin del while
}

void MainWindow::on_actionListar_Registros_triggered()
{
    qDebug() << "entro al metodo listar";
    ui->panelRegistros->setVisible(true);

    listaCamposAbiertos.clear();
    ui->tablaRegistros->setEditTriggers(false);
    for(int i=ui->tablaRegistros->rowCount()-1;i>=0;i--)
        ui->tablaRegistros->removeRow(i);
    for(int i=ui->tablaRegistros->columnCount();i>=0;i--)
        ui->tablaRegistros->removeColumn(i);
    QFile file (ui->comboBoxArchivosRegistros->currentText());
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString line;
    while (!in.atEnd()) {
        line = in.readLine();
        if(line=="|")
            break;
        QStringList divisiones = line.split(" ");
        bool lla =false;
        if(divisiones[3]=="Sí")
            lla=true;
        listaCamposAbiertos.append(Campo(divisiones[0],divisiones[1],divisiones[2].toInt(),lla));
    }//fin del while
    for(int i=0;i<listaCamposAbiertos.count();i++){
        ui->tablaRegistros->insertColumn(i);
        if(listaCamposAbiertos[i].getNombreCampo().length()>listaCamposAbiertos[i].getTamanoCampo())
            ui->tablaRegistros->setColumnWidth(i,listaCamposAbiertos[i].getNombreCampo().length()*10);
        else
            ui->tablaRegistros->setColumnWidth(i,listaCamposAbiertos[i].getTamanoCampo()*20);
            ui->tablaRegistros->setHorizontalHeaderItem(i,new QTableWidgetItem(listaCamposAbiertos[i].getNombreCampo()));
    }//fin del for
    bool empezar = false;
    while (!in.atEnd()) {
        line = in.readLine();
        if(empezar){
            if(line[0]!='*'){
                int rowc = ui->tablaRegistros->rowCount();
                int camino=0;
                ui->tablaRegistros->insertRow(rowc);
                for(int o=0;o<listaCamposAbiertos.count();o++){
                    ui->tablaRegistros->setItem(rowc,o,new QTableWidgetItem(line.mid(camino,listaCamposAbiertos[o].getTamanoCampo())));
                    camino+=listaCamposAbiertos[o].getTamanoCampo();
                }//fin del for
            }
        }
        if(line=="$")
           empezar = true;
    }
    file.close();
}
