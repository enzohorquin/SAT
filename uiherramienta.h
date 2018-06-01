#ifndef UIHERRAMIENTA_H
#define UIHERRAMIENTA_H

#include <QMainWindow>
#include <QDebug>
#include "mainwindow.h"
#include "davisputnam.h"
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <ctype.h>

namespace Ui {
class UIHerramienta;
}

class UIHerramienta : public QMainWindow
{
    Q_OBJECT

public:
    explicit UIHerramienta(QWidget *parent = 0);
    ~UIHerramienta();

private slots:

    void on_botonCargar_clicked();

    void on_botonResolver_clicked();

    void on_botonNegacion_clicked();

    void on_botonBorrar_clicked();

    void on_botonVaciar_clicked();

    void on_actionGuardar_Archivo_triggered();

    void on_actionAbrir_Archivo_triggered();

    void on_actionQue_es_DPLL_triggered();

    void on_actionAtras_triggered();

    void on_actionAtrasInfo_triggered();

    void on_botonValuaciones_clicked();

private:
    Ui::UIHerramienta *ui;
    ConjuntoClausulas conjunto;
    void cargarClausula(const QString & t, Clausula & c);
    void CargaClausulasArchivo(QString mText);
    bool clausulaCorrecta(Clausula clausula);
};

#endif // UIHERRAMIENTA_H
