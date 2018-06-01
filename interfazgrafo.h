#ifndef INTERFAZGRAFO_H
#define INTERFAZGRAFO_H

#include <QMainWindow>
#include <QGraphicsView>
#include <uicoloreografo.h>
#include <list>
#include "conjuntoclausulas.h"
#include <QGraphicsItem>
#include <vector>

namespace Ui {
class InterfazGrafo;
}

class InterfazGrafo : public QMainWindow
{
    Q_OBJECT

public:
    explicit InterfazGrafo(list<QPair<int,int> > ListaArcos, list<list<QString> > ListaValuaciones, QWidget *parent = 0);
    ~InterfazGrafo();
    void crearNodo(QString color);
    void crearArco(int primerNodo, int segundoNodo);
    void CreaEjemplo();
    list<vector<QString> > get_ValuacionesOrdenadas(list<list<QString> > valuaciones);
private slots:
    void on_actionAtras_triggered();

    void on_pushButtonSiguiente_clicked();

private:
    Ui::InterfazGrafo *ui;
    int nroNodo;
    QPair<int,int> pos;
    QGraphicsScene * scene;
    QGraphicsEllipseItem * nodo;
    QGraphicsTextItem * text;
    QPair<int,int> * arrNodos;
    int CantNodos;
    list<vector<QString> >  :: iterator ite ;
    list<QPair<int,int> > ListaA ;
    list<vector<QString> > ListaVal;
    void Crea();

    int RetornaVertice(const QString C) const;
    void InsertaOrd(vector<QString>  & A, QString C, int i , int cont, int size);

};

#endif // INTERFAZGRAFO_H
