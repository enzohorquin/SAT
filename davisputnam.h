#ifndef DAVISPUTNAM_H
#define DAVISPUTNAM_H

#include <QMainWindow>
#include "conjuntoclausulas.h"
#include "uiherramienta.h"
#include "uicoloreografo.h"
#include "uinreinas.h"
#include <vector>

namespace Ui {
class DavisPutnam;
}

class DavisPutnam : public QMainWindow
{
    Q_OBJECT

public:
    explicit DavisPutnam(const ConjuntoClausulas & conjunto, const char &opcion, QWidget *parent = 0);
    bool resolver();
    void mostrar_Valuaciones() const;
    void generar_Valuaciones();
    void set_VarFijas(const set<Clausula> &varFijas);
    list<list<QString> > get_Valuaciones() const;
    ~DavisPutnam();
    bool ExisteValuacion();

private slots:

    void on_actionAtras_triggered();

private:
    Ui::DavisPutnam *ui;
    void mostrarConjunto(ConjuntoClausulas conjunto) const;
    void eliminacionUnitariaVarFijas(ConjuntoClausulas &conjunto);
    bool resolver(ConjuntoClausulas conjunto);
    void generar_Valuaciones(ConjuntoClausulas conjunto, list<QString> valparcial, set<QString> variables,unsigned int cantliterales);
    void completar_Valuaciones(list<QString> valparcial, set<QString> variables);
    void agregar_Valuacion (list<QString> &valparcial, QString & l);
    void eliminacionUnitariaSucesiva(ConjuntoClausulas & conjunto, list<QString> & valparcial, set<QString> & variables);
    char opcionElegida;
    set<Clausula> variablesfijas;
    ConjuntoClausulas conjClausulas;
    list<list<QString> > valuaciones;


};

#endif // DAVISPUTNAM_H
