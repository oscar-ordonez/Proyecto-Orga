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
    ui->panelCampos->setEnabled(true);
    ui->panelModificar->setEnabled(false);
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

    qDebug() << "Click en crear registros\nCargando Archivos a comboBox";
    numHead = 0;
    numEOSE = 0;
    ifstream archivo("./Archivos/todosArchivos.ncr");
    while(archivo.good()){
        string dato;
        archivo >> dato;
        QString m = QString::fromStdString(dato);
        qDebug() << "archivo lee:" + QString::fromStdString(dato) + "\n Tamaño:" + QString::fromStdString(dato).length();
        if(QString::fromStdString(dato).contains(" ")){
            m = QString::fromStdString(dato).replace(" ","_");
        }
        qDebug() << m;
        ui->comboBoxArchivosRegistros->addItem(QString::fromStdString(dato));
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
    fileArchivo.close();
    fileIndice.close();

    ui->labelRegistoNumero->setText("N/A");
    ui->labelRegistoNombre->setText("N/A");
    ui->labelRegistoTipo->setText("N/A");
    ui->labelRegistoTamano->setText("N/A");
    ui->labelRegistoLlave->setText("N/A");

    listaLlaves.clear();
    listaCamposAbiertos.clear();

    numHead = 0;
    numEOSE = 0;
    numCampoLlave = -1;
    numOSH = 0;

    fileArchivo.setFileName(ui->comboBoxArchivosRegistros->currentText());
    if(!fileArchivo.open(QIODevice::ReadWrite | QIODevice::Text)){
        return;
    }

    QTextStream textStream (&fileArchivo);
    QString linea;
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
        ui->labelEsLlave->setText("Si");
    else
        ui->labelEsLlave->setText("No");

    QString mask;
    if(listaCamposAbiertos[0].getTipoCampo() == "INTF"){
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

void MainWindow::on_modificarCampo_clicked()
{
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
    listaCampos.removeAt(ui->comboBoxModificarCampo->currentIndex());
    ui->panelModificar->setEnabled(false);
}

void MainWindow::on_comboBoxModificarCampo_activated(const QString &arg1)//accion no se usa
{

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
    /*//si no hay campos o no hay registros entonces no se crea el archivo
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
    }*/
}
void MainWindow::exportJson() {
    /*//verifica si existen campos y registros
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
    }*/
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
