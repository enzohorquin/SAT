#ifndef UICOLOREOGRAFO_H
#define UICOLOREOGRAFO_H
#include "grafo.h"
#include "grafo.cpp"
#include <QMainWindow>
#include <QDebug>
#include "mainwindow.h"
#include "davisputnam.h"
#include "conjuntoclausulas.h"
#include "qdebug.h"
#include "qmessagebox.h"
#include <QtCore>
#include <QtGui>
#include "interfazgrafo.h"

namespace Ui {
class UIColoreoGrafo;
}

class UIColoreoGrafo : public QMainWindow
{
    Q_OBJECT

public:
    explicit UIColoreoGrafo(QWidget *parent = 0);
    ~UIColoreoGrafo();


private slots:


    void on_CargarArco_clicked();

    void on_BorraTodo_clicked();

    void on_Resolver_clicked();

    void on_CargarVertice_clicked();

    void on_borrarVertice_clicked();

    void on_borrarUltimoArco_clicked();

    void on_action_Que_es_un_Grafo_triggered();

    void on_actionNuevo_triggered();

    void on_actionAtras_triggered();

    void on_actionProblema_del_Coloreo_de_un_Grafo_triggered();

    void on_pushButtonVerGrafo_clicked();

    void on_pushButtonVerVal_clicked();

    void on_botonGrafos_clicked();

    void on_actionVerFormalizacion_triggered();

private:
    Ui::UIColoreoGrafo *ui;
    ConjuntoClausulas conjunto;
    Grafo<int> G;
    int cont;
    list<QPair<int,int> > ListaArcos ;
    void GeneraConjuntoClausulas(Grafo<int> & G, ConjuntoClausulas  & conjunto);
    void GeneraConjuntoCondicion1(Grafo<int> &  G, ConjuntoClausulas & conjunto);
    void GeneraConjuntoCondicion2(ConjuntoClausulas Conj, ConjuntoClausulas &  Resultado );
    void GeneraConjuntoCondicion3(Grafo<int> &  G, ConjuntoClausulas & Resultado);
    void Borra(int vertice);
    void BorraTextBrowser(int vertice);
    bool arcoCorrecto(QString & texto, int &origen, int &destino);
};

#endif // UICOLOREOGRAFO_H
