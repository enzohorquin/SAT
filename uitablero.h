#ifndef UITABLERO_H
#define UITABLERO_H

#include <QMainWindow>
#include <list>
#include "mainwindow.h"

namespace Ui {
class UITablero;
}

class UITablero : public QMainWindow
{
    Q_OBJECT

public:
    explicit UITablero(const list<list<QString> > &valuaciones, QWidget *parent = 0);
    ~UITablero();

private slots:
    void on_pushSiguiente_clicked();

    void on_actionAtras_triggered();

private:
    Ui::UITablero *ui;
    void mostrarValuacion() const;
    void mostrarTablero();
    void crearItems();
    list<list<QString> > valuaciones;
    list<QGraphicsPixmapItem*> items;
    list<list<QString> >::const_iterator it;
    int cantvaluaciones;
    int lado;
    int cantvariables;
    QGraphicsScene * escena;
};

#endif // UITABLERO_H
