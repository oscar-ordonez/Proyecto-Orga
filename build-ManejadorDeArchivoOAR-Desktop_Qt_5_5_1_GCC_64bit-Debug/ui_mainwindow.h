/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNuevo_Archivo;
    QAction *actionSalvar_Archivo;
    QAction *actionCerrar_Archivo;
    QAction *actionSalir;
    QAction *actionCrear_Campos;
    QAction *actionListar_Campos;
    QAction *actionModificar_Campos;
    QAction *actionBorrar_Campos;
    QAction *actionIntroducir_Registros;
    QAction *actionModificar_Registros;
    QAction *actionBuscar_Registros;
    QAction *actionBorrar_Registros;
    QAction *actionListar_Registros;
    QAction *actionCrear_Indices;
    QAction *actionRe_Indexar_Archivos;
    QAction *actionExportar_Excel;
    QAction *actionExportar_XML_con_Schema;
    QAction *actionExportar_JSON;
    QWidget *centralWidget;
    QFrame *panelCampos;
    QTableWidget *tablaCampos;
    QPushButton *abrirArchivo;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *nombreCampo;
    QComboBox *comboBoxTipoCampo;
    QLabel *label_3;
    QSpinBox *tamanoCampo;
    QPushButton *crearCampo;
    QPushButton *pushButton;
    QLabel *label_4;
    QMenuBar *menuBar;
    QMenu *menuEstandarizacion;
    QMenu *menuIndices;
    QMenu *menuRegistros;
    QMenu *menuCampos;
    QMenu *menuArchivo;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(779, 526);
        actionNuevo_Archivo = new QAction(MainWindow);
        actionNuevo_Archivo->setObjectName(QStringLiteral("actionNuevo_Archivo"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Imagenes/new Page.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNuevo_Archivo->setIcon(icon);
        actionSalvar_Archivo = new QAction(MainWindow);
        actionSalvar_Archivo->setObjectName(QStringLiteral("actionSalvar_Archivo"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Imagenes/guardar.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSalvar_Archivo->setIcon(icon1);
        actionCerrar_Archivo = new QAction(MainWindow);
        actionCerrar_Archivo->setObjectName(QStringLiteral("actionCerrar_Archivo"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Imagenes/cerrar.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCerrar_Archivo->setIcon(icon2);
        actionSalir = new QAction(MainWindow);
        actionSalir->setObjectName(QStringLiteral("actionSalir"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Imagenes/salir.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSalir->setIcon(icon3);
        actionCrear_Campos = new QAction(MainWindow);
        actionCrear_Campos->setObjectName(QStringLiteral("actionCrear_Campos"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Imagenes/crear.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCrear_Campos->setIcon(icon4);
        actionListar_Campos = new QAction(MainWindow);
        actionListar_Campos->setObjectName(QStringLiteral("actionListar_Campos"));
        actionModificar_Campos = new QAction(MainWindow);
        actionModificar_Campos->setObjectName(QStringLiteral("actionModificar_Campos"));
        actionBorrar_Campos = new QAction(MainWindow);
        actionBorrar_Campos->setObjectName(QStringLiteral("actionBorrar_Campos"));
        actionIntroducir_Registros = new QAction(MainWindow);
        actionIntroducir_Registros->setObjectName(QStringLiteral("actionIntroducir_Registros"));
        actionModificar_Registros = new QAction(MainWindow);
        actionModificar_Registros->setObjectName(QStringLiteral("actionModificar_Registros"));
        actionBuscar_Registros = new QAction(MainWindow);
        actionBuscar_Registros->setObjectName(QStringLiteral("actionBuscar_Registros"));
        actionBorrar_Registros = new QAction(MainWindow);
        actionBorrar_Registros->setObjectName(QStringLiteral("actionBorrar_Registros"));
        actionListar_Registros = new QAction(MainWindow);
        actionListar_Registros->setObjectName(QStringLiteral("actionListar_Registros"));
        actionCrear_Indices = new QAction(MainWindow);
        actionCrear_Indices->setObjectName(QStringLiteral("actionCrear_Indices"));
        actionRe_Indexar_Archivos = new QAction(MainWindow);
        actionRe_Indexar_Archivos->setObjectName(QStringLiteral("actionRe_Indexar_Archivos"));
        actionExportar_Excel = new QAction(MainWindow);
        actionExportar_Excel->setObjectName(QStringLiteral("actionExportar_Excel"));
        actionExportar_XML_con_Schema = new QAction(MainWindow);
        actionExportar_XML_con_Schema->setObjectName(QStringLiteral("actionExportar_XML_con_Schema"));
        actionExportar_JSON = new QAction(MainWindow);
        actionExportar_JSON->setObjectName(QStringLiteral("actionExportar_JSON"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        panelCampos = new QFrame(centralWidget);
        panelCampos->setObjectName(QStringLiteral("panelCampos"));
        panelCampos->setGeometry(QRect(30, 20, 741, 351));
        panelCampos->setFrameShape(QFrame::StyledPanel);
        panelCampos->setFrameShadow(QFrame::Raised);
        tablaCampos = new QTableWidget(panelCampos);
        tablaCampos->setObjectName(QStringLiteral("tablaCampos"));
        tablaCampos->setGeometry(QRect(20, 40, 661, 231));
        abrirArchivo = new QPushButton(panelCampos);
        abrirArchivo->setObjectName(QStringLiteral("abrirArchivo"));
        abrirArchivo->setGeometry(QRect(20, 10, 111, 27));
        label = new QLabel(panelCampos);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 280, 141, 17));
        label_2 = new QLabel(panelCampos);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 310, 111, 17));
        nombreCampo = new QLineEdit(panelCampos);
        nombreCampo->setObjectName(QStringLiteral("nombreCampo"));
        nombreCampo->setGeometry(QRect(160, 280, 121, 27));
        comboBoxTipoCampo = new QComboBox(panelCampos);
        comboBoxTipoCampo->setObjectName(QStringLiteral("comboBoxTipoCampo"));
        comboBoxTipoCampo->setGeometry(QRect(160, 310, 121, 27));
        label_3 = new QLabel(panelCampos);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(290, 280, 141, 17));
        tamanoCampo = new QSpinBox(panelCampos);
        tamanoCampo->setObjectName(QStringLiteral("tamanoCampo"));
        tamanoCampo->setGeometry(QRect(440, 280, 91, 27));
        crearCampo = new QPushButton(panelCampos);
        crearCampo->setObjectName(QStringLiteral("crearCampo"));
        crearCampo->setGeometry(QRect(290, 310, 241, 27));
        pushButton = new QPushButton(panelCampos);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(700, 100, 31, 27));
        label_4 = new QLabel(panelCampos);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(690, 80, 41, 17));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 779, 25));
        menuEstandarizacion = new QMenu(menuBar);
        menuEstandarizacion->setObjectName(QStringLiteral("menuEstandarizacion"));
        menuIndices = new QMenu(menuBar);
        menuIndices->setObjectName(QStringLiteral("menuIndices"));
        menuRegistros = new QMenu(menuBar);
        menuRegistros->setObjectName(QStringLiteral("menuRegistros"));
        menuCampos = new QMenu(menuBar);
        menuCampos->setObjectName(QStringLiteral("menuCampos"));
        menuArchivo = new QMenu(menuBar);
        menuArchivo->setObjectName(QStringLiteral("menuArchivo"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuArchivo->menuAction());
        menuBar->addAction(menuCampos->menuAction());
        menuBar->addAction(menuRegistros->menuAction());
        menuBar->addAction(menuIndices->menuAction());
        menuBar->addAction(menuEstandarizacion->menuAction());
        menuEstandarizacion->addAction(actionExportar_Excel);
        menuEstandarizacion->addAction(actionExportar_XML_con_Schema);
        menuEstandarizacion->addAction(actionExportar_JSON);
        menuIndices->addAction(actionCrear_Indices);
        menuIndices->addAction(actionRe_Indexar_Archivos);
        menuRegistros->addAction(actionIntroducir_Registros);
        menuRegistros->addAction(actionModificar_Registros);
        menuRegistros->addAction(actionBuscar_Registros);
        menuRegistros->addAction(actionBorrar_Registros);
        menuRegistros->addAction(actionListar_Registros);
        menuCampos->addAction(actionCrear_Campos);
        menuCampos->addAction(actionListar_Campos);
        menuCampos->addAction(actionModificar_Campos);
        menuCampos->addAction(actionBorrar_Campos);
        menuArchivo->addAction(actionNuevo_Archivo);
        menuArchivo->addAction(actionSalvar_Archivo);
        menuArchivo->addAction(actionCerrar_Archivo);
        menuArchivo->addAction(actionSalir);
        mainToolBar->addAction(actionNuevo_Archivo);
        mainToolBar->addAction(actionSalvar_Archivo);
        mainToolBar->addAction(actionCerrar_Archivo);
        mainToolBar->addAction(actionSalir);
        mainToolBar->addAction(actionCrear_Campos);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionNuevo_Archivo->setText(QApplication::translate("MainWindow", "Nuevo Archivo", 0));
        actionSalvar_Archivo->setText(QApplication::translate("MainWindow", "Salvar Archivo", 0));
        actionCerrar_Archivo->setText(QApplication::translate("MainWindow", "Cerrar Archivo", 0));
        actionSalir->setText(QApplication::translate("MainWindow", "Salir", 0));
        actionCrear_Campos->setText(QApplication::translate("MainWindow", "Crear Campos", 0));
        actionListar_Campos->setText(QApplication::translate("MainWindow", "Listar Campos", 0));
        actionModificar_Campos->setText(QApplication::translate("MainWindow", "Modificar Campos", 0));
        actionBorrar_Campos->setText(QApplication::translate("MainWindow", "Borrar Campos", 0));
        actionIntroducir_Registros->setText(QApplication::translate("MainWindow", "Introducir Registros", 0));
        actionModificar_Registros->setText(QApplication::translate("MainWindow", "Modificar Registros", 0));
        actionBuscar_Registros->setText(QApplication::translate("MainWindow", "Buscar Registros", 0));
        actionBorrar_Registros->setText(QApplication::translate("MainWindow", "Borrar Registros", 0));
        actionListar_Registros->setText(QApplication::translate("MainWindow", "Listar Registros", 0));
        actionCrear_Indices->setText(QApplication::translate("MainWindow", "Crear Indices", 0));
        actionRe_Indexar_Archivos->setText(QApplication::translate("MainWindow", "Re Indexar Archivos", 0));
        actionExportar_Excel->setText(QApplication::translate("MainWindow", "Exportar Excel", 0));
        actionExportar_XML_con_Schema->setText(QApplication::translate("MainWindow", "Exportar XML con Schema", 0));
        actionExportar_JSON->setText(QApplication::translate("MainWindow", "Exportar JSON", 0));
        abrirArchivo->setText(QApplication::translate("MainWindow", "Abrir archivo", 0));
        label->setText(QApplication::translate("MainWindow", "Nombre del Campo:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Tipo de Campo:", 0));
        comboBoxTipoCampo->clear();
        comboBoxTipoCampo->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "CHAR", 0)
         << QApplication::translate("MainWindow", "INTF", 0)
         << QApplication::translate("MainWindow", "DEC", 0)
        );
        label_3->setText(QApplication::translate("MainWindow", "Tama\303\261o del Campo:", 0));
        crearCampo->setText(QApplication::translate("MainWindow", "Crear Campo", 0));
        pushButton->setText(QApplication::translate("MainWindow", "+", 0));
        label_4->setText(QApplication::translate("MainWindow", "Rows:", 0));
        menuEstandarizacion->setTitle(QApplication::translate("MainWindow", "Estandarizacion", 0));
        menuIndices->setTitle(QApplication::translate("MainWindow", "Indices", 0));
        menuRegistros->setTitle(QApplication::translate("MainWindow", "Registros", 0));
        menuCampos->setTitle(QApplication::translate("MainWindow", "Campos", 0));
        menuArchivo->setTitle(QApplication::translate("MainWindow", "Archivo", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
