#ifndef UINREINAS_H
#define UINREINAS_H

#include <QMainWindow>
#include <QDebug>
#include "mainwindow.h"
#include "davisputnam.h"
#include <set>

namespace Ui {
class UINReinas;
}

class UINReinas : public QMainWindow
{
    Q_OBJECT

public:
    explicit UINReinas(QWidget *parent = 0);
    ~UINReinas();

private slots:
    void on_pushResolver_clicked();

    void on_pushFijarReina_clicked();

    void on_actionAtras_triggered();

    void on_action_Que_es_esto_triggered();

    void on_actionNuevo_triggered();

    void on_pushButtonN_clicked();

    void on_actionExplicaci_n_triggered();

    void on_pushValuaciones_clicked();

    void on_pushTableros_clicked();

private:
    void cargarConjunto();
    void cargarColumna (Clausula & clausula, Literal & l1, string & fila, string & columna);
    void cargarFila (Clausula & clausula, Literal & l1, string & fila, string & columna);
    void cargarDiagonal (Clausula & clausula, Literal l1, int & diagonal, int & i, int & j);
    bool existe_Coordenada(QString texto) const;
    bool hay_Error(QString  texto);
    set<Clausula> reinasfijas;
    ConjuntoClausulas C;
    int n;
    Ui::UINReinas *ui;
};

#endif // UINREINAS_H
